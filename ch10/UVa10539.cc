// UVa10539 Almost Prime Numbers
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
using namespace std;
typedef long long LL;
const LL MAXN = 1000000 + 10, MAXP = 1000000000000;
vector<LL> aps; // almost primes

void sieve() {
    vector<bool> vis(MAXN, false);
    aps.reserve(MAXN);
    for(LL i = 2; i < MAXN; i++) if(!vis[i]){
        for(LL j = i*i; j < MAXN; j += i) vis[j] = true;
        for(LL p = i*i; p <= MAXP; p *= i) aps.push_back(p);
    }
    
    sort(aps.begin(), aps.end());
}

int main(){
    sieve();
    int N; scanf("%d", &N); LL L, H;
    while(N--) {        
        scanf("%lld%lld", &L, &H);
        auto pL = lower_bound(aps.begin(), aps.end(), L),
            pH = upper_bound(aps.begin(), aps.end(), H);        
        printf("%ld\n", pH - pL);
    }
    return 0;
}

// 14805677	10539	Almost Prime Numbers	Accepted	C++	0.068	2015-01-15 09:33:57