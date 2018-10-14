// UVa11895 Honorary Tickets
// 陈锋
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;
using namespace std;
LL gcd(const LL &a, const LL &b) { return b == 0LL ? a : gcd(b, a % b); }

struct Bag {  // p/q in T bags
  LL p, q, T;
  Bag(LL _p = 1, LL _q = 1, LL _T = 1) : p(_p), q(_q), T(_T) {}
  bool operator<(const Bag &b) const {
    return (double)p * b.q * b.T < (double)b.p * q * T;
  }
};

int main() {
  int T, N, K;
  _ri1(T);
  while (T--) {
    _ri2(N, K);
    priority_queue<Bag> Q;
    _for(i, 0, N) {
      Bag b;
      scanf("%lld%lld", &(b.T), &(b.p)), Q.push(b);
    }
    _for(i, 1, K) {
      const auto &b = Q.top();
      Q.pop();
      LL p = b.p * (b.T - 1LL), q = b.q * b.T, g = gcd(p, q);
      Q.emplace(p / g, q / g, b.T);
    }
    const auto &b = Q.top();
    LL p = b.p, q = b.q * b.T, g = gcd(p, q);
    printf("%lld/%lld\n", p / g, q / g);
  }
  return 0;
}
// 22122246 11895 Honorary Tickets Accepted C++11 0.380 2018-10-14 01:41:04