// DNA Consensus String, ACM/ICPC Seoul 2006, UVa1368
// 陈锋
#include <cstdio>
#include <cassert>
#include <cctype>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

struct ChCnt {
    int cnt; char c;
    void init(char ch = 'A'){ c = ch; cnt = 0; }
    ChCnt() { init(); }
    bool operator<(const ChCnt& cc2) const {
        return cnt > cc2.cnt || (cnt == cc2.cnt && c < cc2.c);
    }
};

const int maxm = 64, maxn = 1024;
const char *DNA = "ACGT";
char seqs[maxm][maxn], IDX[256] = {0};
int main(){    
    int T = 1, m, n;
    scanf("%d", &T);
    _for(i, 0, 4) IDX[DNA[i]] = i;
    ChCnt ccs[4];
    while(T--){
        scanf("%d%d\n", &m, &n);
        _for(i, 0, m) gets(seqs[i]);
        int ans = 0;        
        _for(i, 0, n){
            _for(j, 0, 4) ccs[j].init(DNA[j]);
            _for(j, 0, m) ccs[IDX[seqs[j][i]]].cnt++;
            sort(ccs, ccs + 4);
            printf("%c", ccs[0].c);
            ans += (m - ccs[0].cnt);
        }
        printf("\n%d\n", ans);
    }
    return 0;
}

/* 13561314	1368	DNA Consensus String	Accepted	C++	0.018	2014-04-29 06:10:03 */