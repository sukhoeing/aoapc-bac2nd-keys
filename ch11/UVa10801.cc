// UVa10801 Lift Hopping
// 陈锋
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
const int MAXN = 5, MAXK = 100, MAXP = MAXN * MAXK;
const int INF = 100000 + 10;
struct Edge {
  int from, to, dist;
};
struct HeapNode {
  int d, u;
  bool operator<(const HeapNode &rhs) const { return d > rhs.d; }
};
template <int SZ> 
struct Dijkstra {
  int n, m, d[SZ], p[SZ];
  vector<Edge> edges;
  vector<int> G[SZ];
  bool done[SZ];

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; i++)
      G[i].clear();
    edges.clear(), m = 0;
  }

  void addEdge(int from, int to, int dist) {
    edges.push_back((Edge){from, to, dist});
    m = edges.size(), G[from].push_back(m - 1);
  }

  void dijkstra(int s) {
    priority_queue<HeapNode> Q;
    fill_n(d, n, INF);
    d[s] = 0, fill_n(done, n, false), Q.push((HeapNode){0, s});
    while (!Q.empty()) {
      HeapNode x = Q.top();
      Q.pop();
      int u = x.u;
      if (done[u])
        continue;
      done[u] = true;
      const vector<int> &adj = G[u];
      for (size_t i = 0; i < adj.size(); i++) {
        Edge &e = edges[adj[i]];
        int v = e.to;
        if (d[v] > d[u] + e.dist)
          d[v] = d[u] + e.dist, p[v] = adj[i], Q.push((HeapNode){d[v], v});
      }
    }
  }
};

Dijkstra<MAXP + 1> solver;
int n, k, T[MAXN];
vector<int> Level[MAXK];
char buf[512];
int solve() {
  solver.init(n * MAXK + 1);
  for (int i = 0; i < n; i++)
    cin >> T[i];
  cin.ignore();
  string s;
  for (int e = 0; e < n; e++) {
    getline(cin, s);
    istringstream iss(s, istringstream::in);
    bool first = true;
    int l1, l; // 上一层，当前层
    while (iss >> l) {
      if (first)
        first = false;
      else {
        int v = MAXK * e + l1, v2 = MAXK * e + l, dist = (l - l1) * T[e];
        solver.addEdge(v, v2, dist), solver.addEdge(v2, v, dist);
      }
      Level[l].push_back(e);
      l1 = l;
    }
  }
  for (int i = 0; i < MAXK; i++) {
    vector<int> &li = Level[i];
    for (size_t j = 0; j < li.size(); j++) {
      for (size_t m = j + 1; m < li.size(); m++) {
        int e1 = li[j], e2 = li[m], v1 = e1 * MAXK + i, v2 = e2 * MAXK + i;
        solver.addEdge(v1, v2, 60), solver.addEdge(v2, v1, 60);
      }
    }
  }

  vector<int> &L0 = Level[0], &Lk = Level[k];
  if (L0.empty() || Lk.empty()) return 0;
  int ans = INF;
  for(size_t i = 0; i < L0.size(); i++){
    solver.dijkstra(L0[i] * 100);
    for(size_t j = 0; j < Lk.size(); j++)
      ans = min(ans, solver.d[Lk[j] * 100 + k]);
  }
  return ans;
}

int main() {
  while (cin>>n>>k) {
    int ans = solve();
    if (ans != INF)
      printf("%d\n", ans);
    else
      puts("IMPOSSIBLE");
  }
  return 0;
}

// 14805862 10801 Lift Hopping  Accepted  C++ 0.039
// 2015-01-15 10:14:57
