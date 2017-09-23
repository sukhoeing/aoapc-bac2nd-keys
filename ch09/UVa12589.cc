// Learning Vector, ACM/ICPC Dhaka 2012, UVa12589
// 陈锋
#include<cassert>
#include<cstdio>
#include<cmath>
#include<functional>
#include<algorithm>
#include<sstream>
#include<cstring>
#include<vector>
#include<queue>
#include<set>

using namespace std;
typedef long long int64;

struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
};
typedef Point Vector;

Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator- (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator* (const Vector& A, int p) { return Vector(A.x*p, A.y*p); }
bool operator== (const Point& a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool operator< (const Point& p1, const Point& p2) { return atan2(p1.y, p1.x) > atan2(p2.y, p2.x); }

const int MAXN = 50+2, MAXY = MAXN*MAXN;
int N, K, H, F[MAXN][MAXN][MAXY];
vector<Vector> vs;

// 令F(i,c,y)为已经决策过i个向量，选择了其中c个，折线的最高y坐标为y的时候，后续还能增加的最大面积。
// 结果就是F(0, 0, 0)

int dp(int i, int c, int y) {
    assert(i <= N);
    assert(c <= K);
    int& f = F[i][c][y];
    if(f >= 0) return f;
    
    if(i == N || c == K) return f = 0;
    
    f = dp(i+1, c, y);
    const Vector& v = vs[i];
    f = max(f, dp(i+1, c+1, y+v.y) + (2*y+v.y)*v.x);
    return f;
}

int main()
{
    int t, T;
    Vector v;
    scanf("%d\n", &T);
    for(t = 1; t <= T; t++) {
        H = 0, vs.clear(), scanf("%d%d\n", &N, &K);
        for(int i = 0; i < N; i++) {
            scanf("%d%d\n", &(v.x), &(v.y));
            assert(v.x || v.y);
            vs.push_back(v);
            H += v.y;
        }
        sort(vs.begin(), vs.end());
        for(int i = 0; i <= N; i++)
            for(int j = 0; j <= K; j++)
                for(int y = 0; y <= H; y++)
                    F[i][j][y] = -1;
        int ans = dp(0, 0, 0);
        printf("Case %d: %d\n", t, ans);
    }
}

// 1521430	LA 6208	Learning Vector	Accepted	C++	0.362	2014-08-16 09:49:02