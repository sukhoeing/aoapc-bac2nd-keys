// Eurodiffusion World Finals  2003 - Beverly Hills LA2724
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

const int MAXC = 20 + 5, MAXX = 10 + 2, DX[] = {-1,1,0,0}, DY[] = {0,0,-1,1};
int c;

struct City{
    bool valid, complete; // 是不是一个合法的城市，是否已经完成
    int motif[MAXC], in[MAXC], country; // 各种硬币余额，入账的硬币个数，所在的国家
    void update(){
        assert(valid);
        _for(i, 0, c) if(motif[i] < 1) { complete = false; return; }
        complete = true;
    }
};
City cities[MAXX][MAXX];

struct Country {
    string name; //  国名 
    bool complete; // 完成？
    int xl, yl, xh, yh, day; // 边界，哪一天完成的
    void update(){
        _rep(x, xl, xh) _rep(y, yl, yh)
            if(!cities[x][y].complete) { complete = false; return; }
        complete = true;
    }

	bool operator<(const Country& rhs) const { // 输出时的排序规则
		return day < rhs.day || (day == rhs.day && name < rhs.name);
	}
};
Country cts[MAXC];

void flowIn(int x, int y) {
    City& ci = cities[x][y];
    assert(ci.valid);
    _for(i, 0, c) ci.motif[i] += ci.in[i], ci.in[i] = 0;
    ci.update();
}

void flowOut(int x, int y) {
    City& ci = cities[x][y];
    assert(ci.valid);
    int n = 0;
    _for(i, 0, 4) if(cities[x+DX[i]][y+DY[i]].valid) n++;
	if(!n) return;
    
    _for(i, 0, c){
        int f = ci.motif[i] / 1000;
        ci.motif[i] -= f*n;
        _for(j, 0, 4){
            auto& cj = cities[x+DX[j]][y+DY[j]];
            if(cj.valid) cj.in[i] += f;
        }
    }
}

bool solve(int day) {
    bool ans = true;
    _for(ci, 0, c) {
        Country& ct = cts[ci];
        _rep(x, ct.xl, ct.xh) _rep(y, ct.yl, ct.yh) flowIn(x,y);
        ct.update();
        if(!ct.complete) ans = false;
		else if(ct.day == -1) ct.day = day;
    }
    
    if(ans) return true;
    
    _for(ci, 0, c){
        Country& ct = cts[ci];
        _rep(x, ct.xl, ct.xh) _rep(y, ct.yl, ct.yh) flowOut(x,y);
    }
    return false;     
}

int main(){
    for(int k = 1; cin>>c&&c; k++){
        cout<<"Case Number "<<k<<endl;
        memset(cities, 0, sizeof(cities));
        _for(i, 0, c){
            Country& ct = cts[i];
            ct.complete = false; ct.day = -1;
            cin>>ct.name>>ct.xl>>ct.yl>>ct.xh>>ct.yh;
            _rep(x, ct.xl, ct.xh) _rep(y, ct.yl, ct.yh) {
                City& ci = cities[x][y];
                ci.valid = true, ci.country = i, ci.complete = false, ci.motif[i] = 1000000;
            }
        }
        
        int d = 0;
        while(true) if(solve(d++)) break;
        sort(cts, cts+c);
        _for(i, 0, c) cout<<"   "<<cts[i].name<<"   "<<cts[i].day<<endl;
    }
    return 0;
}
// 13899646	1021	Eurodiffusion	Accepted	C++	0.236	2014-07-18 02:25:44