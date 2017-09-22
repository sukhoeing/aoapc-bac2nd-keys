// Knight Moves, UVa439
// 陈锋 C++11
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <queue>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
};
typedef Point Vector;

Vector operator+ (const Vector &A, const Vector &B) { return Vector(A.x + B.x, A.y + B.y); }
bool operator== (const Point &a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return left <= x && x <= right;
}

const int N = 8;
Point toPoint(const char* ps) { return Point(ps[0] - 'a', ps[1] - '1'); }
bool isValid(const Point &p) { return inRange(p.x, 0, N - 1) && inRange(p.y, 0, N-1); }
Vector dirVs[N] = {{2, 1}, {1, 2}, { -1, 2}, { -2, 1}, { -2, -1}, { -1, -2}, {1, -2}, {2, -1}};

int solve(const Point &from, const Point &to) {
    int vis[N][N];
    memset(vis, -1, sizeof(vis));
    queue<Point> q;
    q.push(from);
    vis[from.x][from.y] = 0;
    while(!q.empty()) {
        const Point &f = q.front(); q.pop();Ï
        int d = vis[f.x][f.y];
        if(f == to) return d;
        _for(i, 0, N) {
            Point np = f + dirVs[i];
            if(isValid(np) && vis[np.x][np.y] == -1) {
                vis[np.x][np.y] = d + 1;
                q.push(np);
            }
        }
    }
    assert(false);
}

int main() {
    char a[16], b[16];
    while(scanf("%s%s", a, b) == 2){
        int ans = solve(toPoint(a), toPoint(b));
        printf("To get from %s to %s takes %d knight moves.\n", a, b, ans);
    }
}
// 14804431	439	Knight Moves	Accepted	C++	0.052	2015-01-15 03:03:43