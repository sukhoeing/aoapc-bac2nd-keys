//
//  main.cpp
//  POJ3131-4
//
//  Created by zhangmin chen on 2019/7/22.
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

const int HASHSZ = 2000007;
const int maxn = 2000007;

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

class HASH {
public:
    struct Node {
        int nxt, val;
    } nodes[HASHSZ];
    
    int head[HASHSZ];
    // head store the value of id
    int tot;
    
    void init() {
        Set(head, -1);
        tot = 0;
    }
    
    void insert(int hashV, int val) {
        nodes[tot].val = val;
        nodes[tot].nxt = head[hashV];
        head[hashV] = tot++;
    }
    
    int find(int dta) {
        int hashV = dta % HASHSZ;
        int i;
        for(i = head[hashV]; ~i; i = nodes[i].nxt) {
            int val = nodes[i].val;
            if(val == dta) return i;
        }
        insert(hashV, dta);
        return tot - 1;
    }
};

HASH hashTb;
void initHash() {
    hashTb.init();
}

bool vis1[maxn], vis2[maxn];
void initVis() {
    Set(vis1, 0);
    Set(vis2, 0);
}

class StNode {
public:
    int state;
    int pos;
    int dist;
    
    StNode(int s = 0, int p = 0, int dist = 0) : state(s), pos(p), dist(dist) {}
};

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
// const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;

/*
 if(top == W && face == R) return 1;
 if(top == W && face == B) return 2;
 if(top == R && face == W) return 3;
 if(top == R && face == B) return 4;
 if(top == B && face == W) return 5;
 if(top == B && face == R) return 6;
 */

// const int Move[0][dir]
// const int Move[1][dir]
// UP LEFT DOWN RIGHT
// Move[1][UP] = (R, W)  Move[1][LEFT] = (B, R) Move[0][DOWN] = (R, W)  Move[0][RIGHT] = (B, R)
// Move[2][UP] = (B, W)  Move[2][LEFT] = (R, B)
// Move[3][UP] = (W, R)  Move[3][LEFT] = (B, W)
// Move[4][UP] = (B, R)  Move[4][LEFT] = (W, B)
// Move[5][UP] = (W, B)  Move[6][LEFT] = (R, W)
// Move[6][UP] = (R, B)  Move[6][LEFT] = (W, R)

const int Move[7][4] = {
    {0, 0, 0, 0},
    {3, 6, 3, 6},
    {5, 4, 5, 4},
    {1, 5, 1, 5},
    {6, 2, 6, 2},
    {2, 3, 2, 3},
    {4, 1, 4, 1}
};
// usage: int newCode = Move[oldCode][dir]

queue<StNode> que1, que2;
char tar[11];
int tep;

void initQue() {
    while(!que1.empty()) que1.pop();
    while(!que2.empty()) que2.pop();
}

int getBit(int state, int k) {
    return ( ( (state >> (3 * k + 2)) & 1 ) << 2 ) |
           ( ( (state >> (3 * k + 1)) & 1 ) << 1 ) |
           ( ( (state >> (3 * k)) & 1 ));
}


void dfs(int d, int state, int tep) {
    if(d == 9) {
        StNode cur(state, tep, 0);
        que2.push(cur);
        
        int dta2 = hashTb.find(state);
        vis2[dta2] = 1;
        return;
    }
    
    if(tar[d] == 'E') {
        dfs(d + 1, state << 3, tep);
        return;
    }
    
    int v1, v2;
    if(tar[d] == 'W') {
        v1 = 1; v2 = 2;
    }
    else if(tar[d] == 'R') {
        v1 = 3; v2 = 4;
    }
    else {
        v1 = 5; v2 = 6;
    }
    
    dfs(d + 1, (state << 3) | v1, tep);
    dfs(d + 1, (state << 3) | v2, tep);
}

