// UVa1631 Locker
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
const int MAXN = 1000 + 4;
int N;
int D[MAXN][10][10][10];
string S, T;

inline int up(int i, int c) { return (i + c) % 10; }
inline int down(int i, int c) { return (i - c + 20) % 10; }
/*
  D(i, i0, i1, i2) -> cur i num in pos (i,i+1,i+2)  is i0,i1,i2
*/
int dp(int i, int i0, int i1, int i2) {
  int &d = D[i][i0][i1][i2], ti = T[i] - '0',
      s3 = i + 3 >= N ? 0 : S[i + 3] - '0';
  if (d > -1) return d;
  if (i == N - 1) return d = min((i0 - ti + 10) % 10, (ti - i0 + 10) % 10);
  if (i0 == ti) return d = dp(i + 1, i1, i2, s3);
  d = INT_MAX;
  int kup = (ti - i0 + 10) % 10;  // steps of rotating up to T[i]
  _rep(k1, 0, kup) _rep(k2, 0, k1) d =
      min(d, kup + dp(i + 1, up(i1, k1), up(i2, k2), s3));
  int kdown = (i0 - ti + 10) % 10;
  _rep(k1, 0, kdown) _rep(k2, 0, k1) d =
      min(d, kdown + dp(i + 1, down(i1, k1), down(i2, k2), s3));
  return d;
}

int main() {
  while (cin >> S >> T) {
    while (S.size() < 3) S.push_back('0'), T.push_back('0');
    N = S.size();
    _init(D, -1);
    int ans = dp(0, S[0] - '0', S[1] - '0', S[2] - '0');
    printf("%d\n", ans);
  }
  return 0;
}
// 20189704	1631	Locker	Accepted	C++11	0.130	2017-10-17
// 03:31:19