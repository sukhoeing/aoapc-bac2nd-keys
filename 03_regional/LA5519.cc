// LA5519 Department
// 陈锋
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

const int MAXN = 32, MAXX = 12;
int readInt() { int x; cin >> x; return x; };
int readTime(istream& is) {
	int h, m, s; char c; is>>h>>c>>m>>c>>s;
	return h * 3600 + m * 60 + s;
}
enum EventType{ AOutRoom = 0, AOutElev, AReachElev, AReachRoom, ElevNext };
enum AState{ Entry, InRoom, InElev, InRoomQ, InElevQ, InTrans, AExit }; // 人员的当前状态
void writeTime(char* dest, int secs) { sprintf(dest, "%02d:%02d:%02d", secs/3600, (secs%3600)/60, secs%60); }
vector<string> typeStr = { "Out Room", "Out Elev", "Reach Elev", "Reach Room", "Elev get next" };

struct Event {
	EventType type;
	int id, time; // 人员id，时间点(s)
	bool operator<(const Event& e) const { return time > e.time || (time == e.time && id > e.id); }
	Event(int i, int t, EventType et) : id(i), time(t), type(et) {}
	void dbgPrint() const {
		char buf[16];
		writeTime(buf, time);
		printf("Event id : %d %s, time: %s\n", id, typeStr[type].c_str(), buf);
	}
};

priority_queue<Event> tmq;

struct RoomId{
	int floor, room, timeLen;
	RoomId(const string& s) : 
		floor((s[0]-'0')*10 + (s[1]-'0')), room((s[2]-'0') * 10 + (s[3]-'0'))
	{ assert(s.size() == 4); }
};

struct Unit{
	int aid; // 里面的人是谁？
	priority_queue<int, vector<int>, greater<int> > Q; // 门口的等待队列
	Unit() : aid(-1){}    
    void getNextAgent(int time);
};

Unit allRooms[MAXX][MAXX], elev;

struct APlan { // 访问计划
	int nextRoom, lastTime, floor, id;
	char code;
	AState curState;
	vector<RoomId> rooms;
	vector<string> log;
	vector<AState> hisStates;
	bool operator<(const APlan& a) const {
		assert(code != a.code);
		return code < a.code;
	}

	void init(char c, int t) {
		code = c, lastTime = t, floor = 1, curState = Entry, nextRoom = 0; 
		rooms.clear(), log.clear(), hisStates.clear();
	}

	void changeState(AState as, int time) {
		char logBuf[64] = { 0 }, tBuf1[64], tBuf2[64], src[64] = { 0 }, dest[64] ={0};
		writeTime(tBuf1, lastTime);
		writeTime(tBuf2, time);
		if (as == AExit) sprintf(logBuf, "%s %s %s", tBuf1, tBuf2, "Exit");
		else {
			AState ls = Entry;
			switch (curState)
			{
			case Entry:
				sprintf(logBuf, "%s %s %s", tBuf1, tBuf2, "Entry");
				break;
			case InRoom:
				sprintf(logBuf, "%s %s Stay in room %02d%02d", tBuf1, tBuf2, rooms[nextRoom].floor, rooms[nextRoom].room);
				break;
			case InElev:
				sprintf(logBuf, "%s %s %s", tBuf1, tBuf2, "Stay in elevator");
				break;
			case InRoomQ:
				sprintf(logBuf, "%s %s Waiting in front of room %02d%02d", tBuf1, tBuf2, rooms[nextRoom].floor, rooms[nextRoom].room);
				break;
			case InElevQ:
				sprintf(logBuf, "%s %s %s", tBuf1, tBuf2, "Waiting in elevator queue");
				break;
			case InTrans:
				assert(!hisStates.empty());
				ls = hisStates.back();
				if (ls == InElev)
					sprintf(src, "elevator");
				else {
					assert(ls == InRoom);
					sprintf(src, "room %02d%02d", rooms[nextRoom - 1].floor, rooms[nextRoom - 1].room);
				};

				if (as == InElev || as == InElevQ)
					sprintf(dest, "elevator");
				else {
					assert(as == InRoom || as == InRoomQ);
					sprintf(dest, "room %02d%02d", rooms[nextRoom].floor, rooms[nextRoom].room);
				}

				sprintf(logBuf, "%s %s Transfer from %s to %s", tBuf1, tBuf2, src, dest);
				break;
			default:
				break;
			}
		}
        
        assert(logBuf[0]);
		if (logBuf[0]) log.push_back(logBuf);
		hisStates.push_back(curState);
		curState = as;
		lastTime = time;
	}
	
