// UVa10824 Regular Polygon
// 陈锋
#include <cassert>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <functional>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

using namespace std;
typedef long long LL;
const double EPS = 1e-8, PI = acos(-1);
const int MAXN = 2000 + 4;
int Vis[MAXN], Ans[MAXN];

int main(){     
	LL N; double ang, x, y;
	vector<double> angs;
	auto dcmp = [](double a, double b){ return a - b < -EPS; };
	auto rg = [](double a){ if(a > 2*PI) a -= 2*PI; return a; };

	for(int t = 1; scanf("%lld", &N) == 1 && N; t++){
		angs.clear(), fill_n(Ans, N+1, 0LL), fill_n(Vis, N+2, 0);
		_for(i, 0, N) {
			scanf("%lf%lf", &x, &y);
			ang = atan2(y, x);
			if(ang < 0) ang += 2*PI;
			angs.push_back(ang);			
		}
		sort(begin(angs), end(angs));
		_rep(K, 3, N) _for(i, 0, N){
			int pt = 1;
			if(Vis[i] == K) continue; // 已经判断过包含i作为顶点的K边形
			Vis[i] = K;
			_for(p, 1, K){ // 依次寻找K-1个顶点
				auto ppr = equal_range(begin(angs), end(angs), 
					rg(angs[i] + PI*2*p / K), dcmp);
				if(ppr.first == ppr.second) break;
				Vis[ppr.first-begin(angs)] = K;									
				pt++;
			}
			if(pt == K) Ans[K]++;
		}

		printf("Case %d:\n", t);
		_rep(K, 3, N) if(Ans[K]) printf("%d %d\n", K, Ans[K]);
	}
}
// 17291560	10824	Regular Polygon	Accepted	C++11	0.540	2016-05-01 03:55:41