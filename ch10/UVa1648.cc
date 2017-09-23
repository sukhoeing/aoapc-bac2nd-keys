// UVa1648	Business Center
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

int main() {
  int n, m, u, d;
  while (scanf("%d%d", &n, &m) == 2) {
    int ans = INT_MAX;
    _for(i, 0, m) {
      scanf("%d%d", &u, &d);
      int a = (n * d) / (u + d) + 1;
      if (a <= n) ans = min(ans, a * u - (n - a) * d);
    }
    printf("%d\n", ans);
  }
  return 0;
}
// 19807130	1648	Business Center	Accepted	C++11	0.010	2017-08-05 12:53:30