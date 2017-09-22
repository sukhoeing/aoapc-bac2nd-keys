// Repeating Decimals, ACM/ICPC World Finals 1990, UVa202
// 陈锋
#include <cassert>
#include <cstring>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

const int MAXN = 3000 + 5;
map<int,int> Pos;
void solve(int n, const int d, string& ans, int& r) {
    assert(n%d && n<d);
    ans = ".";    
    Pos.clear();

    while(true) {
        n *= 10;
        int p = Pos[n];
        if(p == 0) Pos[n] = ans.size();
        else{
            r = ans.size() - p; // 找到循环节
            if(r > 50) ans.erase(p + 50), ans += "...";
            ans.insert(p, "(");
            ans += ')';
            break; 
        }
        
        if(n < d) { ans += '0'; continue; } // 补0
        
        int div = n/d, mod = n%d;
        ans += (char)(div + '0');
        n = mod;
        if(n == 0) { ans += "(0)"; r = 1; break; }
    }
}

int main(){
    int a, b;
    while(scanf("%d%d", &a, &b) == 2) {
        string ans = ".(0)";
        int r = 1; // 循环节长度
        if(a%b) solve(a%b, b, ans, r);
        printf("%d/%d = %d%s\n", a, b, a/b, ans.c_str());
        printf("   %d = number of digits in repeating cycle\n\n", r);
    }
    
    return 0;
}

/* 1444384 (LA)5141 Repeating Decimals Accepted C++ 0.003  2014-05-02 13:58:54 */