// Telescope, ACM/ICPC Tsukuba 2000, UVa1543
// 陈锋
#include <cassert>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <climits>
#include <iomanip>
#include <vector>
#include <functional>
#include <algorithm>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

const int MAXN = 50;
const double PI = acos(-1);
double dist(double p1, double p2) { // p1,p2两个角度对应的点的直线距离
    double a = fabs(p2 - p1); // assert(a < 1);
    if (a > 0.5) a = 1 - a;
    return 2 * sin(a * PI);
}
// 三条边长度为a,b,c的三角形面积
double calArea(double a, double b, double c) {
    double x = (a + b + c) / 2;
    return sqrt(x * (x - a) * (x - b) * (x - c));
}

int n, m;
double P[MAXN], d[MAXN][MAXN], area[MAXN][MAXN][MAXN], DP[MAXN][MAXN][MAXN];
// dp[i][j][k]表示从第i个点到第j个点选k个点的最大面积(i，j必须选)
double dp() {
    memset(DP, 0, sizeof(DP));
    _rep(k, 3, m)
        _for(i, 0, n) _for(x, i+1, n) _for(j, x+1, n) // x in [i, j]
            DP[i][j][k] = max(DP[i][j][k], DP[i][x][k-1] + area[i][x][j]);

    double ans = 0;
    _for(i, 0, n) _for(j, i+1, n) ans = max(ans, DP[i][j][m]);
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2 && n) {
        _for(i, 0, n) scanf("%lf", &(P[i]));
        // 所有点与点之间的距离
        _for(i, 0, n) _for(j, i+1, n) d[i][j] = d[j][i] = dist(P[i], P[j]);
        // 计算所有三角形面积
        _for(i, 0, n) _for(j, i + 1, n) _for(k, j + 1, n) { 
            area[i][j][k] = area[i][k][j] = 
            area[j][i][k] = area[j][k][i] = 
            area[k][i][j] = area[k][j][i] = 
            calArea(d[i][j], d[j][k], d[k][i]);
        }
        printf("%.6lf\n", dp());
    }
    return 0;
}

// 13725657 1543    Telescope   Accepted    C++ 0.089   2014-06-07 06:24:16