// UVa1646 Edge Case, ACM/ICPC NWERC 2012
// 陈锋
#include <cassert>
#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

template<int maxn=200>
struct bign{
  int len, s[maxn];

  bign() { memset(s, 0, sizeof(s)), len = 1; }
  bign(int num) { *this = num; }
  bign(const char* num) { *this = num; }
  bign operator = (int num) {
    char s[maxn];
    sprintf(s, "%d", num);
    *this = s;
    return *this;
  }

  bign operator = (const char* num) {
    len = strlen(num);
    for(int i = 0; i < len; i++) s[i] = num[len-i-1] - '0';
    return *this;
  }

  string str() const {
    string res = "";
    for(int i = 0; i < len; i++) res = (char)(s[i] + '0') + res;
    if(res == "") res = "0";
    return res;
  }

  bign operator+(const bign& b) const{
    bign c;
    c.len = 0;
    for(int i = 0, g = 0; g || i < max(len, b.len); i++) {
      int x = g;
      if(i < len) x += s[i];
      if(i < b.len) x += b.s[i];
      c.s[c.len++] = x % 10;
      g = x / 10;
    }
    return c;
  }

  void clean() { while(len > 1 && !s[len-1]) len--; }

  bign operator * (const bign& b) {
    bign c; c.len = len + b.len;
    for(int i = 0; i < len; i++)
      for(int j = 0; j < b.len; j++)
        c.s[i+j] += s[i] * b.s[j];
    for(int i = 0; i < c.len-1; i++){
      c.s[i+1] += c.s[i] / 10;
      c.s[i] %= 10;
    }
    c.clean();
    return c;
  }

  bign operator - (const bign& b) {
    bign c; c.len = 0;
    for(int i = 0, g = 0; i < len; i++) {
      int x = s[i] - g;
      if(i < b.len) x -= b.s[i];
      if(x >= 0) g = 0;
      else {
        g = 1;
        x += 10;
      }
      c.s[c.len++] = x;
    }
    c.clean();
    return c;
  }

  bool operator < (const bign& b) const{
    if(len != b.len) return len < b.len;
    for(int i = len-1; i >= 0; i--)
      if(s[i] != b.s[i]) return s[i] < b.s[i];
    return false;
  }

  bool operator > (const bign& b) const{ return b < *this; }
  bool operator <= (const bign& b) { return !(b > *this); }
  bool operator == (const bign& b) { return !(b < *this) && !(*this < b); }
  bign operator += (const bign& b) { return *this = *this + b; }
};

int readint() { int x; scanf("%d", &x); return x; }

const int MAXN = 10000;
bign<2096> C[MAXN + 10], F[MAXN + 10];

void init() {
    F[1] = 1, F[2] = 2;
    _rep(i, 3, MAXN) C[i] = F[i-2] + (F[i] = F[i-1] + F[i-2]);
}

int main()
{           
    init();
    int n;
    while(cin>>n) cout<<C[n].str()<<endl;
    return 0;
}

/*
F[n]为 n个点组成的线段，匹配的个数 x-----x----x ... x---x
x
x----x
x----x----x
x(1) = 1
x(2) = 2
x(3) = 3
x(n) = x(n-1) + x(n-2)
C(n) = x(n-2） + x(n)
*/

// 14805715	1646	Edge Case	Accepted	C++	0.416	2015-01-15 09:41:18