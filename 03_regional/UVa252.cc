// UVa252 - Trucking
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>

using namespace std;
const int maxn = 100 + 4, maxd = 16;
#define _for(i,a,b) for(int i=a; i<(b); ++i)
#define _forit(it,c) for((c)::iterator it = (c).begin(); it!=(c).end(); ++it)
struct ICPC;
struct Shipment { // origin and next relay center numbers, the volume of the shipment v as a percentage of trailer volume
	int id, origin, next, v, t; // time t taken to travel from center c to destination r measured in minutes    
};
typedef vector<Shipment> SMVec;

struct Trailer{
	int a, c, s, maxt; //  a is the trailer's arrival time, c - center number, s is the number of shipments in the trailer    
	Shipment SMs[maxd];
	bool relay;
	bool operator<(const Trailer& rhs) const {
		assert(c == rhs.c);
		if (relay && rhs.relay) {
			if (maxt == rhs.maxt) return a > rhs.a;
			return maxt < rhs.maxt;
		}
		if (relay) return false;
		if (rhs.relay) return true;
		return a > rhs.a;
	}
};

struct RelayDoor {
	//  r is the relay door's number, v is the total volume of shipments to that center
	int r, vol, l, sentV; // l is the latest acceptable time for shipments to arrive at center r, expressed as minutes since the start of the day
	SMVec SMs;
	void relay(int time, vector<Shipment>& lateSMs) {
		vector<Shipment> trailer;
		int v = 0;

		for(auto& sm : SMs){
			Shipment nsm = sm;
			assert(sm.next = r); assert(v <= 100);
			trailer.push_back(sm);
			if (v + sm.v >= 100) { nsm.v = v + sm.v - 100; trailer.back().v -= nsm.v; }
			else nsm.v = 0;
			v += trailer.back().v;
			if (v < 100) { assert(!nsm.v); continue; }
			assert(v == 100);

			for(auto ti : trailer){
				if (ti.t + time > l) lateSMs.push_back(ti);
				vol -= ti.v;
			}

			trailer.clear();
			v = nsm.v;
			if (nsm.v) trailer.push_back(nsm);
		}

		SMs.clear();
		if (trailer.empty()) return;

		assert(v < 100);
		if (v == vol) {
			for(auto& ti : trailer) {
				if (ti.t + time > l) lateSMs.push_back(ti);
				vol -= ti.v;
			}
		}
		else{
			SMs.assign(trailer.begin(), trailer.end());
		}
	}
};

enum EventType{ tlArrived = 0, rdFree = 1, smStripped = 2 };
struct Event {
	EventType type;
	int time, sDoor;
	bool operator<(const Event& e2) const {
		if (time != e2.time) return time > e2.time;
		if (type != e2.type) return type < e2.type;
		return false;
	}
	Trailer* pT;
	ICPC* pC;
	Shipment sm;
	Event(EventType t, int a) : type(t), time(a), pT(NULL), pC(NULL){}
};
priority_queue<Event> events;

struct ICPC{ // s is the number of stripping doors, d is the number of relay doors
	int c, s, d;
	bool stripUsed[maxd];
	vector<int> waitingTime;
	vector<Shipment> lateSMs;
	RelayDoor RDs[maxd];
	priority_queue<Trailer> trailerQ;

	void strip(const Trailer& t, int time, int sDoor) { // 卸货
		stripUsed[sDoor] = true;
		assert(sDoor >= 0 && sDoor < s);
		Event e(rdFree, time + 120); e.pC = this; e.sDoor = sDoor;// 2小时后这个门就可以用了。
		events.push(e);

		if (t.a != time) {
			assert(t.a < time);
			waitingTime.push_back(time - t.a);
		}

		_for(i, 0, (int)(t.s)) {
			const Shipment& sm = t.SMs[i];
			if (c == sm.next) continue;
			Event e(smStripped, time + 120);
			e.pC = this;
			e.sm = sm;
			events.push(e);
		}
	}

