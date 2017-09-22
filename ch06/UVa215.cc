// UVa215 Spreadsheet Calculator
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
const int MAXR = 20 + 2, MAXC = 10 + 2;
char E[MAXR][MAXC][80];
int R, C, OK[MAXR][MAXC], V[MAXR][MAXC];

bool eval(int r, int c) {
  const char* p = E[r][c];
  int sign = 1, &v = V[r][c], &o = OK[r][c];
  if (o == 1) return true;
  if (o == -1) return false;
  o = -1, v = 0;
  while (*p) {
    if (*p == '+')
      sign = 1, ++p;
    else if (*p == '-')
      sign = -1, ++p;
    else if (isdigit(*p)) {
      int num = 0;
      auto pd = p;
      while (isdigit(*pd)) num = 10 * num + (*(pd++) - '0');
      v += sign * num, p = pd, sign = 1;
    } else {
      assert(isdigit(*(p + 1)));
      int refR = *p++ - 'A', refC = *p++ - '0';
      if (!eval(refR, refC)) return false;
      v += V[refR][refC] * sign, sign = 1;
    }
  }
  o = 1;
  return true;
}

int main() {
  while (scanf("%d%d", &R, &C) == 2 && R && C) {
    getchar();
    _for(r, 0, R) _for(c, 0, C) scanf("%s", E[r][c]);
    memset(OK, 0, sizeof(OK)), memset(V, 0, sizeof(V));
    bool ok = true;
    _for(r, 0, R) _for(c, 0, C) {
      if (eval(r, c)) continue;
      ok = false;
      printf("%c%d: %s\n", r + 'A', c, E[r][c]);
    }
    if (ok) {
      printf(" ");
      _for(c, 0, C) printf("%6d", c);
      puts("");
      _for(r, 0, R) {
        printf("%c", r + 'A');
        _for(c, 0, C) printf("%6d", V[r][c]);
        puts("");
      }
    }
    puts("");
  }
  return 0;
}
// 2173502	5154	Spreadsheet Calculator	Accepted	C++11	0.003	2017-05-03 06:56:56