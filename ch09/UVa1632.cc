// Alibaba, ACM/ICPC SEERC 2004, UVa1632
// 陈锋
#include <cassert>
#include <cstring>
#include <cstdio>
#include <climits>
#include <functional>
#include <algorithm>
#include <iostream>
using namespace std;
#define _for(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

const int MAXN = 10000 + 4, INF = 1000000000;
int D[MAXN][MAXN][2], X[MAXN], DL[MAXN], N;

/*
D[i][j][0]表示拿i到j的物品最后停在i点所需要的最少时间
D[i][j][1]表示拿i到j的物品最后停在j点所需要的最少时间
*/

int main() {
    while(cin>>N && N) {
        _for(i, 1, N+1) {
            cin>>X[i]>>DL[i];
            D[i][i][0] = D[i][i][1] = 0;
        }
        
        for(int i = N; i >= 1; i--) {
            for(int j = i+1; j <= N; j++) {
                int& d0 = D[i][j][0];
                d0 = min(D[i+1][j][0] + X[i+1] - X[i], D[i+1][j][1] + X[j] - X[i]);
                if(d0 >= DL[i]) d0 = INF;
                int& d1 = D[i][j][1];
                d1 = min(D[i][j-1][1] + X[j] - X[j-1], D[i][j-1][0] + X[j] - X[i]);
                if(d1 >= DL[j]) d1 = INF; 
            }
        }
        int ans = min(D[1][N][0], D[1][N][1]);
        if(ans < INF) cout<<ans<<endl;
        else cout<<"No solution"<<endl;
    }
    
    return 0;
}

// 14934620	1632	Alibaba	Feng Chen (sukhoeing)	AC	C++	1.055	14	