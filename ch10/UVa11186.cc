// UVa11186 Circum Triangle
// 陈锋
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;
const double PI = 2 * acos(0);

int main() {
  int N, R;
  while (_ri2(N, R) == 2 && N && R) {
    double ans = PI * (N * (N - 1) * (N - 2) / 6), x;
    vector<double> A;
    _for(i, 0, N) scanf("%lf", &x), A.push_back(x / 360.0 * 2 * PI);
    sort(begin(A), end(A));
    _for(i, 0, N) _for(j, i + 1, N) {
      int k = j - i;
      double x = (A[j] - A[i]) / 2, area = x - cos(x) * sin(x);
      ans -= (k - 1) * (PI - area) + (N - k - 1) * area;
    }
    ans *= R * R;
    printf("%.0lf\n", ans);
  }
  return 0;
}
// 19900570	11186	Circum Triangle	Accepted	C++11	0.040	2017-08-23 02:03:04