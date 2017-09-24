// UVa11196 - Birthday Cake
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;
const int INF = 1000000000;
int N, M, ans;
/* k: 从上到下第k层, V: 用剩下的蛋糕体积, 
    S: 已经用的蛋糕面积, 
    R: 当前层的半径上限(<=), 
    H: 当前层的高度上限(<=) */
void dfs(int k, int V, int S, int R, int H) {
    if(k == 0) {
        // assert(V == 0);
        ans = min(ans, S);
        return; 
    }
    // V: ∑ ri^2 * hi, S: (∑ 2ri * hi) + r1^2
    if(k*k*(k+1)*(k+1)/4 <= V && S+k*(k+1)*(2*k+1)/3 < ans)
        for(int r = R; r >= k && S + 2*V/r < ans; r--)
            for(int h = min(V/(r*r), H); h >= k && r*r*(h+h-k+1)*k/2 >= V; h--)
                dfs(k-1, V-r*r*h, S + 2*r*h + (k==M? r*r : 0), r-1,h-1);
}

int main(){    
    for(int t = 1; scanf("%d%d", &N, &M) == 2 && N && M; t++){
        ans = INF;
        dfs(M, N, 0, (int)ceil(sqrt(N)), INF);
        if(ans == INF) ans = 0;
        printf("Case %d: %d\n", t, ans);
    }
    return 0;
}
// 17152921	11196	Birthday Cake	Accepted	C++11	0.020	2016-04-06 03:04:57