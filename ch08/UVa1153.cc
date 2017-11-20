// UVa1153 Keep the Customer Satisfied
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
struct Order {
  int q, d;
  bool operator<(const Order& rhs) const { return d < rhs.d; }
};
const int MAXN = 800000 + 4;
int N;
Order Os[MAXN];

int main() {
  int T;
  _ri1(T);
  _for(t, 0, T) {
    if (t) puts("");
    _ri1(N);
    _for(i, 0, N) _ri2(Os[i].q, Os[i].d);
    sort(Os, Os + N);
    priority_queue<int> Q;  // 已经选择的订单
    int due = 0;
    _for(i, 0, N) {
      const auto& o = Os[i];
      if (due + o.q <= o.d)  // 排的下
        due += o.q, Q.push(o.q);
      else if (!Q.empty() && Q.top() > o.q) {
        due = due - Q.top() + o.q;
        Q.pop();
        Q.push(o.q);
      }
    }
    printf("%lu\n", Q.size());
  }
  return 0;
}