// UVa11195 - Another n-Queen Problem
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXN = 32;
int N, rows[MAXN], ans;
/*
    r是当前的行号
    v是一个位集合，其第b位为1表示棋盘的第b列还没有放皇后，可以继续再放
    d1是表示正对角线(左上右下)，其中第b位表示r+c=b的那条对角线是否可用，可用为1
    d2是表示斜对角线(右下左上)的位集合，其中第b位表示r-c+N-1=b的那条对角线是否可以放子，可用为1
*/
void dfs(int r, int v, int d1, int d2) {
    if(r == N) { ans++; return; }
    int can = rows[r] & v & (d1>>r) & (d2>>(N-r-1));
    /*
        当确定了r之后
        d1>>r的第i位表示，第r行第i列所在的正对角线上是否可以放皇后
        d2>>N-r-1的第1位表示，第r行第i列所在的反对角线上是否可以放皇后
        这样直接用位运算就快速求出了所有可以放皇后的列的集合
    */
    while(can) {
        /* 这里使用了一个位运算技巧：使用x & (-x)可以求出一个数，这个数字的二进制只包含一个1，
        这个1的位置对应于x中最右边的1 */
        int x = can & (-can);
        dfs(r+1, v^x, d1^(x<<r), d2^(x<<(N-r-1)));
        can ^= x;
    }
}

int main() {    
    char buf[MAXN];
    for(int t = 1; scanf("%d", &N) == 1 && N; t++){
        _for(i, 0, N){
            rows[i] = (1<<N)-1;
            scanf("%s",buf);
            _for(j, 0, N) if(buf[j]=='*') rows[i] ^= (1<<j);
        }
        ans = 0;
        dfs(0,(1<<N)-1,(1<<(2*N-1))-1,(1<<(2*N-1))-1);
        printf("Case %d: %d\n", t, ans);
    }
    return 0;
}
// 14425429	11195	Another n-Queen Problem	Accepted	C++	1.009	2014-10-26 13:05:52