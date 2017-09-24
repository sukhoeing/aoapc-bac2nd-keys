// https://ser.cs.fit.edu/ser2010/problems/
// LA4870 Roller Coaster 
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

using namespace std;
    
const int MAXN = 1000+4, MAXF = 1000*20, INF = 1000000007;
int DP[MAXN][MAXF], F[MAXN], D[MAXN], N,K,L;
int main() { 
    while(cin>>N>>K>>L && (N+K+L)){
        int ans = 0, FF = 0;
        _rep(i, 1, N) cin>>F[i]>>D[i], FF += F[i];
        _rep(i, 0, N) _rep(f, 0, FF) DP[i][f] = INF;
        DP[0][0] = 0;
        _rep(i, 1, N) _rep(f, 0, FF){
            int& d = DP[i][f];
            d = min(d, max(0, DP[i-1][f]-K)); // 第i段闭眼
            if(f >= F[i] && DP[i-1][f-F[i]] + D[i] <= L) // 第i段睁眼
                d = min(d, DP[i-1][f-F[i]] + D[i]);
        }
        for(int f = FF; f >= 0; f--)
            if(DP[N][f] <= L) { ans = f; break;}
        cout<<ans<<endl;
    }
    return 0;
}
// 1675689	4870	Roller Coaster	Accepted	C++	2.015	2015-04-15 00:31:43