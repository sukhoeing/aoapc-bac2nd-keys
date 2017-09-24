// LA3846 - Typesetting
// 陈锋
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXN = 24;
int N, gn;
struct glyph{
    string rows[MAXN];
    int segs[MAXN][2], width; // 每一行的像素区间，宽度
    void setRow(int ri, const string& row) {
        rows[ri] = row, width = row.size();
        setSeg(ri);
    }
    
    void setSeg(int ri) { // 得到第ri行的区间信息
        int &l = segs[ri][0], &r = segs[ri][1];
        l = MAXN, r = -1; // 这一行的左右区间
        const string& row = rows[ri];
        _for(i, 0, width) if(row[i] != '.') l = min(l, i), r = max(r, i);
    }

    void pack(const glyph& rhs) {
        int c;
        for(c = -rhs.width; c <= width + 1; c++)
            if(canPut(c, rhs)) break; // 区间信息
        assert(c <= width + 1);
        if(c < 0) {
            int aw = -c;
            string pfx(aw, '.');
            width += aw;
            _for(i, 0, N) rows[i].insert(0, pfx), segs[i][0] += aw, segs[i][1] += aw;
            c = 0;
        }
        int nw = c + rhs.width; // 新的宽度
        if(nw > width) {
            _for(i, 0, N) rows[i].resize(nw, '.');
            width = nw;
        }
        
        _for(i, 0, N){
            _for(j, 0, rhs.width){
                char& cell = rows[i][j+c];
                if(cell == '.') cell = rhs.rows[i][j];
            }
            setSeg(i);
        }
    }
    
    bool canPut(int col, const glyph& rhs) { // 会否会重叠呢？
        _for(r, 0, N){
            int tl = segs[r][0], tr = segs[r][1],
                rl = rhs.segs[r][0], rr = rhs.segs[r][1];
            if(rr == -1 || tr == -1) continue;
            rl += col, rr += col;
            if(tr + 1 >= rl) return false;
        }
        
        return true;
    }
    
    void preOut() { // 准备输出
        auto isColEmpty = [this](int col){ // 第col列是否为空的，没字符
            _for(r, 0, N) if(rows[r][col] == '#') return false;
            return true;             
        };

        for(int c = width - 1; c >= 0; c--) // 压缩掉右边的空格
            if(isColEmpty(c)) --width; else break;
                
        int sj = 0;
        for(; sj < width; sj++) if(!isColEmpty(sj)) break; // 左边的空格

        _for(i, 0, N) {
            string& r = rows[i];
            r.resize(width), r.erase(0, sj);
            for(auto& rc : r) if(rc == '0') rc = '.';
        }
    }
};

ostream& operator<<(ostream& os, const glyph& g) {
    _for(i, 0, N) os<<g.rows[i]<<endl;
    return os;
}
int main(){
    string line,r;
    glyph gs[MAXN];
    for(int t = 1; cin>>N && N; t++) {
        getline(cin, line);
        cout<<t<<endl;
        _for(i, 0, N) {
            getline(cin, line);
            stringstream ss(line);
            gn = 0;
            while(ss>>r) gs[gn++].setRow(i, r);
        }
        glyph& g0 = gs[0];
        _for(i, 1, gn) g0.pack(gs[i]);
        g0.preOut();
        cout<<g0;
    }
}

// 1537647	3846	Typesetting	Accepted	C++	0.003	2014-09-06 15:24:11