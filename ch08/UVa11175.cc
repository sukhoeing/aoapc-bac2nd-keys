// UVa11175 - From D to E and Back
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#define _for(i,a,b) for(int i = (a); i<(b); ++i)
using namespace std;
const int maxm = 300 + 4;
vector<int> G[maxm], InvG[maxm];
int To[maxm];

bool check(int m) {
    _for(u, 0, m) {
        fill_n(To, m, 0);
        for(auto v : InvG[u]) // 每一个有边出发到u的点
            for(auto x : G[v]) To[x]++; // 从v出发到达的每个节点计数加1
        
        _for(v, 0, m) {
            if(To[v] == 0 || To[v] == InvG[u].size()) continue;
            return false;
        }
    }
    
    return true;
}

int main(){    
    int N, m, k, x, y;
    scanf("%d", &N);
    for(int t = 1; t <= N; t++) {
        scanf("%d%d", &m, &k);
        _for(i, 0, m) G[i].clear(), InvG[i].clear();
        _for(i, 0, k) { scanf("%d%d", &x, &y); G[x].push_back(y); InvG[y].push_back(x); }
        bool valid = check(m);
        printf("Case #%d: %s\n", t, (valid ? "Yes" : "No"));
    }
    return 0;
}
// 14737643	11175	From D to E and Back	Accepted	C++	0.212	2014-12-29 13:25:35