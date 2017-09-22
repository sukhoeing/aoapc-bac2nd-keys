// Foreign Exchange, UVa10763
// 陈锋 C++11
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
int readint() { int x; scanf("%d", &x); return x;}
typedef pair<int, int> IPair;

int main() {
    map<IPair, int> ex; int n;
    while(n = readint()){
        bool ans = true;
        ex.clear();
        _for(i, 0, n){
            int A = readint(), B = readint();
            ex[make_pair(A,B)]++;
        }
        for(const auto& p : ex) { 
            IPair p2 = make_pair(p.first.second, p.first.first);
            if(p.second != ex[p2]) { ans = false; break; } 
        } 
        puts(ans ? "YES" : "NO");
    }
    return 0;
}
// 16739756	10763	Foreign Exchange	Accepted	C++11	0.083	2016-01-22 09:31:23
