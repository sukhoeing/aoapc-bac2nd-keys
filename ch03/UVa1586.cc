// Molar Mass, ACM/ICPC Seoul 2007, UVa1586
// 陈锋
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
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
    int T, cnt, sz; 
    double W[256], ans; 
    char buf[256], c, s;
    W['C'] = 12.01, W['H'] = 1.008, W['O'] = 16.0, W['N'] = 14.01;
    scanf("%d\n", &T);
    while(T--){
        scanf("%s", buf);
        ans = 0;
        s = 0; cnt = -1; sz = strlen(buf);
        _for(i, 0, sz){
            char c = buf[i];            
            if(isupper(c)) {
                if(i) {  
                    if(cnt == -1) cnt = 1;
                    ans += W[s] * cnt;
                }
                s = c;
                cnt = -1;
            } else {
                assert(isdigit(c));
                if(cnt == -1) cnt = 0;
                cnt = cnt*10 + c - '0';
            }
        }
        if(cnt == -1) cnt = 1;
        ans += W[s] * cnt;
        printf("%.3lf\n", ans);
    }
    
    return 0;
}

/* 13555289	1586	Molar mass	Accepted	C++	0.012	2014-04-27 13:51:04 */