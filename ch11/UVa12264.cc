// UVa12264 Risk
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
#define _rf1(x) scanf("%lf", &(x))
#define _rf2(x, y) scanf("%lf%lf", &(x), &(y))

typedef long long LL;

struct Edge {
  int from, to, cap, flow;
};
bool operator<(const Edge& a, const Edge& b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}

template <int MAXSIZE, int INF>
struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;  // 边数的两倍
  vector<int> G[MAXSIZE];  // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[MAXSIZE];  // BFS使用
  int d[MAXSIZE];     // 从起点到i的距离
  int cur[MAXSIZE];   // 当前弧指针

  void init(int n) {
    for (int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void ClearFlow() {
    for (int i = 0; i < edges.size(); i++) edges[i].flow = 0;
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    d[s] = 0;
    while (!Q.empty()) {
      int x = Q.front();
      Q.pop();
      for (const auto& ei : G[x]) {
        auto e = edges[ei];
        if (!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if (x == t || a == 0) return a;
    int flow = 0, f;
    for (int& i = cur[x]; i < G[x].size(); i++) {
      Edge& e = edges[G[x][i]];
      if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a == 0) break;
      }
    }
    return flow;
  }

  int Maxflow(int s, int t) {
    this->s = s;
    this->t = t;
    int flow = 0;
    while (BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }

  vector<int> Mincut() {  // call this after maxflow
    vector<int> ans;
    for (int i = 0; i < edges.size(); i++) {
      Edge& e = edges[i];
      if (vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
    }
    return ans;
  }
};

const int MAXN = 100 + 4, INF = 0x7f7f7f7f;
int N, A[MAXN];
char Map[MAXN][MAXN];
Dinic<2 * MAXN, INF> solver;

bool isOK(const int m) {
  solver.init(N * 2 + 4);
  int S = 2 * N, T = S + 1, sumF = 0;
  _for(i, 0, N) if (A[i]) {
    solver.AddEdge(i, i + N, INF), solver.AddEdge(S, i, A[i]);
    int f = 1;
    _for(j, 0, N) if (i != j && Map[i][j] == 'Y') {
      if (A[j])
        solver.AddEdge(i, j + N, INF);
      else
        f = m;
    }
    solver.AddEdge(i + N, T, f), sumF += f;
  }
  return solver.Maxflow(S, T) == sumF;  // Full Flow
}

int main() {
  int T;
  _ri1(T);
  while (_ri1(N) == 1) {
    int L = 0, R = 10;
    _for(i, 0, N) _ri1(A[i]), R += A[i];
    _for(i, 0, N) scanf("%s", Map[i]);
    while (L + 1 < R) {  // L is always ok
      int M = L + (R - L) / 2;
      if (isOK(M)) L = M;
      else R = M;
    }
    printf("%d\n", L);
  }

  return 0;
}
// 20222567 12264 Risk Accepted C++11 0.010 2017-10-22 08:31:55