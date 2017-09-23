// UVa11526 H(n)
// 陈锋
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long LL;

LL solve(LL n){
    LL ans = 0, i = 0;
    for(i = 1; i <= n; i++){
        LL c = n/i - n/(i+1);
        ans += i*c;
        if(c <= 1) break;
    }
    for(i = n/(i+1); i >= 1; i--) ans += n/i;
    return ans;
}


int main(){
    LL n, T; cin>>T;
    while(T--) { cin>>n; cout<<solve(n)<<endl; }
    return 0;
}
// 17534177 11526   H(n)    Accepted    C++11   0.320   2016-06-17 13:28:49