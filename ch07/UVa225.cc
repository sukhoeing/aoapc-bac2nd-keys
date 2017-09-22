// Golygons, ACM/ICPC World Finals 1993, UVa225
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <unordered_map>

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
    
using namespace std;
struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
};
typedef Point Vector;

Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator- (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator* (const Vector& A, int p) { return Vector(A.x*p, A.y*p); }
bool operator== (const Point& a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool operator< (const Point& p1, const Point& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }

int readint() { int x; scanf("%d", &x); return x;}

// x in [left, right]
bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return left <= x && x <= right;
}

ostream& operator<<(ostream& os, const vector<char>& s){
    for(const auto c : s) os<<c;
    return os;
}

vector<Point> blocks; // 障碍点
char DIRS[] = "ensw";
Vector dirVs[4] = {{1,0},{0,1},{0,-1},{-1,0}};
unordered_map<char, int> DIX = {{'e', 0}, {'n', 1}, {'s', 2}, {'w', 3}};

string dbgPrintPath(const string& path) {
    Point pos;
    stringstream ss;
    _for(i, 0, path.size()) {
        char d = path[i];
        assert(DIX.count(d));
        ss<<'['<<pos.x<<','<<pos.y<<"]-"<<d<<"->";
        pos = pos + dirVs[DIX[d]]*(i+1);
    }
    ss<<endl;
    return ss.str();
}

// start--end是否被blocked
bool isBlocked(const Point& start, const Point& end) {
    assert(start.x == end.x || start.y == end.y);
    for(const auto& blk : blocks) {
        if(start.x == end.x) {
            if(start.x == blk.x && inRange(blk.y, start.y, end.y))
                return true;
        }
        else if(start.y == end.y) {
            if(start.y == blk.y && inRange(blk.x, start.x, end.x))
                return true;
        }
    }
    return false;
}
const int MAXX = 256;
int vis[MAXX*2][MAXX*2];
void solve(const Point& pos, vector<char>& path, vector<string>& paths, int cities) {
    int n = path.size();
    if(n == cities) { 
        if(pos.x == 0 && pos.y == 0) { // 已经回家了
            stringstream ss; ss<<path;
            paths.push_back(ss.str()); // 搜到一条路径
        }
        return;
    }
    
    int dist = abs(pos.x) + abs(pos.y), // 距离起点的距离
        walks = (cities - n) * (n + 1 + cities) / 2; // 还能走出的步数
    if(walks < dist) return; // 怎么走都走不到终点
    
    _for(i, 0, 4) {
        char d = DIRS[i]; // 下一步走什么方向
        if(n) {
            char lastD = path.back();
            if(lastD == d) continue;
            if(lastD == 'e' && d == 'w') continue; // 反向不行
            if(d == 'e' && lastD == 'w') continue; // 反向不行
            if(lastD == 'n' && d == 's') continue; // 反向不行
            if(d == 'n' && lastD == 's') continue; // 反向不行
        }
        auto dest = pos + dirVs[i]*(n+1); // 这一步的目标点
        if(isBlocked(pos, dest)) continue;
        int& destVis = vis[dest.x+MAXX][dest.y+MAXX];
        if(destVis) continue; // 已经在目标点停留过
        destVis = 1;
        path.push_back(d);
        solve(dest, path, paths, cities);
        path.pop_back();
        destVis = 0;
    }
}

int main(){
    int N,k,K; scanf("%d", &K);
    Point b;
    while(K--){
        blocks.clear();
        scanf("%d%d", &N, &k);
        _for(i, 0, k){
            scanf("%d%d", &(b.x), &(b.y));
            blocks.push_back(b);
        }
        
        Point start; vector<string> paths; vector<char> path;
        memset(vis, 0, sizeof(vis));
        solve(start, path, paths, N);
        for(const auto& p : paths) puts(p.c_str());
        printf("Found %lu golygon(s).\n\n", paths.size());
    }    
    return 0;
}

// 1958220  LA5164    Golygons    Accepted    C++11   0.733   2016-05-16 14:36:58