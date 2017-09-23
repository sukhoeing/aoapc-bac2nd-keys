// UVa557 Burger
// 陈锋
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)

typedef long long LL;

const int MAXK = 100000;
double LNSUM[MAXK];

int main() {
  int T, N;
  scanf("%d", &T);
  LNSUM[1] = 0;
  _for(k, 2, MAXK) LNSUM[k] = log(k) + LNSUM[k - 1];

  while (T--) {
    scanf("%d", &N);
    // 1 - C(2n-2, n-1)/2^2n-2 = 1 - (2n-2)!/(n-1)!(n-1)!*2^(2n-2) = 1 -
    // (2n-2)!/(n-1)!(n-1)!*2^(2n-2)
    N /= 2;
    double ans = 1 - exp(LNSUM[2 * N - 2] - 2 * LNSUM[N - 1] - (2 * N - 2) * log(2));
    printf("%.4lf\n", ans);
  }
  return 0;
}
// 2206466	5578	Burger	Accepted	C++11	0.013	2017-07-16 14:43:25