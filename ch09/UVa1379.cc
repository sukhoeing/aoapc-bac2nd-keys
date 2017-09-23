// Pitcher Rotation, ACM/ICPC Kaosiung 2006, UVa1379
// 陈锋
#include <cassert>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXN = 104, MAXG = 200 + 10 + 4;
struct WinP {
    int p, pit; // 胜率，以及选手编号
    WinP() : p(0), pit(0) {}
    bool operator<(const WinP& s) const { return p > s.p; }
};

WinP winps[MAXN][MAXN];
int N, M, numG, G[MAXG], DP[2][6][6][6][6]; // 滚动数组
// 面对对手op胜率第i高的选手
inline int getPi(int op, int i) { return winps[op][i].pit; }

double solve() {
    memset(DP, 0, sizeof(DP));
    int ans = 0, cur = 0;
    _rep(i, 1, numG) { // 第i天
        int prev = cur, now = 1 - cur;
        cur = 1 - cur;
        memset(DP[now], 0, sizeof(DP[now]));

        int op = G[i]; // 第i天面对的对手
        if (op == 0) { // 当天没有比赛
            _rep(p1, 0, 5) _rep(p2, 0, 5) _rep(p3, 0, 5) _rep(p4, 0, 5) {
                int& d = DP[now][0][p1][p2][p3]; // 当天不用派人上场
                d = max(d, DP[prev][p1][p2][p3][p4]); // 用前一天的数据更新今天
                ans = max(d, ans);
            }
            continue;
        }

        _rep(p0, 1, 5) { // 今天选排第p0的上场
            int opi = getPi(op, p0); // 选上的人是谁？
            _rep(p1, 0, 5) {
                if (i > 1 && getPi(G[i-1], p1) == opi) continue;
                _rep(p2, 0, 5) {
                    if (i > 2 && getPi(G[i-2], p2) == opi) continue;
                    _rep(p3, 0, 5) {
                        if (i > 3 && getPi(G[i-3], p3) == opi) continue;
                        _rep(p4, 0, 5) {
                            if (i > 4 && getPi(G[i-4], p4) == opi) continue;
                            int& d = DP[now][p0][p1][p2][p3];
                            d = max(d, DP[prev][p1][p2][p3][p4] + winps[op][p0].p);
                            ans = max(d, ans);
                        }
                    }
                }
            }
        }
    }

    double d = ans * .01;
    return d;
}

int main() {
    int T; scanf("%d",&T);
    while (T--) {
        scanf("%d%d%d", &N, &M, &numG); numG += 10;
        _rep(i, 1, M){
            _rep(j, 1, N){
                scanf("%d", &(winps[i][j].p));
                winps[i][j].pit = j;
            }
            sort(winps[i] + 1, winps[i] + N + 1);
        }

        G[0] = 0;
        _rep(i, 1, numG) scanf("%d", &(G[i]));

        double ans = solve();
        printf("%.2lf\n", ans);
    }
    return 0;
}
// 15083259 1379    Pitcher Rotation    Accepted    C++ 0.026   2015-03-05 00:34:11