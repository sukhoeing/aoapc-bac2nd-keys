// Flooded! ACM/ICPC World Finals 1999, UVa815
// 陈锋 C++11
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cstring>
#include <vector>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

int main(){
    int m, n, H[1024]; double wl, k, v;
    for(int r = 1; scanf("%d%d", &m, &n) == 2 && m && n; r++){
        n *= m;
        _for(i, 0, n) scanf("%d", &(H[i]));
        H[n] = INT_MAX;
        sort(H, H+n+1);
        scanf("%lf", &v); v /= 100;
        _rep(i, 1, n){ // wl: 把0~i-1个格子都淹没的话形成的高度
            v += H[i-1], wl = v/i;
            if(wl < H[i]){ k = i; break; } // 淹没不了格子i
        }

        printf("Region %d\nWater level is %.2lf meters.\n", r, wl);
        printf("%.2lf percent of the region is under water.\n\n", k*100/n);
    }
    return 0;
}
/* 13538408	815	Flooded!	Accepted	C++	0.039	2014-04-23 15:12:46 */