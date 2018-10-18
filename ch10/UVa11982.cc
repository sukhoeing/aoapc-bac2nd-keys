// UVa11982 Fantasy Cricket
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
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;
const LL M = 1000000007;
const int MAXN = 1000 + 4;
LL D[MAXN][MAXN];

void add_mod(LL& x, LL y) { x = (x + (y % M)) % M; }

LL solve(const char* S) {
  int N = strlen(S + 1);
  if (N == 0) return 1;
  _zero(D);
  D[0][0] = 1;
  _rep(i, 1, N) _rep(j, 0, i) {
    LL& d = D[i][j];
    if (S[i] == 'D')
      add_mod(d, D[i - 1][j] * j + D[i - 1][j + 1] * (j + 1) * (j + 1));
    else if (S[i] == 'U')
      add_mod(d, D[i - 1][j - 1] + D[i - 1][j] * j);
    else
      d = D[i - 1][j];
  }
  return D[N][0];
}

char S[MAXN];
int main() {
  int T;
  _ri1(T);
  _rep(t, 1, T) {
    scanf("%s", S + 1);
    printf("Case %d: %lld\n", t, solve(S));
  }

  return 0;
}
// 22149206 11982 Fantasy Cricket Accepted C++11 0.210 2018-10-18 14:51:43