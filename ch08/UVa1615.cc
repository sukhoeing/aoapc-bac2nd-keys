// UVa1615 Highway
// 陈锋
#include <bits/stdc++.h>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
struct Point {
  double x, y;
  Point(double x = 0, double y = 0): x(x), y(y) {}
};

const double eps = 1e-4;
double dcmp(double x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
typedef Point Segment;

const int MAXN = 100000 + 10;
int L, D, N;
Point points[MAXN];
vector<Segment> segs;

// 圆[p,D]和x轴的两个交点
Segment getInterSeg(const Point& p) {
  double m = sqrt(D * D - p.y * p.y), x = p.x - m, y = p.x + m;
  if (dcmp(x) < 0) x = 0;
  if (dcmp(y - L) > 0) y = L;
  return Segment(x, y);
}

bool segcmp(const Segment & sl, const Segment & sr) {
  double yd = dcmp(sl.y - sr.y);
  return yd < 0 || (yd == 0 && dcmp(sl.x - sr.x) > 0);
}

void solve() {
  segs.clear();
  _for(i, 0, N) segs.push_back(getInterSeg(points[i]));
  sort(segs.begin(), segs.end(), segcmp);
  int ans = 1;
  double p = segs[0].y;
  for (size_t i = 1; i < segs.size(); i++) {
    const Segment& prev = segs[i - 1], &cur = segs[i];
    if (dcmp(cur.x - prev.x) < 0) continue;
    if (dcmp(cur.x - p) > 0) { p = cur.y; ans++; }
  }
  cout << ans << endl;
}

int main() {
  while (cin >> L >> D >> N) {
    _for(i, 0, N) cin >> points[i].x >> points[i].y;
    solve();
  }
  return 0;
}

// 14804615 1615    Highway Accepted    C++ 0.029   2015-01-15 04:20:20