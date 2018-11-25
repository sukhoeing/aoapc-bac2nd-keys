// UVa1674 Lightning Energy Report
// 吴鑫烜 陈锋 魏子豪
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

const int MAXN = 65536;
//Fa[i]为i的父节点,HcHead[i]为i所在重链头,HSon[i]为i的重儿子,SZ[i]为子树i体积,ID[i]为i在线段树中序号
int Fa[MAXN], HcHead[MAXN], Depth[MAXN], HSon[MAXN], SZ[MAXN], ID[MAXN],N,add[MAXN*4],intSz;

void Tree_update(int o,int L,int R,int qL,int qR,int val){
	if(qL <= L && R <= qR){
		add[o] += val;	//区间加上val 
		return ;
	}
	int M = L + R >> 1;
	if(qL <= M) Tree_update(o<<1,L,M,qL,qR,val);//覆盖左区间 
	if(M < qR) Tree_update(o<<1|1,M+1,R,qL,qR,val);//覆盖右区间 
}

void Tree_add(int qL,int qR,int val){
	Tree_update(1,1,N,qL,qR,val);
}

void Tree_init(int o,int L,int R){//初始化线段树 
	add[o] = 0;
	if(L == R)	return;
	int M = L + R >> 1;
	Tree_init(o<<1,L,M);
	Tree_init(o<<1|1,M+1,R);
}

int Tree_query(int o,int L,int R,int qv,int addv){ 
	if(L == R)	return addv + add[o];//找到答案并且将答案返回 
	int M = L + R >> 1;
	if(qv <= M)return Tree_query(o<<1,L,M,qv,addv+add[o]);//答案在左区间 
	else return Tree_query(o<<1|1,M+1,R,qv,addv+add[o]);//答案在右区间
}

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
 void hld(int u, int fa, int x) { // 第二次dfs, 得到每个节点在线段树中的标号及所属重链的标号
  ID[u] = ++intSz, HcHead[u] = x; // 重链的标号为该重链最顶端的节点
  if (HSon[u]) hld(HSon[u], u, x); // 先处理重链，保证剖分完之后每条重链中的标号是连续的
  for (auto v : G[u]) if (v != fa && v != HSon[u])  hld(v, u, v);
}

void addPath(int u, int v, int w) {
  while (true) {
    int hu = HcHead[u],hv = HcHead[v];
    if (hu == hv) break; // 直到两点位于同一条重链才停止
    if (Depth[hu] < Depth[hv]) swap(u, v), swap(hu, hv); // 更新h→head()
    Tree_add(ID[hu], ID[u], w),u = Fa[hu];
  }
  if (Depth[u] < Depth[v]) swap(u, v);
  Tree_add(ID[v], ID[u], w); // 更新u->v
}
 int main() {
  int Q, T;
  scanf("%d", &T);
  for (int kase = 1; kase <= T; kase++) {
    scanf("%d", &N);
    assert(N < MAXN);
    Tree_init(1,1,N);
    for (int i = 1; i <= N; i++) G[i].clear();
    int u, v, w;
    SZ[0] = 0, Depth[1] = 0;
    for (int i = 1; i < N; i++) {
      scanf("%d%d", &u, &v);
      u++, v++;
      G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 1);
    intSz = 0;
    hld(1, 1, 1);
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
      scanf("%d%d%d", &u, &v, &w);
      u++,v++;
      addPath(u,v,w);
    }
    printf("Case #%d:\n", kase);
    for (int i = 1; i <= N; i++) printf("%d\n", Tree_query(1,1,N,ID[i],0));
  }
  return 0;
}
// 17025470 1674  Lightning Energy Report Accepted  C++11 0.130 2018-11-15 20:15:31
//魏子豪重构版本 
//改变一：重写了原代码中的线段树代码，减去了冗余代码和冗余功能 
//改变二：减去了原代码部分函数传递参数数量改用全局变量代替
//代码长度由原本的5354B 减少至3629 运行时间由380ms减少到130ms 
