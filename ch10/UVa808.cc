// UVa808 Bee Breeding
// 陈锋
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

using namespace std;
const int MAXN = 10000;
struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
    Point& operator=(const Point& p) { x = p.x; y = p.y; return *this;}
};
typedef Point Vector;

Vector operator+(const Vector& A, const Vector& B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator-(const Point& A, const Point& B) { return Vector(A.x - B.x, A.y - B.y); }

Point pos[MAXN + 330];
vector<Vector> dirs = {{-1,0}, { -1,1}, {0,1}, {1,0}, {1,-1}, {0,-1}}; //六个方向
int main() {
    int pi = 2;
    pos[pi] = Point(1, -1);
    auto calPos = [&pi](int dir, int l) { //向dir方向递推l个格子的坐标
        pi++;
        while (l--) {
            pos[pi] = pos[pi - 1] + dirs[dir];
            pi++;
        }
        pi--;
    };

    auto dist = [](const Vector & v) {
        if ((v.x < 0 && v.y > 0) || (v.x > 0 && v.y < 0))
            return max(abs(v.x), abs(v.y));
        return abs(v.x + v.y);
    };

    // 按照每一圈递推坐标
    _rep(l, 1, 58) { // 第l个圈
        _for(dir, 0, 4) calPos(dir, l);
        calPos(4, l + 1);
        calPos(5, l);
    }

    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n)
        printf("The distance between cells %d and %d is %d.\n", 
            n, m, dist(pos[n] - pos[m]));

    return 0;
}
// 1950012  LA 5208 Bee Breeding    Accepted    C++11   0.009   2016-05-03 10:20:07