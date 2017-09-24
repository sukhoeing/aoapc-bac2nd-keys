// LA5858 - ASCII Expression
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
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

const int MOD = 2011;
int INV[MOD + 5], N, W;
string S[24];

int base_line(int top, int bottom, int left, int right);
int eval_fraction(int base, int& pos, int top, int bottom);
int eval_primary(int base, int& pos, int top, int bottom);
int eval_powexpr(int base, int& pos, int top, int bottom);
int eval_factor(int base, int& pos, int top, int bottom);
int eval_term(int base, int& pos, int top, int bottom);
int eval_expr(int base, int& pos, int top, int bottom);
int eval(int, int, int, int);

void dbgPrint(int base, int pos, int top, int bottom, const char* log) {
    return;
    char buf[128];
    sprintf(buf, " , %d-, (%d), (%d, %d)", base, pos, top, bottom);
    
    cout<<log<<buf<<endl;
    _for(i, top, bottom){
        if(i == base) cout<<"->"; else cout<<"  ";        
        for(int j = pos; j < S[i].size(); j++) {
            char c = S[i][j]; if(c == '.') c = ' ';
            cout<<c;
        }

        cout<<"|"<<endl;
    }
}

void dbgPrint(int top, int bottom, int left, int right) {
    return;
    // cout<<"Region: "<<endl;
    _for(j, top, bottom){
        _for(i, left, right) cout<<S[j][i];
        cout<<endl;
    }
}

// 找到第一个非'.'字符所在的基线
int base_line(int top, int bottom, int left, int right) {
    assert(right <= W);
    _for(i, left, right) _for(j, top, bottom) if(S[j][i] != '.') return j;
    assert(false);
}
// 分式求值
int eval_fraction(int base, int& pos, int top, int bottom) {
    int left = pos+1;
    // dbgPrint(base, pos, top, bottom, "eval_fraction");
    assert(S[base][pos] == '-');
    while(S[base][pos] == '-') pos++;
    pos++;
    return eval(top, base, left, pos-2) * INV[eval(base+1, bottom, left, pos-2)] % MOD;
}
// 主表达式求值
int eval_primary(int base, int& pos, int top, int bottom) {
    // dbgPrint(base, pos, top, bottom, "eval_primary");
    char cp = S[base][pos];
    if(isdigit(cp)) { pos += 2; return cp - '0'; }
    assert(cp == '(');
    pos += 2;
    int ret = eval_expr(base, pos, top, bottom);
    assert(S[base][pos] == ')');
    pos += 2;    
    return ret;
}

// 求幂
int eval_powexpr(int base, int& pos, int top, int bottom) {
    // dbgPrint(base, pos, top, bottom, "eval_primary");
    int ex = eval_primary(base, pos, top, bottom);
    
    if(pos - 1 < W && S[base][pos-1] == '.' && base > top && isdigit(S[base-1][pos-1])) {
        int p = S[base-1][pos-1] - '0', ret = 1;
        _for(i, 0, p) ret = (ret * ex) % MOD;
        pos++;
        return ret;
    }
    
    return ex;
}
// 因子求值
int eval_factor(int base, int& pos, int top, int bottom) {
    // dbgPrint(base, pos, top, bottom, "eval_factor");
    if(S[base][pos] == '-' && S[base][pos+1] == '-'){  // 分式
        return eval_fraction(base,pos,top,bottom);
    } else if(S[base][pos]=='-') {  // 负因子
        assert(S[base][pos+1] == '.');
        pos += 2;
        return (MOD - eval_factor(base,pos,top,bottom)) % MOD;
    } else {  // 幂
        return eval_powexpr(base,pos,top,bottom);
    }
}

int eval_term(int base, int& pos, int top, int bottom) {
    assert(pos < W);
    // dbgPrint(base, pos, top, bottom, "eval_term");
    int ret = eval_factor(base, pos, top, bottom);
    while(pos < W && S[base][pos] == '*'){
        pos += 2;
        ret = (ret * eval_factor(base, pos, top, bottom)) % MOD;
    }
    
    return ret;
}

int eval_expr(int base, int& pos, int top, int bottom) {
    // dbgPrint(base, pos, top, bottom, "eval_expr");
    int ret = eval_term(base, pos, top, bottom);
    while(pos<W) {
        if(S[base][pos] == '+') {
            pos += 2;
            int term = eval_term(base, pos, top, bottom);
            ret = (ret + term) % MOD;
        }
        else if(S[base][pos] == '-') {
            pos += 2;            
            int term = eval_term(base, pos, top, bottom);
            ret = (ret - term + MOD) % MOD;
        } else {
            break;
        }
    }
    
    return ret;
}

int eval(int top, int bottom, int left, int right) {
    int base = base_line(top, bottom, left, right), i;
    for(i = left; i < right; i++) if(S[base][i] != '.') break;
    // dbgPrint(base, i, top, bottom, "eval");
    return eval_expr(base, i, top, bottom);
}

int main(){    
    // 先把每个数关于模2011的逆求出来
    _rep(i, 1, MOD) _rep(j, 1, MOD) if((i*j)%MOD == 1) INV[i] = j; 
    while(cin>>N && N){
        _for(i, 0, N) cin>>S[i], assert(S[i].length() == S[0].length());
        W = S[0].length();
        cout<<eval(0, N, 0, W)<<endl;
    }

    return 0;
}
// 1602034	5858	ASCII Expression	Accepted	C++	0.016	2014-11-12 05:46:26