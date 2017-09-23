// UVa11246 K-Multiple Free Set
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

LL solve(LL n, LL k) {
  LL pk = k, sign = -1, ans = n;
  while (pk < n) {
    ans += sign * n / pk;
    pk *= k, sign = -sign;
  }
  return ans;
}

int main() {
  int T;
  cin >> T;
  LL n, k;
  while (cin >> n >> k) {
    LL ans = solve(n, k);
    cout << ans << endl;
  }
  return 0;
}
// 19805808	11246	K-Multiple Free set	Accepted	C++11	0.000	2017-08-05 07:31:58 