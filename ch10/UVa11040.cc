// UVa11040 Add Bricks in the Wall
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
int B[9][9];
int readint() { int x; scanf("%d", &x); return x; }

void solve() {
    for(int i = 8; i > 0; i--) {
        if(i%2)
            _rep(j, 0, i) B[i][j] = B[i+1][j] + B[i+1][j+1];
        else
            for(int j = 1; j < i; j+=2)
                B[i][j] = (B[i-2][j-1] - B[i][j-1] - B[i][j+1]) / 2;
    }
    
    _for(i, 0, 9) {
        _rep(j, 0, i){ // i行j列
            if(j) printf(" ");
            printf("%d", B[i][j]);
        }
        printf("\n");
    }
}

int main() {           
    int N = readint();
    while(N--) {
        _for(i, 0, 5) _rep(j, 0, i) B[2*i][2*j] = readint();
        solve();
    }
    return 0;
}

// 14805664	11040	Add bricks in the wall	Accepted	C++	0.019	2015-01-15 09:31:13