// UVa12118 Inspector’s Dilemma
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
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
template <typename T>
inline vector<T>& operator+=(vector<T>& v, const T& x) {
  v.push_back(x);
  return v;
}
template <typename T>
inline set<T>& operator+=(set<T>& s, const T& x) {
  s.insert(x);
  return s;
}

typedef long long LL;
const int MAXV = 1000 + 4;
vector<int> G[MAXV];
int V, E, T, VIS[MAXV];

void dfs(int u, int& cnt) {
  VIS[u] = 1;
  cnt += G[u].size() % 2;
  for (auto v : G[u])
    if (!VIS[v]) dfs(v, cnt);
}

int main() {
  for (int a, b, k = 1; scanf("%d%d%d", &V, &E, &T) == 3 && (V || E || T); k++) {
    _for(i, 0, V) G[i].clear();
    fill_n(VIS, MAXV, 0);
    _for(i, 0, E) scanf("%d%d", &a, &b), G[a - 1] += b - 1, G[b - 1] += a - 1;
    int nc = 0, ans = 0;
    _for(u, 0, V) if (!G[u].empty() && !VIS[u]) {
      int p = 0;
      dfs(u, p);
      if (p > 2) ans += (p - 2) / 2;
      nc++;
    }
    printf("Case %d: %d\n", k, T * (E + ans + max(0, nc - 1)));
  }
}