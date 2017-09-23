// Exponential Towers, ACM/ICPC NWERC 2013, UVa1656
// 陈锋
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

typedef long long LL;
typedef map<int,int> IMAP;
int gcd(int a, int b){ return b ? gcd(b, a%b) : a; }

void factor(int a, IMAP& ans){ // 对整数a进行素数分解，ans是个素数:指数的map
    ans.clear();
    for(int i = 2; i*i <= a; i++) while(a%i==0) a /= i, ans[i]++;
    if(a>1) ans[a] = 1;
}

LL powerTowers(int n){
    if (n == 1) return 1;
	IMAP f; factor(n,f);
	LL ans = 0;
	int e = f.begin()->second;
    for(auto p : f) e = max(e, p.second);

	_rep(i, 1, e) {
        bool valid = true;
        for(auto p : f) if (p.second % i != 0) { valid = false; break; }
		if(valid) ans += powerTowers(i);
	}
	return ans;
}

int main(){
    int a,b,c;
    IMAP fa, fb, fg;
    while (scanf("%d^%d^%d", &a, &b, &c) == 3) {
        factor(a, fa), factor(b, fb);
        int g = 0;        
        for(auto p : fa) g = gcd(g, p.second); // a = x^g
        factor(g, fg); // B = g*b^c, n = x^B, factor(B)
        for(auto p : fb) fg[p.first] += p.second * c; // 求B的唯一分解

        #ifndef ONLINE_JUDGE
        for(auto p : fg){
            printf("%d^%d,", p.first, p.second);            
        }
        printf("\n");
        #endif

        int maxBk = 1; 
        for(auto p : fg) maxBk = max(maxBk, p.second); // w的最大值

        LL sum = 0;
        _rep(w, 2, maxBk) {
            LL tmp = 1;
            for(auto p : fg) tmp *= (p.second/w + 1);
            sum += (tmp-1)*powerTowers(w);
        }
        
        printf("%lld\n", sum);
    }
    return 0;
}

// 14605626	1656	Exponential Towers	Accepted	C++	0.559	2014-11-30 06:11:43