// UVa10886 Standard Deviation
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
#include <numeric>
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
typedef unsigned long long ULL;

struct Gen {
  ULL seed;
  ULL gen() {
    seed >>= 16;
    seed &= (1ULL << 32) - 1;
    seed *= seed;
    return seed;
  }
};

typedef long double LD;
const LD Z = (LD)1.0 / (1LL << 32);

int main() {
  int T, N;
  ULL seed;
  scanf("%d", &T);
  _rep(t, 1, T) {
    Gen gen;
    scanf("%d%llu", &N, &(seed));
    gen.seed = seed;
    LD sq = 0, m = 0;
    _for(i, 0, N) {
      auto g = gen.gen();
      LD x = g * Z;
      printf("%llx, ", g);
      if (g == 0) {
        break;
      } else if (g == (1ULL << 32)) {
        sq += x * x * (N - i), m += x * (N - i);
        break;
      } else {
        sq += x * x, m += x;
      }
    }
    puts("");
    m /= N, sq /= N;
    LD ans = sqrt(sq - m * m);
    printf("Case #%d: %.5Lf\n", t, ans);
  }
}
// 19747300	10886	Standard Deviation	Accepted	C++11	0.000	2017-07-26 15:23:15