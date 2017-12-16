// LA6286 Jumping Around
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
#define _repc(cnt) for (int i = 0; i < (int)(cnt); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;
int N, A[4], cur;
void move(int step) {
  int ci = abs(step); assert(ci > 0);
  cur += step; assert(cur >= 0 && cur < N);
  printf(" %d", cur);
  assert(A[ci]--);
}

void move(int step, int cnt) { _repc(cnt) move(step); }

void solve() {
  printf("0"), cur = 0;
  int c3 = A[3] / 3, cm3 = A[3] % 3;
  if (cm3 == 0) {
    move(3, c3), move(1);    // 0 -> 3 -> 6 -> 7       
    move(-3, c3), move(1);   // 7 -> 4 -> 1 -> 2      
    move(3, c3);             // 2 -> 5 -> 8    
  }
  if (cm3 == 1) {
    move(3, c3 + 1), move(-2);   
    move(-3, c3), move(1);       
    move(3, c3), move(2);        
  }
  if (cm3 == 2) {
    move(3, c3 + 1), move(-1);   
    move(-3, c3), move(-1);      
    move(3, c3 + 1);             
  }
  move(1, A[1] - 1);
  int b2 = A[2] / 2, bm2 = A[2] % 2; // B/2, B%2
  if(bm2 == 0)                  
    move(2, b2), move(1), move(-2, b2);
  else                          
    move(2, b2 + 1), move(-1), move(-2, b2);
  puts("");
}

int main() {
  int t;
  while (_ri1(t) == 1) {
    while (t--) {      
      _ri3(A[1], A[2], A[3]);
      N = A[1] + A[2] + A[3] + 1;
      solve();
    }
  }
  return 0;
}
// 2332234  6286  Jumping Around  Accepted  C++11 0.058 2017-12-16 09:32:52