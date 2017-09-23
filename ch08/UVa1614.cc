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
int N, F[MAXN];
struct Node {
  int id, v;
  bool operator<(const Node& rhs) const { return v > rhs.v; }
};
Node A[MAXN];

int main() {
  while (_ri1(N) == 1 && N) {
    _for(i, 0, N) _ri1(A[i].v), A[i].id = i;
    sort(A, A + N);
    LL sum = 0;
    F[A[0].id] = 1, sum = A[0].v;
    _for(i, 1, N) {
      auto a = A[i];
      if (sum >= 0)
        sum -= a.v, F[a.id] = -1;
      else
        sum += a.v, F[a.id] = 1;
    }
    if (sum == 0) {
      puts("Yes");
      _for(i, 0, N) printf("%d%s", F[i], (i == N - 1) ? "\n" : " ");
    } else {
      puts("No");
    }
  }
  return 0;
}
// 19965076	1614	Hell on the Markets	Accepted	C++11	0.180	2017-09-06 04:08:20