// Cube painting, UVa253
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

int ROT[24][7] = {
{0,1,2,3,4,5,6},
{0,1,3,5,2,4,6},
{0,1,4,2,5,3,6},
{0,1,5,4,3,2,6},
{0,2,1,4,3,6,5},
{0,2,3,1,6,4,5},
{0,2,4,6,1,3,5},
{0,2,6,3,4,1,5},
{0,3,1,2,5,6,4},
{0,3,2,6,1,5,4},
{0,3,5,1,6,2,4},
{0,3,6,5,2,1,4},
{0,4,1,5,2,6,3},
{0,4,2,1,6,5,3},
{0,4,5,6,1,2,3},
{0,4,6,2,5,1,3},
{0,5,1,3,4,6,2},
{0,5,3,6,1,4,2},
{0,5,4,1,6,3,2},
{0,5,6,4,3,1,2},
{0,6,2,4,3,5,1},
{0,6,3,2,5,4,1},
{0,6,4,5,2,3,1},
{0,6,5,3,4,2,1},
};

int main()
{
    string line, s1, s2, t;
    while(cin>>line) {
        assert(line.size() == 12);
        s1 = " "; 
        s2.clear();
        s1 += line.substr(0, 6); s2 += line.substr(6, 6);
        bool ans = false;
        for(int i = 0; i < 24; i++) {
            t.clear();
            for(int j = 1; j <= 6; j++) t += s1[ROT[i][j]];
            // cout<<"t = "<<t<<", s2 = "<<s2<<endl;
            if(t == s2) { ans = true; break; }
        }
        cout<<(ans?"TRUE":"FALSE")<<endl;
    }
}

// 13952506	253	Cube painting	Accepted	C++	0.019	2014-07-27 06:50:41