// UVa12508 triangles in the grid
// 陈锋
#include <cassert>
#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef long long LL;
int n, m, A, B;

void update(LL& cnt, int area, int c) { if(A <= area && area <= B) cnt+=c; }

int solve(int left, int right, int k) { // 求方程 left <= k*x <= right 的解的个数
    if (left > right) return 0;
    left = (int)ceil(left / (double)k);
    right = (int)floor(right / (double)k);
    return right - left + 1;
}

LL solve(int r, int c) { // 计算r*c的方格中有多少符合条件的三角形
    LL cnt = 0;
    int area = r*c;    
    // 三顶点都在cell顶点上，共4种
    update(cnt, area, 4); 
    // 只有两个顶点在cell顶点，并且这两个顶点不是对角线，第三个顶点在对边上
    update(cnt, area, 2*(r-1) + 2*(c-1));
    // 有两个顶点形成对角线，另外的顶点在水平边上
    cnt += 4 * solve(max(A,r), min(B,r*c-r), r);
    // 有两个顶点形成对角线，另外的顶点在垂直边上
    cnt += 4 * solve(max(A,c), min(B, r*c-c), c);
    // 有两个顶点形成对角线，另外的顶点在矩形内部
    _for(i, 1, r) cnt += 4 * solve(max(r, area-B-c*i), min(area-r, area-A-c*i), r);
    // 只有一个顶点在四角上，另外两个点肯定都在跟这个点不相邻的边上。
    _for(i, 1, c) cnt += 4 * solve(max(i, area-B), min(i*r-i, area-A), i);
    return cnt;
}

LL solve() {
    LL cnt = 0;
    _rep(r, 1, n) _rep(c, 1, m) // 遍历三角形所在的矩形的长宽
        cnt += solve(r, c) * (n-r+1) * (m-c+1);
    return cnt;
}

int main(){    
    int T; cin>>T;
    while(T--) {
        cin>>n>>m>>A>>B;
        A*=2, B*=2;
        cout<<solve()<<endl;
    }
    return 0;
}
// 14587105	12508	Triangles in the Grid	Accepted	C++	0.775	2014-11-26 09:33:35