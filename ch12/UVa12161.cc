// LA4409 Ironman Race in Treeland
// 吴鑫烜/陈锋
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
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
typedef long long LL;

struct Edge { int v, d, l; };
struct AnsNode {
  int cost, dist;
  bool operator<(const AnsNode& a) const {
    if (cost != a.cost) return cost < a.cost;
    return dist < a.dist;
  }
  bool operator==(const AnsNode& a) const {
    return cost == a.cost && dist == a.dist;
  }
  bool operator!=(const AnsNode& a) const {
    return !(*this == a);
  }
};
const int INF = 0x3f3f3f3f, MAXN = 3e4 + 10;
int N, M, MaxSub[MAXN], SZ[MAXN], VIS[MAXN], Dep[MAXN], Cost[MAXN];
//MaxSub[i]: 去除节点i后得到的森林中节点数最多的树的节点
//SZ：保存子树的节点数
//depth记录长度，cost记录花费
vector<Edge> G[MAXN];

void find_heart(int u, int fa, const int tree_sz, int &heart) { //找重心
  int &szu = SZ[u], &msu = MaxSub[u];
  szu = 1, msu = 0;
  for (size_t i = 0; i < G[u].size(); i++) {
    const Edge& e = G[u][i];
    if (e.v == fa || VIS[e.v]) continue;
    find_heart(e.v, u, tree_sz, heart);
    szu += SZ[e.v], msu = max(msu, SZ[e.v]);
  }
  msu = max(msu, tree_sz - SZ[u]);
  if (MaxSub[heart] > msu) heart = u;
}

void collect_deps(int u, int fa, vector<AnsNode>& cds) { // 收集子树u所有节点的长度和花费
  SZ[u] = 1, cds.push_back({Cost[u], Dep[u]});
  for (size_t i = 0; i < G[u].size(); i++) {
    const Edge &e = G[u][i];
    if (e.v == fa || VIS[e.v]) continue;
    Dep[e.v] = Dep[u] + e.l, Cost[e.v] = Cost[u] + e.d;
    collect_deps(e.v, u, cds);
    SZ[u] += SZ[e.v];
  }
}

void count(int u, int &max_dist) { // 计算经过子树u根结点的路径数
  vector<AnsNode> udeps, vdeps; // u,v子树的所有结点到u的{长度,费用}
  udeps.push_back({0, 0});
  for (size_t i = 0; i < G[u].size(); i++) {
    const Edge& e = G[u][i];
    if (VIS[e.v]) continue;
    Dep[e.v] = e.l, Cost[e.v] = e.d;

    vdeps.clear(), collect_deps(e.v, u, vdeps), sort(vdeps.begin(), vdeps.end());
    for (size_t j = 1; j < vdeps.size(); j++) // 删除无效路径
      if (vdeps[j].dist <= vdeps[j - 1].dist)
        vdeps[j] = vdeps[j - 1];

    for (size_t j = 0; j < udeps.size(); j++) {
      const auto& uj = udeps[j];
      if (uj.cost > M) continue;
      int pos = upper_bound(vdeps.begin(), vdeps.end(), AnsNode{M - uj.cost, INF}) - vdeps.begin() - 1;
      if (pos < 0) continue;
      max_dist = max(max_dist, vdeps[pos].dist + uj.dist);
    }

    for (size_t j = 0; j < vdeps.size(); j++)
      if (j == 0 || vdeps[j] != vdeps[j - 1]) udeps.push_back(vdeps[j]);
  }
}

void solve(int u, int &max_dist) {
  count(u, max_dist);
  VIS[u] = 1;
  for (size_t i = 0; i < G[u].size(); i++) {
    const Edge& e = G[u][i];
    if (VIS[e.v]) continue;
    int heart = 0;
    find_heart(e.v, u, SZ[e.v], heart), solve(heart, max_dist);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int kase = 1; kase <= T; kase++) {
    scanf("%d%d", &N, &M);
    memset(VIS, 0, sizeof(VIS));
    MaxSub[0] = N;
    for (int i = 1; i <= N; i++) G[i].clear();
    int u, v, d, l;
    for (int i = 1; i < N; i++) {
      scanf("%d%d%d%d", &u, &v, &d, &l);
      G[u].push_back({v, d, l}), G[v].push_back({u, d, l});
    }
    int heart = 0, max_dist = 0;
    find_heart(1, -1, N, heart); // 找到初始的重心
    solve(heart, max_dist); // 递归求解
    printf("Case %d: %d\n", kase, max_dist);
  }
  return 0;
}
// 2486985 4409 Ironman Race in Treeland Accepted C++11 0.476 2018-11-05 09:00:57