// LA4090 - Let's Go to the Movies
// 陈锋
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef vector<int> IVec;
typedef vector<string> SVec;
const int MAXN = 100000 + 4;
int S, F, n;
IVec G[MAXN], roots;
SVec adj[MAXN], words;
map<string, int> indice;

typedef long long LL;
struct Ans{ // 购票方案
	int NS, NF; // 单票个数，套票个数
	LL T; // 购票费用
	Ans(int ns = 0, int nf = 0, LL t = 0) :NS(ns), NF(nf), T(t){}
	void init(int ns = 0, int nf = 0, LL t = 0) { NS = ns, NF = nf, T = t; }
	bool operator<(const Ans& a) const {
		if (T != a.T) return T < a.T;
		return (NF+NS < a.NF+a.NS);
	}
	Ans& operator+=(const Ans& a){ NS += a.NS, NF += a.NF, T += a.T; return *this; }
};

Ans DP[MAXN][2];

const Ans& dp(int u, int f) {  // 以u为根节点的子树，是否被套票覆盖??(f = 1,0)对应的最优结果
	Ans& d = DP[u][f];
	if (d.T != -1) return d;
	d.init();

	const IVec& A = G[u]; bool leaf = A.empty(); // u的邻居
	if (leaf) { // u是叶子
		// 没被套票覆盖，必须买单票或是套票，否则无需买票
		if (!f) d = min(Ans(1,0,S), Ans(0,1,F)); 		
		return d;
	}

	// 所有孩子v的dp(v,f)之和
	auto sumDP = [&A](int f, Ans dt){ for(auto a : A) dt += dp(a,f); return dt; }; 
	// 套票或单票
	d = min(sumDP(1,Ans(0,1,F)), sumDP(0,Ans(1,0,S)));
	if(f) d = min(sumDP(0,Ans()), d); // 还可以选择不买
	return d;
}

int main() {
	string l, w;
	getline(cin, l);
	for(int t = 1;;t++) {
		assert(isdigit(l[0]));
		stringstream si(l);
		assert(si>>S>>F);
		if (!S && !F) break;
		words.clear(), indice.clear();

		n = 0;
		set<int> cRoots; // 所有树根
		while (true) {
			getline(cin, l);
			if (isdigit(l[0])) break;
			stringstream ss(l); ss>>w; 
			words.push_back(w); indice[w] = n; // w是一个父节点
			adj[n].clear(); while (ss >> w) adj[n].push_back(w);
			cRoots.insert(n++);
		}

		_for(i, 0, n){ // 建图
			IVec& g = G[i]; g.clear(); 
			for(auto w : adj[i]){
				bool leaf = !indice.count(w); // w是叶子节点
				if (leaf) adj[n].clear();
				int v = leaf ? n++ : indice[w]; // w对应的节点编号
				g.push_back(v), cRoots.erase(v); // v不是树根
			}
		}
		roots.assign(cRoots.begin(), cRoots.end());
		Ans ans;
		memset(DP, -1, sizeof(DP));

		for(auto r : roots) ans += dp(r, 0);
		cout << t << ". " << ans.NS << " " << ans.NF << " " << ans.T << endl;
	}
	return 0;
}
// 1921476	4090	Let's Go to the Movies	Accepted	C++11	0.119	2016-03-09 15:10:52