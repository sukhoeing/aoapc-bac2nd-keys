// UVa1611 Crane
// 陈锋
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 10000 + 4;
int N, A[MAXN];
typedef pair<int, int> IPair;

void swapSeg(vector<IPair> &ans, int st, int l) { // [st,st+l)
  for (int i = 0; i < l; i++)
    swap(A[st + i], A[st + l + i]);
  ans.push_back(make_pair(st, st + 2 * l - 1));
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  while (cin >> N) {
    vector<pair<int, int>> ans;
    for (int i = 1; i <= N; i++)
      cin >> A[i];
    for (int i = 1; i <= N; i++) {
      int p = find(A + i, A + N + 1, i) - A, l = p - i;
      if (A[i] == i)
        continue;
      if (2 * l > N - i + 1) {
        int sl = (N - i + 1) / 2;
        swapSeg(ans, N - 2 * sl + 1, sl);
      }
      p = find(A + i, A + N + 1, i) - A;
      swapSeg(ans, i, p - i);
    }
    cout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); i++)
      cout << ans[i].first << " " << ans[i].second << endl;
  }
  return 0;
}
// 19960872	1611	Crane	Accepted	C++11	0.190	2017-09-05
// 04:16:56