// Caravan Robbers, ACM/ICPC NEERC 2012, UVa1616
// 陈锋
#include <bits/stdc++.h>
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
using namespace std;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
const double eps = 1e-7;
int dcmp(double x) {
  if (fabs(x) < eps)
    return 0;
  return x < 0 ? -1 : 1;
}
int dcmp(double x, double y) { return dcmp(x - y); }
struct Seg {
  int a, b;
  bool operator<(const Seg &s) const { return a <= s.a; }
};
const int NN = 1e5 + 4;
int n;
Seg segs[NN];
bool tryLen(const double l) {
  double lb = 0;
  _for(i, 0, n) {
    const Seg &s = segs[i];
    lb = max((double)s.a, lb) + l;
    if (lb > s.b)
      return false;
  }
  return true;
}

void output(double l) {
  double ip = floor(l + eps);
  if (dcmp(ip, l) == 0) {
    printf("%.0lf/1\n", ip);
    return;
  }
  int p = 1, q = 1;              // p/q
  double ans = 1;                // 目前为止最接近l的p/q值
  for (int i = 1; i <= n; i++) { // i作为分母
    int cp = (int)(floor(l * (double)i + 0.5)); // 可能的分子
    double x = (double)cp / i;
    if (fabs(x - l) < fabs(ans - l))
      q = i, p = cp, ans = x;
  }
  int g = gcd(p, q);
  printf("%d/%d\n", p / g, q / g);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  while (cin >> n) {
    _for(i, 0, n) cin >> segs[i].a >> segs[i].b;
    sort(segs, segs + n);
    double l = 1, r = 1e6 / n;
    assert(dcmp(l, r) <= 0);
    _for(b, 0, 50) {
      double m = (l + r) / 2;
      if (!tryLen(m))
        r = m;
      else
        l = m;
    }
    output((l + r) / 2);
  }
  return 0;
}
// 20497012 1616    Caravan Robbers Accepted    C++11   0.070   2017-12-16
// 11:44:52