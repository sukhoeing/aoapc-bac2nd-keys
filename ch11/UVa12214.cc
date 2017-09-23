// Rent a Car, UVa12433
// 陈锋
#include<cassert>
#include<cctype>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<functional>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<queue>
#include<set>
using namespace std;

int readint(){ int x; scanf("%d", &x); return x; }

typedef long long Int64;

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

	bool BellmanFord(int s, int t, int &flow, Int64& ans) {
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
		ans += (Int64)d[t] * (Int64)a[t];
		int u = t;
		while (u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return true;
	}

	// 需要保证初始网络中没有负权圈
	Int64 Mincost(int s, int t, int& flow) {
		Int64 ans = 0;
		flow = 0;
		while (BellmanFord(s, t, flow, ans));
		return ans;
	}
};
MCMF<SZ> solver;
int N, C, R, S, T, M[MAXN], Gid[MAXN], Qid[MAXN];
void initId() {
	int _id = 0;
	S = _id++;
	for(int i = 0; i < N; i++) Gid[i] = _id++;
    for(int i = 0; i < N; i++) Qid[i] = _id++;
    T = _id++;
	solver.init(_id + 1);
}

int main()
{
	int K = readint();
	for (int t = 1; t <= K; t++) {
		scanf("%d%d%d", &N, &C, &R);
		initId();

		for (int i = 0; i < N; i++) {
			int r = readint(); // 其中第i天需要rj辆车
            M[i] = r; // 第i天的需求
			solver.AddEdge(Gid[i], T, r, 0);
            solver.AddEdge(S, Qid[i], r, 0);
			if(i) solver.AddEdge(Gid[i-1], Gid[i], INF, 0);
		}

		for (int i = 0; i < C; i++) {
			int c = readint(), p = readint();
            solver.AddEdge(S, Gid[0], c, p);
		}

		for (int i = 0; i < R; i++) {
			int d = readint(), s = readint();
			for (int j = 0; j + d + 1 < N; j++)
                solver.AddEdge(Qid[j], Gid[j+d+1], INF, s);
		}
        
		int flow;
		Int64 ans = solver.Mincost(S, T, flow);
#ifndef ONLINE_JUDGE
		// printf("%d, %lld\n", flow, ans);
#endif

		bool valid = true;
        const vector<int>& es = solver.G[T];
        for (int i = 0; i < es.size(); i++) {
            const Edge& e = solver.edges[es[i]];
            if(e.flow + M[i] != 0) valid = false;
        }
		if (!valid)  printf("Case %d: impossible\n", t);
		else printf("Case %d: %lld\n", t, ans);
	}
	return 0;
}

// 14350392	12433	Rent a Car	Accepted	C++	0.283	2014-10-14 15:30:57