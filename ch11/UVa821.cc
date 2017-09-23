// UVa821 Page Hopping, ACM/ICPC World Finals 2000
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXN = 100 + 5, INF = MAXN * MAXN;

int d[MAXN][MAXN];
int main(){          
    int n, a, b, t = 1;
    while(true) {        
        bool valid = false;
        _for(i, 1, MAXN) _for(j, 1, MAXN) d[i][j] = INF;
        n = 1;
        while(true) {
            scanf("%d%d", &a, &b);
            if(!valid) valid = a && b;
            n = max(n, max(a,b));
            if(!a) break;
            d[a][b] = 1;
        }
        if(!valid) break;
        
        _rep(k, 1, n) _rep(i, 1, n) _rep(j, 1, n) 
            d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
        
        int sum = 0, cnt = 0;
        _rep(i, 1, n) _rep(j, 1, n)
            if(i != j && d[i][j] < INF) sum += d[i][j], cnt++;

        double ans = sum;
        if(cnt) ans /= cnt;
        printf("Case %d: average length between pages = %.3lf clicks\n", t++, ans);
    }
    return 0;
}
// 14805849	821	Page Hopping	Accepted	C++	0.159	2015-01-15 10:12:51