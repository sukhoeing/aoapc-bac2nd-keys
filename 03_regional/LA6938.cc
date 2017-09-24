// LA6938 Outer space invaders
// 陈锋
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
int lowerBoundIdx(const vector<int>& v, int x){ return lower_bound(v.begin(), v.end(), x) - v.begin(); }
const int N = 610, INF = 0x3f3f3f3f;
int main(){
	int T, H[N], A[N], B[N], n, f[N][N]; cin>>T;
	vector<int> p;
	while (T --) {
		cin>>n, p.clear();
		_for(i, 0, n) cin>>A[i]>>B[i]>>H[i], p.push_back(A[i]), p.push_back(B[i]);
		p.push_back(-INF); p.push_back(INF); // 增加无穷远的两个点作为边界
		sort(p.begin(), p.end()); 
		p.erase(unique(p.begin(), p.end()), p.end());
		int k = p.size();
		_for (sl, 1, k) _for(i, 0, k - sl) { // 区间长度sl遍历
			int j = i + sl, hst = -1; // hst -> 最高的那个区间
			_for (q, 0, n)
				if (p[i] < A[q] && B[q] < p[j] && (hst == -1 || H[hst] < H[q])) hst = q; 
			int& df = f[i][j]; df = 0;
			if(hst != -1){
				df = INF;
				int l = lowerBoundIdx(p, A[hst]), r = lowerBoundIdx(p, B[hst]); // hst左右两端对应的idx
				_rep (d, l, r) df = min(df, H[hst] + f[i][d] + f[d][j]);
			}
		}
		printf("%d\n", f[0][k - 1]);
	}
	return 0;
}
// 1885957	6938	Outer space invaders	Accepted	C++11	1.459	2015-12-26 05:30:51
// 参考: http://blog.csdn.net/u012647218/article/details/42148639