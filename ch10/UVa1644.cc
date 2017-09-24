// UVa1644 Prime Gap, ACM/ICPC Japan 2007
// 陈锋
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;

const int MAXP = 1299709 + 4;
void sieve(const int SZ, int* P, vector<int>& primes) {
  assert(SZ > 2);
  fill_n(P, SZ, 1);
  primes.clear();
  P[2] = 1;
  _for(i, 2, SZ) if (P[i]) {
    primes.push_back(i);
    LL j = i;
    for (j *= i; j < SZ; j += i) P[j] = 0;
  }
}
int IsPrime[MAXP];
vector<int> primes;
int solve(int n) {
  if (IsPrime[n]) return 0;
  auto pl = lower_bound(begin(primes), end(primes), n);
  assert(pl != end(primes));
  assert(pl != begin(primes));
  return *(pl) - *(pl - 1);
}

int main() {
  sieve(MAXP, IsPrime, primes);
  int n;
  while (_ri1(n) == 1 && n) printf("%d\n", solve(n));
  return 0;
}
// 20055470	1644	Prime Gap	Accepted	C++11	0.000	2017-09-24 07:13:48