	void stripAll(int time) {
		_for(si, 0, s) {
			if (stripUsed[si]) continue;
			if (trailerQ.empty()) break;
			strip(trailerQ.top(), time, si);
			trailerQ.pop();
		}
	}

	void relayAll(int time) {
		_for(i, 0, d) RDs[i].relay(time, lateSMs);
	}

	RelayDoor& findRelayDoor(const Shipment& s) {
		int ri = -1;
		_for(i, 0, d) if (s.next == RDs[i].r) { ri = i; break; }
		assert(ri >= 0);
		return RDs[ri];
	}
};

istream& operator>>(istream& is, ICPC& ic){
	is >> ic.c >> ic.s >> ic.d;
	_for(i, 0, ic.d) {
		RelayDoor& rd = ic.RDs[i];
		is >> rd.r >> rd.vol >> rd.l;
		fill_n(ic.stripUsed, maxd, false);
		rd.sentV = 0;
	}
	return is;
}

istream& operator>>(istream& is, Trailer& r){
	is >> r.a >> r.c >> r.s;
	r.relay = false;
	r.maxt = -1;
	_for(i, 0, r.s) {
		Shipment& sm = r.SMs[i];
		is >> sm.id >> sm.origin >> sm.next >> sm.v >> sm.t;
		r.maxt = max(r.maxt, sm.t);
		if (sm.next != r.c) r.relay = true;
	}
	return is;
}

int n, m;
ICPC centers[maxn], *pcS[maxn];
Trailer recs[maxn];

void procEvent(const Event& e) {
	int time = e.time;
	if (e.type == tlArrived) {
		pcS[e.pT->c]->trailerQ.push(*e.pT);
		return;
	}

	if (e.type == rdFree) {
		assert(e.pC);
		e.pC->stripUsed[e.sDoor] = false;
		return;
	}

	if (e.type == smStripped) {
		assert(e.pC);
		RelayDoor& rd = e.pC->findRelayDoor(e.sm);
		rd.SMs.push_back(e.sm);
	}
}

int main(){
	while (cin >> n && n) {
		memset(pcS, 0, sizeof(pcS));
		_for(i, 0, n) {
			ICPC& ic = centers[i]; cin >> ic; pcS[ic.c] = &(ic);
		}
		cin >> m;
		_for(i, 0, m) {
			Trailer& t = recs[i];
			cin >> t;
			Event e(tlArrived, t.a); e.pT = &(t); e.pC = pcS[t.c];
			events.push(e);
		}

		while (!events.empty()) {
			int time = events.top().time;
			while (!events.empty() && events.top().time == time) {
				procEvent(events.top());
				events.pop();
			}

			_for(i, 0, n) {
				centers[i].stripAll(time); // 卸货 
				centers[i].relayAll(time); // 中转发货
			}
		}

		_for(i, 0, n) {
			ICPC& ic = centers[i];
			if (ic.waitingTime.empty())
				cout << "There is no wait for a stripping door at ICPC " << ic.c << "." << endl;
			else {
				int sum = 0;
				_for(j, 0, ic.waitingTime.size()) sum += ic.waitingTime[j];
				sum *= 10;
				sum /= ic.waitingTime.size();
				cout << "The average wait for a stripping door at ICPC " << ic.c << " is " << sum / 10 << "." << sum % 10 << " minutes." << endl;
			}
		}
		cout << "\nThe late shipments are:\nId Origin Destination Volume" << endl;
		_for(i, 0, n) {
			ICPC& ic = centers[i];
			_for(j, 0, ic.lateSMs.size()) {
				Shipment& s = ic.lateSMs[j];
				cout << setw(2) << s.id << setw(7) << s.origin << setw(12) << s.next << setw(7) << s.v << endl;
			}
		}
        
        // cout<<endl; 
	}

	return 0;
}

// 14643591	252	Trucking	Accepted	C++	0.015	2014-12-08 10:45:42