// Kickdown, ACM/ICPC NEERC 2006, UVa1588
// 陈锋
#include<cassert>
#include<cstdlib>
#include<iostream>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<set>
using namespace std;

/*
给出两个长度分别为n1, n2（n1,n2<=100）且每列高度只为1或2的长条。
需要将它们放入一个高度为3的容器（如下图），问能够容纳它们的最短容器长度。
*/
const int MAXN = 100 + 1;

int main()
{    
    string sec1, sec2;
    int H[MAXN*3], b1 = MAXN, b2;
    while(cin>>sec1>>sec2){
        memset(H, 0, sizeof(H));
        int len1 = sec1.size(), len2 = sec2.size();
        for(int i = 0; i < sec1.size(); i++)
            H[b1+i] = sec1[i] - '0';
        
        int ans = len1 + len2;
        for(b2 = b1 - len2; b2 <= b1 + len1; b2++) {
            bool ok = true;
            for(int i = 0; i < len2; i++) {
                if(sec2[i] - '0' + H[b2+i] > 3) { ok = false; break; }
            }
            if(ok) ans = min(ans, max(b2+len2, b1+len1) - min(b1,b2));
        }
        
        cout<<ans<<endl;
    }
    return 0;
}
/* 13573012	1588	Kickdown	Accepted	C++	0.016	2014-05-01 09:57:08 */