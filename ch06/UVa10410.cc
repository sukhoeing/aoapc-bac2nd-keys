// UVa10410 Tree Reconstruction
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
typedef vector<int> IVec;
template <typename T>
inline vector<T>& operator+=(vector<T>& v, const T& x) {
  v.push_back(x);
  return v;
}
template <typename T>
inline set<T>& operator+=(set<T>& s, const T& x) {
  s.insert(x);
  return s;
}

typedef long long LL;
const int MAXN = 1004;
int N, B[MAXN], D[MAXN], BIdx[MAXN];
IVec G[MAXN];
void solve(int l, int r) {
  int u = D[l], i = l + 1, lasti = i;
  assert(l <= r);
  if (l == r) return;
  G[u] += D[i++];
  while (i <= r) {
    int lastv = G[u].back(), v = D[i];
    if (v > lastv && BIdx[lastv] + 1 == BIdx[v]) {
      solve(lasti, i - 1);
      G[u] += v, lasti = i;
    }
    ++i;
  }
  solve(lasti, i - 1);
}
int main() {
  while (scanf("%d", &N) == 1) {
    _rep(i, 1, N) scanf("%d", &(B[i])), BIdx[B[i]] = i, G[i].clear();
    _rep(i, 1, N) scanf("%d", &(D[i]));
    solve(1, N);
    _rep(i, 1, N) {
      printf("%d:", i);
      for (auto v : G[i]) printf(" %d", v);
      puts("");
    }
  }
  return 0;
}
// 19308292	10410	Tree Reconstruction	Accepted	C++11	0.000	2017-05-03 08:47:40