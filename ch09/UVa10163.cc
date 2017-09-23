// Storage Keepers, UVa10163
// 陈锋
#include <cassert>
#include <cstring>
#include <cstdio>
#include <climits>
#include <functional>
#include <algorithm>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

const int MAXN = 128, MAXM = 32, INF = 0x3f3f3f3f;
int N, M, mx, P[MAXM], F[MAXM][MAXN], G[MAXM][MAXN];
// F[i][j] 表示前i个工人要管理j个仓库能达到的最高安全度
int dpF(int i, int j) {
	int& d = F[i][j];
	assert(i >= 1);
	if (d >= 0) return d;
	if (j == 0) return d = INF;
	if (i == 1) return d = (j == 0) ? INF : (P[i] / j);

	d = dpF(i - 1, j); // k = 0
	_rep(k, 1, j) d = max(d, min(dpF(i - 1, j - k), P[i]/k));
	return d;
}

// g[i][j]表示前i个人，管理j个仓库达到最大安全局所需要的最小价钱
int dpG(int i, int j) {
    int& d = G[i][j];
    assert(i>=1);
    if(d >= 0) return d;
    if(j == 0) return d = 0;
    if(i == 1) {
        if(P[i]/j >= mx) return d = P[i];
        return d = INF;
    }
    d = dpG(i-1, j);
    _rep(k, 1, j) if(P[i]/k >= mx) d = min(d, dpG(i-1,j-k)+P[i]);
    
	return d;
}

int main() {
	while (scanf("%d%d", &N, &M) == 2 && N) {
		memset(F, -1, sizeof(F)), memset(G, -1, sizeof(G));
		_rep(i, 1, M) scanf("%d", &(P[i]));
		if ((mx = dpF(M,N)) == 0) { puts("0 0"); continue; }
		printf("%d %d\n", mx, dpG(M, N));
	}
	return 0;
}
// 14058655	10163	Storage Keepers	Accepted	C++	0.028	2014-08-18 07:00:48