// LA6469 - Deranged Exams
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef long long LL;
const int MAXN = 20;
LL C[MAXN][MAXN], Fac[MAXN]; // A[i]->i!
void init() {
    Fac[0] = Fac[1] = 1; C[1][0] = C[1][1] = 1;
    _for(i, 2, MAXN) {
        Fac[i] = Fac[i-1]*i, C[i][0] = C[i][i] = 1;
        _for(j, 1, i) C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
}

int main(){
    int P, d, N, k;
    init(); scanf("%d", &P);
    _for(i, 0, P){
        scanf("%d%d%d", &d, &N, &k);
        LL ans = Fac[N];
        _rep(i, 1, k){
            if(i%2) ans -= C[k][i]*Fac[N-i];
            else ans += C[k][i]*Fac[N-i];
        }
        printf("%d %lld\n", d, ans);
    }    
    return 0;
}
// 1670774	6469	Deranged Exams	Accepted	C++	0.003	2015-04-04 00:12:18