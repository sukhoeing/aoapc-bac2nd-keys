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

const int maxn = 1000000 + 5;
int last[maxn], ans[maxn];
int rain[maxn];
int n, m;

void init() {
    Set(last, 0);
    Set(ans, 0);
    Set(rain, 0);
}

bool solve() {
    set<int> noRain;
    bool ok = true;

    _rep(i, 1, m) {
        if(rain[i] == 0) {
            noRain.insert(i);
            continue;
        }

        ans[i] = -1;
        auto day = noRain.lower_bound(last[rain[i]]);

        if(day == noRain.end()) {
            ok = false;
            break;
        }

        ans[*day] = rain[i];
        last[rain[i]] = i;
        noRain.erase(*day);
    }
    return ok;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();
        scanf("%d%d", &n, &m);
        _rep(i, 1, m) scanf("%d", &rain[i]);

        // then solve the problem
        bool ok = solve();
        if(!ok) printf("NO\n");
        else {
            printf("YES\n");
            bool first = 1;

            _rep(i, 1, m) {
                if(ans[i] == -1) continue;

                if(first) first = 0;
                else printf(" ");

                printf("%d", ans[i]);
            }
            puts("");
        }
    }
}