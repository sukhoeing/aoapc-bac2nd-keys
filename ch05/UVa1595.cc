// Symmetry, ACM/ICPC Seoul 2004, UVa1595
// 陈锋
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-7;
int dcmp(double x) {
  if (fabs(x) < eps)
    return 0;
  return x < 0 ? -1 : 1;
}
struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  bool operator<(const Point &rhs) const {
    if (dcmp(x - rhs.x) != 0)
      return dcmp(x - rhs.x) < 0;
    return dcmp(y - rhs.y) < 0;
  }
};

Point points[1024];
set<Point> pIndice;
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  for (int N; T--;) {
    cin >> N;
    double sx = 0;
    pIndice.clear();
    for (int i = 0; i < N; i++) {
      Point &p = points[i];
      cin >> p.x >> p.y, sx += p.x, pIndice.insert(p);
    }
    sx /= N;

    bool ans = true;
    for (int i = 0; i < N; i++) {
      const Point &p = points[i];
      if (dcmp(p.x - sx) == 0)
        continue;
      Point p2(sx * 2 - p.x, p.y);
      if (!pIndice.count(p2)) {
        ans = false;
        break;
      }
    }
    puts(ans ? "YES" : "NO");
  }
  return 0;
}
// 14804235	1595	Symmetry	Accepted	C++	0.052
// 2015-01-15 00:20:13