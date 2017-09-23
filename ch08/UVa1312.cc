// Cricket Field, ACM/ICPC NEERC 2002, UVa1312
// 陈锋
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;

int readint() { int x; cin>>x; return x; }

const int MAXN = 104;
struct Point {
    int x, y;
    bool operator<(const Point & p) const { return x < p.x; }
};
istream& operator>>(istream& is, Point& p) { return is>>p.x>>p.y; }

Point Ps[MAXN];
int N, W, H;
set<int> Ys; // 所有的树的Y坐标

int solve(Point& ans) {
    sort(Ps, Ps+N);
    int len = 0;
    vector<int> Y(Ys.begin(), Ys.end());
    _for(a, 0, Y.size()) _for(b, a+1, Y.size()) {
        int miny = Y[a], maxy = Y[b], dy = maxy - miny;
        if(dy <= len) continue; // 边长

        int left = 0; // 正方形左边界
        _for(i, 0, N) {
            const Point& p = Ps[i];
            if(p.y <= miny || p.y >= maxy) continue;
            if(len < min(dy, p.x - left)) {
                len = min(dy, p.x - left);
                ans.x = left;
                ans.y = miny;
            }
            left = p.x;
        }
        if(len < min(dy, W - left)) {
            len = min(dy, W - left);
            ans.x = left;
            ans.y = miny;
        }
    }
    
    return len;
}

int main(){
    int T = readint();
    Point ans; 
    _for(t, 0, T) {
        if(t) cout<<endl;
        cin>>N>>W>>H;
        Ys.clear(), Ys.insert(0), Ys.insert(H);
        _for(i, 0, N) cin>>Ps[i], Ys.insert(Ps[i].y);
        int len = solve(ans);
        cout<<ans.x<<" "<<ans.y<<" "<<len<<endl;
    }
    return 0;
}

// 14933028	1312	Cricket Field	Feng Chen (sukhoeing)	AC	C++	0.019	7	