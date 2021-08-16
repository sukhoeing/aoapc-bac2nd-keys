// UVa1001,Say Cheese, ACM/ICPC World Finals 2001
// 陈锋
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int NN = 100 + 5;
struct Point3 {
  double x, y, z;
  Point3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
  double dist(const Point3 &p) const {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) +
                (z - p.z) * (z - p.z));
  }
};
istream &operator>>(istream &is, Point3 &p) { return is >> p.x >> p.y >> p.z; }
Point3 C[NN];            // 球心
double R[NN], D[NN][NN]; // 半径, 两球心最短路
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  for (int n, t = 1; cin >> n && n > 0;) {
    for (int i = 0; i < n; i++)
      cin >> C[i] >> R[i];
    cin >> C[n], R[n++] = 0;
    cin >> C[n], R[n++] = 0;
    for (int i = 0; i < n; i++) {
      D[i][i] = 0;
      for (int j = i + 1; j < n; j++)
        D[i][j] = D[j][i] = 10 * max(0.0, C[i].dist(C[j]) - R[i] - R[j]);
    }
    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          D[i][j] = min(D[i][k] + D[k][j], D[i][j]);
    printf("Cheese %d: Travel time = %.0lf sec\n", t++, D[n - 1][n - 2]);
  }
  return 0;
}
// 14805850	1001 Say Cheese	Accepted C++	0.036 2015-01-15 10:13:16