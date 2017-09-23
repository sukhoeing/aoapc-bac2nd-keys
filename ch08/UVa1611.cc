// UVa1611 Crane
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
const int MAXN = 10000 + 4;
int N, A[MAXN];
int main() {
  int T;
  _ri1(T);
  vector<pair<int, int>> ans;
  auto swapSeg = [&ans](int st, int l) {  // [st...], len l
    _for(i, 0, l) swap(A[st + i], A[st + l + i]);
    ans.push_back(make_pair(st, st + 2 * l - 1));
  };

  while (_ri1(N) == 1) {
    ans.clear();
    _rep(i, 1, N) _ri1(A[i]);
    _rep(i, 1, N) {
      int p = find(A + i, A + N + 1, i) - A, l = p - i;
      if (A[i] == i) continue;
      if (2 * l > N - i + 1) {
        int sl = (N - i + 1) / 2;
        swapSeg(N - 2 * sl + 1, sl);
      }
      p = find(A + i, A + N + 1, i) - A;
      swapSeg(i, p - i);
    }
    printf("%lu\n", ans.size());
    for (auto p : ans) printf("%d %d\n", p.first, p.second);
  }
  return 0;
}
// 19960872	1611	Crane	Accepted	C++11	0.190	2017-09-05 04:16:56