// UVa11491 - Erasing and Winning
// 陈锋
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
using namespace std;

const int MAXN = 100000 + 4;
int NUM[MAXN], NEXT[MAXN][10];

void init(int N) {
  _for(d, 0, 10) {
    int pos = N;  // 目前为止出现的最左边的d的位置
    for (int j = N - 1; j >= 0; j--) {
      if (NUM[j] == d) pos = j;
      NEXT[j][d] = pos;
    }
  }
}

// 在NUM的[start, end)区间内选最左边的最大值
int select_max(int start, int end, int& pos) {
  for (int d = 9; d >= 0; d--) {
    if (NEXT[start][d] < end) {
      pos = NEXT[start][d];
      return d;
    }
  }
  assert(false);
}
// 要在NUM[0...N]中选择E位的最大数字
void solve(int N, int E) {
  init(N);
  string ans;
  int start = 0, pos;
  while (E--) ans += select_max(start, N - E, pos) + '0', start = pos + 1;
  puts(ans.c_str());
}

char buf[MAXN];
int main() {
  int N, D;
  while (scanf("%d%d\n", &N, &D) == 2 && N && D) {
    gets(buf);
    _for(i, 0, N) NUM[i] = buf[i] - '0';
    solve(N, N - D);
  }
  return 0;
}

// 14804611	11491	Erasing and Winning	Accepted	C++	0.129
// 2015-01-15 04:17:34