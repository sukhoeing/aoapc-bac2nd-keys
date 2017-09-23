// UVa10285 Longest Run on a Snowboard
// 陈锋
#include<cassert>
#include<cstdio>
#include<functional>
#include<algorithm>
#include<sstream>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
using namespace std;
int readint() { int x; scanf("%d", &x); return x;}

const int MAXH = 100 + 5;
int R, C, M[MAXH][MAXH], D[MAXH][MAXH];

int dp(int i, int j) {
    int& ans = D[i][j];
    if(ans != -1) return ans;
    ans = 1;
    int h = M[i][j];
    if(i > 0 && M[i-1][j] < h) ans = max(ans, 1+dp(i-1,j));
    if(j > 0 && M[i][j-1] < h) ans = max(ans, 1+dp(i,j-1));
    if(i+1 < R && M[i+1][j] < h) ans = max(ans, 1+dp(i+1,j));
    if(j+1 < C && M[i][j+1] < h) ans = max(ans, 1+dp(i,j+1));    
    return ans;
}

int main()
{
    int N = readint();
    char name[64];
    while(N--) {
        scanf("%s", name);
        R = readint(), C = readint();
        for(int i = 0; i < R; i++)
            for(int j = 0; j < C; j++)
                M[i][j] = readint();
        
        memset(D, -1, sizeof(D));
        int ans = 0;
        for(int i = 0; i < R; i++)
            for(int j = 0; j < C; j++)
                ans = max(ans, dp(i,j));
        printf("%s: %d\n", name, ans);
    }    
    return 0;
}

// 14804646	10285	Longest Run on a Snowboard	Accepted	C++	0.029	2015-01-15 04:39:38