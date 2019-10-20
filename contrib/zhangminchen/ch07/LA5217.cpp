//
//  main.cpp
//  LA5217
//
//  Created by zhangmin chen on 2019/8/1.
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
#include <bitset>
#include <assert.h>
#include <unordered_set>

using namespace std;
typedef long long llong;
typedef set<string>::iterator ssii;

const int maxn = 10 + 15;

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

const int ch[3] = {'*', '+', '-'};
set<string> output;
char str[maxn];
string res;
int sign[maxn];
int len = 0;
bool ok = 0;

bool cmp(const string& lhs, const string& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

void init() {
    output.clear();
    res.clear();
    Set(sign, 0);
    len = (int)(strlen(str) - 1);
    ok = 0;
}

// is digit [0, len - 1]

inline int cal() {
    vector<int> val1, val2;
    vector<int> cmd1, cmd2;

    val1.push_back(str[0] - '0');
    _for(i, 0, len - 1) {
        if(sign[i] == 3) {
            // add no operator
            if(val1.back() == 0) return 0;

            int x = val1.back() * 10 + str[i + 1] - '0';
            val1.pop_back();
            val1.push_back(x);
        }
        else {
            cmd1.push_back(sign[i]);
            val1.push_back(str[i + 1] - '0');
        }
    }

    // then calculate *
    val2.push_back(val1[0]);
    _for(i, 0, cmd1.size()) {
        if(cmd1[i] == 0) {
            int x = val2.back() * val1[i + 1];
            val2.pop_back();
            val2.push_back(x);
        }
        else {
            cmd2.push_back(cmd1[i]);
            val2.push_back(val1[i + 1]);
        }
    }

    int ans = val2[0];
    _for(i, 0, cmd2.size()) {
        if(cmd2[i] == 1) ans += val2[i + 1];
        else ans -= val2[i + 1];
    }
    return ans;
}


void dfs(int d) {
    if(d == len - 1) {
        // calculate
        // [0, len - 1]
        int val = cal();
        //debug(val);
        if(val == 2000) {
            //
            ok = 1;
            res += str[0];
            _for(j, 0, d) {
                if(sign[j] == 3) {
                    // put no operator
                    res += str[j + 1];
                }
                else {
                    //
                    res += ch[sign[j]];
                    res += str[j + 1];
                }
            }
            //cout << "ans" << ans << endl;
            output.insert(res);
            res.clear();
        }
        return;
    }

    _for(i, 0, 4) {
        sign[d] = i;
        dfs(d + 1);
    }
}

void solve() {
    if(strcmp(str, "2000=") == 0) {
        printf("  IMPOSSIBLE\n");
        return;
    }
    dfs(0);
    if(ok == 0) printf("  IMPOSSIBLE\n");
    else {
        for(auto& it : output) {
            cout << "  " << it << "=" << endl;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%s", str) && str[0] != '=') {
        init();
        printf("Problem %d\n", ++kase);

        // then we solve the problem
        solve();
    }
}