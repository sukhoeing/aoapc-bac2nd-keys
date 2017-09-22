// UVa804 Petri Net Simulation
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
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
template <typename T>
inline vector<T>& operator+=(vector<T>& v, const T& x) {
  v.push_back(x);
  return v;
}
template <typename T>
inline set<T>& operator+=(set<T>& s, const T& x) {
  s.insert(x);
  return s;
}

typedef long long LL;

vector<int> tokens;
struct Trans {
  unordered_map<int, int> input;
  vector<int> output;
  bool enabled() const {
    for (auto p : input)
      if (tokens[p.first] < p.second) return false;
    return true;
  }
  void fire() const {
    for (auto p : input) {
      assert(tokens[p.first] >= p.second);
      tokens[p.first] -= p.second;
    }
    for (auto pi : output) tokens[pi]++;
  }
};
vector<Trans> TS;
int enabledTrans() {
  _for(ti, 0, TS.size()) if (TS[ti].enabled()) return ti;
  return -1;
}

int main() {
  int NP, NT, NF;
  for (int kase = 1; scanf("%d", &NP) == 1 && NP; kase++) {
    tokens.resize(NP);
    _for(i, 0, NP) scanf("%d", &(tokens[i]));
    scanf("%d", &NT);
    TS.clear(), TS.resize(NT);
    _for(i, 0, NT) {
      int pi;
      auto& t = TS[i];
      while (scanf("%d", &pi) == 1 && pi != 0) {
        if (pi < 0)
          ++t.input[-pi - 1];
        else
          t.output += pi - 1;
      }
    }
    scanf("%d", &NF);
    int cnt = 0, live = 1;
    _for(f, 0, NF) {
      int ti = enabledTrans();
      if (ti == -1) live = ti != -1;
      if (!live) break;
      TS[ti].fire(), ++cnt;
    }
    printf("Case %d: ", kase);
    if (live)
      printf("still live after %d transitions\n", NF);
    else
      printf("dead after %d transitions\n", cnt);
    printf("Places with tokens:");
    _for(pi, 0, NP) if (tokens[pi]) printf(" %d (%d)", pi + 1, tokens[pi]);
    puts("\n");
  }
  return 0;
}
// 19342087	804	Petri Net Simulation	Accepted	C++11	0.040	2017-05-09 14:57:34