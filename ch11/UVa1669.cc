// Holiday's Accomodation, ACM/ICPC Chengdu 2011, UVa1669
// 陈锋
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
int readint() { int x; scanf("%d", &x); return x; }
typedef long long LL;
const int MAXN = 100000 + 4;
struct Edge{ int from, to, weight; };
int N, Pa[MAXN], D[MAXN]; // Pa[u]是u的父节点编号，D[u]表示u为根节点的子树节点个数(包括u)
vector<Edge> edges;
vector<int> G[MAXN];

void addEdge(int from, int to, int weight) {
	G[from].push_back(edges.size());
	edges.push_back(Edge{from, to, weight});
}

void dfs(int u, int pa){ // 构造树结构，计算子树上的结点个数
	int& d = D[u];
	d = 1, Pa[u] = pa;
	for(auto a : G[u]){
		const Edge& e = edges[a]; assert(e.from == u);
		if (e.to == pa) continue;
		dfs(e.to, u);
		d += D[e.to];
	}
}

int main(){    
    int T = readint(), X, Y, Z;
    _rep(t, 1, T){
        N = readint();
		edges.clear();
		fill_n(Pa, N + 1, -1);
        _rep(i, 0, N) G[i].clear();
        _for(i, 0, N-1) scanf("%d%d%d", &X, &Y, &Z), addEdge(X,Y,Z), addEdge(Y,X,Z);
		dfs(1, -1);
        
        LL ans = 0;
		for(int i = 0; i < edges.size(); i += 2){
			const Edge& e = edges[i];
			int x = e.from, y = e.to;
			if(Pa[x] != y) swap(x, y); assert(Pa[x] == y); // y是x的父结点
            ans += 2*e.weight*(min(D[x], N - D[x]));
		}
        printf("Case #%d: %lld\n", t, ans);
    }
    return 0;
}
// 14097979	1669	Holiday's Accommodatio	Accepted	C++	0.828	2014-08-26 13:10:21