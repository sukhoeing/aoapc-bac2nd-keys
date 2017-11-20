// UVa307 Sticks
// 陈锋
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
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

const int MAXN = 200;
int N, S, A[MAXN];
bool used[MAXN];

// len: 当前大棍子还差多少长度, num: 已经拼成的棍子数量, cur: 当前决策的小棍子
bool testLen(int len, int num, int cur, const int L) {
  if (num * L == S) return true;
  _for(i, cur, N) if (!used[i] && A[i] <= len) {
    used[i] = true;  // 尝试用第i个棍子
    if (len == A[i]) {
      if (testLen(L, num + 1, 0, L)) return true;
    } else {
      if (testLen(len - A[i], num, i + 1, L)) return true;
    }
    used[i] = false;                  // 发现用A[i]不行
    if (len == L && cur == 0) break;  // 作为第一节失败了, 总不能把它剩下
    if (len == A[i]) break;           // 之后一定无法组装完成
    while (i + 1 < N && A[i + 1] == A[i]) i++;  // 相同长度的stick不要再尝试
  }
  return false;
}

int main() {
  while (_ri1(N) == 1 && N) {
    S = 0;
    _for(i, 0, N) _ri1(A[i]), S += A[i];
    sort(A, A + N, greater<int>());
    _rep(L, A[0], S) if (S % L == 0) {
      fill(used, used + N, false);
      if (testLen(L, 0, 0, L)) {
        printf("%d\n", L);
        break;
      }
    }
  }
  return 0;
}
// 20367314 307 Sticks Accepted C++11 0.110 2017-11-19 07:34:11