// UVa1390 Interconnect
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
#include <numeric>
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
const int MAXN = 32;
int N, M, G[MAXN][MAXN], VIS[MAXN];
int dfs(int u) {
  int ans = 1;
  VIS[u] = 1;
  _for(v, 0, N) if (G[u][v] && !VIS[v]) ans += dfs(v);
  return ans;
}
unordered_map<string, double> D;
double dp(const string& s) {
  if (D.count(s)) return D[s];
  double& d = D[s];
  int k = s.size();
  if (k == 1) {
    assert(s[0] == N);
    return d = 0;
  }
  double e = 0, p = 0;
  _for(i, 0, k) {
    int ci = s[i];
    _for(j, i + 1, k) {
      int cj = s[j];
      auto s2 = s;
      s2[i] = ci + cj, s2.erase(s2.begin() + j);
      sort(begin(s2), end(s2));
      e += ci * cj * 2 * (dp(s2) + 1), p += ci * cj * 2;
    }
  }
  e /= (N * (N - 1)), p /= N * (N - 1);
  // d = e + (1+d)*(1-p) = e + 1-p + (1-p)d -> d = e/p + (1-p)/p
  return d = e / p + (1 - p) / p;
}

int main() {
  while (scanf("%d%d", &N, &M) == 2) {
    memset(G, 0, sizeof(G)), memset(VIS, 0, sizeof(VIS)), D.clear();
    int u, v;
    _for(i, 0, M) {
      scanf("%d%d", &u, &v);
      --u, --v;
      G[u][v] = G[v][u] = 1;
    }
    string s;
    _for(u, 0, N) if (!VIS[u]) s.push_back((char)dfs(u));
    printf("%.6lf\n", dp(s));
  }
  return 0;
}
// 2211999	3710	Interconnect	Accepted	C++11	0.206
// 2017-07-22 13:58:36