// UVa163 City Directions
// 陈锋
#include <cmath>
#include <cassert>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#define _for(i,a,b) for(int i=(a); i<(b); ++i)
using namespace std;

bool eq(const char *l, const char *r) { return !strcmp(l, r); }

struct Point{ 
    int x, y; 
    Point(int a=0, int b=0) : x(a), y(b) {}
};
typedef Point Vector;
Vector operator * (const Vector& A, int n) { return Vector(A.x*n, A.y*n); }
bool operator == (const Point& A, const Vector& B) { return A.x == B.x && A.y == B.y; }
Point operator + (const Point& A, const Vector& B) { return Point(A.x+B.x, A.y+B.y); }

struct Line {
    int a, b, c; // a*x + b*y = c
    Line(int A, int B, int C) : a(A), b(B), c(C) {}   
    bool onLine(const Point& A) const { return A.x*a + A.y*b == c; }
};

vector<Line> throughWays = { 
    Line(1,0,0), Line(0,1,0), Line(1,-1,0), Line(1,1,0), 
    Line(1,0,50), Line(1,0,-50), Line(0,1,-50), Line(0,1,50) };
const Vector N(0,1), NE(1,1), E(1,0), SE(1,-1), S(0,-1), SW(-1,-1), W(-1,0), NW(-1,1);
vector<Vector> dirs = {E, NE, N, NW, W, SW, S, SE};
vector<string> dirNames = {"E", "NE", "N", "NW", "W", "SW", "S", "SE"};
map<string, Vector> dirNameMap;
const int SIZE = 50;
struct Graph {
    set<int> g[10201];
    
    Graph() { // 建图
        _for(x, -SIZE, SIZE+1) _for(y, -SIZE, SIZE+1) { // 水平和垂直间隔之间相连
            connect(Point(x,y), Point(x, y+1));
            connect(Point(x,y), Point(x+1, y));
        }

        _for(x, -SIZE, SIZE) {
            connect(Point(x, x), Point(x+1, x+1));
            connect(Point(x, -x), Point(x+1, -x-1));
        }
        
        _for(x, 0, SIZE) {
            int y = SIZE - x, x1 = x + 1, y1 = SIZE - x1;            
            connect(Point(x, y), Point(x1, y1));
            connect(Point(-x, -y), Point(-x1, -y1));
            connect(Point(-x, y), Point(-x1, y1));
            connect(Point(x, -y), Point(x1, -y1));
        }
    }
    
    inline void connect(const Point& A, const Point& B) {
        assert(valid(A));
        if(!valid(B)) return;
        int a = toInt(A), b = toInt(B);
        g[a].insert(b), g[b].insert(a);
    }
    
    inline int toInt(const Point& A) { return (A.x + SIZE) * SIZE * 2 + A.y + SIZE; }
    
    inline bool valid(const Point& A) { return -SIZE <= A.x && A.x <= SIZE && -SIZE <= A.y && A.y <= SIZE; }
    
    bool connected(const Point& A, const Point& B) {
        if(!valid(A) || !valid(B)) return false;
        return g[toInt(A)].count(toInt(B));
    }
};

bool locSet;
Point pos, headPos;
int dir;
Graph graph;

void printLoc(const Point& p) {
    printf("A%d", abs(p.x));
    putchar(p.x>=0 ? 'E' : 'W');    
    
    printf(" S%d", abs(p.y));
    putchar(p.y>=0 ? 'N' : 'S');
    printf(" %s\n", dirNames[dir].c_str());
}

bool onThroughWay(const Point& p, int d) {
    const Vector& dv = dirs[d];
    Point p2 = p + dv;
    for(auto l : throughWays) if(l.onLine(p) && l.onLine(p2)) return true;
    return false;
}

bool posValid(const Point& p) {
    int ret = -SIZE <= p.x && p.x <= SIZE && -SIZE <= p.y && p.y <= SIZE;
    // if(!ret)
        // printf("%d, %d", p.x, p.y);
    return ret;
}

