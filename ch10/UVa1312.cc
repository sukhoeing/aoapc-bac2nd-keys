// UVa1312 Cricket Field
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
const int MAXN = 100 + 4;

int main() {
  int T, N, W, H, X[MAXN], Y[MAXN];
  scanf("%d", &T);
  _for(t, 0, T) {
    if (t) puts("");
    scanf("%d%d%d", &N, &W, &H);
    set<int> tmp{0, H};
    _for(i, 0, N) {
      scanf("%d%d", &(X[i]), &(Y[i]));
      tmp.insert(Y[i]);
    }
    vector<int> ys(begin(tmp), end(tmp));
    int L = -1, P, Q, YC = ys.size();
    _for(l, 0, YC) for (int u = YC - 1; u > l; u--) {
      int min_y = ys[l], max_y = ys[u], h = max_y - min_y;
      if (h < L) continue;
      set<int> xs{0, W};
      _for(i, 0, N) if (min_y < Y[i] && max_y > Y[i]) xs.insert(X[i]);
      auto px = begin(xs);
      int left = *px++;
      while (px != end(xs)) {
        int side = min(h, *px - left);
        if (side > L) L = side, P = left, Q = max_y - side;
        left = *px++;
      }
    }
    printf("%d %d %d\n", P, Q, L);
  }
  return 0;
}
// 19846818	1312	Cricket Field	Accepted	C++11	0.050	2017-08-13 09:30:34