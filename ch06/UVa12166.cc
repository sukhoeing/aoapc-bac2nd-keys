// Equilibrium Mobile, NWERC 2008, UVa12166
// 陈锋
#include<cassert>
#include<cmath>
#include<string>
#include<iostream>
#include<functional>
#include<algorithm>
#include<map>

using namespace std;
const int MAXN = 24;
typedef long long LL;

int main()
{
    int T; cin>>T;
    string line;
    map<LL, int> vCnt;
    while(T--) {
        cin>>line;
        vCnt.clear();
        int sz = line.size(), depth = 0, nodeCnt = 0;
        for(int i = 0; i < sz; i++) {
            char c = line[i];
            if(c == '[') depth++;
            else if(c == ']') depth--;
            else if(isdigit(c)) {
                LL v = c - '0';
                int j;
                for(j = i + 1; j < sz && isdigit(line[j]); j++) {
                    v *= 10;
                    v += line[j] - '0';
                }
                i = j-1;
                v <<= depth;
                vCnt[v] = vCnt[v] + 1;
                nodeCnt++;
            }
        }
        
        int K = -1;
        for(const auto& p : vCnt) K = max(K, p.second);
        assert(K > 0);
        cout<<(nodeCnt-K)<<endl;
    }
}

/* 13600716 12166 Equilibrium Mobile Accepted C++ 0.172  2014-05-07 14:38:32  */