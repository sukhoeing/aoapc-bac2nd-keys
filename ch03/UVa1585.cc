// Score, ACM/ICPC Seoul 2005, UVa1585
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

int main() {    
    int T;
    char buf[128];
    scanf("%d\n", &T);
    while(T--) {
        gets(buf);
        int cnt = 0, sum = 0, sz = strlen(buf);
        _for(i, 0, sz){
            if(buf[i] == 'O') sum += (++cnt);
            else cnt = 0;
        }
        printf("%d\n", sum);
    }
    return 0;
}
/* 13555134	1585	Score	Accepted	C++	0.006	2014-04-27 13:01:27 */