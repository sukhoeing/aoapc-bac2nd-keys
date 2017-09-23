// UVa1575 Factors
// 陈锋
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;

void sieve(const int SZ, int* P, vector<int>& primes) {
  assert(SZ > 2);
  fill_n(P, SZ, 1);
  primes.clear();
  P[2] = 1;
  _for(i, 2, SZ) if (P[i]) {
    primes.push_back(i);
    for (int j = i * i; j < SZ; j += i) P[j] = 0;
  }
}

void defactor(int n, unordered_map<int, int>& M, const vector<int>& primes) {
  M.clear();
  if (n == 0) return;
  for (auto p : primes) {
    if (p > n) break;
    while (n % p == 0) M[p]++, n /= p;
  }
}

const int MAXP = 1000 + 4;
int P[MAXP];
vector<int> primes;
unordered_map<int, int> DEF[64];

ULL comb(const vector<int>& E) {  // (C(e1+e2+e3, e1, e2, e3))
  unordered_map<int, int> RM, M;
  int se = 0;
  for (auto e : E) {
    se += e;
    _rep(i, 1, e) for (auto p : DEF[i]) RM[p.first] -= p.second;
  }
  _rep(i, 1, se) for (auto p : DEF[i]) RM[p.first] += p.second;

  ULL ans = 1;
  for (auto p : RM) {
    assert(p.second >= 0);
    LL po = 1;
    _for(i, 0, p.second) po *= p.first;
    ans *= po;
    if (ans >= LLONG_MAX) return 0;
  }
  return ans;
}

unordered_map<ULL, ULL> ANS;

// make k < 2^63
void dfs(vector<int>& E, ULL k) {
  assert(k < LLONG_MAX);
  if (!E.empty()) {
    ULL n = comb(E);
    if (n) {
      if (!ANS.count(n) || ANS[n] > k) ANS[n] = k;
    }
  }
  // 2^62
  int esz = E.size(), last = esz == 0 ? 62 : E.back(), p = primes[esz];
  ULL nk = k;
  for (int i = 1; i <= last; i++) {  // p^i
    if ((LD)nk * p > LLONG_MAX) break;
    nk *= p;
    E.push_back(i);
    dfs(E, nk);
    E.pop_back();
  }
}

int main() {
  sieve(MAXP, P, primes);
  _for(i, 1, 64) defactor(i, DEF[i], primes);
  vector<int> E;
  ANS[1] = 2;
  dfs(E, 1);
  ULL n;
  while (scanf("%llu", &n) == 1) {
    assert(ANS.count(n));
    printf("%llu %llu\n", n, ANS[n]);
  }

  return 0;
}
// 19749626	1575	Factors	Accepted	C++11	0.070	2017-07-27 01:47:10