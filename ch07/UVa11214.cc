// Guarding the Chessboard, UVa11214
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
using namespace std;

int n, m;
struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
};
typedef Point Vector;
const int MAXM = 9;

Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector dirs[] = // 8个方向向量
    {{-1, -1},{1, 1}, {1, -1},{-1, 1}, {1, 0},{-1, 0}, {0, 1},{0, -1}}; 
bool isValid(const Point& p) { return p.x >= 0 && p.x < n && p.y >= 0 && p.y < m; }

struct Grid{
    int bits[4];
    inline void clear() { memset(bits, 0, sizeof(bits)); }
    
    inline void set(int r, int c) {
        int l = r*m+c;
        bits[l/32] |= (1<<(l&31));
    }
    
    inline bool canCover(const Grid& g) const {
        return (bits[0]&g.bits[0]) == g.bits[0]
            && (bits[1]&g.bits[1]) == g.bits[1]
            && (bits[2]&g.bits[2]) == g.bits[2];
    }

    Grid() { clear(); }
};

// [i,j]如果有皇后，所有被其覆盖的布局就是covers[i*m+j]
Grid covers[MAXM*MAXM + 3], target;

void dfs(int ci, const Grid& g, int depth, int& best) {
    if(depth >= best) return;
    if(g.canCover(target)) {
        best = min(best, depth);
        return;
    }
    if(ci > n*m || depth + 1 > best) return;
    
    dfs(ci+1, g, depth, best);
    Grid ng = g;
    int *cb = covers[ci].bits;
    ng.bits[0] |= cb[0], ng.bits[1] |= cb[1], ng.bits[2] |= cb[2];
    dfs(ci+1, ng, depth+1, best);
}

int main(){
    string line;
    for(int k = 1; cin>>n>>m && n && m; k++) {
        target.clear();
        memset(covers, 0, sizeof(covers));
        _for(i, 0, n) {
            cin>>line;
            assert(line.size() == m);
            _for(j, 0, m){
                if(line[j] == 'X') target.set(i, j);
                for(const auto& dv : dirs) {
                    Point pc(i,j);
                    while(isValid(pc)) {
                        covers[i*m+j].set(pc.x, pc.y);
                        pc = pc + dv;
                    }
                }
            }
        }        
        
        int best = 6;
        Grid g;
        dfs(0, g, 0, best);
        cout<<"Case "<<k<<": "<<best<<endl;
    }
    return 0;
}

// 13974823	11214	Guarding the Chessboard	Accepted	C++	4.619	2014-08-01 07:08:10