// UVa1632 Alibaba
// 陈锋
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
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

const int MAXN = 10000 + 4, INF = 0x7f7f7f7f;
int N, D[MAXN], T[MAXN];
int DP[2][MAXN][2];

int main() {
  while (_ri1(N) == 1) {
    _for(i, 0, N) _ri2(D[i], T[i]);
    _zero(DP);
    int cur = 0;
    for (int i = N - 1; i >= 0; i--){ // cur:i cur^1 : i+1
      for (int j = i + 1; j < N; j++) {
        int& d0 = DP[cur][j][0];
        d0 = min(DP[cur^1][j][0] + D[i+1] - D[i], DP[cur^1][j][1] + D[j] - D[i]);
        if (d0 >= T[i]) d0 = INF;
        int& d1 = DP[cur][j][1];
        d1 = min(DP[cur][j-1][1] + D[j] - D[j-1], DP[cur][j-1][0] + D[j] - D[i]);
        if (d1 >= T[j]) d1 = INF;
      }
      cur ^= 1;
    } 

    int ans = min(DP[cur^1][N - 1][0], DP[cur^1][N - 1][1]);
    if (ans == INF)
      puts("No solution");
    else
      printf("%d\n", ans);
  }
  return 0;
}
// 20174917 1632    Alibaba Accepted    C++11   0.360   2017-10-14 08:44:56