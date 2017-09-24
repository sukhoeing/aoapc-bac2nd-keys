// LA6195 The Dueling Philosophers Problem
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>
#include <string>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const int MAXN = 1024;    
vector<int> G[MAXN]; // 有向图
int IND[MAXN]; // IND[u]是u的入度
    
int main(){
	int n, m, u, d;
    queue<int> q;
    while(cin>>n>>m && n && m){
        _for(i, 0, n) G[i].clear();
        fill_n(IND, n, 0);
        _for(i, 0, m) cin>>d>>u, G[d-1].push_back(u-1), IND[u-1]++;
        
        int cnt = 0, ans = 1;
        bool flag = false;
        _for(i, 0, n) if(IND[i] == 0) q.push(i);
        while(!q.empty()){
            cnt++;
            if(q.size() > 1) flag = true;
            u = q.front(); q.pop();
            for(int v : G[u]){ IND[v]--; if(IND[v] == 0) q.push(v); }
        }
        
        if(cnt != n) ans = 0;
        else if(flag) ans = 2;
        cout<<ans<<endl;
    }
	return 0;
}
// 1674618	6195	The Dueling Philosophers Problem	Accepted	C++	0.476	2015-04-11 14:04:21