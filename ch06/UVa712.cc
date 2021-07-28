// UVa712 S-Trees
// 陈锋
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
typedef long long LL;
const int NN = 8;
int N, DX[NN];
char T[1 << NN], V[NN];
int main() {
  char buf[1 << NN];
  for (int t = 1, m; scanf("%d", &N) == 1 && N; t++) {
    printf("S-Tree #%d:\n", t);
    _for(i, 0, N) scanf("%s", buf), DX[i] = buf[1] - '1';
    scanf("%s", T), scanf("%d", &m);
    _for(i, 0, m) {
      scanf("%s", V);
      int d = 0, u = 1;
      while (d < N)
        u = 2 * u + (V[DX[d++]] - '0');
      printf("%c", T[u - (1 << N)]);
    }
    puts("\n");
  }
}
// 2173418	5565	S-Trees	Accepted	C++11	0.003	2017-05-03
// 04:47:54