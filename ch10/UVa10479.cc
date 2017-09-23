// UVA 10479 - The Hendrie Sequence
// 陈锋
#include <climits>
#include <cassert>
#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
typedef unsigned long long ull;
const ull u1 = 1;

// block size of m
inline ull bsz(ull m) { return m==0 ? 1 : (u1<<(m-1)); }
ull solve(ull b, ull n) { // 寻找第b个block的第n个数字
    if(b == 0 || b == 1) { assert(n == 1); return b; }
    if(n == bsz(b)) return b;
    for(ull i = 1; i < b; i++) {
        ull k = b-i-1, sz = bsz(k); // i 个block k
        if(n <= i*sz) return n%sz ? solve(k, n%sz) : solve(k, sz);
        n -= i*sz; 
    }
    return 0;
}

ull solve(ull n) {
    if(n == 0) return 0;
    ull b = 1; // 属于哪个块的
    while(true) {
        ull sz = bsz(b);
        if(sz < n) n -= sz;
        else return solve(b, n);
        b++;
    }
}

int main(){
    ull n;
    while(cin>>n && n) cout<<solve(n-1)<<endl;
    return 0;
}

// 14074988	10479	The Hendrie Sequence	Accepted	C++	0.019	2014-08-21 13:40:46