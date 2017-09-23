// Conquer a New Region, ACM/ICPC Changchun 2012, UVa1664
// 陈锋
#include <cassert>
#include <cctype>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXN = 200000 + 4;
typedef long long LL;
struct Edge{ 
    int from, to, weight;
    bool operator<(const Edge& rhs) const { return weight > rhs.weight; }
};

Edge edges[MAXN];
LL WS[MAXN], Pa[MAXN], Cnt[MAXN]; // WS[i]表示以i为根节点的树的边权和
int main(){    
    int N;
    while(scanf("%d", &N) == 1 && N){
        _for(i, 1, N) {
            Edge& e = edges[i];
            scanf("%d%d%d", &(e.from), &(e.to), &(e.weight));
        }
        
        sort(edges + 1, edges + N);
        _rep(i, 1, N) Cnt[i] = 1, Pa[i] = i, WS[i] = 0;
        function<int(int)> find_pa = [&find_pa](int i){
            return Pa[i] == i ? i : (Pa[i] = find_pa(Pa[i]));
        };

        auto merge = [](int from, int to, LL v){ // 合并，更新容量和点集大小
            Pa[from] = to, Cnt[to] += Cnt[from], WS[to] = v;
        };
        
        LL ans = 0;
        _for(i, 1, N){
            const Edge& e = edges[i];
            int a = find_pa(e.from), b = find_pa(e.to);
            LL wb = WS[b] + Cnt[a]*e.weight, wa = WS[a] + Cnt[b]*e.weight;
            if(wb > wa) merge(a, b, wb); else merge(b, a, wa);
            ans = max(wa, wb);
        }

        printf("%lld\n", ans);
    }
    return 0;
}
// 1982256  6070    Conquer a New Region    Accepted    C++11   0.572   2016-07-07 07:58:12