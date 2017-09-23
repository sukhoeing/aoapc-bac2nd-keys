// UVa1149 Bin Packing
// 陈锋
#include <cassert>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const int MAXN = 100000 + 10;
int n, l, len[MAXN];

int readint() { int x; scanf("%d", &x); return x; }

void solve() {
    n = readint(), l = readint();
    _for(i, 0, n) len[i] = readint();
    sort(len, len + n, greater<int>());
    int ans = 0, left = 0, right = n - 1;
    while(left <= right) {
        ans++; left++;
        if(left != right && len[left] + len[right] <= l) right--;
    }
    printf("%d\n", ans);
}

int main()
{           
    int k = readint(), first = 1;
    while(k--) {
        if(first) first = 0; else puts("");
        solve();
    }
    return 0;
}

// 14804603	1149	Bin Packing	Accepted	C++	0.052	2015-01-15 04:13:32