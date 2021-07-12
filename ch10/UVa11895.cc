// UVa11895 Honorary Tickets
// 陈锋
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
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
  cin >> T;
  while (T--) {
    cin >> N >> K;
    priority_queue<Bag> Q;
    _for(i, 0, N) {
      Bag b; cin >> b.T >> b.p, Q.push(b);
    }
    _for(i, 1, K) {
      const Bag &b = Q.top();
      Q.pop();
      LL p = b.p * (b.T - 1LL), q = b.q * b.T, g = gcd(p, q);
      Q.emplace(p / g, q / g, b.T);
    }
    const Bag &b = Q.top();
    LL p = b.p, q = b.q * b.T, g = gcd(p, q);
    printf("%lld/%lld\n", p / g, q / g);
  }
  return 0;
}
// 22122246 11895 Honorary Tickets Accepted C++11 0.380 2018-10-14 01:41:04