// UVa766 Sum of powers
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
#include <map>
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
const int MAXK = 20 + 4;
LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
LL lcm(LL a, LL b) { return (a && b) ? a * b / gcd(a, b) : 0; }
struct Rational {
  LL a, b;  // a/b
  Rational operator+(const Rational& r) {
    if (r.a == 0) return *this;
    LL na = a * r.b + b * r.a, nb = b * r.b;
    Rational ans = {na, nb};
    return ans.reduce();
  }
  Rational operator-(const Rational& r) {
    if (r.a == 0) return *this;
    Rational ans = {a * r.b - b * r.a, b * r.b};
    return ans.reduce();
  }
  Rational operator/(LL x) {
    assert(x);
    Rational ans = {a, b * x};
    return ans.reduce();
  }
  Rational operator*(LL x) {
    Rational ans = {a * x, b};
    return ans.reduce();
  }
  Rational& reduce() {
    LL g = gcd(a, b);
    a /= g, b /= g;
    return *this;
  }
};

LL C[MAXK][MAXK], M[MAXK];
Rational S[MAXK][MAXK];

void init() {
  C[0][0] = 1;
  C[1][0] = 1, C[1][1] = 1;
  _for(k, 2, MAXK) {
    C[k][0] = 1;
    _rep(i, 1, k) C[k][i] = C[k - 1][i] + C[k - 1][i - 1];
  }
}

int main() {
  init();
  _for(i, 0, MAXK) _for(j, 0, MAXK) S[i][j] = {0, 1};
  M[0] = 1, S[0][1] = Rational{1, 1};
  _rep(k, 1, 20) {
    _rep(i, 1, k + 1) S[k][i] = S[k][i] + Rational{C[k + 1][i], 1};
    _for(i, 0, k) _rep(j, 0, k + 1) S[k][j] = S[k][j] - S[i][j] * C[k + 1][i];
    M[k] = 1;
    _rep(i, 0, k + 1) {
      S[k][i] = S[k][i] / (k + 1);
      M[k] = lcm(M[k], abs(S[k][i].b));
    }
  }

  int T, k;
  scanf("%d", &T);
  for (int t = 0; scanf("%d", &k) == 1; t++) {
    if (t) puts("");
    printf("%lld", M[k]);
    for (int i = k + 1; i >= 0; i--) {
      auto& r = S[k][i];
      printf(" %lld", M[k] / r.b * r.a);
    }
    puts("");
  }

  return 0;
}
// 19817919	766	Sum of powers	Accepted	C++11	0.000	2017-08-07 22:15:06