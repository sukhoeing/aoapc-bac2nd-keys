// UVa712 S-Trees
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
const int MAXN = 8;
int N, DX[MAXN];
char T[1 << MAXN], V[MAXN];

int main() {
  char buf[1 << MAXN];
  int m;
  for (int t = 1; scanf("%d", &N) == 1 && N; t++) {
    printf("S-Tree #%d:\n", t);
    _for(i, 0, N) scanf("%s", buf), DX[i] = buf[1] - '1';
    scanf("%s", T);
    scanf("%d", &m);
    _for(i, 0, m) {
      scanf("%s", V);
      int d = 0, u = 1;
      while (d < N) u = 2 * u + (V[DX[d++]] - '0');
      printf("%c", T[u - (1 << N)]);
    }
    puts("\n");
  }
}
// 2173418	5565	S-Trees	Accepted	C++11	0.003	2017-05-03 04:47:54