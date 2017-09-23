// UVa1210 Sum of Consecutive Prime Numbers, ACM/ICPC Japan 2005
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
const int MAXN = 10000 + 4;
vector<int> primes, PS;
int readint() { int x; scanf("%d", &x); return x; }

void gen_primes() {
    vector<int> vis;
    vis.resize(MAXN, 0);
    primes.reserve(MAXN);
    _for(i, 2, MAXN) if(!vis[i]) {
        primes.push_back(i);
        for(int j = i*i; j >= 0 && j < MAXN; j += i) vis[j] = 1;
    }

    PS.resize(primes.size());
    PS[0] = primes[0];
    _for(i, 1, primes.size()) PS[i] = primes[i] + PS[i-1];
}

int main(){        
    int N;
    gen_primes();    
    while(scanf("%d", &N) == 1 && N) {
        int ans = 0;
        _for(i, 0, PS.size()){           
            if(PS[i] == N) ans++;
            if(primes[i] > N) break;
            ans += binary_search(PS.begin()+i, PS.end(), PS[i] + N);
        }
        printf("%d\n", ans);
    }
    
    return 0;
}

// 14805675	1210	Sum of Consecutive Prime Numbers	Accepted	C++	0.022	2015-01-15 09:33:24