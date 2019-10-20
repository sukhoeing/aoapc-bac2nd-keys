//
//  main.cpp
//  LA3784
//
//  Created by zhangmin chen on 2019/7/13.
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

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;
//const int maxn = 10 + 5;

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


const string buf = "*0123456789";
const int BUFLEN = 11;
int len[3];
string data;

void init() {
    //
    data.clear();
    Set(len, 0);
}

/*
void clearVis() {
    Set(vis, 0);
}
 */

// only one solution
// check exp 0;

// st3[i] == bit + '0' || str3[i] == '*'
// ans is correct

int cal(const string& str, int from, int to) {
    // [from, to]
    int ans = 0, base = 1;

    _rep(i, from, to) {
        ans *= base;
        ans += str[i] - '0';
        base *= 10;
    }
    
    return ans;
}

// find one and only one solution
// return true

bool _equal(const string& str) {
    // string lhs1 = lhs.substr(0, len1), lhs2 = lhs.substr(len1, len2);
    // assert(lhs1.length() == len1);
    // assert(lhs2.length() == len2);
    
    //if(lhs1[0] == '0' || lhs2[0] == '0' || rhs[0] == '0') return false;
    
    int a = cal(str, 0, len[0] - 1), b = cal(str, len[0], len[0] + len[1] - 1);
    int c = a * b;
    
    char ans[5];
    /*
    stringstream ss;
    ss << c;
     */
    sprintf(ans, "%d", c);
    int ansL = (int)strlen(ans);
    
    assert(ansL > 0);
    //debug(ans);
    
    
    if(ansL != len[2]) return false;
    else {
        // bool ok = 1;
        _for(i, len[0] + len[1], str.length()) {
            if(str[i] == '*') continue;
            // debug(ans[i]);
            if(ans[i - (len[0] + len[1])] != str[i]) return false;
        }
        return true;
    }
}

void check(string& str, int i, int& cnt) {
    if(cnt > 1) return;
    
    if(i == len[0] + len[1]) {
        if(_equal(str)) cnt++;

        return;
    }
   
    
    if(str[i] != '*') check(str, i + 1, cnt);
    else {
        _for(k, 1, BUFLEN) {
            if(k == 1 && (i == 0 || i == len[0])) continue;
            str[i] = buf[k];
            check(str, i + 1, cnt);
            str[i] = '*';
        }
    }
}

// ans O(8100)


bool dfs(string& str, int i, int d, int maxd) {
    if(d == maxd) {
        int cnt = 0;
        check(str, 0, cnt);
        // debug(cnt);
        
     
        if(cnt == 1) return true;
        else return false;
    }
    
    if(i == str.length()) return false;
    if(str.length() - i < maxd - d) return false;
    
    // debug(len1);
    
    char old = str[i];
    _for(k, 0, BUFLEN) {
        if(k == 1 && (i == 0 || i == len[0] || i == len[0] + len[1])) continue;
        if(old == buf[k]) {
            // debug(old);
            if(dfs(str, i + 1, d, maxd)) return true;
        }
        else {
            str[i] = buf[k];
            if(dfs(str, i + 1, d + 1, maxd)) return true;
            str[i] = old;
        }
    }
    
    // if(dfs(nxt)) return true
    return false;
}


string solve() {
    int maxd = 0;
    string clone = data;
    for(maxd = 0; ; maxd++) {
        if(dfs(clone, 0, 0, maxd)) break;
    }
    //debug(maxd);
    return clone;
}



int main() {
    freopen("input.txt", "r", stdin);
    string line;
    int kase = 1;
    while(getline(cin, line)) {
        init();

        if(line[0] == '0') return 0;
        
        // then line is the input data
        // line -> Exp
        stringstream ss(line);
        string tmp;
        
        int k = 0;
        while (ss >> tmp) {
            len[k++] = (int)tmp.length();
            data += tmp;
        }

        // cout << data << endl;
        string ans = solve();
        // cout << ans << endl;
        
        printf("Case %d: ", kase++);
        cout << ans.substr(0, len[0]) << " " << ans.substr(len[0], len[1])
        << " " << ans.substr(len[0] + len[1]) << endl;

    }
}
