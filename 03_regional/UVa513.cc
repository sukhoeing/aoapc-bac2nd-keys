// UVa513 - Window Frames
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
template<typename T>
struct MemPool {
    std::vector<T*> buf;
    T* createNew() {
        buf.push_back(new T());
        return buf.back();
    }
    
    void dispose() {
        for(int i = 0; i < buf.size(); i++) delete buf[i];
        buf.clear();
    }
};
using namespace std;

struct Frame{
    int n, p, d, e, minW, minH, W, H;
    char s;
    bool isHori, isVert;
    vector<Frame*> children;
    
    Frame() : n(0), d(1), isVert(true), isHori(false), s('r') { }
    
    void calcMinSize() { // 计算最小宽高
        for(auto pc : children) pc->calcMinSize();
        minW = isVert ? d : 1; minH = isHori ? d : 1;
        int cavW = minW, cavH = minH;
        for(auto pc : children ){
            if(cavW < pc->minW) minW += pc->minW - cavW, cavW = pc->minW;
            if(cavH < pc->minH) minH += pc->minH - cavH, cavH = pc->minH;
            if(pc->isVert) cavW -= pc->minW; else cavH -= pc->minH;
        }
    }
    
    void distribute() {
        assert(W >= minW); assert(H >= minH);
        int w = W - minW, h = H - minH, cntW = 0, cntH = 0;
        for(auto pc : children){ // 需要分配空间的各个子Frame的个数
            if(pc->e && pc->isVert) cntW++;
            if(pc->e && pc->isHori) cntH++;
        }
        
        int qw = 0, rw = 0, qh = 0, rh = 0;
        if(cntW) qw = w/cntW, rw = w%cntW;
        if(cntH) qh = h/cntH, rh = h%cntH;
        
        for(auto pc : children){ // 分配空间
            pc->W = pc->minW; pc->H = pc->minH;
            if(pc->e && pc->isVert) {
                pc->W += qw;
                if(rw) pc->W++, --rw;
            }
            if(pc->e && pc->isHori) {
                pc->H += qh;
                if(rh) pc->H++, --rh;
            }
        }
        
        int cavW = W, cavH = H;
        for(auto pc : children){ // 重新计算空洞的大小
            if(pc->isVert) cavW -= pc->W, pc->H = cavH;
            else cavH -= pc->H, pc->W = cavW;
        }
        
        for(auto pc : children) pc->distribute();
    }
    
    void print(ostream& os, int lR, int lC, int rR, int rC) { // 在[lR,lC] -> [rR,rC]中输出
        char buf[128];
        if (n) {
            sprintf(buf, "   Frame: %d  (%d,%d)  (%d,%d)", n, lC, lR, rC, rR);
            os<<buf<<endl;
        }
        
        for(auto pc : children){
            switch (pc->s){
                case 'R' :
                    pc->print(os, lR, rC - pc->W + 1, rR, rC), rC -= pc->W;
                    break;
                case 'L' :
                    pc->print(os, lR, lC, rR, lC + pc->W-1), lC += pc->W;
                    break;
                case 'T' :
                    pc->print(os, lR, lC, lR + pc->H-1, rC), lR += pc->H;
                    break;
                case 'B' :    
                    pc->print(os, rR-pc->H+1, lC, rR, rC), rR -= pc->H;
                    break;
            }
        }
    }
};

istream& operator>>(istream& is, Frame& f) {
    is>>f.n>>f.p>>f.s>>f.d>>f.e;
    f.isHori = (f.s == 'B' || f.s == 'T');
    f.isVert = !(f.isHori);
    return is;
}

int main(){
	int M, N;
    map<int, Frame*> frames;
    MemPool<Frame> pool;
    for(int t = 1; cin>>M>>N && M && N; t++) {
        cout<<"Root Frame #"<<t<<endl<<"--------------------------------------------"<<endl;
        frames.clear();
        Frame& root = *(frames[0] = pool.createNew());
        _for(i, 0, M) {
            Frame* pf = pool.createNew(); cin>>(*pf);
            frames[pf->n] = pf;
            assert(frames.count(pf->p));
            frames[pf->p]->children.push_back(pf);
        }
        
        _for(i, 0, N) {
            cin>>root.W>>root.H;
            cout<<"  Display: "<<root.W<<" X "<<root.H;
            root.calcMinSize();
            if(root.minW > root.W || root.minH > root.H)
                cout<<" is too small"<<endl;
            else {
                root.distribute();
                cout<<endl;
                root.print(cout, 0, 0, root.H-1, root.W-1);
            }
            cout<<"--------------------------------------------"<<endl;
        }
        
        pool.dispose();
    }
    
	return 0;
}

// 14799550	513	Window Frames	Accepted	C++	0.032	2015-01-14 01:03:08