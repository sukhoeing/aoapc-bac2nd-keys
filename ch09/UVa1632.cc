// UVa1632 Alibaba
// 陈锋
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int MAXN = 10000 + 4, INF = 0x7f7f7f7f;
int N, D[MAXN], T[MAXN];
int DP[2][MAXN][2];

int main() {

  while (cin>>N) {
    for(int i = 0; i < N; i++) cin>>D[i]>>T[i];
    memset(DP, 0, sizeof(DP));
    int cur = 0;
    for (int i = N - 1; i >= 0; i--){ // cur:i cur^1 : i+1
      for (int j = i + 1; j < N; j++) {
        int& d0 = DP[cur][j][0];
        d0 = min(DP[cur^1][j][0] + D[i+1] - D[i], DP[cur^1][j][1] + D[j] - D[i]);
        if (d0 >= T[i]) d0 = INF;
        int& d1 = DP[cur][j][1];
        d1 = min(DP[cur][j-1][1] + D[j] - D[j-1], DP[cur][j-1][0] + D[j] - D[i]);
        if (d1 >= T[j]) d1 = INF;
      }
      cur ^= 1;
    } 

    int ans = min(DP[cur^1][N - 1][0], DP[cur^1][N - 1][1]);
    if (ans == INF)
      puts("No solution");
    else
      printf("%d\n", ans);
  }
  return 0;
}
// 20174917 1632    Alibaba Accepted    C++11   0.360   2017-10-14 08:44:56