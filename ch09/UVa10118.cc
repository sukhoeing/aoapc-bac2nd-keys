// Free Candies, UVa10118
// 陈锋
#include <cassert>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;

const int MAXH = 40+4, COLOR = 20;
int n, DP[MAXH][MAXH][MAXH][MAXH], pile[4][MAXH];

struct Basket {
    int color[COLOR + 4], size;
    Basket() : size(0){ memset(color, 0, sizeof(color)); }
    bool isFull() { return size == 5; }
    void take(int c) { // 取出颜色为c的糖果
        assert(color[c]); 
        color[c] = 0; 
        size--; 
    }
    void put(int c) { // 放入颜色为c的糖果
        assert(!isFull()); 
        assert(!color[c]); 
        color[c] = 1; 
        size++; 
    }
};
// 给定篮子的状态和每个pile的高度，返回最多能取出多少个糖果
int dfs(Basket& bkt, vector<int>& hs) {
    int& ans = DP[hs[0]][hs[1]][hs[2]][hs[3]];    
    if(ans != -1) return ans;
    ans = 0;
    if(bkt.isFull()) return ans;
    
    _for(i, 0, hs.size()){
        int& h = hs[i];
        if(h <= 0) continue;
        int sum = 0, top = pile[i][h-1];
        h--; // 尝试把pile[i]顶端的糖果取出来
        if(bkt.color[top]) {
            bkt.take(top);
            sum = dfs(bkt, hs) + 1;
            bkt.put(top);
        }
        else if(!bkt.isFull()){
            bkt.put(top);
            sum = dfs(bkt, hs);
            bkt.take(top);
        }
        ans = max(ans, sum);
        h++;
    }
    
    return ans;
}
int main(){
    vector<int> hs(4);
    while(cin>>n && n){
        hs.assign(4, n);
        memset(DP, -1, sizeof(DP));
        _for(j, 0, n) _for(i, 0, 4) cin>>pile[i][n-j-1];
        Basket bkt;
        cout<<dfs(bkt, hs)<<endl;
    }
}

// 14804648	10118	Free Candies	Accepted	C++	0.269	2015-01-15 04:40:13