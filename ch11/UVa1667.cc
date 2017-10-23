// UVa1667 Network Mess
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
#define _for(i, a, b) for (decltype(b) i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;
const int MAXN = 50 + 2;
int N, A[MAXN][MAXN], Pa[MAXN];
vector<int> D;
int find_pa(int u) { return u == Pa[u] ? u : (Pa[u] = find_pa(Pa[u])); }
void solve(const vector<int>& G, int pa = -1) {
  for (auto u : G) Pa[u] = u;
  int deg = 1;  // internal node, parent
  _for(ui, 0, G.size()) {
    auto u = G[ui];
    if (A[0][u] == 1) {
      ++deg;
      continue;
    }
    _for(vi, ui + 1, G.size()) {
      int v = G[vi];
      if (A[0][v] == 1) continue;
      if (A[0][u] + A[0][v] > A[u][v]) Pa[v] = u;
    }
  }
  unordered_map<int, vector<int>> SubTrees;
  for (auto u : G) {
    if (A[u][0] == 1) continue;  // u is direct child of root 0
    SubTrees[find_pa(u)].push_back(u);
  }
  deg += SubTrees.size();
  if (pa != -1) D.push_back(deg);
  for (const auto& p : SubTrees) {
    for (auto u : p.second) A[0][u]--, A[u][0]--;
    solve(p.second, 0);
  }
}

void solve() {
  D.clear();
  vector<int> G;
  _for(i, 1, N) G.push_back(i);
  solve(G, -1);
}

int main() {
  while (_ri1(N) == 1 && N) {
    _for(i, 0, N) _for(j, 0, N) _ri1(A[i][j]);
    solve();
    sort(begin(D), end(D));
    _for(i, 0, D.size()) printf("%d%c", D[i], i < D.size() - 1 ? ' ' : '\n');
  }
  return 0;
}
// 20226774 1667 Network Mess Accepted C++11 0.000 2017-10-23 02:35:52
