// UVa10118 Free Candies
// 陈锋
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
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
const int MAXN = 40 + 2;
int N;
int P[4][MAXN], D[MAXN][MAXN][MAXN][MAXN], H[4];

int dp(bitset<32>& b) {
  int& d = D[H[0]][H[1]][H[2]][H[3]];
  if (d > -1) return d;
  d = 0;
  if (b.count() == 5) return d = 0;
  _for(pi, 0, 4) if (H[pi] < N) {
    int t = P[pi][H[pi]++];
    if (b.test(t))
      b.reset(t), d = max(d, dp(b) + 1), b.set(t);
    else
      b.set(t), d = max(d, dp(b)), b.reset(t);
    H[pi]--;
  }
  return d;
}

int main() {
  while (_ri1(N) == 1 && N) {
    _for(i, 0, N) _for(j, 0, 4) _ri1(P[j][i]);
    _init(D, -1), _zero(H);
    bitset<32> b;
    int ans = dp(b);
    printf("%d\n", ans);
  }
  return 0;
}
// 20188891	10118	Free Candies	Accepted	C++11	0.060	2017-10-16 23:08:12