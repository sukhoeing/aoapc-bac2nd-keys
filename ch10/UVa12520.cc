// UVa12520 Square Garden
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
LL solve(LL L, LL N) {
  LL g = (L * L + 1) / 2;
  if (N <= g) return 4 * N;
  if (L % 2) {
    LL tN = N - g, ans1 = 4 * g, ans2 = 4 * (g - 1);
    /*
      *_*
      _*_
      *_*
    */
    LL e = min(tN, L / 2 * 4);
    ans1 -= 2 * e, tN -= e;
    assert(tN <= (L - 2) * (L - 2) / 2 + 1);
    ans1 -= tN * 4;

    /*
      _*_
      *_*
      _*_
    */
    tN = N - (g - 1);
    tN -= min(4LL, tN);
    e = min((L / 2 - 1) * 4, tN);
    ans2 -= 2 * e, tN -= e;
    ans2 -= 4 * tN;

    // printf("ans1 = %lld, ans2 = %lld\n", ans1, ans2);
    return max(ans1, ans2);
  }
  /*
    _*_*
    *_*_
    _*_*
    *_*_
  */
  LL tN = N - g, ans = g * 4;
  tN -= min(tN, 2LL);  // 先放两个对角
  LL e = min(tN, L * 2 - 4);
  ans -= 2 * e, tN -= e;  // 放四边上
  ans -= 4 * tN;          // 中间
  return ans;
}

int main() {
  LL l, n;
  while (scanf("%lld%lld", &l, &n) == 2 && l) {
    LL ans = solve(l, n);
    printf("%lld\n", ans);
  }
  return 0;
}
// 19903491	12520	Square Garden	Accepted	C++11	0.000	2017-08-23 11:42:51