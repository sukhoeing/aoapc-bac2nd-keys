// Floating-Point Numbers, UVa11809
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cstring>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
const double EPS = 1e-6;
int main(){    
    char line[256];
    double lg2 = log10(2), A, v; int B;
    while(scanf("%s", line) == 1 && strcmp(line, "0e0") != 0){
        *strchr(line, 'e') = ' ';
        sscanf(line, "%lf%d", &A, &B);
        v = log10(A)+B;
        _rep(M, 1, 10){
            int E = round(log10((v+M*lg2-log10(pow(2,M)-1))/lg2 + 1) / lg2);            
            if(fabs(((1<<E)-1)*lg2 + log10(pow(2,M)-1) - M*lg2 - v) <= EPS) {
                printf("%d %d\n",M-1, E);
                break;
            }
        }
    }
    
    return 0;
}
// 16712930 11809   Floating-Point Numbers  Accepted    C++ 0.000   2016-01-16 08:08:21
