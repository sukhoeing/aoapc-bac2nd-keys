// UVa11536 Smallest Sub-Array
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const int MAXN = 1000001;
int N, M, K, x[MAXN];
int readint() { int x; scanf("%d", &x); return x; }
int in_range(int i) { return i >= 1 && i <= K; }
int safe_insert(int i, map<int,int>& s) {
    if(in_range(i)) { s[i] = s[i] + 1; }
    return s.size(); 
}
void safe_del(int i, map<int,int>& s) {
    if(!s.count(i)) return;
    assert(s[i] > 0);
    s[i] = s[i] - 1; 
    if(s[i] < 1) s.erase(i);
}

int solve() {
    int ans = 0, L = 0, R = 0;
    _for(i, 0, N) {
        if(i < 3) x[i] = i + 1;
        else x[i] = (x[i-1] + x[i-2] + x[i-3]) % M + 1;
    }
    
    map<int, int> s;
    safe_insert(x[R], s);
    while(L < N && R < N) {
        while(s.size() < K) { 
            safe_insert(x[++R], s);            
            if(R >= N) break;
        }
        
        if(s.size() == K) {
            while(!s.count(x[L]) || s[x[L]] > 1) safe_del(x[L++], s);
            int len = R-L+1;
            if(ans) ans = min(ans, len);
            else ans = len;
        }
        
        safe_del(x[L], s);
        L++;
        R = max(L, R);
    }
    
    return ans;
}

int main() {           
    int T = readint();
    _for(t, 1, T+1) {
        printf("Case %d: ", t);
        scanf("%d%d%d", &N, &M, &K);
        int ans = solve();
        if(ans) printf("%d\n", ans);
        else printf("sequence nai\n");
    }
    
    return 0;
}

// 14804618	11536	Smallest Sub-Array	Accepted	C++	3.236	2015-01-15 04:21:50