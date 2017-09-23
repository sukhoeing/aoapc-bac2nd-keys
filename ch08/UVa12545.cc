// UVa12545 Bits Equalizer
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
string S, T;

int solve() {
  int N = S.size(), s01 = 0, s10 = 0, q0 = 0, q1 = 0, ans = 0;  // S-0,? T-0
  assert(N == T.size());
  _for(i, 0, N) if (S[i] != T[i]) {
    int cs = S[i], ct = T[i];
    if (cs == '0') s01++;              // 0->1
    if (cs == '1') s10++;              // 1->0
    if (cs == '?' && ct == '0') q0++;  // ? -> 0
    if (cs == '?' && ct == '1') q1++;  // ? -> 1
  }
  int x = min(s01, s10);
  ans = x + q0, s01 -= x, s10 -= x;  // swap 1->0 && 0->1 and ? -> 0 first
  assert(s01 == 0 || s10 == 0);
  if (s10 > q1) return -1;  // not enougth ? -> 0
  ans += s10 + s01 + q1;    // 0->1 + (?->0 swap with 1->0) + ?->1
  return ans;
}

int main() {
  int C;
  cin >> C;
  for (int t = 1; cin >> S >> T; t++) {
    int ans = solve();
    printf("Case %d: %d\n", t, ans);
  }
  return 0;
}
// 19964767	12545	Bits Equalizer	Accepted	C++11	0.000
// 2017-09-06 02:24:07