// UVa1282 Fibonacci Words
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
typedef unsigned long long ULL;
const int MAXP = 100000 + 4, MAXN = 100 + 4;
LL F[MAXN], D[MAXN];
string FS[MAXN], P;

// FS[n] starts with P[st,ed)
bool startsWith(int n, const string &p, int st, int ed) {
  assert(n >= 0);
  int sz = ed - st;
  if (F[n] < sz) return false;
  if (F[n] == sz) return equal(begin(p) + st, begin(p) + ed, begin(FS[n]));
  if (F[n - 1] >= sz) return startsWith(n - 1, p, st, ed);
  return equal(begin(FS[n - 1]), end(FS[n - 1]), begin(p) + st) &&
         startsWith(n - 2, p, st + F[n - 1], ed);
}

bool endsWith(int n, const string &p, int st, int ed) {  // FS[n] ends with P
  assert(n >= 0);
  int sz = ed - st;
  if (F[n] < sz) return false;
  if (F[n] == sz) return equal(begin(FS[n]), end(FS[n]), begin(p) + st);
  if (F[n - 2] >= sz) return endsWith(n - 2, p, st, ed);
  return endsWith(n - 1, p, st, ed - F[n - 2]) &&
         equal(begin(FS[n - 2]), end(FS[n - 2]), begin(p) + ed - F[n - 2]);
}

LL DP(int n) {  // count of P in F(n)
  LL &d = D[n];
  if (d > -1) return d;
  d = 0;
  int sz = P.size();
  if (F[n] < sz) return d = 0;
  if (F[n] == sz) return d = (P == FS[n] ? 1 : 0);
  assert(n >= 2);
  d += DP(n - 1) + DP(n - 2);
  _for(i, 1, sz) {
    if (endsWith(n - 1, P, 0, i) && startsWith(n - 2, P, i, sz)) d++;
  }
  return d;
}

void init() {
  fill_n(F, MAXN, LONG_MAX);
  F[0] = 1, F[1] = 1;
  FS[0] = '0', FS[1] = '1';
  _for(i, 2, MAXN) {
    F[i] = F[i - 1] + F[i - 2];
    FS[i] = FS[i - 1] + FS[i - 2];
    if (F[i] > MAXP) break;
  }
}

int main() {
  int N;
  init();
  for (int t = 1; cin >> N; t++) {
    cin >> P;
    _init(D, -1);
    LL ans = DP(N);
    cout << "Case " << t << ": " << ans << "\n";
  }
  return 0;
}
// 20233095 1282 Fibonacci Words Accepted C++11 1.340 2017-10-24 08:17:43