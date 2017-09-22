// Do You Know The Way to San Jose?, ACM/ICPC World Finals 1997, UVa511
// 陈锋
#include <cassert>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Point {
    double x, y;
    Point(double x=0, double y=0):x(x),y(y) {}
};

typedef Point Vector;
const double eps = 1e-7;
int dcmp(double x) { if(fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
int cmp(double x, double y) { return dcmp(x-y); }

// x in [left, right]
bool inRange(double x, double l, double r) {
    if(cmp(l, r) > 0) return inRange(x, r, l);
    return cmp(l, x) <= 0 && cmp(x, r) <= 0;
}

bool inArea(const Point& p, const Point& l, const Point& r) {
    return inRange(p.x, l.x, r.x) && inRange(p.y, l.y, r.y);
}

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Dist2(const Point& A, const Point& B) { return Dot(A-B,A-B); }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }

istream& operator>> (istream& is, Point& p) { return is>>p.x>>p.y; }

struct Map {
    string name;
    Point corner1, corner2, center, lowerRight;
    double ratio, width, height, area, minX;
    void init() {
        center = (corner1 + corner2) * .5;
        width = fabs(corner1.x - corner2.x);
        height = fabs(corner1.y - corner2.y);
        ratio = fabs(height/width - 0.75);
        area = width * height;
        lowerRight.x = center.x + width/2;
        lowerRight.y = center.y - height/2;
        minX = center.x - width/2;
    }
};

vector<Map> maps;
map<string, Point> locIndice;

struct mapComp {
    Point loc;

    bool operator() (int i1, int i2) {
        const Map& m1 = maps[i1];
        const Map& m2 = maps[i2];       
        int cr;
        // area compare
        cr = cmp(m1.area, m2.area);
        if(cr > 0) return true; 
        if(cr < 0) return false; // 面积小的往后排
        
        // location is nearest the center of the map.
        cr = cmp(Dist2(loc, m1.center), Dist2(loc, m2.center));
        if(cr > 0) return true; 
        if(cr < 0) return false;
        
        //  aspect ratio is nearest to the aspect ratio of the browser window, which is 0.75.
        cr = cmp(m1.ratio, m2.ratio);
        if(cr > 0) return true; 
        if(cr < 0) return false;
        
        // which the location is furthest from the lower right corner of the map 
        cr = cmp(Dist2(loc, m1.lowerRight), Dist2(loc, m2.lowerRight));
        if(cr < 0) return true;
        if(cr > 0) return false;
        
        /*        
        one containing the smallest x-coordinate. 
        */
        cr = cmp(m1.minX, m2.minX);
        assert(!cr);
        
        if(cr > 0) return true; 
        if(cr < 0) return false;
        
        return true;
    }
};

void getMaps(const Point& p, vector<int>& mis, vector<int>& level) {
    mis.clear();
    mapComp mc;
    mc.loc = p;
    for(int i = 0; i < maps.size(); i++) {
        const Map& m = maps[i];
        if(inArea(p, m.corner1, m.corner2)) mis.push_back(i);
    }
    sort(mis.begin(), mis.end(), mc);
    level.clear();
    level.assign(mis.size(), 1);
    
    // cout<<endl;
    for(int i = 0; i < mis.size(); i++) {
        if(!i) continue;
        const Map& m = maps[mis[i]];
        const Map& pm = maps[mis[i-1]];
        int c = cmp(m.area, pm.area);
        assert(c <= 0);
        level[i] = level[i-1];
        if(c<0) level[i]++;
        // cout<<"name: "<<m.name<<", area : "<<m.area<<", level : "<<level[i]<<endl;
    }
}

void doRequest(const string& name, int level) {
    cout<<name<<" at detail level "<<level;
    
    if(!locIndice.count(name)) {
        cout<<" unknown location"<<endl;
        return;
    }
    
    vector<int> mis, levels;
    getMaps(locIndice[name], mis, levels);
    if(mis.empty()) {
        cout<<" no map contains that location"<<endl;
        return;
    }
    
    int maxLevel = levels.back();
    if(maxLevel < level)
         cout<<" no map at that detail level; using "<<maps[mis.back()].name<<endl;
    else
    {
         vector<int>::iterator it = upper_bound(levels.begin(), levels.end(), level);
         assert(it != levels.begin());
         cout<<" using "<<maps[mis[it-levels.begin()-1]].name<<endl;
    }
}

int main()
{
    string buf;
    getline(cin, buf);
    while(true) {
        Map m;
        cin>>m.name;
        if(m.name == "LOCATIONS") break;
        cin>>m.corner1>>m.corner2;
        m.init();
        maps.push_back(m);
    }
    Point loc;
    string name;
    while(true) {
        cin>>name;
        if(name == "REQUESTS") break;
        cin>>loc;
        locIndice[name] = loc;
    }
    
    while(true) {
        cin>>name;
        if(name == "END") break;
        int level;
        cin>>level;
        doRequest(name, level);
    }
    
    return 0;
}

/* 13481355	511	Do You Know the Way to San Jose?	Accepted	C++	0.018	2014-04-11 07:28:17 */