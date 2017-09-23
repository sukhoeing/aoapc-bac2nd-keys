// UVa1653 Yet Another Multiple Problem
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

int D[10];
bool VIS[10000 + 4];

struct Node {
  int v;
  string path;
};
string solve(int n) {
  if (n == 1) {
    _for(d, 1, 10) if (D[d]) return to_string(d);
    assert(false);
  }
  memset(VIS, 0, sizeof(VIS));
  queue<Node> Q;
  _for(d, 1, 10) if (D[d] && !VIS[d % n]) {
    Q.push({d % n, to_string(d)});
    VIS[d % n] = true;
  }

  while (!Q.empty()) {
    auto node = Q.front();
    Q.pop();
    if (node.v == 0) return node.path;
    _for(d, 0, 10) if (D[d]) {
      int nv = (node.v * 10 + d) % n;
      if (VIS[nv]) continue;
      VIS[nv] = true;
      auto nnd = node;
      nnd.v = nv, nnd.path += (char)(d + '0');
      Q.push(nnd);
    }
  }
  return "-1";
}

int main() {
  int n, m;
  for (int t = 1; scanf("%d%d", &n, &m) == 2; t++) {
    fill_n(D, 10, 1);
    _for(i, 0, m) {
      int d;
      scanf("%d", &d);
      D[d] = 0;
    }
    auto ans = solve(n);
    printf("Case %d: %s\n", t, ans.c_str());
  }
  return 0;
}
// 2227476	6370	Yet Another Multiple Problem	Accepted	C++11	0.802	2017-08-06
// 04:03:33