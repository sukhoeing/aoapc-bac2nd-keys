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

const int maxn = 500 + 10;
int A[maxn], B[maxn], pos[maxn];
int N;

void init() {
    Set(A, 0);
    Set(B, 0);
    Set(pos, 0);
}

void copy(int st, int step) {
    _for(i, 0, N) {
        B[i] = A[(st + step * i + N) % N];
        pos[B[i]] = i;
    }
}

int solve() {
    int ans = 0;
    _for(i, 0, N) {
        int p = pos[i];
        if(p == i) continue;
        pos[B[i]] = p;
        pos[i] = i;
        swap(B[i], B[p]);
        ans++;
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &N) == 1 && N) {
        init();

        _for(i, 0, N) {
            scanf("%d", &A[i]);
            A[i]--;
        }

        int res = maxn;
        _for(i, 0, N) {
            copy(i, 1);
            res = min(res, solve());
            copy(i, -1);
            res = min(res, solve());
        }
        printf("%d\n", res);
    }
}