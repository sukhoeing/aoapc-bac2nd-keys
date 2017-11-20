// UVa1614 Hell on the Markets
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
const int MAXN = 100000 + 4;
int A[MAXN], N, F[MAXN];

int main() {
  while (_ri1(N) == 1 && N) {
    LL S = 0, T = 0;
    _for(i, 0, N) _ri1(A[i]), S += A[i];
    if (S % 2 == 1) {
      puts("No");
      continue;
    }
    puts("Yes");
    for (int i = N - 1; i >= 0; i--) {
      F[i] = 1;
      if (2 * (T + A[i]) <= S) F[i] = -1, T += A[i];
    }
    _for(i, 0, N) printf("%d%s", F[i], i == N - 1 ? "\n" : " ");
  }
  return 0;
}
// 20363675 1614 Hell on the Markets Accepted C++11 0.180 2017-11-18 13:19:14