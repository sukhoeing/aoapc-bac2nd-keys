// UVa1213 Sum of Different Primes, ACM/ICPC Yokohama 2006
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const int MAXN = 1120 + 10, MAXK = 14 + 1;
vector<int> primes; // almost primes
int D[189][MAXN][MAXK];
int dp(int i, int n, int k){
    int& ans = D[i][n][k];
    assert(k >= 1);
    if(ans != -1) return ans;
    ans = 0;
    if(n < 2) return ans;

    int p = primes[i];
    if(p > n) return ans;
    if(k == 1) return ans = binary_search(primes.begin()+i, primes.end(), n) ? 1 : 0;       
    return ans = dp(i+1, n, k) + dp(i+1, n-p, k-1);
}

void sieve() { // 筛法求所有素数
    vector<int> vis;
    vis.resize(MAXN, 0);
    primes.reserve(MAXN);
    _for(i, 2, MAXN) if(!vis[i]) {
        for(int j = i*i; j < MAXN; j += i) vis[j] = 1;
        primes.push_back(i);
    }
}

int main() {
    sieve();
    memset(D, -1, sizeof(D));
    while(true) {
        int N,K;
        scanf("%d %d", &N, &K);
        if(N == 0) break;      
        printf("%d\n", dp(0, N, K));
    }
    return 0;
}

// 14805672	1213	Sum of Different Primes	Accepted	C++	0.162	2015-01-15 09:32:50