// UVa1650 Number String
// 陈锋
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
typedef long long LL;
const int MOD = 1000000007;
const int MAXN = 1000 + 4;
string S;
int N, D[MAXN][MAXN], SD[MAXN][MAXN];

int main() {
  D[1][1] = 1, SD[1][1] = 1;
  while (cin >> S) {
    N = S.size() + 1;
    _rep(i, 2, N) _rep(j, 1, i) {
      SD[i][0] = 0;
      if (S[i - 2] == '?')
        D[i][j] = SD[i - 1][i - 1];
      else if (S[i - 2] == 'I')
        D[i][j] = SD[i - 1][j - 1];
      else
        D[i][j] = (SD[i - 1][i - 1] - SD[i - 1][j - 1] + MOD) % MOD;
      SD[i][j] = (SD[i][j - 1] + D[i][j]) % MOD;
    }

    cout << SD[N][N] << endl;
  }
  return 0;
}
// 2228606	5697	Number String	Accepted	C++11	0.126	2017-08-08 01:47:09