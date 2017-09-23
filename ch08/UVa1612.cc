// Guess, ACM/ICPC Beijing 2006, UVa1612
// 陈锋
#include <cassert>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)

using namespace std;
int readint() { int x; scanf("%d", &x); return x; }
const int maxn = 16384 + 4;
vector<int> PS[maxn], IDs;
int n;

int solve() {
    int lastScore, lastId = -1;
    for (auto id : IDs) {
        const auto& p = PS[id];
        if (lastId == -1){
            lastScore = p.front();
        }
        else{
            bool found = false;
            for(auto s : p){
                if (s < lastScore || (s == lastScore && id > lastId)) {
                    lastScore = s;
                    found = true;
                    break;
                }
            }
            if (!found) return -1;
        }
        lastId = id;
    }
    return lastScore;
}

int readF2i() {
    char buf[8];
    scanf("%s", buf);
    int a, b = 0;
    sscanf(buf, "%d", &a);
    char *pp = strchr(buf, '.');
    if (pp) sscanf(++pp, "%d", &b);
    return a*100 + b;
}

int main(){
    int n; 
    for (int k = 1; scanf("%d", &n) == 1 && n; k++) {
        _for(i, 0, n) {
            auto& p = PS[i];
            p.clear(); p.push_back(0);
            _for (j, 0, 3) p.push_back(readF2i());
            p.push_back(p[1]+p[2]), p.push_back(p[1]+p[3]), p.push_back(p[2]+p[3]);
            p.push_back(p[1]+p[2]+p[3]);
            sort(begin(p), end(p), greater<int>());
        }
        IDs.clear(); _for (i, 0, n) IDs.push_back(readint() - 1);
        int ans = solve();
        if (ans == -1) printf("Case %d: No solution\n", k);
        else printf("Case %d: %d.%02d\n", k, ans / 100, ans % 100);
    }
    return 0;
}
// 1516113 LA 3664 Guess Accepted C++ 0.122  2014-08-10 14:10:13