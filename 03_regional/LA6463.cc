// LA6463 Tower Defense
// 陈锋
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

using namespace std;

typedef long long LL;
const int MAXN = 200+4;
const LL MOD = 1000000007, R = 500000004;
//组合数，阶乘，组合数求和
LL C[MAXN][MAXN], Fac[MAXN*2], CS[MAXN][MAXN];
LL G2[MAXN];//G2[p] = (2p)!/(2^p)表示，1~2p的2p个数字，被分成p个都包含2个数字的组，所有的分组方案数。

void prepare(){
    Fac[0] = 1;
    _for (i, 1, 2* MAXN) Fac[i] = (Fac[i-1]*i) % MOD; // 阶乘
    fill_n(G2, MAXN, 0);
    G2[0] = 1, G2[1] = 1;
    LL rp = R; // 1/2^p ≡ ((MOD+1)/2)^p ≡(500000004)^p (mod MOD)
    _for (i, 2, MAXN) {
        rp = (rp * R) % MOD;
        G2[i] = (Fac[2*i]*rp) % MOD;
    }
    memset(C, 0, sizeof(C));
    C[0][0] = 1;
    _for (i, 1, MAXN) {
        C[i][0] = 1, C[i][i] = 1;
        _for (j, 1, i) C[i][j] = (C[i-1][j-1] + C[i-1][j]) %  MOD;
    }
    memset(CS, 0, sizeof(CS));
    _for (i, 0, MAXN) {
        CS[i][0] = 1;
        _for (j, 1, i + 1) CS[i][j] = (CS[i][j-1] + C[i][j]) % MOD;
    }
    return ;
}
//在r行*c列的棋盘里，选择p行，2*p列放置每行两个重塔
LL p2C(int r, int c, int p) { 
    return ((C[r][p] * C[c][2*p]) % MOD * G2[p]) % MOD; 
}

//z个塔，最少放minP个重塔，最多放maxP个重塔的方案数
LL p1C(int k, int minP, int maxP) { 
    if (minP > 0) 
        return ((CS[k][maxP] - CS[k][minP-1]) % MOD + MOD) % MOD;
    return (CS[k][maxP]) % MOD;
}
int main(){
    int N, M, P, Q, T; cin>>T;
    prepare();
    while (T--) {
        cin>>N>>M>>P>>Q; // 行，列，重，轻
        LL ans = 0;

        // i行，j列上各2个重塔
        _rep(i, 0, N) _rep(j, 0, M) { 
            const int r = N-(i+2*j), c = M-(2*i+j), p = P-2*(i+j); 
            // 剩下r行c列，p个重塔以及Q个轻塔都只占一行
            if (r<0 || c<0 || p<0) continue; 

            // i行,j列d都有2重塔的选择方案数
            LL ijC = (p2C(N, M, i) * p2C(M-2*i, N-i, j)) % MOD; 

            // 剩下的共要放k个塔，都是占1行1列的
            for (int k = 0; k <= p+Q && k <= min(r,c); k++) { 
                // k个塔中重塔个数的上下限
                int minp = max(0, k-Q), maxp = min(k,p); 
                // 放置k个塔的方案数
                LL pq1c = C[r][k] * C[c][k] % MOD * p1C(k, minp, maxp) % MOD; 
                ans = (pq1c * Fac[k] % MOD * ijC % MOD + ans) % MOD;
            }
        }
        cout<<ans-1<<endl; // 要减去什么都不放的情况
    }
    return 0;
}
// 1887111  6463    Tower Defense   Accepted    C++ 0.402   2015-12-29 14:02:04
// refer to: http://www.cnblogs.com/wangsouc/articles/3639137.html