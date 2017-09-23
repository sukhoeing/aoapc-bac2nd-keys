// UVa12535 Probability Through experiment
// 陈锋
#include <cassert>
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
const double EPS = 1e-6;

int main(){
	LL N, R; double ang;
	vector<double> angs;
	for(int t = 1; scanf("%lld%lld", &N, &R) == 2 && N && R; t++){
		LL ans = N*(N-1)*(N-2)/6; angs.clear();
		_for(i, 0, N) {
			scanf("%lf", &ang);
			angs.push_back(ang);
			angs.push_back(ang + 360);
		}
		sort(begin(angs), end(angs));		
		_for(ai, 0, N){
			auto ait = angs.begin() + ai;
			LL M = distance(ait + 1, // B,C可选的点数
				upper_bound(ait, angs.end(), *ait+180, [](double d1, double d2){
					return d1 - d2 < -EPS;
				}));
			ans -= M*(M-1)/2;
		}

		printf("Case %d: %lld\n", t, ans);
	}
}
// 1948076	LA6142	Probability Through Experiments	Accepted	C++11	0.205	2016-04-30 12:47:20
