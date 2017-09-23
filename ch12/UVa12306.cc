// UVa12306 - My SketchUp
// 陈锋 C++11
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define _for(i,a,b) for(int i=a; i<(b); ++i)

const double eps = 1e-6;
int dcmp(double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
int dcmp(double x, double y) { return dcmp(x - y); }
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point& operator=(const Point& p) { x = p.x; y = p.y; return *this; }
};
typedef Point Vector;

Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator- (const Point& A, const Point& B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator* (const Vector& A, double p) { return Vector(A.x * p, A.y * p); }
bool operator== (const Point& a, const Point &b) { return dcmp(a.x, b.x) == 0 && dcmp(a.y, b.y) == 0; }
bool operator< (const Point& p1, const Point& p2) { return dcmp(p1.x, p2.x) < 0 || (dcmp(p1.x, p2.x) == 0 && dcmp(p1.y, p2.y) < 0); }
double Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }

struct Line {
    Point p1, p2;
    Line(const Point &p_1, const Point &p_2) : p1(p_1), p2(p_2) { if (p2 < p1)swap(p1, p2); };
    bool operator<(const Line&b)const { return p1 < b.p1 || (p1 == b.p1 && p2 < b.p2); }
    Vector dir()const { return p2 - p1; };
};
/*直线是否平行*/
bool isParallel(const Line &l1, const Line &l2) { return dcmp(Cross(l1.dir(), l2.dir())) == 0; } 
/*直线交点*/
Point intersection(const Line &l1, const Line &l2) { 
    Point v = l1.dir(), w = l2.dir(), u = l1.p1 - l2.p1;
    double t = Cross(w, u) / Cross(v, w);
    return l1.p1 + v * t;
}
enum PointLinePos { 
    ON_LINE = -1, NOT_ON_LINE = 0, ON_SEGMENT = 1, ON_SEGMENT_TERMINAL = 2 
};
int pointSegPos(const Line &l, const Point &p) { // 点相对于线段的位置
    Vector dd = l.dir(), d1 = p - l.p1, d2 = p - l.p2;
    if (dcmp(Cross(dd, d1)) != 0) return NOT_ON_LINE;
    double a = Dot(d1, d2);
    if (dcmp(a) == 0) return ON_SEGMENT_TERMINAL;
    if (dcmp(a) < 0) return ON_SEGMENT;
    return ON_LINE;
}
double distToLine(const Line &l, const Point &p) { // 点到直线的距离
    Vector v1 = l.p2 - l.p1, v2 = p - l.p1;
    return fabs(Cross(v1, v2)) / sqrt(Dot(v1, v1));
}
double distToSeg(const Line &l, const Point &p) { // 点到线段的距离
    if (l.p1 == l.p2)return Length(p - l.p1);
    Vector v1 = l.dir(), v2 = p - l.p1, v3 = p - l.p2;
    if (dcmp(Dot(v1, v2)) < 0)return Length(v2);
    if (dcmp(Dot(v1, v3)) > 0)return Length(v3);
    return fabs(Cross(v1, v2)) / Length(v1);
}

typedef list<Line>::iterator ILL;
bool operator<(const ILL &a, const ILL &b) { return *a < *b; }

struct Picture {
    list<Line> lines; // 所有的直线
    map<Point, set<ILL> > V; // 顶点，以及与这个顶点连接的线段
    map<Point, int> id; // 顶点编号，输出用

    void newSeg(const Line &l) { // 插入新的线段
        if (l.p1 == l.p2) return;
        lines.push_front(l); 
        V[l.p1].insert(lines.begin()); 
        V[l.p2].insert(lines.begin());
    }

    void removeSeg_IncIter(ILL &il) { // 删除线段，并且指向下一条线段
        V[il->p1].erase(il); 
        V[il->p2].erase(il); 
        lines.erase(il++);
    }

