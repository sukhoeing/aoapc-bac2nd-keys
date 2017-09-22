// IP Networks, ACM/ICPC NEERC 2005, UVa1590
// 陈锋
#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

// x in [left, right]
bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return left <= x && x <= right;
}

const int W = 8, IPW = 4*W;
void printIp(const int *v) {
    bool first = true;
    _for(i, 0, 4) {
        int x = 0;
        _for(j, i*W, (i+1)*W) x = (x<<1)|v[j];
        if(first) first = false; else printf(".");
        printf("%d", x);
    }
    puts("");
}

void toBinary(int x, int* v, int pos) {
    assert(inRange(x, 0, 255));
    _for(i, 0, W) v[pos+W-i-1] = x%2, x/=2;
}

const int MAXM = 1024;
int ips[MAXM][IPW + 4];

int main(){
    int m, ip[4], subNet[IPW]; 
    while(scanf("%d", &m) == 1) {
        memset(subNet, 0, sizeof(subNet));
        _for(i, 0, m){
            scanf("%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
            _for(j, 0, 4) toBinary(ip[j], ips[i], j*W);
        }
        
        int n;        
        for(n = 0; n < IPW; n++){
            bool same = true;       
            _for(j, 1, m) if(ips[j][n] != ips[j-1][n]) { same = false; break; }
            if(!same) break;
        }
                                
        fill_n(subNet, n, 1);
        fill_n(ips[0] + n, IPW - n, 0);
        printIp(ips[0]);
        printIp(subNet);
    }
    return 0;
}
// 15947878    1590    IP Networks Accepted    C++ 0.006   2015-08-17 06:15:15
