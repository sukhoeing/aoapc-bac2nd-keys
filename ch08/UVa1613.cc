// UVa1613 K-Graph Oddity
// 陈锋
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
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
const int MAXN = 10000 + 4;
int N, M, C[MAXN];
vector<int> G[MAXN];

int main() {
  int a, b;
  for (int t = 0; _ri2(N, M) == 2 && N && M; t++) {
    if (t) puts("");
    _for(i, 0, N) G[i].clear();
    size_t k = 0;
    _for(i, 0, M) {
      _ri2(a, b), --a, --b;
      G[a].push_back(b), G[b].push_back(a);
      k = max(k, G[a].size()), k = max(k, G[b].size());
    }
    if (k % 2 == 0) ++k;
    unordered_set<int> colors;
    _rep(i, 1, k) colors.insert(i);
    _init(C, -1);
    queue<int> Q;
    Q.push(0), C[0] = 0;
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      auto cs = colors;
      assert(C[u] == 0);
      for (auto v : G[u]) {
        if (C[v] > 0) cs.erase(C[v]);
        if (C[v] < 0) C[v] = 0, Q.push(v);
      }
      C[u] = *(cs.begin());
    }
    printf("%zu\n", k);
    _for(i, 0, N) printf("%d\n", C[i]);
  }
  return 0;
}
// 19965260	1613	K-Graph Oddity	Accepted	C++11	0.080
// 2017-09-06 05:10:15
/*
题解：一个点和周围的点的颜色数加起来最大为它的度数+1；如果最大度数是偶数，那么k种颜色一定够了。
如果最大度数是奇数，而且n是奇数，那么k种颜色也一定是足够的。
可以反证，最大度数的点是u，deg[u]是奇数，
而且和u相邻的点颜色各不相同，那么与u的一个相邻点v，至少和deg[u]个颜色不同的点相邻，这样构造出来连通图
点数一定是偶数，和n是奇数是矛盾的，所以不会出现颜色数为deg[u]+1的情况。
*/