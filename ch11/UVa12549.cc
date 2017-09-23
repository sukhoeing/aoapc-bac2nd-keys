// Sentry Robots, ACM/ICPC SWERC 2012, UVa12549
// 陈锋
#include <cassert>
#include <cctype>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXX = 100+5;

// 二分图最大基数匹配
template<int maxn>
struct BPM {
  int n, m;               // 左右顶点个数
  vector<int> G[maxn];    // 邻接表
  int left[maxn];         // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool T[maxn];           // T[i]为右边第i个点是否已标记

  int right[maxn];        // 求最小覆盖用
  bool S[maxn];           // 求最小覆盖用

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    for(int i = 0; i < n; i++) G[i].clear();
  }

  void AddEdge(int u, int v) {
    G[u].push_back(v);
  }

  bool match(int u){
    S[u] = true;
    for(int i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (!T[v]){
        T[v] = true;
        if (left[v] == -1 || match(left[v])){
          left[v] = u;
          right[u] = v;
          return true;
        }
      }
    }
    return false;
  }

  // 求最大匹配
  int solve() {
    memset(left, -1, sizeof(left));
    memset(right, -1, sizeof(right));
    int ans = 0;
    for(int u = 0; u < n; u++) { // 从左边结点u开始增广
      memset(S, 0, sizeof(S));
      memset(T, 0, sizeof(T));
      if(match(u)) ans++;
    }
    return ans;
  }

  // 求最小覆盖。X和Y为最小覆盖中的点集
  int mincover(vector<int>& X, vector<int>& Y) {
    int ans = solve();
    memset(S, 0, sizeof(S));
    memset(T, 0, sizeof(T));
    for(int u = 0; u < n; u++)
      if(right[u] == -1) match(u); // 从所有X未盖点出发增广
    for(int u = 0; u < n; u++)
      if(!S[u]) X.push_back(u); // X中的未标记点
    for(int v = 0; v < m; v++)
      if(T[v]) Y.push_back(v);  // Y中的已标记点
   return ans;
  }
};

struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
  char ch;  
};

int Y, X, P, W;
vector<Point> points;

BPM<MAXX*MAXX*2> solver;

void dbgPrint() {
    cout<<X<<"*"<<Y<<endl;
    string line(X, '.');
    vector<string> M(Y, line);
    for(auto& p : points) {
        // cout<<"p-> "<<p.y<<", "<<p.x<<endl;
        assert(p.y < Y); assert(p.x < X);
        M[p.y][p.x] = p.ch;
    }
    _for(i, 0, Y) cout<<M[i]<<endl;
}

int solve() {  
    sort(points.begin(), points.end(), [](const Point& p1, const Point& p2){
      return p1.y < p2.y || (p1.y==p2.y && p1.x < p2.x); });
    int dy = 0; // 垂直拆开
    for(auto& p : points) {
        bool isOb = (p.ch == '#');
        if(isOb) dy++;
        p.y += dy;
        if(isOb) dy++;
    }
    Y += dy;
    
    sort(points.begin(), points.end(), [](const Point& p1, const Point& p2){
      return p1.x < p2.x || (p1.x==p2.x && p1.y < p2.y);});
    int dx = 0; // 水平拆开
    for(auto& p : points) {
        bool isOb = (p.ch == '#');
        if(isOb) dx++;
        p.x += dx;
        if(isOb) dx++;
    }
    X += dx;
    
    solver.init(X, Y);
    for(const auto& p : points)
      if(p.ch == '*') solver.AddEdge(p.x, p.y);
    vector<int> t1, t2;
    solver.mincover(t1, t2);
    return t1.size() + t2.size();
}

int main(){
    int C; cin>>C;
    _rep(t, 1, C){
        cin>>Y>>X>>P;
        points.clear();
        Point p;
        _for(i, 0, P){
            cin>>p.y>>p.x;
            p.ch = '*', p.x--, p.y--;
            points.push_back(p);
        }
        cin>>W;
        _for(i, 0, W) {
            cin>>p.y>>p.x;
            p.ch = '#', p.x--, p.y--;
            points.push_back(p);
        }
        
        int ans = solve();
        cout<<ans<<endl;
    }
    return 0;
}
// LiveArchive: 1473662	6156	Sentry Robots	Accepted	C++	0.056	2014-06-27 07:22:02