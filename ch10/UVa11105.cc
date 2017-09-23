// UVa11105 Semi-prime H-numbers
// 陈锋
#include <cassert>
#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef long long LL;
const LL MAXN = 250000, MAXP = 4*MAXN+1;
vector<LL> primes;
int cnt[MAXN + 1]; // cnt[i]表示 [1,i]区间内所求素数的种类个数
void sieve() {
    vector<int> vis(MAXN + 1, 0); // vis[i] -> 4i+1是否是H-素数
    for(LL i = 1; i <= MAXN; i++) if(!vis[i]){
        LL hi = 4*i + 1;
        for(LL j = hi*hi; j <= MAXP; j += hi)
            if(j%4 == 1) vis[(j-1)/4] = 1; // j不是H-素数
        primes.push_back(hi);
    }

    _for(i, 0, primes.size()) _for(j, i, primes.size()){
        LL hi = primes[i]*primes[j];
        if(hi > MAXP) break;
        vis[(hi-1)/4] = 2; // vis[4i+1] 是H-半素数
    }
    
    cnt[0] = 0;
    _rep(i, 1, MAXN) cnt[i] = cnt[i-1] + ((vis[i] == 2)?1:0);
}

int main(){           
    sieve();
    int h;
    while(scanf("%d", &h) == 1 && h) printf("%d %d\n", h, cnt[(h-1)/4]);
    return 0;
}

// 14805756	11105	Semi-prime H-numbers	Accepted	C++	0.035	2015-01-15 09:49:32