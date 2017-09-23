// UVa10801 Lift Hopping
// 陈锋
#include <cassert>
#include <cstdio>
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
const int MAXN = 5, MAXK = 100, MAXP = MAXN*MAXK;
const int INF = 100000 + 10;

struct Edge{ int from, to, dist; };
struct HeapNode{
    int d, u;
    bool operator < (const HeapNode& rhs) const { return d > rhs.d; }
};
template<int MAXSIZE>
struct Dijkstra{
    int n, m, d[MAXSIZE], p[MAXSIZE];
    vector<Edge> edges;
    vector<int> G[MAXSIZE];
    bool done[MAXSIZE];
    
    void init(int n)
    {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
        m = 0;
    }
    
    void addEdge(int from, int to, int dist)
    {
        edges.push_back((Edge){from, to, dist});
        m = edges.size();        
        G[from].push_back(m - 1);
    }
    
    void dijkstra(int s)
    {
        priority_queue<HeapNode> Q;
        fill_n(d, n, INF);
        d[s] = 0;
        fill_n(done, n, false);
        Q.push((HeapNode){0, s});
        while(!Q.empty()) {
            HeapNode x = Q.top(); Q.pop();
            int u = x.u;
            if(done[u]) continue;
            done[u] = true;
            const vector<int>& adj = G[u];
            for(int i = 0; i < adj.size(); i++)
            {
                Edge& e = edges[adj[i]];
                int to = e.to;
                if(d[to] > d[u] + e.dist) {
                    d[to] = d[u] + e.dist;
                    p[to] = adj[i];
                    Q.push((HeapNode){d[to], to});
                }
            }
        }
    }
};

Dijkstra<MAXP+1> solver;
int n, k, T[MAXN];
vector<int> Level[MAXK];
char buf[512];
int readint() { int x; scanf("%d", &x); return x; }

int solve() {
    solver.init(n*MAXK+1);
    _for(i, 0, n) T[i] = readint();
    gets(buf);
    _for(e, 0, n){
        gets(buf);
        istringstream iss(string(buf), istringstream::in);
        bool first = true; 
        int l1, l; // 上一层，当前层
        while(iss>>l) { 
            if(first) first = false;
            else { 
                int v = MAXK*e + l1, v2= MAXK*e + l;
                int dist = (l-l1)*T[e];
                solver.addEdge(v,v2,dist);
                solver.addEdge(v2,v,dist);
                // printf("[%d,%d]-%d\n",v, v2, dist);
            }
            Level[l].push_back(e);
            l1 = l;
        }
    }

    _for(i, 0, MAXK) {
        vector<int>& li = Level[i];
        _for(j, 0, li.size()){
            _for(m, j+1, li.size()) {
                int e1 = li[j], e2 = li[m], v1 = e1*MAXK+i, v2 = e2*MAXK+i;
                solver.addEdge(v1,v2,60);
                solver.addEdge(v2,v1,60);
                // printf("[%d,%d]-%d\n",v1, v2, 60);
            }
        }
    }
    
    vector<int>& L0 = Level[0];
    vector<int>& Lk = Level[k];
    if(L0.empty() || Lk.empty()) return 0;
    
    int ans = INF;
    for(auto i : L0) {
        solver.dijkstra(i * 100);
        for(auto j : Lk) ans = min(ans, solver.d[j*100 + k]);
    }
    
    return ans;
}

int main(){
    while(scanf("%d %d\n", &n, &k) == 2) {
        int ans = solve();
        if(ans != INF) printf("%d\n", ans);
        else puts("IMPOSSIBLE");
    }    
    return 0;
}

// 14805862	10801	Lift Hopping	Accepted	C++	0.039	2015-01-15 10:14:57