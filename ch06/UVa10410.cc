// UVa10410 Tree Reconstruction
// 陈锋
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> IVec;
const int MAXN = 1004;
int N, B[MAXN], D[MAXN], BIdx[MAXN];
IVec G[MAXN];
void solve(int l, int r) {
  assert(l <= r);
  if (l == r) return;
  int u = D[l], i = l + 1, lasti = i;
  G[u].push_back(D[i++]);
  while (i <= r) {
    int lastv = G[u].back(), v = D[i];
    if (v > lastv && BIdx[lastv] + 1 == BIdx[v])
      solve(lasti, i - 1), G[u].push_back(v), lasti = i;
    ++i;
  }
  solve(lasti, i - 1);
}
int main() {
  while (scanf("%d", &N) == 1) {
    for (int i = 1; i <= N; i++)
      scanf("%d", &(B[i])), BIdx[B[i]] = i, G[i].clear();
    for (int i = 1; i <= N; i++)
      scanf("%d", &(D[i]));
    solve(1, N);
    for (int i = 1; i <= N; i++) {
      printf("%d:", i);
      for (size_t vi = 0; vi < G[i].size(); vi++)
        printf(" %d", G[i][vi]);
      puts("");
    }
  }
  return 0;
}
// 19308292	10410	Tree Reconstruction	Accepted	C++11	0.000
// 2017-05-03 08:47:40