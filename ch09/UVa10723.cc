// UVa10723 Cyborg Genes
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef long long LL;

const int MAXL = 32;
char S1[MAXL], S2[MAXL];
LL len1, len2, Pa[MAXL][MAXL], Pac[MAXL][MAXL];

// 求SL[i1, i2] : S1[1...i1] 和S2[1...i2]的公共父串的最短长度
LL dpPa(int i1, int i2) {
    LL& ans = Pa[i1][i2];
    if(ans != -1) return ans;
    if(i1 == 0 || i2 == 0) return ans = max(i1,i2);
    if(S1[i1] == S2[i2]) return ans = dpPa(i1-1, i2-1) + 1;
    return ans = min(dpPa(i1-1,i2), dpPa(i1,i2-1)) + 1;
}

// 长度为S1[1...i1] S2[1...i2]的最短长度公共父串的个数
LL dpPac(int i1, int i2) {
    LL& ans = Pac[i1][i2];
    if(ans != -1) return ans;
    if(i1 == 0 || i2 == 0) return ans = 1;
    if(S1[i1] == S2[i2]) return ans = dpPac(i1-1, i2-1);

    LL sl1 = dpPa(i1-1, i2), sl2 = dpPa(i1, i2-1);
    if(sl1 == sl2)  ans = dpPac(i1-1, i2) + dpPac(i1, i2-1);
    else if(sl1 < sl2)  ans = dpPac(i1-1, i2);
    else ans = dpPac(i1, i2-1);
    return ans;
}

int main(){
    int T; scanf("%d\n", &T);
    _rep(t, 1, T){
        gets(S1+1), gets(S2+1);
        len1 = strlen(S1+1), len2 = strlen(S2+1);
        memset(Pa, -1, sizeof(Pa)), memset(Pac, -1, sizeof(Pac));
        printf("Case #%d: %lld %lld\n", t, dpPa(len1, len2), dpPac(len1, len2));
    }
}
// 10723    Cyborg Genes    Feng Chen (sukhoeing)   AC  C++ 0.009s