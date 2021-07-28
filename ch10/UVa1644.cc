// UVa1644 Prime Gap, ACM/ICPC Japan 2007
// 陈锋
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXP = 1299709 + 4;
bool IsPrime[MAXP];
vector<int> primes;
void sieve() {
  fill_n(IsPrime, MAXP, true), primes.clear(), IsPrime[2] = 1;
  for (LL i = 2; i < MAXP; i++) {
    if (!IsPrime[i])
      continue;
    primes.push_back(i);
    for (LL j = i * i; j < MAXP; j += i)
      IsPrime[j] = false;
  }
}
int solve(int n) {
  if (IsPrime[n])
    return 0;
  vector<int>::iterator pl = lower_bound(primes.begin(), primes.end(), n);
  assert(pl != primes.end()), assert(pl != primes.begin());
  return *(pl) - *(pl - 1);
}

int main() {
  sieve();
  for (int n; cin >> n && n;)
    cout<<solve(n)<<endl;
  return 0;
}
// 20055470	1644	Prime Gap	Accepted	C++11	0.000
// 2017-09-24 07:13:48