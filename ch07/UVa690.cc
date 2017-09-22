// Pipeline Scheduling, UVa690
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
const int MAXN = 20+1, UNITS = 5, MAXT = 10;
int n, S[UNITS][MAXT*MAXN];
int Task[MAXN]; // Task[i]第i个时间点是在unit?
int Ans[MAXT+1]; // 将i个Task调度好所需要的最小时间
vector<int> Dist;

bool canPut(int clock){ // 能不能在clock开始执行一个任务
    _for(i, 0, n) if(S[Task[i]][clock+i]) return false;
    return true;
}
// 在clock开始安排一个任务
void put(int clock) { _for(i, 0, n) S[Task[i]][clock+i] = 1; }
// 清除从clock开始安排的任务
void remove(int clock){ _for(i, 0, n) S[Task[i]][clock+i] = 0; }
// 已经安排了t个任务，共安排T个任务，第t+1个任务从clock开始执行
void dfs(int t, int T, int clock, int& ans){
    if(t == T){
        ans = min(ans, clock + n);
        return;
    }
    
    for(auto D : Dist) {
        int c = clock + D;
        if(c + Ans[T-t] >= ans) break; // 无论如何不会搜出最优答案了
        if(!canPut(c)) continue;
        put(c);
        dfs(t+1, T, c, ans);
        remove(c);
    }
}

int main(){
    char line[64];
    while(scanf("%d", &n) == 1 && n){
        memset(S, 0, sizeof(S)), memset(Task, 0, sizeof(Task)), memset(Ans, 0, sizeof(Ans));
        Dist.clear();
        _for(i, 0, UNITS){
            scanf("%s", line);
            _for(j, 0, n)
                if(line[j] == 'X') Task[j] = i; 
        }
                
        put(0);        
        _for(i, 1, n+1) if(canPut(i)) Dist.push_back(i); // 两个任务可以间隔i
        
        Ans[1] = n;
        _for(T, 1, MAXT+1) {
            Ans[T] = T * n; // T个任务执行完需要的最优时间
            dfs(1, T, 0, Ans[T]);
        }
        
        printf("%d\n", Ans[MAXT]);
    }    
    return 0;
}

// Live Archive: 1451402 5678 Pipeline Scheduling Accepted C++ 0.049  2014-05-14 23:43:26 