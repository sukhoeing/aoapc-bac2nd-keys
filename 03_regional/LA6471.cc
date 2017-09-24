// LA6471 - Triangle Count Sequences of Polygon Triangulations
// 陈锋
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

int readint() { int x; cin>>x; return x; }
typedef vector<int> IntVec;

void record(int a, int b, int c, vector<IntVec>& ts) {
    IntVec t{a,b,c};
    sort(t.begin(), t.end());
    ts.push_back(t);
}

bool judge(IntVec& s, IntVec& si, vector<IntVec>& ts) {
    int SZ = s.size();
    assert(si.size() == SZ);
    if(SZ < 3) return false;
    if(SZ == 3)  {
        record(si[0], si[1], si[2], ts);
        return all_of(s.begin(), s.end(), [](int i){return i == 1;});
    }
    
    int pi = find(s.begin(), s.end(), 1) - s.begin();
    if(pi == SZ) return false;
    int pl = (pi-1+SZ)%SZ, pr = (pi+1)%SZ;
    if(s[pl] <= 1 || s[pr] <= 1) return false;
    s[pl]--, s[pr]--;
    
    record(si[pi], si[pl], si[pr], ts);
    s.erase(s.begin() + pi);
    si.erase(si.begin() + pi);
    return judge(s, si, ts);
}

int main() {
    int P,K,N; cin>>P;
    IntVec s, si; vector<IntVec> ts;
    while(P--) {
        cin>>K>>N;
        s.clear(), si.clear(), ts.clear();
        _for(i, 0, N) s.push_back(readint()), si.push_back(i+1);
        IntVec buf(s);
        bool ans = judge(buf, si, ts);
        cout<<K<<" "<<(ans ? "Y" : "N")<<endl;
        if(!ans) continue;
        sort(ts.begin(), ts.end());
        for(auto& t : ts){
            bool first = true;
            for(auto i : t){
                if(first) first = false; else cout<<" ";
                cout<<i;
            }
            cout<<endl;
        }
    }
}

// 1538697	6471	Triangle Count Sequences of Polygon Triangulations	Accepted	C++	0.003	2014-09-08 10:14:27
