// Learning Vector, ACM/ICPC Dhaka 2012, UVa12589
// 陈锋
#include<bits/stdc++.h>
using namespace std;
struct Point {
  int x, y;
  Point(int x = 0, int y = 0): x(x), y(y) {}
};
typedef Point Vector;
bool operator< (const Point& p1, const Point& p2) { return atan2(p1.y, p1.x) > atan2(p2.y, p2.x); }
const int NN = 50 + 2, YY = NN * NN;
int N, K, H, F[NN][NN][YY];
vector<Vector> vs;
// F(i,c,y)为已经决策过i个向量，选择了其中c个，折线的最高y坐标为y的时候，后续还能增加的最大面积。
int dp(int i, int c, int y) {
  assert(i <= N), assert(c <= K);
  int& f = F[i][c][y];
  if (f >= 0) return f;
  if (i == N || c == K) return f = 0;
  f = dp(i + 1, c, y);
  return f = max(f, dp(i + 1, c + 1, y + vs[i].y) + (2 * y + vs[i].y) * vs[i].x);
}
int main() {
  int T;
  ios::sync_with_stdio(false), cin.tie(0);
  cin>>T;
  for (int t = 1; t <= T; t++) {
    H = 0, vs.clear(), cin>>N>>K;
    for (int i = 0, x, y; i < N; i++)
      cin>>x>>y, vs.push_back(Vector(x,y)), H += y;
    sort(vs.begin(), vs.end());
    memset(F, -1, sizeof(F));
    int ans = dp(0, 0, 0);
    printf("Case %d: %d\n", t, ans);
  }
}
// 1521430  LA 6208 Learning Vector Accepted  C++ 0.362 2014-08-16 09:49:02