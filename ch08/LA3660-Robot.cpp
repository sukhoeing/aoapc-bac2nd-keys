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

llong solve(llong n, llong m, llong cntn, llong cnts, llong cntw, llong cnte) {
    llong ans = 0;
    if(cnts > cntn) swap(cnts, cntn);
    if(cnte > cntw) swap(cnte, cntw);

    if(cntn) {
        ans += n * m;
        n--;
        cntn -= cnts;

        if(cntn == 0) ans += n * m * (2 * cnts - 1);
        else {
            ans += n * m * 2 * cnts;
            cntn--;
        }

        cnts = 0;
    }

    if(cntw) {
        cntw -= cnte;
        if(cntw == 0) cnte = cnte * 2 - 1;
        else {
            cnte = cnte * 2;
            cntw--;
        }

        while (m + (m - 1) * cnte <= n && cntn) {
            ans += n * m;
            cntn--;
            n--;
        }

        ans += n * m;
        m--;

        ans += n * m * cnte;
        cnte = 0;
    }

    while (n * m > 0 && cntw + cntn > 0) {
        ans += n * m;
        if((n > m && cntn) || cntw == 0) {
            cntn--;
            n--;
        }
        else {
            cntw--;
            m--;
        }
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    llong n, m, cntn, cnts, cntw, cnte;
    int kase = 0;

    while (scanf("%lld%lld", &n, &m) && n && m) {
        scanf("%lld%lld%lld%lld", &cntn, &cnts, &cntw, &cnte);
        // then solve the problem

        llong res = max(solve(n, m, cntn, cnts, cntw, cnte), solve(m, n, cnte, cntw, cntn, cnts));
        printf("Case %d: %lld\n", ++kase, res);
    }
}