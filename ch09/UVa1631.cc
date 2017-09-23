// UVa1631 Locker, Tianjin 2012
// 陈锋
#include <cassert>
#include <cstring>
#include <cstdio>
#include <climits>
#include <functional>
#include <algorithm>
#define _for(i,a,b) for(int i=(a); i<(b); ++i)
#define _rep(i,a,b) for(int i=(a); i<=(b); ++i)
using namespace std;

const int MAXN = 1024, MAXD = 10, INF = 100000000;
int DP[MAXN][MAXD][MAXD], N, A[MAXN], B[MAXN];
char S1[MAXN], S2[MAXN];

inline int Up(int x, int k){ return (x+k)%10; } // x向上拨k次能变成的数字
inline int Down(int x, int k){ return (x-k+10)%10; } // x向下拨k次能变成的数字

int main(){
    while(scanf("%s%s", S1, S2) == 2){
        N = strlen(S1);
        _rep(i, 0, N) _for(x, 0, 10) _for(y, 0, 10) DP[i][x][y] = INF;
        _for(i, 0, N) A[i+1] = S1[i]-'0', B[i+1] = S2[i]-'0';

        A[0]=B[0]=A[N+1]=A[N+2]=B[N+1]=B[N+2]=0;
        DP[0][A[1]][A[2]] = 0;
        
        _rep(i, 1, N) _for(x, 0, 10) _for(y, 0, 10){
            int down = Down(x, B[i]); // 把x向下转成B[i]需要转几次
            _rep(d1, 0, down) _rep(d2, 0, d1){ // d1:i+1位转几次，d2:i+2位转几次
                int& d = DP[i][Down(y,d1)][Down(A[i+2],d2)];
                d = min(DP[i-1][x][y]+down, d);                
            }
            int up = 10 - down; // 把x向上转成B[i]需要转几次
            _rep(u1, 0, up) _rep(u2, 0, u1){ // u1:i+1位转几次，u2:i+2位转几次
                int& d = DP[i][Up(y,u1)][Up(A[i+2],u2)];
                d = min(DP[i-1][x][y]+up, d);                
            }
        }

        printf("%d\n", DP[N][0][0]);
    }
    return 0;
}

// LiveArchive: 1463685	6384	Locker	Accepted	C++	0.129	2014-06-06 14:40:20