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

const int maxn = 300 + 5;
int n = -1, k = -1;
int T;

vector<int> G[maxn], invG[maxn];
int indeg[maxn];


bool check(int n) {
    _for(u, 0, n) {
        fill_n(indeg, n, 0);

        for(auto s : invG[u]) {
            for(auto x : G[s]) indeg[x]++;
        }

        _for(v, 0, n) {
            if(v == u) continue;
            if(indeg[v] == 0 || indeg[v] == invG[u].size()) continue;
            return false;
        }
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &T);

    _rep(kase, 1, T) {
        scanf("%d%d", &n, &k);
        assert(n != -1 && k != -1);
        _for(i, 0, n) G[i].clear(), invG[i].clear();

        _for(i, 0, k) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            invG[v].push_back(u);
        }

        // then solve the problem

        bool ok = check(n);

        printf("Case #%d: %s\n", kase, (ok ? "Yes" : "No"));
    }
}