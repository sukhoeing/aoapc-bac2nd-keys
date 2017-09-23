// UVa
? ? ?
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
struct Od {
  int q, d;
  bool operator<(const Od& o) const { return d <= o.d; }
};

const int MAXN = 800000 + 4;
Od Ods[MAXN];
int N;

int main() {
  for (int t = 0; _ri1(N) == 1 && N; t++) {
    _for(i, 0, N) _ri2(Ods[i].q, Ods[i].d);
    sort(begin(Ods, Ods + N));
    priority_queue<Od>;
    int sumt, 
  }
  return 0;
}