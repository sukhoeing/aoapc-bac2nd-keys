// UVa806 Spatial Structures
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
/* NW = 1, NE = 2, SW = 3, SE = 4 */
const int MAXN = 64 + 4, DX[] = {0, 0, 1, 1}, DY[] = {0, 1, 0, 1};
int N;
char IMG[MAXN][MAXN];

void countBlack(int x, int y, int len, vector<int>& ans, int path = 0, int p5 = 1) {
  int f = 0, len2 = len / 2;
  _for(i, x, x + len) _for(j, y, y + len) f += IMG[i][j] - '0';
  if (f == 0) return;
  if (f == len * len) {
    ans.push_back(path);
    return;
  }
  _for(di, 0, 4) countBlack(x+DX[di]*len2, y+DY[di]*len2, len2, ans, path+p5*(di+1), p5*5);
}

void draw(int path, int x, int y, int len) {
  if (path == 0) {
    assert(len);
    _for(i, x, x + len) _for(j, y, y + len) IMG[i][j] = '*';
    return;
  }
  int di = path % 5 - 1, len2 = len / 2;
  draw(path / 5, x + DX[di] * len2, y + DY[di] * len2, len2);
}

int main() {
  for (int kase = 1; scanf("%d", &N) == 1 && N; kase++) {
    if (kase > 1) puts("");
    printf("Image %d\n", kase);
    if (N > 0) {
      _for(i, 0, N) scanf("%s", IMG[i]);
      vector<int> blacks;
      countBlack(0, 0, N, blacks);
      sort(begin(blacks), end(blacks));
      int sz = blacks.size();
      _for(i, 0, sz) printf("%d%s", blacks[i], (i % 12 == 11 || i == sz - 1) ? "\n" : " ");
      printf("Total number of black nodes = %d\n", sz);
    } else {
      int p;
      memset(IMG, 0, sizeof(IMG));
      N = -N;
      _for(i, 0, N) _for(j, 0, N) IMG[i][j] = '.';
      while (scanf("%d", &p) == 1 && p >= 0) draw(p, 0, 0, N);
      _for(i, 0, N) puts(IMG[i]);
    }
  }
  return 0;
}
// 2175495	5206	Spatial Structures	Accepted	C++11	0.036	2017-05-06 04:37:51