// UVa1674 Lightning Energy Report
// 吴鑫烜 陈锋
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
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;

struct NodeInfo { int minv, maxv, sumv; };
NodeInfo operator+(const NodeInfo& n1, const NodeInfo& n2) 
{ return {min(n1.minv, n2.minv), max(n1.maxv, n2.maxv), n1.sumv + n2.sumv}; }
template<size_t SZ, int INF = 0x7f7f7f7f>
struct IntervalTree {
  NodeInfo nodes[SZ * 2];
  int setv[SZ * 2], addv[SZ * 2], qL, qR, N;
  bitset < SZ * 2 > isSet;
  inline void setFlag(int o, int v) { setv[o] = v, isSet.set(o), addv[o] = 0; }
  void init(int n) {
    N = n;
    int sz = N * 2 + 2;
    fill_n(addv, sz, 0), isSet.reset(), isSet.set(1);
    memset(nodes, 0, sizeof(NodeInfo) * sz);
  }

  inline void maintain(int o, int L, int R) { // 维护信息
    int lc = o * 2, rc = o * 2 + 1, a = addv[o], s = setv[o];
    auto &nd = nodes[o], &li = nodes[lc], &ri = nodes[rc];
    if (R > L) nd = li + ri;
    if (isSet[o]) nd = {s, s, s * (R - L + 1)};
    if (a) nd.minv += a, nd.maxv += a, nd.sumv += a * (R - L + 1);
  }

  inline void pushdown(int o) { // 标记传递
    int lc = o * 2, rc = o * 2 + 1;
    if (isSet[o])
      setFlag(lc, setv[o]), setFlag(rc, setv[o]), isSet.reset(o); // 清除本结点标记
    if (addv[o])
      addv[lc] += addv[o], addv[rc] += addv[o], addv[o] = 0; // 清除本结点标记
  }

  void update(int o, int L, int R, int op, int v) { // op(1:add, 2:set)
    // printf("update %d(%d,%d),%d\n", o, L, R, v);

    int lc = o * 2, rc = o * 2 + 1, M = L + (R - L) / 2;
    if (qL <= L && qR >= R) { // 标记修改
      if (op == 1) addv[o] += v; // add
      else setFlag(o, v); // set
    } else {
      pushdown(o);
      if (qL <= M) update(lc, L, M, op, v); else maintain(lc, L, M);
      if (qR > M) update(rc, M + 1, R, op, v); else maintain(rc, M + 1, R);
    }
    maintain(o, L, R);
  }

  NodeInfo query(int o, int L, int R) {
    int lc = o * 2, rc = o * 2 + 1, M = L + (R - L) / 2;
    maintain(o, L, R);
    if (qL <= L && qR >= R) return nodes[o];

    pushdown(o);
    NodeInfo li = {INF, -INF, 0}, ri = {INF, -INF, 0};
    if (qL <= M) li = query(lc, L, M); else maintain(lc, L, M);
    if (qR > M) ri = query(rc, M + 1, R); else maintain(rc, M + 1, R);
    return li + ri;
  }

  NodeInfo query(int L, int R) {
    qL = L, qR = R;
    const auto& ni = query(1, 1, N);
    return ni;
  }
  void add(int L, int R, int val) {
    qL = L, qR = R;
    update(1, 1, N, 1, val);
  }
};

const int MAXN = 65536;
//Fa[i]为i的父节点, HcHead[i]为i所在重链头, HSon[i]为i的重儿子, SZ[i]为子树i体积, ID[i]为i在线段树中序号
int Fa[MAXN], HcHead[MAXN], Depth[MAXN], HSon[MAXN], SZ[MAXN], ID[MAXN];
vector<int> G[MAXN]; //存储图

int dfs(int u, int fa) { //第一次dfs, 得到每个节点的重儿子, 深度, 和父节点
  SZ[u] = 1, Fa[u] = fa, HSon[u] = 0, Depth[u] = Depth[fa] + 1;
  for (auto v : G[u]) {
    if (v == fa) continue;
    SZ[u] += dfs(v, u);
    if (SZ[v] > SZ[HSon[u]]) HSon[u] = v; //重儿子为体积最大的子树
  }
  return SZ[u];
}

void hld(int u, int fa, int x, int& intSz) { // 第二次dfs, 得到每个节点在线段树中的标号及所属重链的标号
  ID[u] = ++intSz, HcHead[u] = x; // 重链的标号为该重链最顶端的节点
  if (HSon[u]) hld(HSon[u], u, x, intSz); // 先处理重链，保证剖分完之后每条重链中的标号是连续的
  for (auto v : G[u]) if (v != fa && v != HSon[u])  hld(v, u, v, intSz);
}

IntervalTree<MAXN> intTree;
void addPath(int u, int v, int w) {
  while (true) {
    int hu = HcHead[u], hv = HcHead[v];
    if (hu == hv) break; // 直到两点位于同一条重链才停止
    if (Depth[hu] < Depth[hv]) swap(u, v), swap(hu, hv); // 更新h→head()
    intTree.add(ID[hu], ID[u], w), u = Fa[hu];
  }
  if (Depth[u] < Depth[v]) swap(u, v);
  intTree.add(ID[v], ID[u], w); // 更新u->v
}

int main() {
  int N, Q, T;
  scanf("%d", &T);
  for (int kase = 1; kase <= T; kase++) {
    scanf("%d", &N);
    assert(N < MAXN);
    intTree.init(N);
    for (int i = 1; i <= N; i++) G[i].clear();
    int u, v, w;
    SZ[0] = 0, Depth[1] = 0;
    for (int i = 1; i < N; i++) {
      scanf("%d%d", &u, &v);
      u++, v++;
      G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 1);
    int intSz = 0;
    hld(1, 1, 1, intSz);
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
      scanf("%d%d%d", &u, &v, &w);
      u++, v++;
      addPath(u, v, w);
    }
    printf("Case #%d:\n", kase);
    for (int i = 1; i <= N; i++) printf("%d\n", intTree.query(ID[i], ID[i]).sumv);
  }
  return 0;
}
// 22285530 1674  Lightning Energy Report Accepted  C++11 0.330 2018-11-10 15:29:54