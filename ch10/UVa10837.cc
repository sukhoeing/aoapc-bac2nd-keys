// UVa10837 A Research Problem
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXP = 14143, INF = 200000000 + 1; // sqrt(200000000) + 1
typedef long long int64;
vector<int> primes, isPrime(MAXP, 0); // primes
void sieve() {
    _for(i, 2, MAXP) if(!isPrime[i]) {
        for(int j = i*i; j < MAXP; j += i) isPrime[j] = 1;
        primes.push_back(i);
    }
}
// φ(n) = phi的时候，所有可能是n的素因子的数字，存放到ps中
void getPrimeFactors(int phi, vector<int>& ps) {
    ps.clear();
    for(auto p : primes){
        if(p > phi) break;
        if(phi%(p-1) == 0) ps.push_back(p);
    }
}
// 可能的素因子，决策过的素因子个数，使用的素因子，目前使用的p组成的n, 除剩下的phi
void dfs(const vector<int>& ps, int cur, set<int>& usedPs, int n, int rem, int& ans) {
    // printf("cur == %d, usedPs=%s n = %d, rem = %d\n", cur, toString(usedPs).c_str(), n, rem);
    if(cur == ps.size()) {        
        if(rem == 1) { ans = min(ans, n); return; } // phi被除尽
        bool r = true;
        int pr = rem+1;
        for(auto p : primes) { // 判断rem+1是不是素数
            if(p*p > pr) break;
            if(pr%p == 0) { r = false; break; } // p不是素数
        }

        //rem+1是没有用过的素数
        if(r && usedPs.count(pr) == 0) ans = min(ans, n*pr);
        return;
    }
    
    int p = ps[cur];
    // 不用p作为n的因子
    dfs(ps, cur+1, usedPs, n, rem, ans);

    if(rem % (p-1)) return; // 不是n的因子，否则尝试用p作为n的因子
    rem /= p-1, n *= p;
    usedPs.insert(p);
    while(true) { // 尝试各种次方
        dfs(ps, cur+1, usedPs, n, rem, ans);
        if(rem%p) break;

        assert(rem >= p);
        rem /= p, n *= p;
    }
    usedPs.erase(p);
}
int solve(int phi) {
    vector<int> ps;
    set<int> usedPs;
    getPrimeFactors(phi, ps);
    int ans = INF;
    dfs(ps, 0, usedPs, 1, phi, ans);     
    return ans;
}
int main() {
    sieve();
    for(int phi, t = 1; scanf("%d", &phi) == 1 && phi; t++)
        printf("Case %d: %d %d\n", t, phi, solve(phi));
    return 0;
}

// 14805758	10837	A Research Problem	Accepted	C++	0.032	2015-01-15 09:49:59