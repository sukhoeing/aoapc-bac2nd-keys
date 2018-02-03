// Use of Hospital Facilities, ACM/ICPC World Finals 1991, UVa212
// 陈锋
#include<cassert>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<ctime>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<set>
#include<queue>
using namespace std;

enum eventType { opFree = 0, opPre = 1, reFree = 3, rePre = 4 };

struct Room {
    int pat, minutes;
    void init() { pat = -1; minutes = 0; }
};
struct Event {
    int time, id, type;
    Event(int t, int id, int type) : time(t), id(id), type(type) {}
    bool operator<(const Event& e) const { return time > e.time; }
};
struct Patient {
    string name;
    int surgeryTime, recoveryTime, opRoomId, opBeginTime, opEndTime, reRoomId, reBeginTime, reEndTime;
};

priority_queue<Event> em;
int nOp, nRe, T0, tTrans, tPreOp, tPreRe, nPat, allTime;
Room opRooms[10+1], reRooms[30+1];
Patient pats[100+1];
struct patComp {
    bool operator() (int i1, int i2) { 
        const Patient &p1 = pats[i1], &p2 = pats[i2];
        assert(p1.opRoomId != -1 && p2.opRoomId != -1);
        return p1.opRoomId < p2.opRoomId;
    }
};

set<int> opQueue, freeOpRooms, freeReRooms;
set<int, patComp> reQueue;
typedef set<int>::iterator siit;

void writeTime(char* buf, int time) {
    int h = time / 60 + T0, m = time % 60;
    sprintf(buf, "%2d:%02d", h, m);
}

ostream& operator<<(ostream& os, const Patient& p) {
    char buf[16];
    sprintf(buf, "  %-10s%2d   ", p.name.c_str(), p.opRoomId+1); os<<buf;
    writeTime(buf, p.opBeginTime); os<<buf<<"   ";
    writeTime(buf, p.opEndTime); os<<buf;
    sprintf(buf, "%7d", p.reRoomId+1); os<<buf<<"   ";
    writeTime(buf, p.reBeginTime); os<<buf<<"   ";
    writeTime(buf, p.reEndTime); os<<buf;
    return os;
}

ostream& operator<<(ostream& os, const Room& r) {
    double p = r.minutes * 100;
    p /= allTime;
    char buf[64];
    sprintf(buf, "%8d   %5.2lf", r.minutes, p);
    return os<<buf;
}

void solve() {
    int time = em.top().time;    
    while(!em.empty() && em.top().time == time) {
        Event e = em.top();
        em.pop();
		int pid;
        switch(e.type) { // What to do from now
            case opFree:
                assert(!freeOpRooms.count(e.id));
                freeOpRooms.insert(e.id);
                assert(opRooms[e.id].pat == -1);
                break;
            case opPre: // opRoom start pre
                assert(!freeOpRooms.count(e.id));
                pid = opRooms[e.id].pat;
                assert(pid != -1);
                reQueue.insert(pid);
                opRooms[e.id].pat = -1;
                em.push(Event(time + tPreOp, e.id, opFree));
                break;
            case reFree:
                assert(!freeReRooms.count(e.id));
                assert(reRooms[e.id].pat == -1);
				freeReRooms.insert(e.id);
                break;
            case rePre: // reRoom start pre
                assert(!freeReRooms.count(e.id));
                assert(reRooms[e.id].pat != -1);
                reRooms[e.id].pat = -1;
                em.push(Event(time + tPreRe, e.id, reFree));
                break;
            default:
                assert(false);
        }
    }

    int opSz = min(opQueue.size(), freeOpRooms.size());
    for(int i = 0; i < opSz; i++) {
        int pid = *(opQueue.begin());
        opQueue.erase(opQueue.begin());
        int rid = *(freeOpRooms.begin());
        freeOpRooms.erase(freeOpRooms.begin());

        Room& r = opRooms[rid];
        r.pat = pid;
        Patient& p = pats[pid];
        p.opRoomId = rid;
        p.opBeginTime = time;
        p.opEndTime = time + p.surgeryTime;
        r.minutes += p.surgeryTime;
        em.push(Event(p.opEndTime, rid, opPre));
    }

    int reSz = min(reQueue.size(), freeReRooms.size());
    for(int i = 0; i < reSz; i++) {
        int pid = *(reQueue.begin()); reQueue.erase(reQueue.begin());
        int rid = *(freeReRooms.begin()); freeReRooms.erase(freeReRooms.begin());
        Room& r = reRooms[rid];
        r.pat = pid;
        Patient& p = pats[pid];
        p.reRoomId = rid;
        p.reBeginTime = time + tTrans;
        p.reEndTime = p.reBeginTime + p.recoveryTime;
        r.minutes += p.recoveryTime;
        em.push(Event(p.reEndTime, rid, rePre));
        allTime = max(allTime, p.reEndTime);
    }
}

int main()
{
    while(cin>>nOp) {
        assert(opQueue.empty());
        assert(reQueue.empty());
        assert(em.empty());

        freeOpRooms.clear();
        freeReRooms.clear();
        allTime = 0;

        cin>>nRe>>T0>>tTrans>>tPreOp>>tPreRe>>nPat;
        for(int i = 0; i < nOp; i++) {
            em.push(Event(0, i, opFree));
            opRooms[i].init();
        }
        for(int i = 0; i < nRe; i++) {
            em.push(Event(0, i, reFree));
            reRooms[i].init();
        }

        for(int i = 0; i < nPat; i++) {
            Patient& p = pats[i];
            p.opRoomId = -1;
            p.reRoomId = -1;
            cin>>p.name>>p.surgeryTime>>p.recoveryTime;
            opQueue.insert(i);
        }

        while(!em.empty()) {
            solve();
        }
        cout<<" Patient          Operating Room          Recovery Room"<<endl;
        cout<<" #  Name     Room#  Begin   End      Bed#  Begin    End"<<endl;
        cout<<" ------------------------------------------------------"<<endl;
        for(int i = 0; i < nPat; i++) cout<<setw(2)<<i+1<<pats[i]<<endl;
        cout<<endl;
        cout<<"Facility Utilization"<<endl;
        cout<<"Type  # Minutes  % Used"<<endl;
        cout<<"-------------------------"<<endl;
        for(int i = 0; i < nOp; i++) cout<<"Room "<<setw(2)<<i+1<<opRooms[i]<<endl;
        for(int i = 0; i < nRe; i++) cout<<"Bed  "<<setw(2)<<i+1<<reRooms[i]<<endl;
        cout<<endl;
    }
    return 0;
}

// LA: 1499421	5151	Use of Hospital Facilities	Accepted	C++	0.006	2014-07-29 02:06:09