// const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
inline void update(StNode& u, int dir) {
    if(dir == 0) {
        //
        int np = u.pos - 3;
        int bit = getBit(u.state, 8 - np);
        
        int nbit = Move[bit][dir];
        u.state = (u.state ^ ( bit << ((8 - np) * 3) )) | ( nbit << ((8 - np - 3) * 3) );
        u.dist++;
        u.pos = np;
    }
    else if(dir == 1) {
        int np = u.pos - 1;
        int bit = getBit(u.state, 8 - np);
        
        int nbit = Move[bit][dir];
        u.state = (u.state ^ ( bit << ((8 - np) * 3) )) | ( nbit << ((8 - np - 1) * 3) );
        u.dist++;
        u.pos = np;
    }
    else if(dir == 2) {
        int np = u.pos + 3;
        int bit = getBit(u.state, 8 - np);
        
        int nbit = Move[bit][dir];
        u.state = (u.state ^ ( bit << ((8 - np) * 3) )) | ( nbit << ((8 - np + 3) * 3) );
        u.dist++;
        u.pos = np;
    }
    else if(dir == 3) {
        int np = u.pos + 1;
        int bit = getBit(u.state, 8 - np);
        
        int nbit = Move[bit][dir];
        u.state = (u.state ^ ( bit << ((8 - np) * 3) )) | ( nbit << ((8 - np + 1) * 3) );
        u.dist++;
        u.pos = np;
    }
}

bool valid(int x, int y) {
    if(0 <= x && x < 3 && 0 <= y && y < 3) return true;
    return false;
}

int bfs() {
    const int DEP1 = 20, DEP2 = 9;
    int lv1 = 0, lv2 = 0;
    
    for(lv1 = 0; lv1 <= DEP1; lv1++) {
        while (!que1.empty() && que1.front().dist == lv1) {
            // do something
            StNode x = que1.front(); que1.pop();
            int ex = x.pos / 3, ey = x.pos % 3;
            _for(dir, 0, 4) {
                int nx = ex + dx[dir], ny = ey + dy[dir];
                if(!valid(nx, ny)) continue;
                
                StNode clone = x;
                update(clone, dir);
                int hashV = hashTb.find(clone.state);
                
                if(!vis1[hashV]) {
                    vis1[hashV] = true;
                    if(vis2[hashV]) return lv1 + lv2 + 1;
                    que1.push(clone);
                }
            }
        }
        
        while(!que2.empty() && que2.front().dist == lv2 && lv2 < DEP2) {
            // do something
            StNode x = que2.front(); que2.pop();
            int ex = x.pos / 3, ey = x.pos % 3;
            _for(dir, 0, 4) {
                int nx = ex + dx[dir], ny = ey + dy[dir];
                if(!valid(nx, ny)) continue;
                
                StNode clone = x;
                update(clone, dir);
                int hashV = hashTb.find(clone.state);
                
                if(!vis2[hashV]) {
                    vis2[hashV] = true;
                    if(vis1[hashV]) return lv1 + lv2 + 2;
                    que2.push(clone);
                }
            }
        }
        
        if(lv2 < DEP2) lv2++;
    }
    return -1;
}


int main() {
    freopen("input.txt", "r", stdin);
    
    int ex, ey;
    while (scanf("%d%d", &ex, &ey) != EOF && ex && ey) {
        initVis();
        initQue();
        initHash();
        ex--; ey--;
        int ep = ey * 3 + ex;
        
        StNode s(0, ep, 0);
        _for(i, 0, 9) {
            s.state <<= 3;
            if(i == ep) continue;
            s.state |= 1;
        }
        que1.push(s);
        
        int dta1 = hashTb.find(s.state);
        vis1[dta1] = 1;
        // get start state finished
        
        
        // then get end status
        char c[3];
        _for(i, 0, 3) _for(j, 0, 3) {
            scanf("%s", c);
            tar[i * 3 + j] = c[0];
            if(c[0] == 'E') tep = i * 3 + j;
        }
        
        // judge 0
        int i;
        for(i = 0; i < 9; i++) {
            if(tar[i] == 'W' && i != s.pos) continue;
            if(tar[i] == 'E' && i == s.pos) continue;
            else break;
        }
        if(i == 9) {
            printf("0\n");
            continue;
        }
        
        // then add all 256 situation to the end queue
        dfs(0, 0, tep);
        // printf("%d\n", que2.size());
        
        // then double-way bfs
        printf("%d\n", bfs());
    }
}
