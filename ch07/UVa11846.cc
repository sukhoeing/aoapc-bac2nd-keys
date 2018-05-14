// UVa11846 Finding Seats Again
// 陈锋
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <climits>
#include <iostream>
#include <sstream>
#include <list>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;

const int MAXN = 20;
int N, K;
char G[MAXN][MAXN], Ans[MAXN][MAXN];
bool dfs(const char c, int pos) { // 当前决策的格子编号，以及所要放置的字符
  while(pos != N*N && Ans[pos/N][pos%N] != '.') pos++; // 忽略已经决策过的格子
  if(pos == N*N) return true;
  int x1 = pos%N, y1 = pos/N; // uppper-left corner
  _for(y2, y1, N) _for(x2, x1, N){ // bottom-right corner
    int lcnt = 0, area = (y2 - y1 + 1) * (x2 - x1 + 1); // leader count, area
    if(area > 9 || Ans[y2][x2] != '.') break; // max area ≤ 9
    int ld = -1; // leader digit
    bool used = false, too_large = false;
    _rep(y, y1, y2) { // every cell
      _rep(x, x1, x2){
        char gc = G[y][x];
        if(isdigit(gc)) {
          lcnt++, ld = gc - '0';
          // too many leaders, area too large, width invalid
          if(lcnt > 1 || area > ld || ld%(y2-y1+1)) {
            too_large = true;
            break;
          }
        }     
        if(Ans[y][x] != '.') {
          used = true;
          break;
        }
      }
      if(used || too_large) break;
    }
    if(used || too_large) break;
    if(lcnt == 0 || ld > area) continue; // area too small, continue trying
    _rep(y, y1, y2) _rep(x, x1, x2) Ans[y][x] = c; // fill the region
    if(dfs(c+1, pos+(x2-x1+1))) return true; // go to right of the rectangle
    _rep(y, y1, y2) _rep(x, x1, x2) Ans[y][x] = '.';
  }
  return false;
}

int main() {
  while(_ri2(N, K) == 2 && N && K){
    _init(Ans, '.');
    _for(i, 0, N) _for(j, 0, N) scanf(" %c ", &G[i][j]);
    dfs('A', 0);
    _for(i, 0, N) {
      _for(j, 0, N) putchar(Ans[i][j]);
      puts("");
    }
  }
  return 0;
}
// 20432842 11846 Finding Seats Again Accepted  C++11 0.000 2017-12-02 11:46:07