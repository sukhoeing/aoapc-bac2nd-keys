// Protecting Zonk, ACM/ICPC Dhaka 2006, UVa12093
// 陈锋
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <climits>
#include <vector>
#include <functional>
#include <algorithm>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

const int MAXN = 10004, INF=INT_MAX;
int N, C1, C2, DP[MAXN][4];
vector<int> G[MAXN];
int min(int a, int b, int c){ return min(min(a,b), c);}
int min(int a, int b, int c, int d){ return min(min(a,b), min(c, d));}
void dfs(int u, int fa){
    int *D = DP[u], U1E = 0, minV0 = INF;
    memset(D, 0, sizeof(DP[u]));
    for(auto v : G[u]){
        if(v == fa) continue;   
        dfs(v, u);
        int *DV = DP[v], w = min(DV[0], DV[1], DV[2]);
        D[0] += min(DV[0], DV[1], DV[2], DV[3]);
        D[1] += w; // u上面放A
        D[2] += DV[1];
        D[3] += w;
        U1E += w; // u上面不放A的费用
        minV0 = min(minV0, DV[0]-w); // DV=0对于费用的增加
    }
    D[0] += C2, D[1] = min(D[1]+C1, U1E + minV0);
}

int main(){
    int u, v;
    while(scanf("%d%d%d", &N, &C1, &C2) == 3 && N){
        _rep(i, 0, N) G[i].clear();
        _for(i, 1, N)
            scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
        dfs(1, -1);
        printf("%d\n", min(DP[1][0], DP[1][1], DP[1][2]));
    }
    return 0;
}
// 2003345  2198    Protecting Zonk Accepted    C++11   0.042   2016-07-31 04:00:19
