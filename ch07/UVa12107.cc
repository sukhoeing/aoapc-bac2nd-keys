// UVa12107 Digit Puzzle
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
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
struct Exp {
  string A[3];
  bool operator<(const Exp& exp) const {
    _for(i, 0, 3) if (A[i] != exp.A[i]) return A[i] < exp.A[i];
    return false;
  }
};

ostream& operator<<(ostream& os, const Exp& ce) {
  return os << ce.A[0] << " " << ce.A[1] << " " << ce.A[2];
}

typedef long long LL;
map<Exp, int> SolCnt;

void dfsGen(Exp& e, int cur, int pos) {
  if (cur == 3) return;
  auto back = e.A[cur][pos];
  int nCur = cur + (pos + 1) / e.A[cur].size(), nPos = (pos + 1) % e.A[cur].size();
  dfsGen(e, nCur, nPos);

  e.A[cur][pos] = '*';
  ++SolCnt[e];
  dfsGen(e, nCur, nPos);
  e.A[cur][pos] = back;
}

void generate() {
  Exp e;
  _for(a, 1, 100) _for(b, 1, 100) {
    e.A[0] = to_string(a), e.A[1] = to_string(b), e.A[2] = to_string(a * b);
    // Exp ce = e;
    dfsGen(e, 0, 0);
  }
}

const string CH = "*0123456789";

void dfs(const int c, const int maxc, Exp& e, int cur, int pos, bool& found, Exp& ans) {
  if (found && ans < e) return;
  if (SolCnt.count(e) && SolCnt[e] == 1) {
    if (!found) found = true, ans = e;
    if (e < ans) ans = e;
    return;
  }
  if (cur >= 3) return;

  int nCur = cur + (pos + 1) / e.A[cur].size(), nPos = (pos + 1) % (e.A[cur].size());
  const char bk = e.A[cur][pos];
  for (auto cd : CH) {
    if ((cd == '0' && pos == 0)) continue;
    e.A[cur][pos] = cd;
    int nc = c + (cd != bk);
    if (nc <= maxc) dfs(nc, maxc, e, nCur, nPos, found, ans);
    e.A[cur][pos] = bk;
  }
}

int main() {
  generate();
  Exp E;
  for (int t = 1; cin >> E.A[0] && E.A[0] != "0"; t++) {
    cin >> E.A[1] >> E.A[2];
    cout << "Case " << t << ": ";
    _rep(maxc, 0, 8) {
      Exp ce = E, ans;
      bool found = false;
      dfs(0, maxc, ce, 0, 0, found, ans);
      if (found) {
        cout << ans;
        break;
      }
    }
    cout << endl;
  }
  return 0;
}
// 19507094	12107	Digit Puzzle	Accepted	C++11	1.960	2017-06-11 12:50:30
