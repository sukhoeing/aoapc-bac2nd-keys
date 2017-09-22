// Overlapping Squares, Xia’an 2006, UVa12113
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
#include <bitset>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
struct Grid {
    int HEdges, VEdges;
    inline void clear() { HEdges = 0, VEdges = 0; }
    inline bool getHEdge(int row, int col) const { return HEdges & (1<<(row*5+col)); }
    inline bool getVEdge(int row, int col) const { return VEdges & (1<<(row*5+col)); }
    
    inline void setHEdge(int row, int col) { HEdges |= (1<<(row*5 + col)); }
    inline void clearHEdge(int row, int col) { HEdges &= ~(1<<(row*5 + col)); }
    inline void setVEdge(int row, int col) { VEdges |= (1<<(row*5 + col)); }
    inline void clearVEdge(int row, int col) { VEdges &= ~(1<<(row*5 + col)); }
    
    Grid() { clear(); }
    inline bool operator==(const Grid& g) const { 
        return HEdges == g.HEdges && VEdges == g.VEdges; 
    }
    
    void putSquare(int r, int c) { // 以r,c为左上角放一张纸
        assert(0 <= r && r <= 2);
        assert(0 <= c && c <= 2);
        
        setHEdge(r,c), setVEdge(r,c), setHEdge(r,c+1);
        clearVEdge(r,c+1);
        setVEdge(r,c+2), setVEdge(r+1,c);
        clearHEdge(r+1,c), clearHEdge(r+1,c+1), clearVEdge(r+1,c+1);
        setVEdge(r+1,c+2), setHEdge(r+2,c), setHEdge(r+2,c+1);
    }
};

ostream& operator<<(ostream& os, const Grid& g) {
    _for(r, 0, 5) {
        _for(c, 0, 5) {
            os<<((r && g.getVEdge(r-1, c)) ? '|' : ' ');
            os<<(g.getHEdge(r,c)?'_':' ');
        }
        os<<"#"<<endl;
    }
    return os;
}

Grid target;
// g: 目前已经放好的Grid布局 dep : 已经放上去的纸张个数
bool dfs(const Grid& g, int dep) {
    if(g == target) return true;
    if(dep >= 6) return false;
    _for(r, 0, 3) _for(c, 0, 3){
        Grid ng = g;
        ng.putSquare(r, c); // 新的局面
        if(dfs(ng, dep + 1)) return true;
    }
    return false;
}

int main(){
    string line;
    for(int k = 1; ;k++){
        target.clear();
        _for(i, 0, 5){
            getline(cin, line);
            if(line == "0") return 0;
            _for(j, 0, 9){
                switch(line[j]){
                    case ' ':
                        break;
                    case '_':
                        assert(j%2);
                        target.setHEdge(i, j/2);
                        break;
                    case '|':  
                        assert(j%2==0);
                        target.setVEdge(i-1, j/2);
                        break;
                    default:
                        cout<<"c = "<<line[j]<<endl;
                        assert(false);
                }
            }
        }
        Grid g;
        bool ans = dfs(g, 0);
        cout<<"Case "<<k<<": "<<(ans?"Yes":"No")<<endl;
    }
    return 0;
}

// 13978335	12113	Overlapping Squares	Accepted	C++	0.102	2014-08-02 02:56:25