    void addSegment(Line l) {
        vector<Point> newPts;
        for (auto it = lines.begin(); it != lines.end();) {
            // 处理l和现有线段共线并且有互相覆盖的情况
            if (isParallel(*it, l) && dcmp(distToLine(*it, l.p1)) == 0){ 
                if (it->p1 < l.p2 && l.p1 < it->p2) {
                    l.p1 = min(it->p1, l.p1), l.p2 = max(it->p2, l.p2);
                    removeSeg_IncIter(it);
                    continue;
                }
            }
            ++it;
        }
        for (auto it = lines.begin(); it != lines.end();) {
            if (!isParallel(*it, l)) { // 查看与现有所有线段的交点
                Point is = intersection(*it, l);
                int sa = pointSegPos(l, is), si = pointSegPos(*it, is);
                if (sa > 0 && si > 0) {
                    if (sa == ON_SEGMENT) newPts.push_back(is); // l被切割开
                    if (si == ON_SEGMENT) { // 现有线段被切割，删除老的线段，增加新的线段
                        newSeg(Line(it->p1, is)); 
                        newSeg(Line(is, it->p2)); 
                        removeSeg_IncIter(it);
                        continue;
                    }
                }
            }
            ++it;
        }
        newPts.push_back(l.p1), newPts.push_back(l.p2);
        sort(newPts.begin(), newPts.end());
        _for(i, 0, newPts.size() - 1) // 把l被切割成的段挨个加进去
            newSeg(Line(newPts[i], newPts[i + 1])); 
    }

    void removeNear(const Point& p, double d) { // 删除距离p<=d的所有线段
        for (auto it = lines.begin(); it != lines.end();) {
            if (dcmp(distToSeg(*it, p), d) <= 0) {
                removeSeg_IncIter(it); continue;
            }
            ++it;
        }
    }

    void combine() { // 合并所有的从一个点出发的共线线段
        for (const auto& v : V) {
            if (v.second.size() != 2) continue;
            auto i1 = *(v.second.begin()), i2 = *(v.second.rbegin());
            if (!isParallel(*i1, *i2)) continue;
            // 两条线段共线
            Line l(min(i1->p1, i2->p1), max(i1->p2, i2->p2)); // 两条线段合并
            removeSeg_IncIter(i1), removeSeg_IncIter(i2);
            newSeg(l);
        }
    }

    void cleanup() { // 清理没有线段相连的点
        for (auto it = V.begin(); it != V.end();)
            if (it->second.empty()) V.erase(it++); else ++it;
    }

    void init() { id.clear(); lines.clear(); V.clear(); }
};

int main() {
    int n; char cmd[16]; Point p; vector<Point> ps;
    Picture pic;
    while (scanf("%d", &n) == 1 && n) {
        pic.init();
        _for(i, 0, n) {
            scanf("%s", cmd);
            if (cmd[0] == 'D') {
                ps.clear();
                while (scanf("%lf%lf", &(p.x), &(p.y)) == 2) ps.push_back(p);
                _for(j, 1, ps.size()) pic.addSegment(Line(ps[j - 1], ps[j]));
            }
            else if (cmd[0] == 'R') {
                double d;
                scanf("%lf%lf%lf", &(p.x), &(p.y), &d);
                pic.removeNear(p, d);
            };
            pic.combine();
        }
        while (strcmp("END", cmd) != 0) scanf("%s", cmd);
        pic.cleanup();
        printf("%lu\n", pic.V.size());
        int nid = 0;
        for (const auto& v : pic.V) {
            printf("%.2lf %.2lf\n", v.first.x + eps, v.first.y + eps);
            pic.id[v.first] = ++nid;
        }

        printf("%lu\n", pic.lines.size());
        for (const auto& v : pic.V) for (const auto& l : v.second)
            if (v.first == l->p1) printf("%d %d\n", pic.id[l->p1], pic.id[l->p2]);
    }
    return 0;
}
// 16064296 12306   My SketchUp Accepted    C++11   0.033   2015-09-08 08:04:48