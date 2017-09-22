// UVa818 Cutting Chains
// 陈锋
#include <bitset>
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
const int MAXN = 16;
int N, VIS[MAXN], DEG[MAXN];
unordered_set<int> G[MAXN];
bitset<MAXN> OPEN;

bool dfs(int u, int pa) {
  VIS[u] = -1;
  int d = 0;
  for (auto v : G[u]) {
    if (OPEN[v]) continue;
    if (++d > 2) return false;
    if (v != pa) {
      if (VIS[v] == -1) return false;
      if (VIS[v] == 0 && !dfs(v, u)) return false;
    }
  }
  return true;
}

int solve() {
  int ans = N;
  _for(B, 0, (1 << N)) {
    OPEN.reset();
    _for(i, 0, N) if (B & (1 << i)) OPEN.set(i);
    int oc = OPEN.count(), comp = 0;
    if (oc > ans) continue;
    bool valid = true;
    fill_n(VIS, N, 0);
    _for(u, 0, N) if (!OPEN[u] && !VIS[u]) {
      if (++comp > oc + 1 || !dfs(u, -1)) {
        valid = false;
        break;
      }
    }

    if (valid) ans = min(ans, oc);
  }
  return ans;
}

int main() {
  for (int t = 1; scanf("%d", &N) == 1 && N; t++) {
    _for(i, 0, N) G[i].clear();
    int i, j;
    while (scanf("%d%d", &i, &j) == 2 && i > 0 && j > 0) {
      --i, --j;
      G[i].insert(j), G[j].insert(i);
    }
    int ans = solve();
    printf("Set %d: Minimum links to open is %d\n", t, ans);
  }
  return 0;
}
// 19543127	818	Cutting Chains	Accepted	C++11	0.030	2017-06-19 14:50:27