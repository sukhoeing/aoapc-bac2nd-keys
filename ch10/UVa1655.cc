// UVa1655 Exam
// 陈锋
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;
using namespace std;

int main() {
  LL N;
  for (int kase = 1; cin >> N && N; kase++) {  // a ≤ b ≤ c
    LL ans = 0;
    for (LL a = 1; a * a * a <= N; a++) {    // 1 ≤ a ≤ N^(1/3)
      for (LL b = a; b * b <= N / a; b++) {  // a ≤ b ≤ (N/ab)
        LL c = N / (a * b);                  // b ≤ c ≤ N/ab
        if (c < b) break;
        if (a < b) {
          ans += 3;            // b = c, 2 3 3, 3 2 3, 3 3 2
          ans += 6 * (c - b);  // b < c < N/ab
        } else {               // a = b
          ans += 1;            // b = c, 2 2 2
          ans += 3 * (c - b);  // b < c < N/ab
        }
      }
    }
    printf("Case %d: %lld\n", kase, ans);
  }
  return 0;
}
// 2470438 6369 Exam Accepted C++11 2.236 2018-10-14 04:31:57