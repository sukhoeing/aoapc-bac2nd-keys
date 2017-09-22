// Moving Pegs, ACM/ICPC Taejon 2000, UVa1533
// 陈锋
#include <cassert>
#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
int readint() { int x; cin>>x; return x; }

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    bool first = true;    
    for(const auto& e : v) {
        if(first) first = false; else os<<" ";
        os<<e;
    }
    return os;
}

const int N = 15, D = 6, DIRS[N+1][D] = { // 6个方向能跳到的洞
    {0,0,0,0,0,0 },
    {0,0,0,0,2,3 }, // 1 
    {0,1,0,3,4,5 }, // 2
    {1,0,2,0,5,6 }, // 3
    {0,2,0,5,7,8 }, // 4
    {2,3,4,6,8,9 }, // 5
    {3,0,5,0,9,10 }, // 6
    {0,4,0,8,11,12 }, // 7
    {4,5,7,9,12,13 }, // 8
    {5,6,8,10,13,14 }, // 9
    {6,0,9,0,14,15 }, // 10
    {0,7,0,12,0,0 }, // 11
    {7,8,11,13,0,0 }, // 12
    {8,9,12,14,0,0 }, // 13
    {9,10,13,15,0,0 }, // 14
    {10,0,14,0,0,0 } // 15
};

struct Board{ // 棋盘状态
    int pos, cnt; // 表示每个位置上是否有小球的位向量，现有小球的个数
    vector<int> path;
    Board() { pos = ~0; cnt = N; }
    // 取出i的棋子
    void clear(int i) { assert(test(i)); pos ^= (1<<i); cnt--; }
    // 在i放棋子
    void put(int i) { assert(!test(i)); pos |= (1<<i); cnt++; }
    // i位置上有棋子吗？
    bool test(int i) const { return (pos & (1<<i)) != 0; }
    int findJump(int i, int d) const { // i往d方向能跳吗，返回是跳的最远位置
        int j = DIRS[i][d];
        if(!j || !test(j)) return 0;
        while(j && test(j)) j = DIRS[j][d];
        return j;
    }
    
    void dbgPrint() {
        int len = 1, p = 1;
        cout<<"cnt = "<<cnt<<endl;
        for(int i = 1; i <= N; i++) {
            if(test(i)) cout<<"*";
            else cout<<"_";
            if(i == p) { cout<<endl; len += 1; p += len; }
        }
        cout<<endl<<path.size()<<" -> "<<path<<endl;
    }
};

void solve(int e) {
    Board ib; ib.clear(e);
    queue<Board> q; q.push(ib);
    unordered_set<int> vis; vis.insert(ib.pos);
    
    while(!q.empty()) {
        Board b = q.front(); q.pop();
        if(b.cnt == 1 && b.test(e)) {
            cout<<b.path.size()/2<<endl;
            cout<<b.path<<endl;
            return;
        }
        
        for(int i = 1; i <= N; i++) {
            if(!b.test(i)) continue;
            _for(d, 0, D) { // 尝试不同的方向
                int t = b.findJump(i, d); // 看看最远跳多远
                if(!t) continue;
                int j = DIRS[i][d]; // assert(j && b.test(j));
                Board nb = b;
                nb.clear(i); // 从i起跳
                while(j != t) nb.clear(j), j = DIRS[j][d];  // 路过的棋子全部取出来
                nb.put(t);
                if(vis.count(nb.pos)) continue; // 局面已经搜过
                vis.insert(nb.pos);
                nb.path.push_back(i);
                nb.path.push_back(t);
                q.push(nb);
            }
        }
    }
    
    cout<<("IMPOSSIBLE\n");
}

int main() {    
    int T = readint();
    while(T--) solve(readint());
    return 0;
}

// Live Archive 2093: 1452420	2093	Moving Pegs	Accepted	C++	0.236	2014-05-17 05:08:25