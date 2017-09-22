// Queue and A, ACM/ICPC World Finals 2000, UVa822
// 陈锋
#include <cassert>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int maxn = 20 + 1, maxm = 8;

struct Event {
    int time, id;
    bool isRorC; // is request event or staff event  
    bool operator<(const Event& e) const { return time > e.time; }
    Event(int t, int i, bool isr = true) : time(t), id(i), isRorC(isr) {
		assert(t >= 0);
	}
};
struct ReqInfo { int tid, num, t0, t, dt; };
struct StaffInfo { 
    int pid, k, tids[maxn], idx, last, req;
    bool operator<(const StaffInfo& s) const { 
        return last < s.last || (last == s.last && pid < s.pid); 
    }
};

ReqInfo reqs[maxn];
StaffInfo staffs[maxm];
int n, m, kase;
multiset<int> rQs; // 当前队列中的所有任务
priority_queue<Event> em; // 按照时间排序的事件
set<int> freeStaffs;

struct StaffComp {
    bool operator() (int lhs, int rhs) const { return staffs[lhs]<staffs[rhs]; }
};
set<int, StaffComp> rt[maxn];

void solve() {
    int time = em.top().time; // 最新事件的时间
	while(!em.empty() && time == em.top().time) { // 收集所有的事件
        const Event& e = em.top();
        if(e.isRorC) rQs.insert(e.id); // 往请求队列里面
        else freeStaffs.insert(e.id); // 客服开始空闲了
        em.pop();
    }
    
    // 人选请求如何选呢？
    while(!rQs.empty() && !freeStaffs.empty()) { // 有请求并且有人
        _for(i, 0, n) rt[i].clear();
        bool canAssign = false;
        
        for(auto& i : freeStaffs){
            auto& si = staffs[i];
            _for(j, 0, si.k){
                int tid = si.tids[j];
                if(!rQs.count(tid)) continue;
                canAssign = true;
                rt[tid].insert(si.idx);
                break;
            }
        }
        
        if(!canAssign) break;
        
        _for(i, 0, n){
            auto& ss = rt[i];
            while(rQs.count(i) && !ss.empty()) {
                rQs.erase(rQs.find(i));
                int si = *(ss.begin());
                auto& s = staffs[si];
                s.last = time;
                em.push(Event(time + reqs[i].t, s.idx, false));
                freeStaffs.erase(s.idx);
                ss.erase(si);
            }
        }
    }
    
    if(em.empty()) 
        cout<<"Scenario "<<kase++<<": All requests are serviced within "<<time<<" minutes."<<endl;
}

int main(){
    map<int, int> tids;
    kase = 1;
    while(cin>>n && n) {        
        freeStaffs.clear(), tids.clear(), rQs.clear();
        _for(i, 0, n){
            auto& r = reqs[i];
            cin>>r.tid>>r.num>>r.t0>>r.t>>r.dt;
            tids[r.tid] = i;
            r.tid = i;
            _for(j, 0, r.num) em.push(Event(r.t0 + r.dt*j, i));
        }
        
        cin>>m;
        _for(i, 0, m){
            auto& s = staffs[i];
            cin>>s.pid>>s.k;
            _for(j, 0, s.k){
                cin>>s.tids[j];
                s.tids[j] = tids[s.tids[j]];
            }
            s.last = 0;
            s.idx = i;
            em.push(Event(0, s.idx, false));
        }
        
        while(!em.empty()) solve();
    }
    return 0;
}
// 13939915	822	Queue and A	Accepted	C++	0.128	2014-07-24 22:28:53