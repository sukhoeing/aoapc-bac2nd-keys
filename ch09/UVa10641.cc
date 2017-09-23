// Barisal Stadium, UVa10641
// 陈锋
#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <climits>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const double eps = 1e-7, Pi = acos(-1);
double dcmp(double x) { if(fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
bool dcmp(double x, double y) { return dcmp(x-y) < 0; }

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) {}
  Point& operator=(const Point& p) {
    this->x = p.x, this->y = p.y;
    return *this;
  }
};
typedef Point Vector;
Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Point& operator+=(Point& p, const Vector& A) { p.x += A.x; p.y += A.y; return p; }
Vector operator- (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator* (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
bool operator== (const Point& a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool operator< (const Point& p1, const Point& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }

double operator*(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Length(const Vector& A) { return sqrt(A*A); }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }

istream& operator>>(istream& is, Point& p) { return is>>p.x>>p.y; }

// 灯的照射范围为[l, r)，代价为c，如果r>N，那么表示r-N号顶点
struct Light{ int l, r, c; }; 

const int MAXN = 32, MAXM = 1000+4, INF = 0x3f3f3f3f;
int N, M;
Point V[MAXN], O;
Light lights[MAXM];

// lt能照到线段[a,b]吗？
bool canCover(const Point& lt, const Point& a, const Point& b) {
    return dcmp(Cross(lt-a, b-a) * Cross(O-a, b-a)) < 0;
}
// 坐标为p的灯lt能照亮顶点编号区间呢，预处理出来
void getCover(Light& lt, const Point& p) {
    vector<bool> flag(N);
    _for(i, 0, N) flag[i] = canCover(p, V[i], V[i+1]);

    if(flag[0] && flag[N-1]) {
        int l = N - 1, r = N;
        while(flag[l]) lt.l = l--;
        while(flag[r-N]) lt.r = r++;
    } else {
        int l = 0, r = N-1;
        while(l<N && !flag[l]) l++;
        lt.l = l;
        while(r>=0 && !flag[r]) r--;
        lt.r = r;
    }

    lt.r++;
    if(lt.r < lt.l) lt.r += N;    
}

int solve() {
    int ans = INF;
    vector<int> D(2*N);
    _for(i, 0, N) { // 从第i个顶点开始考虑
        fill(D.begin(), D.end(), INF);
        D[i] = 0; // D[j]表示i到第j个顶点之间的边都被照射到的最小代价
        _for(j, i, i+N) _for(k, 0, M){
            const Light& lt = lights[k];
            if(lt.l > j) continue; // lt照不到j
            int r = min(lt.r, i+N); // 使用了灯lt之后能照到的右边界
            D[r] = min(D[r], D[j] + lt.c); // 是否使用灯lt
        }
        ans = min(ans, D[i+N]);
    }
    return ans;
}

int main() {
    while(cin>>N && N) {
        O.x = 0, O.y = 0;
        _for(i, 0, N) cin>>V[i], O += V[i];
        O.x /= N, O.y /= N;
        V[N] = V[0];
        
        cin>>M;
        Point p;
        _for(i, 0, M) {
            cin>>p>>lights[i].c;
            getCover(lights[i], p);
        }
        
        int ans = solve();
        if(ans == INF) cout<<"Impossible."<<endl;
        else cout<<ans<<endl;
    }
    return 0;
}

// 14975237	10641	Barisal Stadium	Accepted	C++	0.196	2015-02-13 08:57:42