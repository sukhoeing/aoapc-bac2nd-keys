//
//  main.cpp
//  UVA12558
//
//  Created by zhangmin chen on 2019/6/27.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

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

using namespace std;
typedef long long llong;
typedef set<string>::iterator ssii;

const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }

set<llong> vis;
llong v[maxn], ans[maxn];
int a, b, k;

void init() {
    vis.clear();
    Set(v, 0);
    Set(ans, -1);
}

llong gcd(llong a, llong b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool better(int d) {
    _forDown(i, d, 0) {
        if(v[i] != ans[i]) {
            return ans[i] == -1 || v[i] < ans[i];
        }
    }
    return false;
}

inline int getFrom(llong a, llong b) {
    return (int)(b / a + 1);
}

bool dfs(int d, int maxd, int from, llong a, llong b) {
    //
    if(d == maxd) {
        if(b % a) return false;
        if(vis.count(b / a)) return false;
        
        v[d] = b / a;
        if(better(d)) {
            memcpy(ans, v, sizeof(llong) * (d + 1));
        }
        return true;
    }
    
    bool ok = false;
    from = max(from, getFrom(a, b));
    
    _for(i, from, inf) {
        if(b * (maxd - d + 1) <= a * i) break;
        if(vis.count(i)) continue;
        v[d] = i;
        
        llong a2 = i * a - b;
        llong b2 = i * b;
        llong g = gcd(a2, b2);
        
        // I made a bug here:
        if(dfs(d+1, maxd, i+1, a2/g, b2/g)) {
            ok = true;
        }
    }
    
    return ok;
}

bool solve(int& maxd) {
    //
    int ok = 0;
    for(maxd = 1; maxd <= 100; maxd++) {
        //
        Set(ans, -1);
        Set(v, 0);
        int f = getFrom(a, b);
        if(dfs(0, maxd, f, a, b)) {
            ok = 1;
            break;
        }
    }
    return ok;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    int t;
    scanf("%d", &t);
    
    while (t--) {
        init();
        
        cin >> a >> b >> k;
        _for(i, 0, k) {
            int v;
            cin >> v;
            vis.insert(v);
        }
        
        // finished init
        
        // bool solve()
        int maxd;
        int ok = solve(maxd);
        
        cout << "Case " << ++kase << ": ";
        if(ok) {
            cout << a << "/" << b << "=";
            _for(i, 0, maxd) cout << "1/" << ans[i] << "+";
            cout << "1/" << ans[maxd] << "\n";
        } else cout << "No solution.\n";
    }
    return 0;
}
