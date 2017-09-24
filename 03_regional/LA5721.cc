// LA5721 Activation
// 陈锋
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const double eps = 1e-10;
double dcmp(double x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
const int MAXN = 2000 + 4;
double D[MAXN][MAXN], C[MAXN];
int main(){
	int N, M, K;
	double p1, p2, p3, p4, q2, q3, q4;
	while (scanf("%d%d%d%lf%lf%lf%lf", &N, &M, &K, &p1, &p2, &p3, &p4) == 7) {
		if (dcmp(p4) == 0) { puts("0.00000"); continue; }
		q2 = p2 / (1 - p1), q3 = p3 / (1 - p1), q4 = p4 / (1 - p1);
		D[1][1] = p4 / (1 - p1 - p2);
		_rep(i, 2, N){
			_rep(j, 2, (i<K?i:K)) C[j] = D[i-1][j-1] * q3 + q4;
			_rep(j, K+1, i) C[j] = D[i-1][j-1] * q3;
			double q2Pow = 1, cs = 0; // q2Pow = q2^i
			for (int j = i; j > 1; j--) cs += q2Pow * C[j], q2Pow *= q2;
			D[i][i] = (cs + q2Pow * q4) / (1 - q2Pow * q2);
			D[i][1] = q2 * D[i][i] + q4;
			_for(j, 2, i) D[i][j] = q2 * D[i][j - 1] + C[j];
		}
		printf("%.5f\n", D[N][M]);
	}
	return 0;
}
// 886080	5721	Activation	Accepted	C++	0.509	2015-12-26 09:57:29 