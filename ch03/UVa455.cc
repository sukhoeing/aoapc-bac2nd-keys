// Periodic Strings, UVa455
// 陈锋
#include <cassert>
#include <cctype>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

int main(){    
    int N; scanf("%d", &N);
    char line[256]; 
    bool first = true;
    while(N--) {      
        if(first) first = false;
        else puts("");
        scanf("%s", line);
        int sz = strlen(line);
        _rep(p, 1, sz){
            if(sz % p) continue;
            bool ans = true;
            _for(i, 0, p) {
                for(int j = i + p; j < sz; j+=p) {
                    if(line[j] != line[i]) { ans = false; break; }
                }
                if(!ans) break;
            }
            if(ans) { printf("%d\n", p); break; }
        }
    }
    
    return 0;
}
/* 13555368	455	Periodic Strings	Accepted	C++	0.009	2014-04-27 14:13:50 */
