// Folding, ACM/ICPC NEERC 2001, UVa1630
// 陈锋
#include <iostream>
#include <string>
#include <climits>
#include <cassert>
#include <sstream>

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

using namespace std;
const int INF = 0x3f3f3f3f, MAXN = 104;
string S, Fold[MAXN][MAXN];

int getMinCycle(int l, int r){
    int segLen = r-l+1;
    _rep(cycle, 1, segLen/2){
        if(segLen%cycle) continue;
        bool flag = true;
        _rep(j, l, r-cycle){
            if(S[j] == S[j+cycle]) continue;
            flag = false;
            break;
        }
        if(flag) return cycle;
    }
    return 0;
}

string& solve(int l, int r){
    string& ans = Fold[l][r];
    if(!ans.empty()) return ans;
    if(l == r) return ans = S[l];

    int minK, ansLen = INF;
    _for(i, l, r){
        int len = solve(l,i).size() + solve(i+1, r).size();
        if(len < ansLen) minK = i, ansLen = len;
    }
    ans += solve(l, minK);
    ans += solve(minK+1, r);

    int cycle = getMinCycle(l, r);
    if(cycle){
        stringstream ss;
        ss<<(r-l+1)/cycle<<"("<<solve(l, l+cycle-1)<<")";
        if(ss.tellp() < ans.size()) ss>>ans;
    }
    return ans;
}

int main(){
    while(cin>>S){
        int n = S.size();
        _for(i, 0, n) _for(j, 0, n) Fold[i][j].clear();
        cout<<solve(0, n-1)<<endl;
    }
}
// 1992297  2692    Folding Accepted    C++11   0.062   2016-07-20 09:47:42