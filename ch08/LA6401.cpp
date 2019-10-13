#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <assert.h>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)
#define lowbit(i) (i & (-i))

const int maxn = 500 + 5;
const int inf = 0x3f;

int a, b, m, n;
int d[maxn][maxn];
int dep[maxn];
llong ans, v, s;

void init() {
    ans = 0;
}

void initdep() {
    Set(dep, inf);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d%d%d", &a, &b, &m, &n) == 4) {
        init();

        _for(x, 0, m) _for(y, 0, n) scanf("%d", &d[x][y]);

        if(b > a) swap(a, b);
        // always a >= b

        _for(x, 0, m) _rep(y, 0, n) {
            initdep();

            _for(xx, x, m) {
                int aa = xx - x + 1;
                if(aa > a) break;

                // dep[y] = min(dep[y], d[xx][y]);
                // debug(dep[y]);
                _for(yy, y, n) {
                    int bb = yy - y + 1;
                    if(bb > a || min(bb, aa) > b) break;

                    // then we solve the problem
                    dep[yy] = min(dep[yy], d[xx][yy]);
                    if(yy) dep[yy] = min(dep[yy - 1], dep[yy]);

                    s = aa * bb * 1LL;
                    v = aa * bb * dep[yy] * 1LL;

                    int rem = (v % (m * n - s) == 0) ? 1 : 0;
                    ans = max(ans, 1LL * (dep[yy] + (v / (m * n - s)) - rem) * s);
                }
            }
        }
        printf("%lld\n", ans);
    }
}