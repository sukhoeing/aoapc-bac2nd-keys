// Paper Folding, UVa177
// 陈锋
#include <cassert>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
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
bool operator!= (const Point& a, const Point &b) { return !(a==b); }
bool operator< (const Point& p1, const Point& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }
ostream& operator<<(ostream& os, const Point& p) { 
    return os<<p.x<<','<<p.y;
}

// p围绕r顺时针旋转90度，返回旋转后的点
Point rotate(const Point& p, const Point& r) {
    Vector pv = p - r;
    Point ans = r + Vector(pv.y, -pv.x);
    return ans;
}

const int MAXN = 13;
struct Line {
    Point start, end;
    bool vertical;
    
    // 围绕r顺时针旋转90度
    Line rotate(const Point& r) {
        Line ret;
        ret.start = ::rotate(start, r);
        ret.end = ::rotate(end, r);
        return ret;
    }
    // 规整，保证start在end的左边或者上边
    void normalize() {
        assert(start != end);
        assert(start.x == end.x || start.y == end.y);
        vertical = (start.x == end.x);
        if(vertical) {
            if(start.y > end.y) swap(start.y, end.y);
        } else {
            if(start.x > end.x) swap(start.x, end.x);
        }
    }
};

int n, LineCnt;
vector<Line> lines;

int main()
{    
    lines.reserve(1<<MAXN);
    while(cin>>n&&n) {
        Line l;
        l.end = Point(1, 0);
        l.vertical = false;
        lines.clear();
        lines.push_back(l);
        int maxY = l.start.y, minY = l.start.y,
            minX = l.start.x, maxX = l.end.x;
        
        Point s = l.start, rot = l.end;
        _for(i, 0, n) {
            int sz = lines.size();            
            _for(j, 0, sz) {
                Line nl = lines[j].rotate(rot);
                nl.normalize();
                lines.push_back(nl);
            }
            rot = rotate(s, rot);
        }
        
        map<Point, char> pc;
        for(auto& l : lines) {
            Point& lp = l.start;
            lp.x *= 2;
            if(l.vertical) lp.x--;
            minX = min(lp.x, minX);
            maxX = max(lp.x, maxX);
            minY = min(lp.y, minY);
            maxY = max(lp.y, maxY);
            pc[lp] = l.vertical ? '|' : '_';
        }
        
        // cout<<"minX = "<<minX<<endl;
        string buf;
        for(int y = maxY; y >= minY; y--) {
            buf.clear();
            for(int x = minX; x <= maxX; x++) {
                Point p(x,y);
                if(pc.count(p)) buf += pc[p];
                else buf += ' ';
            }
            while(*(buf.rbegin()) == ' ') buf.erase(buf.size()-1);
            cout<<buf<<endl;
        }
        
        cout<<"^"<<endl;
    }
    return 0;
}
// 13700866	177	Paper Folding	Accepted	C++	0.026	2014-05-31 14:30:34

