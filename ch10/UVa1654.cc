// UVa1654 Pairs of integers
// 陈锋
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
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
void gcd(LL a, LL b, LL& d, LL& x, LL& y) {
  if (!b)
    d = a, x = 1, y = 0;
  else
    gcd(b, a % b, d, y, x), y -= x * (a / b);
}

const int MAXD = 10;
LL P10[MAXD];

void solve(LL N, map<LL, LL>& ans) {
  ans.clear();
  int D = to_string(N).size();
  if (N % P10[D - 1] == 0) ans[N] = 0;
  _for(i, 0, D) {
    _for(d, 0, 10) if (N > d * P10[i]) {  // solve the eq: 10^i*11*x + 2*y = N-d*10^i
      LL x, y, g, a = P10[i] * 11, b = 2, c = N - d * P10[i];
      gcd(a, b, g, x, y);
      if (c % g) continue;
      LL k = c / g;
      a /= g, b /= g, x *= k, y *= k;  // x + kb, y - ka, 0 <= x < 10^(D-i-1), 0 <= y < 10^i
      for (LL step = 1 << 30; step >= 1; step >>= 1) {
        if (y >= step * a) y -= step * a, x += step * b;
        if (y < -step * a) y += step * a, x -= step * b;
      }
      while (y < 0) y += a, x -= b;
      // while (y >= P10[i]) y -= a, x += b;
      // printf("i = %d, d = %d, x = %lld, y = %lld\n", i, d, x, y);
      if (y >= 0 && y < P10[i] && x >= 0 && x < P10[D - i - 1]) {
        LL X = x * P10[i + 1] + d * P10[i] + y, Y = x * P10[i] + y;
        if (X > Y && X + Y == N) ans[X] = Y;
      }
    }
  }
}

int main() {
  P10[0] = 1;
  _for(i, 1, MAXD) P10[i] = 10 * P10[i - 1];
  int T, N;
  scanf("%d", &T);
  map<LL, LL> ans;
  bool first = true;
  while (scanf("%d", &N) == 1) {
    if (first)
      first = false;
    else
      puts("");
    solve(N, ans);
    printf("%lu\n", ans.size());
    for (auto p : ans)
      printf("%lld + %0*lld = %d\n", p.first, (int)(to_string(p.first).size() - 1), p.second, N);
  }
  return 0;
}
// 2227129	2457	Pairs of integers	Accepted	C++11	0.000	2017-08-05 09:34:02