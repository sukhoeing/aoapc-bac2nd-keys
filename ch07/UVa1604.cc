// UVa1604 Cubic Eight-Puzzle
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
const string CH = "WRB";
const int W = 0, R = 1, B = 2, DX[] = {0, 0, 1, -1}, DY[] = {1, -1, 0, 0},
          Pos[6][3] = {{W, R, B}, {W, B, R}, {B, W, R},
                       {B, R, W}, {R, W, B}, {R, B, W}},  // TOP, FRONT, RIGHT
    HRoll[6] = {3, 5, 4, 0, 2, 1},                        // Roll H
    VRoll[6] = {4, 2, 1, 5, 0, 3};                        // Roll V
// {{B, R, W}3, {R, B, W}5, {R, W, B}4, {W, R, B}0, {B, W, R}2, {W, B, R}1}, H, top<->right
// {{R, W, B}4, {B, W, R}2, {W, B, R}1, {R, B, W}5, {W, R, B}0, {B, R, W}3}, V, top<->front

inline int getPose(const string& s, int x, int y) {
  // assert(s.size() == 10);
  return s[3 * x + y + 1] - '0';
}
inline void setPose(string& s, int x, int y, int pos) {
  // assert(s.size() == 10);
  s[3 * x + y + 1] = pos + '0';
}
inline void getEmpty(const string& s, int& ex, int& ey) {
  // assert(s.size() == 10);
  ex = (s[0] - '0') / 3, ey = (s[0] - '0') % 3;
}
inline void setEmpty(string& s, int ex, int ey) {
  // assert(s.size() == 10);
  s[0] = 3 * ex + ey + '0';
  s[3 * ex + ey + 1] = '7';
}

char Target[4][4];
void dbgPrint(const string& s) {
  assert(s.size() == 10);
  int ex, ey;
  getEmpty(s, ex, ey);
  _for(x, 0, 3) {
    _for(y, 0, 3) {
      if (ex == x && ey == y)
        printf("E");
      else
        printf("%c", CH.at(Pos[getPose(s, x, y)][0]));
    }
    puts("");
  }
}

inline int H(const string& s) {
  int ans = 0, ex, ey;
  getEmpty(s, ex, ey);
  _for(x, 0, 3) _for(y, 0, 3) {
    char c = (ex == x && ey == y) ? 'E' : CH.at(Pos[getPose(s, x, y)][0]);
    if (c != Target[x][y]) ans++;
  }
  return ans;
}

void dfs(int paEx, int paEy, const string& s, const int d, int& ans) {
  int h = H(s);
  if (h == 0) {
    ans = min(ans, d);
    return;
  }
  if (h + d > ans) return;
  int ex, ey;
  getEmpty(s, ex, ey);
  _for(di, 0, 4) {
    int ax = ex + DX[di], ay = ey + DY[di];
    if (ax < 0 || ax >= 3 || ay < 0 || ay >= 3) continue;
    if (ax == paEx && ay == paEy) continue;
    string ns = s;
    int p = getPose(ns, ax, ay);
    setEmpty(ns, ax, ay);
    setPose(ns, ex, ey, (ax == ex ? HRoll[p] : VRoll[p]));
    dfs(ex, ey, ns, d + 1, ans);
  }
}

int main() {
  int ex, ey;
  while (scanf("%d%d", &ey, &ex) == 2 && ex && ey) {
    string s(10, '0');
    --ex, --ey;
    setEmpty(s, ex, ey);
    memset(Target, 0, sizeof(Target));
    _for(x, 0, 3) _for(y, 0, 3) scanf(" %c ", &(Target[x][y]));
    int ans = 32;
    dfs(-1, -1, s, 0, ans);
    if (ans > 30) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}
// 19518240	1604	Cubic Eight-Puzzle	Accepted	C++11	1.080	2017-06-13 13:01:22