    const RoomId* nextRoomP() const { return (nextRoom < rooms.size()) ? &(rooms[nextRoom]) : NULL; }
    int nextFloor() { return nextRoom < rooms.size() ? rooms[nextRoom].floor : 1; }
    void gotoFloor(int floor, int time) {
        assert(this->floor != floor);
        tmq.push(Event(id, time + (curState == Entry ? 30 : 10), AReachElev));
    }

    void gotoNextRoom(int time) {
        if (nextRoom < rooms.size()) {
            RoomId& ri = rooms[nextRoom];
            if (ri.floor == floor) tmq.push(Event(id, time + (curState == Entry ? 30 : 10), AReachRoom));
            else gotoFloor(ri.floor, time);
            return;
        }

        if (floor != 1) gotoFloor(1, time);
        else changeState(AExit, time + 30);
    }
    
    void OnRoomOut(int time) {
        RoomId& ri = rooms[nextRoom];
		Unit& r = allRooms[ri.floor][ri.room];
		r.aid = -1;
		changeState(InTrans, time);
		r.getNextAgent(time);
		nextRoom++;
        gotoNextRoom(time);
    }
    
    void OnElevOut(int time) {
		changeState(InTrans, time);
		if (nextRoom < rooms.size()) floor = rooms[nextRoom].floor;
		else floor = 1;
		gotoNextRoom(time);
    }
    
    void OnReachElev(int time) {
        int sec = time % 60;
        if (sec % 5) {
			changeState(InElevQ, time);
			elev.Q.push(id);
			tmq.push(Event(0, time + 5 - sec % 5, ElevNext));
            return;
		}
        
        if (elev.aid != -1) {
            changeState(InElevQ, time);
            elev.Q.push(id);
        }
        else {
            changeState(InElev, time);
            elev.aid = id;
            tmq.push(Event(id, time + 30 * abs(floor - nextFloor()), AOutElev));
            tmq.push(Event(0, time + 5, ElevNext));
        }
    }
    
    void OnReachRoom(int time) {
        assert(nextRoom < rooms.size());
        const RoomId& ri = rooms[nextRoom];
        Unit& r = allRooms[ri.floor][ri.room];
		if (r.aid != -1) {
			changeState(InRoomQ, time);
			r.Q.push(id);
		}
		else {
			changeState(InRoom, time);
			r.aid = id;
			tmq.push(Event(id, time + ri.timeLen, AOutRoom));
		}    
    }
};

APlan plan[MAXN];
int n;

void procEvent(const Event& e) {
	switch (e.type) {
	case AOutRoom:
        plan[e.id].OnRoomOut(e.time);
		break;
	case AOutElev:
        plan[e.id].OnElevOut(e.time);
		break;
	case AReachElev:
        plan[e.id].OnReachElev(e.time);
		break;
	case AReachRoom:
        plan[e.id].OnReachRoom(e.time);
		break;
	case ElevNext:
		elev.aid = -1;
		if (!elev.Q.empty()) {
			int nAid = elev.Q.top(); elev.Q.pop();
            APlan& ap = plan[elev.aid = nAid];
			ap.changeState(InElev, e.time);
			tmq.push(Event(nAid, e.time + 30 * abs(ap.floor - ap.nextFloor()), AOutElev));
			tmq.push(Event(0, e.time + 5, ElevNext));
		}

		break;
	default:
		assert(false);
	}
}

void Unit::getNextAgent(int time) {
    if (Q.empty()) return;
    int id = Q.top(); Q.pop();
    APlan& ap = plan[id];
    tmq.push(Event(aid = id, time + ap.rooms[ap.nextRoom].timeLen, AOutRoom));
    ap.changeState(InRoom, time);
}

int main(){
	char c; string s; int t;
	n = 0;
	while (cin>>c && c != '.') {
		t = readTime(cin);
		APlan& v = plan[n++]; v.init(c, t);
		while (cin>>s && s != "0") {
			v.rooms.emplace_back(s);
			v.rooms.back().timeLen = readInt();
		}
	}

	sort(plan, plan + n);
	_for(i, 0, n){
        plan[i].id = i;
        plan[i].gotoNextRoom(plan[i].lastTime);
    }

	while (!tmq.empty()) procEvent(tmq.top()), tmq.pop();
	_for(i, 0, n){
		APlan& ap = plan[i];
		cout << ap.code << endl;
		for(const auto& l : ap.log) cout<<l<< endl;
		cout << endl;
	}
	return 0;
}
// 1566745	5519	Department	Accepted	C++	0.003	2014-10-06 03:19:17