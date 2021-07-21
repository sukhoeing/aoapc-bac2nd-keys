// UVa1619 Feel Good
// 陈锋
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;
typedef long long LL;
const int MAXN = 100000 + 4;
int A[MAXN], L[MAXN], R[MAXN], N; // A[i] is minimum in A(L, R)
LL S[MAXN];

int main() {
  S[0] = 0;
  ios::sync_with_stdio(false), cin.tie(0);
  for (int t = 0; cin >> N; t++) {
    if (t) cout << endl;
    for (int i = 1; i <= N; i++) cin >> A[i], S[i] = S[i - 1] + A[i];
    stack<int> s1;
    for (int i = 1; i <= N; i++) {
      while (!s1.empty() && A[s1.top()] >= A[i]) s1.pop();
      L[i] = s1.empty() ? 0 : s1.top();
      s1.push(i);
    }
    stack<int> s2;
    for (int i = N; i >= 1; i--) {
      while (!s2.empty() && A[s2.top()] >= A[i]) s2.pop();
      R[i] = s2.empty() ? (N + 1) : s2.top();
      s2.push(i);
    }
    LL ans = -1;
    int ans_i;
    for (int i = 1; i <= N; i++) {
      LL v = (S[R[i] - 1] - S[L[i]]) * A[i];
      if (v > ans) ans = v, ans_i = i;
    }
    if (ans == 0) printf("0\n1 1\n");
    else printf("%lld\n%d %d\n", ans, L[ans_i] + 1, R[ans_i] - 1);
  }
  return 0;
}
// 19949519	1619	Feel Good	Accepted	C++11	0.140
// 2017-09-02 08:04:46