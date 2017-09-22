// Printer Queue, ACM/ICPC NWERC 2006, UVa12100
// ³Â·æ
#include<cassert>
#include<cstdio>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<queue>

using namespace std;
int readint() { int x; scanf("%d", &x); return x; }
const int MAXN = 128, MAXP = 10;
int n, m, priority[MAXN], pCnt[MAXP];
int main()
{
    int T = readint();    
    while(T--) {
        n = readint(), m = readint();
        fill_n(pCnt, MAXP, 0);
        fill_n(priority, MAXN, 0);
        queue<int> q;
        for(int i = 0; i < n; i++) {
            q.push(i);
            priority[i] = readint();
            pCnt[priority[i]]++;
        }
        
        int timer = 1;
        while(!q.empty()) {
            int t = q.front(), p = priority[t];
            bool lower = false;
            for(int hp = MAXP-1; hp > p; hp--)
                if(pCnt[hp] > 0) { lower = true; break; }
                
            q.pop();
            if(lower) { q.push(t); continue; }
            if(t == m) break;
            
            pCnt[p]--;
            assert(pCnt[p] >= 0);            
            timer++;
        }
        
        printf("%d\n", timer);
    }
        
    return 0;
}

// 13439845	12100	Printer Queue	Accepted	C++	0.019	2014-04-03 14:51:17