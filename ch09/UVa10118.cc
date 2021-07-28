// UVa10118 Free Candies
// 陈锋
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 40 + 2;
int N, P[4][MAXN], D[MAXN][MAXN][MAXN][MAXN], H[4];
int dp(bitset<32> &b) {
  int &d = D[H[0]][H[1]][H[2]][H[3]];
  if (d > -1)
    return d;
  d = 0;
  if (b.count() == 5)
    return d = 0;
  for (int pi = 0; pi < 4; pi++)
    if (H[pi] < N) {
      int t = P[pi][H[pi]++];
      if (b.test(t))
        b.reset(t), d = max(d, dp(b) + 1), b.set(t);
      else
        b.set(t), d = max(d, dp(b)), b.reset(t);
      H[pi]--;
    }
  return d;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  while (cin >> N && N) {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < 4; j++)
        cin >> P[j][i];
    memset(D, -1, sizeof(D)), memset(H, 0, sizeof(H));
    bitset<32> b;
    int ans = dp(b);
    printf("%d\n", ans);
  }
  return 0;
}
// 20188891	10118	Free Candies	Accepted	C++11	0.060
// 2017-10-16 23:08:12