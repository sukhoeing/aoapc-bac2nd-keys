// Bungee Jumping, UVa10868
// 陈锋
#include<climits>
#include<cassert>
#include<cmath>
#include<cstring>
#include<iostream>
#include<functional>
#include<algorithm>
#include<string>
#include<vector>
#include<set>
using namespace std;
const double eps = 1e-7;
double dcmp(double x) { if(fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

double k,l,s,w;
const double g = 9.81;

int main()
{           
    while(true) {
        cin>>k>>l>>s>>w;
        if(k == 0) break;
        double dl = s < l ? 0 : (s-l); // dl为绳子要增加的长度
        // 令v为触底的速度，根据动能守恒, wgs = k dl^2 /2 + w * v^2/2
        // g*s*2 = k*dl*dl/w + v*v
        double vq = g*s*2 - k*dl*dl/w;
        // cout<<"v^2 = "<<vq<<endl;
        if(dcmp(vq) <= 0)
            cout<<"Stuck in the air."<<endl;
        else if(dcmp(vq - 100) < 0)
            cout<<"James Bond survives."<<endl;
        else
            cout<<"Killed by the impact."<<endl;
    }
    return 0;
}

// 14067520	10868	Bungee Jumping	Accepted	C++	0.009	2014-08-20 03:34:09