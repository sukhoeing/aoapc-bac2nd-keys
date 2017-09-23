// UVa1645 Count, Chengdu 2012
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MOD = 1000000007, MAXN = 1024;
typedef long long int64;
int64 A[MAXN];

int readint() { int x; scanf("%d", &x); return x; }

void init() {
    A[1] = A[2] = 1;
    _for(i, 3, MAXN){
        int64& a = A[i];
        a = 0;
        _rep(j, 1, i-1)
            if((i-1)%j == 0) a = (a + A[j]) % MOD;
    }
}

int main()
{           
    init();
    int n, t = 1;
    for(int n, t = 1; scanf("%d", &n) == 1; t++) printf("Case %d: %d\n", t, A[n]);
    return 0;
}

// 14805709	1645	Count	Accepted	C++	0.022	2015-01-15 09:40:55