// UVa1610 Party Games
// 陈锋
#include <cassert>
#include <algorithm>
#include <string>
#include <iostream>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
int main() {
    const int MAXN = 1000 + 4;
    int n; string P, D[MAXN]; 
    while(cin>>n && n) {
        _for(i, 0, n) cin>>D[i];
        sort(D, D + n);
        const string &l = D[n/2-1];
        P = "A";
        int i = 0, sl = l.size();
        while(i < sl){
            while (P[i] <= 'Z' && P < l) ++P[i];
            if (P[i] <= 'Z' && P >= l && P < D[n/2]) break;
            if (l[i] != P[i]){ assert(P[i] == l[i] + 1); --P[i]; }
            P += 'A';
            ++i;
        }
        cout<<P<<endl;
    }
    return 0;
}

// 15163524 1610    Party Games Accepted    C++ 0.022   2015-03-17 14:17:25