// d : 顺时针(-)或者逆时针(+)转多少个45度。
bool tryTurn(int d, Point& newPos, Point& newHeadPos, int& newDir) {
    newDir = (dir + d + 8) % 8;
    const Vector& dv = dirs[dir], ndv = dirs[newDir];    
    newPos = pos + dv; // 先继续走1个路口
    newHeadPos = newPos + ndv; // 按照新的方向设定前方的下一个路口    
    assert(newPos == headPos);
    int nx = newPos.x, ny = newPos.y;
    
    if(!posValid(newPos)) return false;
    
    // 首先检查拐弯是否有效(在你要拐到的方向上是有路的)。
    if(posValid(newHeadPos) && !graph.connected(newPos, newHeadPos))
        return false;
    
    // 如果是在9个特殊的环岛路那里，那么任意方向拐弯都是有效的
    if((!nx && !ny) || 
        (abs(nx) == 0 && abs(ny) == SIZE) ||
        (abs(ny) == 0 && abs(nx) == SIZE) || 
        (abs(ny) == SIZE && abs(nx) == SIZE))
        return true;
    
    // 是进入一个高架
    if(onThroughWay(newPos, newDir) && !onThroughWay(pos, dir)) {
        if(fabs(ndv.x) == fabs(ndv.y)) {
            if(d != 3) return false;
        }
        else if(d != 2) return false;
    }
    
    // 离开一个高架
    if(onThroughWay(pos, dir) && !onThroughWay(newPos, newDir)) {
        if(fabs(dv.x) == fabs(dv.y)){
            if(d != 3) return false; 
        }
        else if(d != 2) return false;
    }
    
    return true;
}

bool cmdValid(const char *cmd, vector<string>& parts) {
    char p1[16] = {0}, p2[16] = {0}, p3[16] = {0};
    int ret = sscanf(cmd, "%s%s%s", p1, p2, p3);
    if(ret == 2) {
        parts.emplace_back(p1), parts.emplace_back(p2);
        if(p1[0] == 'G') {
            int l = strtoul(p2, NULL, 0);
            return eq(p1, "GO") && l >= 1 && l <= 99;
        }
        return eq(p1, "TURN") && (eq(p2, "RIGHT") || eq(p2, "LEFT"));
    }
    else if(ret == 3) {    
        parts.emplace_back(p1), parts.emplace_back(p2), parts.emplace_back(p3);
        
        if(p1[0] == 'G') {
            int l = strtoul(p3, NULL, 0);
            return eq(p1, "GO") && eq(p2, "STRAIGHT") && l >= 1 && l <= 99;
        }

        return eq(p1, "TURN") && (eq(p2, "HALF") || eq(p2, "SHARP"))
            && (eq(p3, "RIGHT") || eq(p3, "LEFT"));
    }
    
    return false;
}

void exec(const char *cmd) {
    if(cmd[0] == 'A') {        
        if(locSet) return;
        char p1[16], p2[16], p3[16];
        sscanf(cmd, "%s%s%s", p1, p2, p3);
        char xc, yc; int x, y;
        sscanf(p1+1, "%d%c", &x, &xc);
        sscanf(p2+1, "%d%c", &y, &yc);
        if(xc == 'W') x = -x;
        if(yc == 'S') y = -y;
        pos.x = x, pos.y = y;
        dir = find(begin(dirs), end(dirs), dirNameMap[string(p3)]) - begin(dirs);
        headPos = pos + dirs[dir];
        assert(graph.connected(pos, headPos));
        locSet = true;
        
        // printLoc();
        return;
    }
    
    vector<string> parts;
    if(!cmdValid(cmd, parts)) { 
        // printf("%s - invalid ignore\n", cmd);
        return;
    }
    
    if(cmd[0] == 'T') {
        int d = 2;
        if(parts.size() == 3) {
            if(parts[1][0] == 'H') d--;
            else if(parts[1][0] == 'S') d++;
            else assert(false);
        }
        if(parts.back()[0] == 'R') // RIGHT
            d = -d;
        
        Point newPos = pos, newHeadPos;
        int newDir = dir;
        
        if(tryTurn(d, newPos, newHeadPos, newDir)) {
            pos = newPos;
            headPos = newHeadPos;
            dir = newDir;
        }
    } else if(cmd[0] == 'G') {       
        int l = strtoul(parts.back().c_str(), NULL, 0);
        pos = pos + dirs[dir] * l;
        assert(posValid(pos));
        headPos = headPos + dirs[dir] * l;
    }
}

void stop() {
    if(onThroughWay(pos, dir)) puts("Illegal stopping place");
    else printLoc(pos);
}

int main(){
    _for(i, 0, 8) dirNameMap[dirNames[i]] = dirs[i];
    locSet = false;
    char buf[256];
    while(true) {
        gets(buf);
        if(!strlen(buf)) continue;
        if(eq(buf, "STOP")) stop(), locSet = false;
        else if(eq(buf, "END")) break;
        exec(buf);
    }
    
    return 0;
}
// 20054229	163	City Directions	Accepted	C++11	0.000	2017-09-24 02:36:31