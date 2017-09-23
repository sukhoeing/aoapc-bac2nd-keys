// UVa1629 Cake Slicing, ACM/ICPC Nanjing 2007
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const int MAXN = 20 + 1;
int n, m, k, D[MAXN][MAXN][MAXN][MAXN], Chery[MAXN][MAXN][MAXN][MAXN];

void Check(int r, int c, int width, int height) {
    assert(width >= 1);
    assert(height >= 1);
    assert(0 <= r && r < n);
    assert(0 <= c && c < m);
    assert(r + height <= n);
    assert(c + width <= m);
}

// 区域[r,c,width,height]内的樱桃个数
int CR_Cnt(int r, int c, int width, int height){
    int& ans = Chery[r][c][width][height];
    if(ans != -1) return ans;
    
    if(width > 1)
        return ans = CR_Cnt(r, c, 1, height) + CR_Cnt(r, c+1, width-1, height);
    return ans = CR_Cnt(r, c, 1, 1) + CR_Cnt(r+1, c, 1, height-1);
}

int dp(int r, int c, const int W, const int H) {
    int &ans = D[r][c][W][H];
    if(ans != -1) return ans;
    if(CR_Cnt(r,c,W,H) == 1) return ans = 0;
    
    auto updateAns = [&](int a){
        if(ans == -1) ans = a;
        else ans = min(ans, a);
    };
    // 遍历横着切
    _for(h, 1, H) // h上半部分的高度
        if(CR_Cnt(r,c,W,h) >= 1 && CR_Cnt(r+h,c,W, H-h) >= 1)
            updateAns(W + dp(r+h, c, W, H-h) + dp(r, c, W, h));
    
    // 遍历竖着切
    _for(w, 1, W) // w左边的宽度
        if(CR_Cnt(r,c,w,H) >= 1 && CR_Cnt(r,c+w,W-w,H) >= 1)
            updateAns(H + dp(r,c,w,H) + dp(r,c+w,W-w,H));
    
    return ans;
}

int main(){
    for(int kase = 1,r,c; scanf("%d%d%d", &n, &m, &k) == 3; kase++){
        memset(D, -1, sizeof(D));
        memset(Chery, -1, sizeof(D));
        _for(i, 0, n) _for(j, 0, m) Chery[i][j][1][1] = 0;
        _for(i, 0, k) {
            scanf("%d%d", &r, &c);
            Chery[r-1][c-1][1][1] = 1;
        }
        
        printf("Case %d: %d\n", kase, dp(0,0,m,n));
    }    
    return 0;
}

// 14804649	1629	Cake slicing	Accepted	C++	2.112	2015-01-15 04:40:34