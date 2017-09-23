// UVa12063 Zeros and Ones
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
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, sizeof(D));
#define _init(D, v) memset((D), (v), sizeof(D));
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 64 + 4, MAXK = 100 + 4;
/*
 to get all the
 set D(i,b,k) is count of bin numbers satisfied:
 %K = k, no prefix 0, length is i, has b 1s
*/
ULL D[MAXN][MAXN][MAXK];
int N, K;

ULL solve() {
  if (N % 2) return 0;
  if (K == 0) return 0;
  _zero(D);
  D[1][1][0] = (K == 1), D[1][1][1] = 1 % K;
  _for(i, 1, N) _rep(b, 1, i) _for(k, 0, K) {
    D[i + 1][b][(2 * k) % K] += D[i][b][k];          // append 0
    D[i + 1][b + 1][(2 * k + 1) % K] += D[i][b][k];  // append 1
  }
  return D[N][N / 2][0];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; scanf("%d%d", &N, &K) == 2; t++) {
    ULL ans = solve();
    printf("Case %d: %llu\n", t, ans);
  }
  return 0;
}
// 19819967	12063	Zeros and Ones	Accepted	C++11	0.090	2017-08-08 08:19:28