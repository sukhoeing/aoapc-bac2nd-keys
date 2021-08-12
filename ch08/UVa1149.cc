// UVa1149 Bin Packing
// 陈锋
#include <algorithm>
#include <iostream>
using namespace std;
const int MAXN = 100000 + 10;
int n, l, len[MAXN];
void solve() {
  cin >> n >> l;
  for (int i = 0; i < n; i++) cin >> len[i];
  sort(len, len + n, greater<int>());
  int ans = 0, left = 0, right = n - 1;
  while (left <= right) {
    ans++, left++;
    if (left != right && len[left] + len[right] <= l)
      right--;
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int k;
  cin >> k;
  for (int t = 0; t < k; t++) {
    if (t) cout << endl;
    solve();
  }
  return 0;
}
// 14804603 1149    Bin Packing Accepted    C++ 0.052   2015-01-15 04:13:32