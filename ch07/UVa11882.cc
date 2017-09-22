// Biggest Number, UVa11882
// 陈锋
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#define _for(i,a,b) for(int i=(a); i<(b); ++i)
using namespace std;
typedef long long ll;
const int MAXR = 32, MAXC = 32;

int R,C, Walked[MAXR][MAXC], Vis[MAXR][MAXC], DX[4] = {0,1,0,-1}, DY[4] = {1,0,-1,0};
char Grid[MAXR][MAXC];

inline bool isValid(int x, int y) {
    return 0 <= x && x < R && 0 <= y && y < C && isdigit(Grid[x][y]);
}

struct Rec {
    vector<char> buf;
    bool operator<(const Rec& r2) const {
        if(buf.size() != r2.buf.size()) return buf.size() < r2.buf.size();
        return buf < r2.buf;
    }
    Rec& operator+=(const Rec& r2) {
        int sz = buf.size();
        buf.resize(buf.size() + r2.buf.size());
        copy_backward(begin(r2.buf), end(r2.buf), begin(buf) + sz);
        return *this;
    }
    Rec& operator+=(char c) { buf.push_back(c); return *this; }
    inline int size() const { return buf.size(); }
    inline void clear(){ buf.clear(); }
    void printLn() const {
        for(int i = 0; i < size(); i++) putchar(buf[i]);
        puts("");
    }
};

void bfs(int x, int y, Rec& rs) { // 已经走到(x,y)，还能走多远，bfs一下，存到rs中
    queue<int> q;
    q.push(x * MAXC + y);
    memset(Vis, 0, sizeof(Vis));
    Vis[x][y] = 1;
    while(!q.empty()) {
        int tmp = q.front(); q.pop();
        x = tmp / MAXC, y = tmp % MAXC;
        _for(i, 0, 4) {
            int ax = x + DX[i], ay = y + DY[i];
            if(!isValid(ax,ay) || Walked[ax][ay] || Vis[ax][ay]) continue;
            Vis[ax][ay] = 1;
            rs += Grid[ax][ay];
            q.push(ax*MAXC + ay);
        }
    }
}

bool lessThan(const Rec& l1, Rec& l2, const Rec& t) {
    assert(l1.size() + l2.size() == t.size());
    int i = 0,a,b;
    for(i = 0; i < l1.size(); i++) {
        a = l1.buf[i], b = t.buf[i];
        if(a<b) return true;
        if(a>b) return false;
    }
    
    sort(l2.buf.begin(), l2.buf.end(), greater<char>());
    for(; i < t.size(); i++) {
        a = l2.buf[i-l1.size()], b = t.buf[i];
        if(a<b) return true;
        if(a>b) return false;
    }
    return false;
}

// 从[x,y]开始走，已经走出的数字是cur，目前的最优答案是ans
void solve(int x, int y, Rec& cur, Rec& ans) {
    Rec rs;
    bfs(x,y,rs);
    if(cur.size() + rs.size() < ans.size()) return;
    if(cur.size() + rs.size() == ans.size() && lessThan(cur, rs, ans)) return;
    
    _for(i, 0, 4){
        int ax = x + DX[i], ay = y + DY[i];
        if(!isValid(ax, ay) || Walked[ax][ay]) continue;
        cur += Grid[ax][ay];
        Walked[ax][ay] = 1;
        solve(ax, ay, cur, ans);
        cur.buf.pop_back();
        Walked[ax][ay] = 0;
    }

    if(ans < cur) ans = cur; // 更新答案
}

int main()
{
    Rec ans, cur;
    while(scanf("%d%d", &R, &C) == 2 && R && C) {
        memset(Grid, 0, sizeof(Grid));     
        memset(Walked, 0, sizeof(Walked));
        _for(i, 0, R) scanf("%s", Grid[i]);
        ans.clear();
        _for(i, 0, R){
            _for(j, 0, C){
                if(!isdigit(Grid[i][j])) continue;
                cur.clear(), cur += Grid[i][j];// 尝试从[i,j]开始走
                Walked[i][j] = 1;
                solve(i,j, cur, ans);
                Walked[i][j] = 0;
            }
        }
        ans.printLn();
    }
    
    return 0;
}
// 15041893	11882	Biggest Number	Accepted	C++	0.839	2015-02-26 09:50:17