// UVa11694 Gokigen Naname
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

struct Point {
  int x, y;
  Point(int x = 0, int y = 0) : x(x), y(y) {}
  Point& operator=(const Point& p) {
    x = p.x, y = p.y;
    return *this;
  }
};
typedef Point Vector;
bool operator==(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
bool operator!=(const Point& a, const Point& b) { return !(a == b); }
bool operator<(const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
istream& operator>>(istream& is, Point& p) { return is >> p.x >> p.y; }

const int MAXN = 8 + 2;
// up-left corner of 4 cells around (x, y) and their connection flag
const int CDX[] = {-1, -1, 0, 0}, CDY[] = {-1, 0, -1, 0}, CG[] = {1, -1, -1, 1};
int N, G[MAXN][MAXN], Deg[MAXN][MAXN], Done[MAXN][MAXN];
vector<Point> pts, PtConn[MAXN][MAXN];

/*
  x-1,y-1 x-1,y  x-1,y+1
  x,y-1   x,y    x,y+1
  x+1,y-1 x+1,y  x+1,y+1
*/
bool validP(int x, int y) { return 0 <= x && x <= N && 0 <= y && y <= N; }
bool validG(int x, int y) { return 0 <= x && x < N && 0 <= y && y < N; }

void connect(const Point& p1, const Point& p2) {
  if (!validP(p1.x, p1.y) || !validP(p2.x, p2.y)) return;
  PtConn[p1.x][p1.y].push_back(p2), PtConn[p2.x][p2.y].push_back(p1);
  int xc = min(p1.x, p2.x), yc = min(p1.y, p2.y), &g = G[xc][yc];
  g = (p1.x - p2.x) / (p1.y - p2.y);  // 1:\ -1:/
}

void connect(const Point& p, int g) {  // g = -1, 1
  if (g == 1)
    connect({p.x, p.y}, {p.x + 1, p.y + 1});
  else if (g == -1)
    connect({p.x, p.y + 1}, {p.x + 1, p.y});
}

void printLayout() {  // 1:\ -1:/
  _for(x, 0, N) {
    _for(y, 0, N) {
      char c = ' ';
      if (G[x][y] == 1) c = '\\';
      if (G[x][y] == -1) c = '/';
      putchar(c);
    }
    puts("");
  }
}

bool connected(const Point& p1, const Point& p2) {
  if (p1 == p2) return true;
  set<Point> VIS;
  queue<Point> Q;
  VIS.insert(p1), Q.push(p1);
  while (!Q.empty()) {
    auto p = Q.front();
    Q.pop();
    if (p == p2) return true;
    for (const auto& v : PtConn[p.x][p.y])
      if (!VIS.count(v)) Q.push(v), VIS.insert(v);
  }
  return false;
}

bool dfs(int x, int y) {  // consider every cell's upper left point (x,y)
  if (x >= N) {
    for (const auto& pt : pts)
      if (PtConn[pt.x][pt.y].size() != Deg[pt.x][pt.y]) return false;
    return true;
  }

  if (validP(x - 1, y - 1) && Deg[x - 1][y - 1] != -1 &&
      PtConn[x - 1][y - 1].size() != Deg[x - 1][y - 1])
    return false;

  int nx = x + (y + 1) / N, ny = (y + 1) % N;
  if (G[x][y] != 0) return dfs(nx, ny);
  /*
  x,y   x,y+1
  x+1,y x+1,y+1
  */
  auto ok = [](int i, int j) { return Deg[i][j] == -1 || Deg[i][j] >= PtConn[i][j].size() + 1; };
  if (ok(x, y) && ok(x + 1, y + 1) && !connected({x, y}, {x + 1, y + 1})) { /*  \  */
    G[x][y] = 1, PtConn[x][y].push_back({x + 1, y + 1}), PtConn[x + 1][y + 1].push_back({x, y});
    if (dfs(nx, ny)) return true;
    G[x][y] = 0, PtConn[x][y].pop_back(), PtConn[x + 1][y + 1].pop_back();
  }
  if (ok(x + 1, y) && ok(x, y + 1) && !connected({x + 1, y}, {x, y + 1})) { /*  /  */
    G[x][y] = -1, PtConn[x + 1][y].push_back({x, y + 1}), PtConn[x][y + 1].push_back({x + 1, y});
    if (dfs(nx, ny)) return true;
    G[x][y] = 0, PtConn[x + 1][y].pop_back(), PtConn[x][y + 1].pop_back();
  }

  return false;
}

void solve() {
  bool change = true;
  while (change) {
    change = false;
    for (const auto& pt : pts) {
      if (Done[pt.x][pt.y]) continue;
      int x = pt.x, y = pt.y, d = Deg[x][y], c = 0, free = 0;  // G: 1:\ -1:/
      _for(cd, 0, 4) {
        int cx = x + CDX[cd], cy = y + CDY[cd];
        if (validG(cx, cy)) {
          if (!G[cx][cy]) ++free;
          if (G[cx][cy] == CG[cd]) ++c;
        }
      }
      if (c == d && free) {  // already has enough connections and has empty cells
        _for(cd, 0, 4) {
          int cx = x + CDX[cd], cy = y + CDY[cd];
          if (validG(cx, cy) && !G[cx][cy]) connect({cx, cy}, -CG[cd]);
        }
        Done[x][y] = 1, change = true;
      } else if (c + free == d) {
        _for(cd, 0, 4) {
          int cx = x + CDX[cd], cy = y + CDY[cd];
          if (validG(cx, cy) && !G[cx][cy]) connect({cx, cy}, CG[cd]), --free;
        }
        Done[x][y] = 1, change = true;  // assert(free == 0); // assert(PtConn[x][y].size() == d);
      }
    }
  }
  dfs(0, 0);
}

int main() {
  char buf[MAXN];
  int T;
  scanf("%d", &T);
  _rep(t, 1, T) {
    scanf("%d", &N);
    pts.clear();
    _for(i, 0, MAXN) _for(j, 0, MAXN) PtConn[i][j].clear();
    memset(Deg, -1, sizeof(Deg)), memset(G, 0, sizeof(G)), memset(Done, 0, sizeof(Done));
    _rep(x, 0, N) {
      scanf("%s", buf);
      _rep(y, 0, N) if (isdigit(buf[y])) Deg[x][y] = buf[y] - '0', pts.emplace_back(x, y);
    }
    solve();
    printLayout();
  }
  return 0;
}
// 19786233	11694	Gokigen Naname	Accepted	C++11	0.120	2017-08-01 08:43:57
