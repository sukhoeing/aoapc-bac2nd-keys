// UVa12538 Version Controlled IDE
// 陈锋
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ext/rope>
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
using namespace __gnu_cxx;

#define _for(i, a, b) for (decltype(b) i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
crope ro, version[50100];

int main() {
  int n, d = 0, ver = 1;
  char buf[256];
  _ri1(n);
  while (n--) {
    int opt, p, c, v;
    _ri1(opt);
    switch (opt) {
      case 1:
        _ri1(p);
        scanf("%s", buf), p -= d;
        ro.insert(p, buf), version[ver++] = ro;
        break;
      case 2:
        _ri2(p, c), p -= d, c -= d;
        ro.erase(p - 1, c), version[ver++] = ro;
        break;
      default:
        _ri3(v, p, c);
        v -= d, p -= d, c -= d;
        const auto& tmp = version[v].substr(p - 1, c);
        for (auto c : tmp) d += (c == 'c'), putchar(c);
        puts("");
        break;
    }
  }
  return 0;
}
// 2401972	LA6145	Version Controlled IDE	Accepted	C++11 0.362
// 2018-06-28 07:21:23