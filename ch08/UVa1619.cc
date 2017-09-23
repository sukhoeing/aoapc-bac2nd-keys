// UVa1619 Feel Good
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
#include <stack>
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
int A[MAXN], L[MAXN], R[MAXN], N;  // A[i] is minimum in A(L, R)
LL Sum[MAXN];

int main() {
  Sum[0] = 0;
  for (int t = 0; _ri1(N) == 1; t++) {
    if (t) puts("");
    _rep(i, 1, N) { _ri1(A[i]), Sum[i] = Sum[i - 1] + (LL)A[i]; }
    stack<int> s1;
    _rep(i, 1, N) {
      while (!s1.empty() && A[s1.top()] >= A[i]) s1.pop();
      L[i] = s1.empty() ? 0 : s1.top();
      s1.push(i);
    }

    stack<int> s2;
    for (int i = N; i >= 1; i--) {
      while (!s2.empty() && A[s2.top()] >= A[i]) s2.pop();
      R[i] = s2.empty() ? (N + 1) : s2.top();
      s2.push(i);
    }
    LL ans = -1;
    int ans_i;
    _rep(i, 1, N) {
      LL v = (Sum[R[i] - 1] - Sum[L[i]]) * (LL)A[i];
      if (v > ans) ans = v, ans_i = i;
    }
    if (ans == 0)
      printf("0\n1 1\n");
    else
      printf("%lld\n%d %d\n", ans, L[ans_i] + 1, R[ans_i] - 1);
  }
  return 0;
}
// 19949519	1619	Feel Good	Accepted	C++11	0.140	2017-09-02 08:04:46