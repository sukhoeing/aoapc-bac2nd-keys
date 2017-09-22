// Xiangqi, ACM/ICPC Fuzhou 2011, UVa1589
// 陈锋 C++ 11
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
};
typedef Point Vector;

Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator- (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator* (const Vector& A, int p) { return Vector(A.x*p, A.y*p); }
Vector operator/ (const Vector& A, int p) { return Vector(A.x/p, A.y/p); }
bool operator== (const Point& a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool operator< (const Point& p1, const Point& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }
// istream& operator>>(istream& is, Point& p) { return is>>p.x>>p.y; }
// ostream& operator<<(ostream& os, const Point& p) { return os<<"["<<p.x<<","<<p.y<<"]"; }
// x in [left, right]
bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return left <= x && x <= right;
}
Point blackG, redG; // 将帅
char board[16][16];
vector<Point> 
    DIRS = {{1,0}, {0,1}, {-1,0}, {0,-1}}, // 4个方向
    HDIRS = {{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}}, // 跳马方向
    redPieces;

bool inBPalace(const Point& bPos) { return inRange(bPos.x, 1, 3) && inRange(bPos.y, 4, 6); }

// p1能不能直接飞到p2，中间有sz个妻子
bool canFly(const Point& p1, const Point& p2, int sz = 0) {
    bool v = (p1.x == p2.x), h = (p1.y == p2.y);
    assert(v || h); assert(!(v&&h));
    int lx = min(p1.x, p2.x), ux = max(p1.x, p2.x),
        ly = min(p1.y, p2.y), uy = max(p1.y, p2.y),
        cnt = 0;
    if(v) {
        _for(y, ly+1, uy)
            if(board[p1.x][y] && ++cnt > sz) return false;
        return cnt == sz;
    }
    
    _for(x, lx+1, ux)
        if(board[x][p1.y] && ++cnt > sz) return false;
    return cnt == sz;
}

// r上面的红棋子会不会吃到b上面的黑棋子
bool checkmate(const Point& r, const Point& b) {
    // cout<<"try checkmate "<<r<<" "<<b<<endl;
    bool ans = true;
    switch(board[r.x][r.y]) {
        case 'G': // general 将帅对面
            return r.y == b.y && canFly(r, b);
        case 'R': // chariot 车吃将
            return (r.x == b.x || r.y == b.y) && canFly(r, b);
        case 'H': // horse 马往各个方向尝试着跳
            for(const auto& HD : HDIRS) {
                Point hPos = r + HD, legPos = r + HD/2;
                if(hPos == b && board[legPos.x][legPos.y] == 0) return true;
            }
            return false;
        case 'C': // 炮打
            return (r.x == b.x || r.y == b.y) && canFly(r, b, 1);
        default:
            assert(false);
            break;
    }
}

bool canWin() {
    assert(inBPalace(blackG));
    if(blackG.y == redG.y && canFly(blackG, redG))
        return false; 

    for(const auto& D : DIRS) { // 尝试各种方向，看看能不能不被将死
        Point bp = blackG + D;
        if(!inBPalace(bp)) continue; // 不能
        
        char back = board[bp.x][bp.y];
        board[bp.x][bp.y] = 0; // 红子可能被吃掉的
        
        bool live = true;
        for(const auto& r : redPieces) {
            if(board[r.x][r.y] && checkmate(r, bp)) {
                live = false;             
                break;
            }
        }
        
        board[bp.x][bp.y] = back;
        if(live) return false;
    }
    return true;
}

int main(){    
    int N;    
    while(scanf("%d%d%d", &N, &(blackG.x), &(blackG.y)) == 3 && N){
        redPieces.clear();
        memset(board, 0, sizeof(board));
        _for(i, 0, N){
            char type;
            Point p;
            scanf("%c%d%d", &type, &(p.x), &(p.y));
            redPieces.push_back(p);
            board[p.x][p.y] = type;
            if(type == 'G') redG = p;
        }

        puts(canWin()?"YES":"NO");        
    }
    
    return 0;
}

/* 13554728	1589	Xiangqi	Accepted	C++	0.009	2014-04-27 10:25:10 */