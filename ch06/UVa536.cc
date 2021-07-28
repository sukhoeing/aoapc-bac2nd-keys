// Tree Recovery, ULM 1997, UVa 536
// 陈锋
#include <iostream>
using namespace std;
string A, B; // pre order, in order
void solve(int pL, int pR, int iL, int iR) {
  if (pL == pR)
    return;
  int x = 0;
  for (int i = iL; i < iR; i++)
    if (B[i] == A[pL]) {
      x = i;
      break;
    }
  solve(pL + 1, pL + 1 + x - iL, iL, x);
  solve(pL + 1 + x - iL, pR, x + 1, iR);
  cout << A[pL];
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  while (cin >> A >> B)
    solve(0, A.size(), 0, B.size()), cout << endl;
  return 0;
}
// 2255 Accepted  360K  0MS G++ 1092B 2021-07-27 21:33:13