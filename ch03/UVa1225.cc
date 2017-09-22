// Digit Counting , ACM/ICPC Danang 2007, UVa1225
// 陈锋
#include<cassert>
#include<cctype>
#include<iostream>
#include<iomanip>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
using namespace std;

const int MAXN = 10000 + 1;
int C[MAXN][10] = {0};

int main()
{    
    for(int i = 1; i < MAXN; i++) {
        for(int k = 0; k < 10; k++)
            C[i][k] = C[i-1][k];
        
        int n = i;
        while(n) {
            ++C[i][n%10];
            n /= 10;
        }
    }
    
    int T, n;
    cin>>T;
    while(T--) {
        cin>>n;
        for(int i = 0; i < 10; i++) {
            if(i) cout<<" ";
            cout<<C[n][i];
        }
        cout<<endl;
    }
    
    return 0;
}
/* 13575949	1225	Digit Counting	Accepted	C++	0.016	2014-05-02 00:09:23 */