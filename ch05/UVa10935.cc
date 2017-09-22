// Throwing cards away I, UVa 10935
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <functional>
#include <algorithm>
#include <queue>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n) {
        queue<int> q;
        _rep(i, 1, n) q.push(i);
        printf("Discarded cards:");
        bool first = true;
        while(q.size() >= 2) {
            if(first) { first = false; printf(" %d", q.front()); }
            else printf(", %d", q.front());
            q.pop(), q.push(q.front()), q.pop();
        }
        printf("\nRemaining card: %d\n", q.front());
    }
    return 0;
}

/* 特殊情况：n=1时，
Discarded cards:<- No space here!!!
Remaining card: 1 */

/* 13436432	10935	Throwing cards away I	Accepted	C++	0.012	2014-04-03 00:11:51 */