// Weak Key, ACM/ICPC Seoul 2004, UVa1618
// 陈锋
#include <bits/stdc++.h>
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
using namespace std;
const int maxk = 5000 + 4;

vector<int> H[maxk], L[maxk];
typedef vector<int>::iterator VIT;
int k, N[maxk];
// Nq > Ns > Np > Nr
// p
// q N[q] > N[p] q in H[p]
// r N[r] < N[p] r in L[p] && r > q
// s N[s] > N[p] && N[s] < N[q] && s > r, s in H[p] && s in L[q] && s > r
bool find1(int p) {
  for (size_t qi = 0; qi < H[p].size(); qi++) { // Nq > Np, && q > p
    int q = H[p][qi];
    VIT rit = upper_bound(L[p].begin(), L[p].end(), q);
    if (rit == L[p].end())
      continue;
    int r = *rit; // Nr < Nq, r > q
    assert(r > q);
    VIT sit = upper_bound(H[p].begin(), H[p].end(), r);
    while (sit != H[p].end()) {
      int s = *sit++;
      assert(s > r);
      if (binary_search(L[q].begin(), L[q].end(), s))
        return true;
    }
  }

  return false;
}

// Nq < Ns < Np < Nr
// p
// q q in L[p]
// r r > q && r in H[p]
// s s > r && s in H[q] && s in L[p]
bool find2(int p) {                             // Nq > Ns > Np > Nr p<q<r<s
  for (size_t qi = 0; qi < L[p].size(); qi++) { // Nq > Np, && q > p
    int q = L[p][qi];
    VIT rit = upper_bound(H[p].begin(), H[p].end(), q);
    if (rit == end(H[p]))
      continue;
    int r = *rit; // Nr < Nq, r > q
    assert(r > q);
    VIT sit = upper_bound(L[p].begin(), L[p].end(), r);
    while (sit != L[p].end()) {
      int s = *sit++;
      assert(s > r);
      if (binary_search(H[q].begin(), H[q].end(), s))
        return true;
    }
  }

  return false;
}

bool solve() {
  _for(i, 0, k) if (find1(i) || find2(i)) return true;
  return false;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> k;
    _for(i, 0, k) cin >> N[i], H[i].clear(), L[i].clear();
    _for(i, 0, k) {
      _for(j, i + 1, k) {
        if (N[j] > N[i])
          H[i].push_back(j);
        else if (N[j] < N[i])
          L[i].push_back(j);
      }
    }
    cout << (solve() ? "YES" : "NO") << endl;
  }
  return 0;
}
// 20497013 1618    Weak Key    Accepted    C++11   0.050   2017-12-16 11:45:09