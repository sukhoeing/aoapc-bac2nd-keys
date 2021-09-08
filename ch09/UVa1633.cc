// Dyslexic Gollum, ACM/ICPC Amritapuri 2012, UVa1633
// 陈锋
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 1e9+7;
const int maxn = 400 + 4, KK = 10;
int T, n, k, P[1 << (KK + 1)], P1[1 << (KK + 1)];
LL F[maxn][1 << KK];
void dfsP(int w, int b) { // 搜索所有的长度≤k+1回文
  assert(w <= k + 1);
  if (w == k) { P[b] = 1; return; }
  if (w == k + 1) { P1[b] = 1; return; }
  dfsP(w + 2, b << 1);                          // 两边都加0
  dfsP(w + 2, ((1 << (w + 1)) + 1) | (b << 1)); // 两边都加1
}

void init() {
  memset(F, -1, sizeof(F)), memset(P, 0, sizeof(P)), memset(P1, 0, sizeof(P1));
  dfsP(1, 0); // 1 0 奇数长度回文，中间为0
  dfsP(1, 1); // 1 1 奇数长度回文，中间为1
  dfsP(2, 0); // 2 00 偶数长度回文
  dfsP(2, 3); // 2 11 偶数长度回文
}
// 前i位已经决策完成，并且最右边k位为b
int dp(int i, int b) {
  assert(i >= k && i <= n);
  assert(!P[b]);
  LL &d = F[i][b];
  if (d != -1) return d;
  if (i == n) return d = 1;
  d = 0;
  int nb = b << 1; // 第i+1位为0
  if (!P1[nb] && !P[nb &= ((1 << k) - 1)])
    d = (d + dp(i + 1, nb)) % MOD;
  nb = ((b << 1) + 1); // 第i+1位为1
  if (!P1[nb] && !P[nb &= ((1 << k) - 1)])
    d = (d + dp(i + 1, nb)) % MOD;
  return d;
}
inline LL pow_mod(LL x, LL k) { // x^k % MOD
  LL ans = 1;
  for (LL p = x, i = 0; (1 << i) <= k; i++, p = p * p % MOD)
    if (k & (1 << i)) ans = ans * p % MOD; // p = x ^ (2^i)
  return ans;
}
int main() {
  cin >> T;
  while (T--) {
    cin >> n >> k;
    if (k > n) { cout << pow_mod(2, n) << endl; continue; }
    init();
    LL ans = 0;
    for (int i = 0; i < (1 << k); i++)
      if (!P[i]) (ans += dp(k, i)) %= MOD;
    cout << ans << endl;
  }
  return 0;
}
// 1522684	LA 6343	Dyslexic Gollum	Accepted	C++	0.453	2014-08-17 13:48:35