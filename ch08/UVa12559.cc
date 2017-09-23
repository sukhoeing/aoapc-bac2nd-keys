// UVa12559	Finding Black Circles
// 陈锋
#include <cassert>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
int readint() { int x; cin>>x; return x; }
const double pi=acos(-1);

struct circle { // 表示一个圆的结构
    int r, x, y;
    circle(int _r, int _x, int _y = 0) : r(_r), x(_x), y(_y) { }
    bool operator<(const circle& c) const {
        if(r != c.r) return r < c.r;
        if(x != c.x) return x < c.x;
        return y < c.y;
    }
};

ostream& operator<<(ostream& os, const circle& c) {
    char buf[128];
    sprintf(buf, " (%d,%d,%d)", c.r, c.x, c.y);
    return os<<buf;
}

vector<string> lines;
int w, h;
bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return left <= x && x <= right;
}

int main()
{
    int T = readint();
    vector<circle> ans;
    _for(t, 1, T+1) {
        ans.clear();
        cin>>w>>h;
        lines.resize(h);
        _for(j, 0, h) cin>>lines[j];
        
        _for(r, 5, 51) _for(x, r, w-r+1) _for(y, r, h-r+1) { // r是坐标, x 是列，y是行
            int all = 0, per = 0;                        
            _for(i, 0, 100){
                double th = rand()/(RAND_MAX+1.0) * 2 * pi; // 随机选取一个角度
                int cx = (int)(x + r * cos(th) + 0.5), cy = (int)(y + r * sin(th) + 0.5);
                if(inRange(cx, 0, w-1) && inRange(cy, 0, h-1) && lines[cy][cx]=='1') per++; 
                all++;
                if(all > 10 && 2*per < all) break; // 剪枝
            }
            
            if(per / (double)all > 0.8) ans.push_back(circle(r, x, y));
        }
            
        cout<<"Case "<<t<<": "<<ans.size();
        _for(i, 0, ans.size()) cout<<ans[i];
        cout<<endl;
    }
    
    return 0;
}

// 14772360	12559	Finding Black Circles	Accepted	C++	2.139	2015-01-07 06:35:20