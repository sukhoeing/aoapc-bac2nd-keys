// UVa1647 Computer Transformations, ACM/ICPC SEERC 2005
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

template <int maxn = 200>
struct bign {
  int len, s[maxn];

  bign() {
    memset(s, 0, sizeof(s));
    len = 1;
  }

  bign(int num) { *this = num; }

  bign(const char* num) { *this = num; }

  bign operator=(int num) {
    char s[maxn];
    sprintf(s, "%d", num);
    *this = s;
    return *this;
  }

  bign operator=(const char* num) {
    len = strlen(num);
    for (int i = 0; i < len; i++) s[i] = num[len - i - 1] - '0';
    return *this;
  }

  string str() const {
    string res = "";
    for (int i = 0; i < len; i++) res = (char)(s[i] + '0') + res;
    if (res.empty()) res = "0";
    return res;
  }

  bign operator+(const bign& b) const {
    bign c;
    c.len = 0;
    for (int i = 0, g = 0; g || i < max(len, b.len); i++) {
      int x = g;
      if (i < len) x += s[i];
      if (i < b.len) x += b.s[i];
      c.s[c.len++] = x % 10;
      g = x / 10;
    }
    return c;
  }

  void clean() {
    while (len > 1 && !s[len - 1]) len--;
  }

  bign operator*(const bign& b) {
    bign c;
    c.len = len + b.len;
    for (int i = 0; i < len; i++)
      for (int j = 0; j < b.len; j++) c.s[i + j] += s[i] * b.s[j];
    for (int i = 0; i < c.len - 1; i++) {
      c.s[i + 1] += c.s[i] / 10;
      c.s[i] %= 10;
    }
    c.clean();
    return c;
  }

  bign operator-(const bign& b) {
    bign c;
    c.len = 0;
    for (int i = 0, g = 0; i < len; i++) {
      int x = s[i] - g;
      if (i < b.len) x -= b.s[i];
      if (x >= 0)
        g = 0;
      else {
        g = 1;
        x += 10;
      }
      c.s[c.len++] = x;
    }
    c.clean();
    return c;
  }

  bool operator<(const bign& b) const {
    if (len != b.len) return len < b.len;
    for (int i = len - 1; i >= 0; i--)
      if (s[i] != b.s[i]) return s[i] < b.s[i];
    return false;
  }

  bool operator>(const bign& b) const { return b < *this; }

  bool operator<=(const bign& b) { return !(b > *this); }

  bool operator==(const bign& b) { return !(b < *this) && !(*this < b); }

  bign operator+=(const bign& b) {
    *this = *this + b;
    return *this;
  }
};

template <int maxn = 200>
istream& operator>>(istream& in, bign<maxn>& x) {
  string s;
  in >> s;
  x = s.c_str();
  return in;
}

template <int maxn = 200>
ostream& operator<<(ostream& out, const bign<maxn>& x) {
  out << x.str();
  return out;
}
const int MAXN = 1000 + 4;

typedef bign<384> BI;
BI F[MAXN];

int main() {
  BI p2 = 2;
  F[1] = 1, F[2] = 1;
  _for(i, 3, MAXN) {
    F[i] = F[i - 2] + p2;
    p2 = p2 * 2;
  }
  int n;
  while (cin >> n) cout << F[n - 1] << endl;
  return 0;
}
// 2228795	3308	Computer Transformation	Accepted	C++11	0.162	2017-08-08 13:41:35