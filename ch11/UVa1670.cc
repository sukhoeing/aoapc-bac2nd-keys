// Kingdom Roadmap, ACM/ICPC NEERC 2011, UVa1670
// 陈锋
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXN = 100000 + 4;
struct Edge { int from, to; };
struct Node {
    int id, deg, vis;
    vector<int> adj; // children;
    void init(int i) { id = i, deg = 0, adj.clear(); }
};
int n, root;
Node nodes[MAXN];
// 去掉u为节点的子树中的桥
void connect(int u, int pa, vector<int>& ls, vector<Edge>& edges) {
    const Node& nu = nodes[u];
    ls.clear();
    if(nu.deg == 1) { ls.push_back(u); return; }
    
    vector<int> lvs; // u的子节点的遗留节点
    for(auto v : nu.adj) {
        if(v == pa) continue;
        lvs.clear();
        connect(v, u, lvs, edges);
        if(ls.size() + lvs.size() > 2){
            assert(!ls.empty() && !lvs.empty());
            edges.push_back(Edge{ls.back(), lvs.back()});
            ls.pop_back(), lvs.pop_back();
        }
        for(auto& lv : lvs) ls.push_back(lv);
    }
}

void solve(vector<Edge>& edges) {
    edges.clear();
    vector<int> ls; // 悬着的点
    connect(root, 0, ls, edges);
    assert(ls.size() <= 2);

    if(ls.size() == 2) edges.push_back(Edge{ls[0], ls[1]});
    else edges.push_back(Edge{root, ls[0]});
}

int main(){    
    int u,v;
    vector<Edge> edges;
    while(scanf("%d", &n) == 1 && n){
        _rep(i,1,n) nodes[i].init(i);
        root = 0;
        _for(i, 0, n-1){
            scanf("%d%d", &u, &v);
            auto &nu = nodes[u], &nv = nodes[v];
            nu.adj.push_back(v), nv.adj.push_back(u);
            nu.deg++; nv.deg++;
            if(!root && nu.deg > 1) root = u;
            if(!root && nv.deg > 1) root = v;
        }

        edges.clear();
        if(n == 2) edges.push_back(Edge{1, 2});
        else solve(edges);
        
        printf("%lu\n", edges.size());
        for(auto e : edges) printf("%d %d\n", e.from, e.to);
    }
    
    return 0;
}
// 14102762	1670	Kingdom Roadmap	Accepted	C++	0.235	2014-08-27 13:28:27