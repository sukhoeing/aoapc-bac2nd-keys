// LA7078 Yuefei’s Battle
// 陈锋
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
int K;
typedef long long LL;
LL gcd(LL a, LL b,LL &x, LL &y){
    if(!b) { x = 1, y = 0; return a; }
    LL ret = gcd(b,a%b,y,x);
    y -= x*(a/b);
    return ret;
}
LL Inv(LL b,LL mod){
    LL x,y,d = gcd(b,mod,x,y);
    return d == 1?(x%mod + mod)%mod:-1;
}

const LL MOD = 1000000007, inv2 = Inv(2, MOD), inv6 = Inv(6, MOD);
const int MAXI = 50000 + 4;
LL D[MAXI], S[MAXI];
int main() {
	fill_n(D, MAXI, -1);
	fill_n(S, MAXI, -1);
	S[0] = 1, D[0] = 1, D[1] = 1, S[1] = 2;
	_for(i, 2, MAXI){ // D[i] = D[i-1] + (D[i-1]*(D[i-1]-1)) / 2 + D[i-1]*S[i-2];
		LL d1 = D[i-1], &d = D[i];
		d = (d1 + d1*(d1-1)%MOD*inv2%MOD + d1*S[i-2]%MOD)%MOD;
		S[i] = (d + S[i-1]) % MOD;
	}
	int K;
	while(cin>>K && K){
		int i = K/2;
		LL ans, d = D[i];
		if(K <= 2){ ans = 1; }
		else if(K%2) { // S[i-1]*(D[i]*(D[i]-1)/2 + D[i]) + D[i] + D[i]*(D[i]-1) + D[i]*(D[i]-1))*(D[i]-2)/6			
			ans = S[i-1] * (d*(d-1)%MOD*inv2%MOD + d) % MOD;
			ans = (ans + d + d*(d-1)%MOD)%MOD;
			ans = (ans + d*(d-1)%MOD*(d-2)%MOD*inv6%MOD) % MOD;
		} else { // D[i] + D[i] * (D[i]-1) / 2
			ans = (d + d*(d-1)%MOD*inv2%MOD)%MOD;
		}
		cout<<ans<<endl;
	}

	return 0;
}
// 1882890	7078	Yue Fei's Battle	Accepted	C++11	0.003	2015-12-17 03:42:28
// refer to http://www.cnblogs.com/crackpotisback/p/4801279.html