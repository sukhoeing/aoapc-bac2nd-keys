// UVa1591 Data Mining
// 陈锋
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <climits>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
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

int main() {
  LL N, SP, SQ;
  auto f = [](LL x, int a, int b){
    return (x + (x<<a)) >> b;
  };
  while(scanf("%lld%lld%lld", &N, &SP, &SQ) == 3){
    int A = 64, B = 64;
    LL K = LLONG_MAX;
    _rep(a, 0, 31) _rep(b, 0, 31){      
      if(f(SP,a,b) < SQ) continue;
      LL k = f(SP*(N-1),a,b) + SQ;
      if(k < K) K = k, A = a, B = b;      
    }
    printf("%lld %d %d\n", K, A, B);
  }
  return 0; 
}
// 2136321	2959	Data Mining	Accepted	C++11	0.003	2017-03-05 14:30:20