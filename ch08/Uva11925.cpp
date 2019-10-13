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

vector<int> cmd, A;
int n;

void init() {
    cmd.clear();
    A.clear();
}

bool ok() {
    _for(i, 0, n) {
        if(A[i] != i + 1) return false;
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d", &n) == 1 && n) {
        init();

        int x;
        _for(i, 0, n) {
            scanf("%d", &x);
            A.push_back(x);
        }
        // input finished, then solve

        if(n == 1) {
            puts("");
            continue;
        }

        while(true) {
            if(ok()) break;

            if(A[0] > A[1] && A[0] != n) {
                swap(A[0], A[1]);
                cmd.push_back(1);
            } else {
                A.insert(A.begin(), A[n - 1]);
                A.resize(n);
                cmd.push_back(2);
            }
        }

        _forDown(i, cmd.size() - 1, 0) printf("%d", cmd[i]);
        printf("\n");
    }
}