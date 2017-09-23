// Faucet Flow, UVa10366
// 陈锋
#include <cassert>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
const int MAXD = 1000+4;

vector<int> H;
int L, R, LHs[MAXD], RHs[MAXD], LH, RH, LHi, RHi;

int solve() {
    if(LH == RH) {
        int lt = 0, rt = 0;
        for(int i = L, h = LHs[L]; i > LHi; i--) // 从左边最高点溢出之后到边缘需要的水量
            lt += h, h = max(h, LHs[i-1]); 
        for(int i = R, h = RHs[R]; i > RHi; i--) // 从右边最高点溢出之后到边缘需要的水量
            rt += h, h = max(h, RHs[i-1]); 
        return (LHi + RHi + 1) * LH * 2 + min(lt, rt) * 2 * 2;
    }
    
    int T = min(LH, RH), LTi = 0, RTi = 0; // 左右两边第一个高度 >= T的
    while(LTi < L && LHs[LTi] < T) LTi++;
    while(RTi < R && RHs[RTi] < T) RTi++;
    
    int lt = 0, rt = 0, t;
    if(LH < RH) { // 从左边溢出
        for(int i = L, h = LHs[L]; i > LHi; i--)
            lt += h, h = max(LHs[i-1], h);
        for(int i = RTi, h = T; RHs[i] <= T; i++)
            rt += h, h = max(RHs[i+1], h);
        t = lt > rt ? (lt+rt) : 2*lt;
    }
    if(LH > RH) { // 从右边溢出
        for(int i = R, h = RHs[R]; i > RHi; i--)
            rt += h, h = max(RHs[i-1], h);
        for(int i = LTi, h = T; LHs[i] <= T; i++)
            lt += h, h = max(h, LHs[i+1]);
        t = rt > lt ? (rt+lt) : 2*rt;
    }
    
    return t*2 + (RTi + LTi + 1) * T * 2;
}

int main() {
    int leftx, rightx;
    while(cin>>leftx>>rightx && leftx && rightx) {
        LH = RH = 0;
        L = (-leftx)/2, R = rightx/2;
        for(int i = leftx; i < 0; i += 2) {
            int xi = (-i)/2; cin>>LHs[xi];
            if(LH <= LHs[xi]) LH = LHs[xi], LHi = xi; // 左边离0最近的最高点，注意加上等号
        }
        
        for(int i = 1; i <= rightx; i += 2) {
            int xi = i/2; cin>>RHs[xi];
            if(RH < RHs[xi]) RH = RHs[xi], RHi = xi; // 右边离0最近的最高点及其位置
        }
        
        cout<<solve()<<endl;
    }
    return 0;
}
// 14781612	10366	Faucet Flow	Accepted	C++	0.019	2015-01-09 09:35:21