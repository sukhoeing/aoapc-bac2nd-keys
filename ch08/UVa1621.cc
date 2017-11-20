// LA6286 Jumping Around
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
#define _repc(cnt) for (int i = 0; i < (int)(cnt); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;
int N, A[4], cur;
set<int> vis;
void move(int step) {
  int ci = abs(step);
  assert(ci > 0);
  cur += step;
  assert(cur >= 0 && cur < N);
  // assert(!vis.count(cur));
  // vis.insert(cur);
  printf(" %d", cur);
  assert(A[ci--]);
}

void move(int step, int cnt) { _repc(cnt) move(step); }

void solve() {
  printf("0"), vis.clear(), cur = 0, vis.insert(0);
  int c3 = A[3] / 3, cm3 = A[3] % 3;
  if (cm3 == 0) {
    move(3, c3), move(1);   // 0, 3...c3*3 c3*3+1
    move(-3, c3), move(1);  // c3*3-2, ....4, 1 -1-> 2
    move(3, c3);            // 2->5->8..-> c3*3+2
  }
  if (cm3 == 1) {
    move(3, c3 + 1), move(-2);  // 0, 3...c3*3 3*c3 -> 3*c3+3-2
    move(-3, c3), move(1);      // 3*c3+1...4,1->2
    move(3, c3), move(2);       // 2,5,8...
  }
  if (cm3 == 2) {
    move(3, c3 + 1), move(-1);  // 0, 3...c3*3, 3*c3+3->3*c3+2
    move(-3, c3), move(-1);     // 3*c3+2->5->2->1
    move(3, c3 + 1);            // 1->4->3*c3+4
  }
  move(1, A[1] - 1);
  int b2 = A[2] / 2, bm2 = A[2] % 2;
  if (bm2 == 0)  // x -> x+2 -> x+4, N-2 -> N-2 -> ...x+1
    move(2, b2), move(1), move(-2, b2);
  else  // x -> x+2 -> x+4 -> N-1 -> N-2 -> ... x+1
    move(2, b2 + 1), move(-1), move(-2, b2);
  // assert(vis.size() == (size_t)N);
  puts("");
}

int main() {
  int t;
  while (_ri1(t) == 1) {
    while (t--) {
      _ri3(A[1], A[2], A[3]);
      N = A[1] + A[2] + A[3] + 1;
      solve();
    }
  }
  return 0;
}
// 2319168 6286 Jumping Around Accepted C++11 0.059 2017-11-18 09:27:43