// UVa1634 The Picnic
// 陈锋
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))

struct Point {
  int x, y;
  Point(int x = 0, int y = 0) : x(x), y(y) {}
  Point& operator=(const Point& p) {
    x = p.x, y = p.y;
    return *this;
  }
};
typedef Point Vector;
Vector operator+(const Vector& A, const Vector& B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator-(const Point& A, const Point& B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator*(const Vector& A, int p) { return Vector(A.x * p, A.y * p); }
bool operator==(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
bool operator!=(const Point& a, const Point& b) { return !(a == b); }
bool operator<(const Point& a, const Point& b) {
  if(a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}
int Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
int Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
int Area(const Point& A, const Point& B, const Point& C){ return abs(Cross(B-A, C-A)); }
// P inside Triangle ABC
bool inTriangle(const Point& P, const Point& A, const Point& B, const Point& C){
  int s = Area(A,B,C), s0 = Area(P,A,B), s1 = Area(P,A,C), s2 = Area(P,B,C);
  return s0 && s1 && s2 && (s0+s1+s2) == s;
}

const int MAXN = 100+4, INF = 0x7f7f7f7f;
int N, F[MAXN][MAXN]; // F[i][j] - 以j-i凸包最后一条边的凸包的最小面积
Point D[MAXN], Q[MAXN];
int DP(const int m){
  int ans = 0;
  _zero(F);
  _rep(i, 1, m) _for(j, 1, i) _for(k, j+1, i)
    if(Q[k] != Q[i] && Q[k] != Q[j] && inTriangle(Q[k], Point(0, 0), Q[j], Q[i])) {
      F[j][i] = -INF;  // 有点在三角形OIJ中，非法
      break;
    }
  _rep(i, 1, m) _for(j, 1, i) if(0 == F[j][i]){ // j,i是合法的凸壳边
    int &f = F[j][i], s = Cross(Q[j], Q[i]);
    f = s;
    for(int k = j-1; k; k--){
      if(Cross(Q[j]-Q[k], Q[i]-Q[j]) >= 0) // k->j->i是凸的
        f = max(f, s + F[k][j]);
      if(Cross(Q[k], Q[j]) == 0) break;
    }
    ans = max(ans, f);
  }
  return ans;
}
int solve(){
  int m, ans=0;
  sort(D+1, D+N+1);
  _for(i, 0, N){
    m = 0;
    _for(j, i+1, N) Q[++m] = D[j] - D[i];
    sort(Q+1, Q+m+1, [](const Point& A, const Point& B){ // 逆时针排列
      return Cross(A, B)>0 || (Cross(A,B) == 0 && Dot(A,A) < Dot(B,B));
    });
    ans = max(ans, DP(m));
  }
  return ans;
}
int main(){
  int T; 
  _ri1(T);
  while(T--){
    scanf("%d", &N);
    _for(i, 0, N) _ri2(D[i].x, D[i].y);
    double ans = 0.5 * solve();
    printf("%.1lf\n",ans);
  }
  return 0;
}
// 20658408 1634  The Picnic  Accepted  C++11 0.160 2018-01-24 15:57:23