// UVa1660 - Cable TV Network, ACM/ICPC World Finals 2000
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
struct Edge { int from, to, cap, flow; };
bool operator < (const Edge& a, const Edge& b) 
{ return a.from < b.from || (a.from == b.from && a.to < b.to); }

template<int MAXSIZE, int INF>
struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;    // 边数的两倍
  vector<int> G[MAXSIZE];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[MAXSIZE];         // BFS使用
  int d[MAXSIZE];           // 从起点到i的距离
  int cur[MAXSIZE];        // 当前弧指针

  void ClearAll(int n) {
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void ClearFlow() {
    for(int i = 0; i < edges.size(); i++) edges[i].flow = 0;    
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    d[s] = 0;
    while(!Q.empty()) {
      int x = Q.front(); Q.pop();
      for(int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if(!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int& i = cur[x]; i < G[x].size(); i++) {
      Edge& e = edges[G[x][i]];
      if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i]^1].flow -= f;
        flow += f;
        a -= f;
        if(a == 0) break;
      }
    }
    return flow;
  }

  int Maxflow(int s, int t) {
    this->s = s; this->t = t;
    int flow = 0;
    while(BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }

  vector<int> Mincut() { // call this after maxflow
    vector<int> ans;
    for(int i = 0; i < edges.size(); i++) {
      Edge& e = edges[i];
      if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
    }
    return ans;
  }
};

const int maxn = 50+1, maxm = maxn*maxn, INF = 1000000;
int n, m;
Edge edges[maxm];

Dinic<2*maxn, INF> d;

int solve(int u, int v) {
    d.ClearAll(2*n);
    _for(i, 0, n) d.AddEdge(i, i+n, 1);
    _for(i, 0, m) {
        const Edge& e = edges[i];
        d.AddEdge(e.from + n, e.to, INF);
        d.AddEdge(e.to + n, e.from, INF);
    }
    int s = u+n, t=v;
    return d.Maxflow(s, t);
}

int main(){
    char buf[4];
    while(scanf("%d%d", &n, &m) == 2) {
        int u,v;
        _for(i, 0, m) {
            Edge& e = edges[i];
            scanf(" (%d,%d)", &(e.from), &(e.to));
        }

        int ans = INF;
        _for(i, 0, n) _for(j, 0, n)
            if(i != j) 
              ans = min(ans, solve(i,j));
        
        if(ans == INF) ans = n;
        printf("%d\n", ans);
    }
    return 0;
}

// 14805855	1660	Cable TV Network	Accepted	C++	0.146	2015-01-15 10:14:00