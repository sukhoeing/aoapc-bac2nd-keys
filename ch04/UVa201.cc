// Squares, ACM/ICPC World Finals 1990, UVa201
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

using namespace std;
const int MAXN = 16;
int n, m, vExp[MAXN][MAXN], hExp[MAXN][MAXN], H[MAXN][MAXN], V[MAXN][MAXN], Squares[MAXN];
int main(){
    char buf[4]; int x, y;
    for(int t = 1; scanf("%d", &n) == 1; t++){
        if(t > 1) printf("\n**********************************\n\n");
        memset(vExp, 0, sizeof(vExp)), memset(hExp, 0, sizeof(hExp));
        memset(H, 0, sizeof(H)), memset(V, 0, sizeof(V)), memset(Squares, 0, sizeof(Squares));

        scanf("%d", &m);
        _for(i, 0, m){
            scanf("%s%d%d", buf, &x, &y);
            if(buf[0] == 'H')  H[x][y] = 1; else V[y][x] = 1;
        }

        for(int i = n; i >= 1; i--) for(int j = n; j >= 1; j--) {
            if(H[i][j]) hExp[i][j] = hExp[i][j+1] + 1;
            if(V[i][j]) vExp[i][j] = vExp[i+1][j] + 1;
        }

        _rep(i, 1, n) _rep(j, 1, n) {
            int maxS = min(hExp[i][j], vExp[i][j]);
            _rep(s, 1, maxS) if(hExp[i+s][j] >= s && vExp[i][j+s] >= s) Squares[s]++;
        }
        
        printf("Problem #%d\n\n", t);
        bool found = false;
        _rep(i, 1, n) if(Squares[i]) {
            found = true;
            printf("%d square (s) of size %d\n", Squares[i], i);
        }
        if(!found) puts("No completed squares can be found.");
    }
    return 0;
}

/*13519021	201	Squares	Accepted	C++	0.152	2014-04-19 08:42:05*/