// UVa1665 Islands, ACM/ICPC CERC 2009
// 陈锋
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
inline int readint() { int x; scanf("%d", &x); return x; }

struct Point{
    int x,y,v;
    void init(int r, int c, int value){
        assert(r >= 0), assert(c >= 0);
        x = r, y = c, v = value;
    }
};

const int MAXM = 1024, MAXN = 1024, MAXT = 100000 + 5;
int m, n, T, t[MAXT], Ans[MAXT], indice[MAXN][MAXM], pa[MAXN*MAXM];
Point points[MAXN*MAXM];
vector<int> tmp; // 储存p的邻居
int findPa(int i) { return pa[i] == i ? i : (pa[i] = findPa(pa[i])); }
void getAdjs(const Point& p, vector<int>& ans) {
    ans.clear();
    int r = p.x-1, c = p.y;
    if(r>=0) ans.push_back(indice[r][c]);
    r=p.x+1;
    if(r<n) ans.push_back(indice[r][c]);
    r = p.x; c = p.y-1;
    if(c>=0) ans.push_back(indice[r][c]);
    c = p.y+1;
    if(c<m) ans.push_back(indice[r][c]);    
}

void solve() {
    scanf("%d%d", &n, &m);
    int psz = 0;
    _for(i, 0, n) _for(j, 0, m) points[psz++].init(i,j,readint());
    sort(points, points+psz, [](const Point& p1, const Point& p2){
        return p1.v > p2.v;
    });

    _for(i, 0, psz){
        const Point& p = points[i];
        pa[i] = i;
        indice[p.x][p.y] = i;
    }
    
    T = readint();
    _for(i, 0, T)  t[i] = readint();
   
    int pi = 0;
    Ans[T] = 0;
    for(int i = T-1; i>=0; i--){
        int& ans = Ans[i];
        ans = Ans[i+1];
        while(pi < psz && points[pi].v > t[i]){
            ans++;            
            getAdjs(points[pi], tmp); // 遍历p的上下左右四个邻居
            for(auto j : tmp){
                Point& pn = points[j];
                if(pn.v <= t[i]) continue;
                int pnpa = findPa(indice[pn.x][pn.y]);
                if (pnpa == findPa(pi)) continue;
                pa[pnpa] = pi;
                ans--;
            }
            pi++;
        }
    }
}

int main(){
    int Z = readint();
    _for(z, 0, Z) {
        solve();
        _for(i, 0, T) printf("%d ", Ans[i]);
        puts("");
    }
    return 0;
}

// 1627186	LA4627	Islands	Accepted	C++	2.852	2015-01-15 10:23:55