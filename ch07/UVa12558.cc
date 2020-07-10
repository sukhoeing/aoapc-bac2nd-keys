// UVa12558 Egyptian Fractions (HARD version)
// 陈锋
#include <bits/stdc++.h>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
typedef long long LL;
int A, B, K;
unordered_set<int> R;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }

bool better(const vector<LL>& D, const vector<LL>& Ans) {
  if (Ans.empty()) return true;
  size_t sz = D.size();
  assert(sz == Ans.size());
  for (int i = sz - 1; i >= 0; i--)
    if (D[i] != Ans[i]) return D[i] < Ans[i];
  return false;
}

inline LL get_first(LL a, LL b, LL last) {
  // a/b + 1/c = A/B
  // 1/c <= A/B - a/b = (A*b-a*B)/(B*b)
  // c >= (B*b)/(A*b-a*B)
  return max((B * b) / (A * b - a * B), last + 1);
}

void dfs(LL a, LL b, const int d, const int maxd, vector<LL>& D, vector<LL>& Ans) {
  if (d > maxd) return;
  if (a * B > A * b) return;
  if (a == A && b == B) {
    if (better(D, Ans)) Ans = D;
    return;
  }
  LL deno = get_first(a, b, D.empty() ? 1LL : D.back());
  while (true) {
    // if(a/b + (maxd-d)/deno < A/B) break;
    if (a * B * deno + (maxd - d) * B * b < A * b * deno) break;
    if (!R.count(deno)) {
      LL na = a * deno + b, nb = b * deno, g = gcd(na, nb);
      D.push_back(deno);
      dfs(na / g, nb / g, d + 1, maxd, D, Ans);
      D.pop_back();
    }
    deno++;
  }
  return;
}

int main() {
  int T, x;
  scanf("%d", &T);
  _rep(t, 1, T) {
    scanf("%d%d%d", &A, &B, &K);
    R.clear();
    _for(i, 0, K) scanf("%d", &x), R.insert(x);
    _rep(maxd, 2, 100) {
      vector<LL> D, Ans;
      dfs(0, 1, 0, maxd, D, Ans);
      if (!Ans.empty()) {
        printf("Case %d: %d/%d=", t, A, B);
        for (size_t i = 0; i < Ans.size(); i++)
          printf("1/%lld%c", Ans[i], (i == Ans.size() - 1) ? '\n' : '+');
        break;
      }
    }
  }
  return 0;
}
// 19544890 12558 Egyptian Fractions (HARD version) Accepted  C++11 6.610 2017-06-20 03:44:31