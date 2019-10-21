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
int L, P;

struct Node {
    int pre, nxt;
};
Node nodes[maxn];

int twist[maxn];
int level[maxn];

void del(int x) {
    level[x] = 0;
    nodes[nodes[x].pre].nxt = nodes[x].nxt;
    nodes[nodes[x].nxt].pre = nodes[x].pre;
}

void init() {
    Set(twist, 0);
    Set(level, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    _rep(kase, 1, T) {
        init();
        scanf("%d%d", &L, &P);

        _for(i, 0, L) {
            nodes[i].pre = i - 1;
            nodes[i].nxt = i + 1;
        }
        nodes[0].pre = L - 1;
        nodes[L - 1].nxt = 0;

        _rep(i, 1, P) {
            int u, v;
            scanf("%d%d", &u, &v);
            // (u, v)
            twist[u] = v;
            twist[v] = u;

            level[u] = 1;
            level[v] = -1;
        }

        // then we solve the problem
        _for(i, 0, L) if(level[i] == 0) del(i);

        int idx = 0;
        while (P) {
            bool untie = false;
            while (level[idx] == 0) idx++;

            for(int i = nodes[idx].nxt; i != idx && untie == false; i = nodes[i].nxt) {
                int u = i, v = nodes[i].nxt;

                if(level[u] == level[v] && (nodes[twist[u]].nxt == twist[v] || nodes[twist[v]].nxt == twist[u])) {
                    del(u); del(v);
                    del(twist[u]); del(twist[v]);

                    P -= 2;
                    untie = true;
                }
                else if(twist[u] == v || twist[v] == u) {
                    del(u);
                    del(v);

                    P -= 1;
                    untie = true;
                }
            }

            if(untie == false) break;
        }

        printf("Case #%d: ", kase);
        if(P) printf("NO\n");
        else printf("YES\n");
    }

}