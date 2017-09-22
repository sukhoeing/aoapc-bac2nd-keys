// Firetruck, ACM/ICPC World Finals 1991, UVa208
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const int MAXN = 20 + 4;
int N, pa[MAXN];
set<int> G[MAXN];

int find_pa(int x) { return pa[x] == x ? x : (pa[x] = find_pa(pa[x])); }

ostream& operator<<(ostream& os, const vector<int>& s){
    bool first = true;
    for(const auto x : s){
        if(first) first = false; else os<<' ';
        os<<x;
    }
    return os;
}
// 搜索src -> dest的所有路径
void dfs(int src, int dest, vector<int>& path, vector<string>& paths) {
    path.push_back(src);
    if(src == dest) { // 搜到目标了
        stringstream os; os<<path;
        paths.push_back(os.str());
    } else {
        for(auto v : G[src]) { // 遍历所有的下一步节点
            if(find(path.begin(), path.end(), v) != path.end()) 
                continue; // 走出的路径上已经有v存在了
            dfs(v, dest, path, paths);
        }
    }
    path.pop_back();
}

int main(){
    for(int kase = 1,from,to; scanf("%d", &N)==1; kase++){
        _for(i, 0, MAXN) G[i].clear(), pa[i] = i;
        while(true) {
            scanf("%d%d", &from, &to);
            if(from == 0 || to == 0) break;
            G[from].insert(to), G[to].insert(from);
            int pf = find_pa(from), pt = find_pa(to);
            if(pf != pt) pa[pt] = pf;
        }
        
        vector<string> paths;
        vector<int> path;
        if(find_pa(1) == find_pa(N)) dfs(1, N, path, paths);
        printf("CASE %d:\n", kase);
        for(auto& p : paths) puts(p.c_str());
        printf("There are %lu routes from the firestation to streetcorner %d.\n", 
            paths.size(), N);
    }    
    return 0;
}

// 15037599	208	Firetruck	Accepted	C++	0.025	2015-02-25 09:47:26