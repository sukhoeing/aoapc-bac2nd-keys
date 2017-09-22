// UVa11846 Finding Seats Again
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
const int MAXN = 20, MAXK = 32;
int N, K;
char G[MAXN][MAXN];

struct Group {
  int leaderX, leaderY, size, ch;
  bool operator<(const Group& g) const { return size > g.size; }
};
vector<Group> groups;

bool dfs(int ki) {
  if (ki == K) return true;
  const auto& kg = groups[ki];
  int kx = kg.leaderX, ky = kg.leaderY;
  auto isEmpty = [&](int x, int y) { return !isalpha(G[x][y]) || G[x][y] == kg.ch; };
  _rep(H, 1, kg.size) if (kg.size % H == 0) {  // height of the rec
    int W = kg.size / H;                       // width of the rec
    _rep(rx, max(0, kx - H + 1), min(kx, N - H)) _rep(ry, max(0, ky - W + 1), min(ky, N - W)) {
      bool valid = isEmpty(rx, ry) && isEmpty(rx + H - 1, ry) && isEmpty(rx, ry + W - 1) &&
                   isEmpty(rx + H - 1, ry + W - 1);
      if (!valid) continue;
      _for(x, rx, rx + H) {
        _for(y, ry, ry + W) {
          if (isEmpty(x, y)) {
            G[x][y] = kg.ch;
          } else {
            valid = false;
            break;
          }
        }
        if (!valid) break;
      }

      if (valid && dfs(ki + 1)) return true;
      _for(x, rx, rx + H) _for(y, ry, ry + W) if (G[x][y] == kg.ch) G[x][y] = '_';
      G[kx][ky] = kg.ch;
    }
  }
  return false;
}

int main() {
  char buf[MAXK];
  while (scanf("%d%d", &N, &K) == 2 && N && K) {
    memset(G, 0, sizeof(G));
    groups.clear();
    _for(r, 0, N) {
      scanf("%s", buf);
      _for(c, 0, N) {
        G[r][c] = '_';
        if (!isdigit(buf[c])) continue;
        G[r][c] = groups.size() + 'A';
        groups.push_back({r, c, buf[c] - '0', G[r][c]});
      }
    }

    sort(begin(groups), end(groups));
    assert(dfs(0));
    _for(r, 0, N) puts(G[r]);
  }
  return 0;
}
// http://d.hatena.ne.jp/shioshiota/20110519/1305818334
/*
search.
Since the answer is surely found,
Take a look from the top left,
If there is an uncertain mass, make a rectangle with the square at the upper left appropriately.
Since the area is up to 9, there are not many candidates so far,
The answer finishes earlier because it always finds it.
*/