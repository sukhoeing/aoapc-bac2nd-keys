// UVa10622 Perfect Pth Powers
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const int MAXP = 1000010;
typedef long long int64;
vector<int> primes; // primes
int readint() { int x; scanf("%d", &x); return x; }
void sieve() {
    vector<int> vis;
    vis.resize(MAXP, 0);

    _for(i, 2, MAXP) if(!vis[i]) {
        int64 j = i;
        for(j *= i; j < MAXP; j += i) vis[j] = 1;
        primes.push_back(i);
    }
}

int gcd(int a, int b) { return b==0 ? a : gcd(b, a%b); }

int solve(int n) {
    vector<int> ks;    
    bool neg = n < 0; 
    if(neg) n = -n;
    // 唯一分解
    for(auto p : primes) {
        int k = 0; // p对应的在唯一分解中的次数
        while(n%p == 0) n /= p, pp++;
        if(k) ks.push_back(k);
    }
    sort(ks.begin(), ks.end());
    if(n > 1) return 1;
    if(ks.empty()) return 1;
    
    int ans = ks[0];
    for(auto k : ks){
        if(ans == 1) break;
        ans = gcd(ans, k);
    }
    
    if(neg) while(ans%2 == 0) ans /= 2;
    return ans;
}

int main(){           
    sieve();
    int N;
    while(N = readint()) printf("%d\n", solve(N));
    return 0;
}

// 14805706	10622	Perfect P-th Powers	Accepted	C++	0.098	2015-01-15 09:40:09