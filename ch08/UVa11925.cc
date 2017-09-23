// UVa11925 Generating Permutations
// 陈锋
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;
int main() {
  string ans;
  deque<int> A, T;
  int N, L[300 + 2];
  while (_ri1(N) == 1 && N) {
    ans.clear(), A.resize(N, 0), T.resize(N, 0);
    _rep(i, 1, N) A[i-1] = i, _ri1(T[i - 1]), L[T[i - 1]] = i;
    while (A != T) {
      int a0 = A[0], a1 = A[1], l0 = L[a0], l1 = L[a1];
      if (l0 < l1 || (l0 == N && l1 == 1)) {
        ans += '2', A.push_back(A.front()), A.pop_front();
      } else {
        ans += '1', swap(A[0], A[1]);
      }
    }
    cout << ans << endl;
  }
  return 0;
}
// 19960589	11925	Generating Permutations	Accepted	C++11	0.010	2017-09-05 02:31:50