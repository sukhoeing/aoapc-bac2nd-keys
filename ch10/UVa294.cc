// UVa294 Divisors
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXP = 100000;
typedef long long LL;
vector<LL> primes; // primes
void sieve() {
    vector<int> vis;
    vis.resize(MAXP, 0);
    for(LL i = 2; i < MAXP; i++) if (!vis[i]) {
        for(LL j = i*i; j < MAXP; j += i) vis[j] = 1;
        primes.push_back(i);
    }
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

LL div_num(int n) {    
    LL ans = 1; // 唯一分解
    for (auto p : primes) {
        if (n < 2) break;
        int pp = 0;
        while (n % p == 0) n /= p, pp++;
        ans *= pp + 1;
    }
    if (n > 1) ans *= 2;
    return ans;
}

int main(){
    sieve();
    int N, L, H, P; scanf("%d", &N);
    while (N--) {
        scanf("%d%d", &L, &H);
        LL D = 1;
        P = L;
        assert(L <= H);
        _rep(i, L, H){
            LL d = div_num(i);
            if (d > D) P = i, D = d;
        }
        printf("Between %d and %d, %d has a maximum of %lld divisors.\n", L, H, P, D);
    }
    return 0;
}

// 14805707 294 Divisors    Accepted    C++ 0.056   2015-01-15 09:40:26