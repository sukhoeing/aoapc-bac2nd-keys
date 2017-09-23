// Rent a Car, UVa12433
// 陈锋
#include <cassert>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

int readint(){ int x; scanf("%d", &x); return x; }

typedef long long LL;
const int MAXN = 50 + 2, INF = 65536, SZ = MAXN * (MAXN + 5);
struct Edge {
	int from, to, cap, flow, cost;
	Edge(int u, int v, int c, int f, int co) : from(u), to(v), cap(c), flow(f), cost(co){}
};

template<int MAXSIZE>
struct MCMF {
	int n, m;
	vector<Edge> edges;
	vector<int> G[MAXSIZE];
	bool inq[MAXSIZE];         // 是否在队列中
	int d[MAXSIZE];           // Bellman-Ford
	int p[MAXSIZE];           // 上一条弧
	int a[MAXSIZE];           // 可改进量

	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap, int cost) {
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	bool BellmanFord(int s, int t, int &flow, LL& ans) {
		fill_n(d, n, INF);
		fill_n(inq, n, false);
		d[s] = 0; inq[s] = true; p[s] = 0; a[s] = INF;

		queue<int> Q;
		Q.push(s);
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			inq[u] = false;
			for (int i = 0; i < G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
					d[e.to] = d[u] + e.cost;
					p[e.to] = G[u][i];
					a[e.to] = min(a[u], e.cap - e.flow);
					if (!inq[e.to]) { Q.push(e.to); inq[e.to] = true; }
				}
			}
		}
		if (d[t] == INF) return false; //s-t 不连通，失败退出  
		flow += a[t];
		ans += (LL)d[t] * (LL)a[t];
		int u = t;
		while (u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return true;
	}

	// 需要保证初始网络中没有负权圈
	LL Mincost(int s, int t, int& flow) {
		LL ans = 0;
		flow = 0;
		while (BellmanFord(s, t, flow, ans));
		return ans;
	}
};
MCMF<SZ> solver;
int N, C, R, S, T, M[MAXN], Gid[MAXN], Qid[MAXN];
void initId(){
	int _id = 0; S = _id++;
	_for(i, 0, N)Gid[i] = _id++;
    _for(i, 0, N)Qid[i] = _id++;
    T = _id++;
	solver.init(_id + 1);
}

int main(){
	int K = readint(), r, c, p, d, s;
	_rep(t, 1, K){
		scanf("%d%d%d", &N, &C, &R);
		initId();

		_for(i, 0, N){
            M[i] = r = readint(); // 其中第i天需要ri辆车
			solver.AddEdge(Gid[i], T, r, 0), solver.AddEdge(S, Qid[i], r, 0);
			if(i) solver.AddEdge(Gid[i-1], Gid[i], INF, 0);
		}

		_for(i, 0, C) scanf("%d%d", &c, &p), solver.AddEdge(S, Gid[0], c, p);

		_for(i, 0, R) {
			scanf("%d%d", &d, &s);
			for (int j = 0; j + d + 1 < N; j++)
                solver.AddEdge(Qid[j], Gid[j+d+1], INF, s);
		}
        
		int flow;
		LL ans = solver.Mincost(S, T, flow);
		bool valid = true;
        const vector<int>& es = solver.G[T];
        _for(i, 0, es.size())
            if(solver.edges[es[i]].flow + M[i] != 0) { valid = false; break; }
		if (!valid)  printf("Case %d: impossible\n", t);
		else printf("Case %d: %lld\n", t, ans);
	}
	return 0;
}

// 16914801	12433	Rent a Car	Accepted	C++11	0.119	2016-02-27 13:52:20