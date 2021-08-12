// Patrol Robot, ACM/ICPC Hanoi 2006, UVa1600
// 陈锋
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>
using namespace std;

#define _for(i, a, b) for (int i = (a); i < (b); ++i)
bool inRange(int x, int l, int r) {
  return (l > r) ? inRange(x, r, l) : (l <= x && x <= r);
}

struct Point {
  int x, y;
  Point(int x = 0, int y = 0) : x(x), y(y) {}
};
typedef Point Vector;
Vector operator+(const Vector &A, const Vector &B) {
  return Vector(A.x + B.x, A.y + B.y);
}
bool operator==(const Point &a, const Point &b) {
  return a.x == b.x && a.y == b.y;
}

const int MAXN = 24;
int M, N, K, Grid[MAXN][MAXN], vis[MAXN][MAXN][MAXN];
bool isValid(const Point &p) {
  return inRange(p.x, 0, M - 1) && inRange(p.y, 0, N - 1);
}
Vector dirVs[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Stat {
  Point pos;
  int turbo;
};

int &getVisd(const Stat &s) { return vis[s.pos.x][s.pos.y][s.turbo]; }

int solve() {
  Stat s;
  Point dest(M - 1, N - 1);
  s.pos.x = 0;
  s.pos.y = 0;
  s.turbo = 0;
  memset(vis, -1, sizeof(vis));

  queue<Stat> q;
  q.push(s);
  vis[s.pos.x][s.pos.y][s.turbo] = 0;

  while (!q.empty()) {
    const Stat &f = q.front();
    q.pop();
    const int &fd = getVisd(f);
    if (f.pos == dest)
      return fd;
    assert(f.turbo <= K);

    _for(i, 0, 4) {
      Point np = f.pos + dirVs[i];
      if (!isValid(np))
        continue;
      int isBlock = Grid[np.x][np.y];
      if (isBlock && f.turbo + 1 > K)
        continue;

      Stat ns = {np, (isBlock ? (f.turbo + 1) : 0)};
      int &d = getVisd(ns);
      if (d == -1) {
        d = fd + 1;
        q.push(ns);
      }
    }
  }

  return -1;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &M, &N, &K);
    _for(i, 0, M) _for(j, 0, N) scanf("%d", &(Grid[i][j]));
    int ans = solve();
    printf("%d\n", ans);
  }
}

// 1627141	LA3670	Patrol Robot	Accepted	C++	0.003
// 2015-01-15 03:05:38