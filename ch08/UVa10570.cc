// UVa10570 Meeting with Aliens
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
const int MAXN = 500 + 4;
int N, O[MAXN], OC[MAXN], Pos[MAXN];
int solve() {
  int ans = 0;
  _for(i, 0, N) {
    int p = Pos[i];
    if (p == i) continue;
    Pos[OC[i]] = p, Pos[i] = i;
    swap(OC[i], OC[p]), ans++;
  }
  return ans;
}

void copy(int st, int step) {
  _for(i, 0, N) {
    int a = (OC[i] = O[(st + step * i + N) % N]);
    Pos[a] = i;
  }
}

int main() {
  while (_ri1(N) == 1 && N) {
    _for(i, 0, N) _ri1(O[i]), O[i]--;
    int ans = MAXN;
    _for(i, 0, N) {
      copy(i, 1);
      ans = min(ans, solve());
      copy(i, -1);
      ans = min(ans, solve());
    }
    printf("%d\n", ans);
  }
  return 0;
}
// 19969928	10570	Meeting with Aliens	Accepted	C++11	0.060	2017-09-07 05:23:47