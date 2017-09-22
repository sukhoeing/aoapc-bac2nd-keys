// UVa817 According to Bartjens
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
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)

struct OP {
  int val;
  char op;
  OP(int v) : op(0) { val = v; }
  OP(char _op) : val(-1) { op = _op; }
};

ostream& operator<<(ostream& os, const OP& op) {
  if (op.op)
    os << op.op;
  else
    os << op.val;
  return os;
}

int eval(const vector<OP>& exp, int l, int r) {
  assert(l <= r);
  const auto& le = exp[l];
  if (l == r) {
    assert(le.op == 0 && le.op != -1);
    return le.val;
  }
  int ai = -1, mi = -1;
  _rep(i, l, r) {
    auto op = exp[i].op;
    if (op == '+' || op == '-') ai = i;
    if (op == '*') mi = i;
  }
  if (ai != -1) {
    int lval = eval(exp, l, ai - 1), rval = eval(exp, ai + 1, r);
    return exp[ai].op == '+' ? lval + rval : lval - rval;
  }
  assert(mi != -1);
  return eval(exp, l, mi - 1) * eval(exp, mi + 1, r);
}

const string OPS = "+-*";
char S[16];
int SZ;

void dfs(int cur, vector<OP>& exp, vector<string>& ans) {
  if (cur == 0) {
    exp.emplace_back((int)(S[0] - '0'));
    dfs(cur + 1, exp, ans);
    exp.pop_back();
    return;
  }
  if (cur == SZ) {
    if (eval(exp, 0, exp.size() - 1) == 2000) {
      stringstream ss;
      for (auto e : exp) ss << e;
      ans.push_back(ss.str());
    }
    return;
  }
  auto lv = exp.back().val;
  assert(lv != -1);
  if (lv != 0) {
    exp.back().val = lv * 10 + S[cur] - '0';
    dfs(cur + 1, exp, ans);
    exp.back().val = lv;
  }
  for (auto op : OPS) {
    exp.emplace_back(op), exp.emplace_back((int)(S[cur] - '0'));
    dfs(cur + 1, exp, ans);
    exp.pop_back(), exp.pop_back();
  }
}

int main() {
  vector<OP> exp;
  vector<string> ans;
  for (int t = 1; scanf("%s", S) == 1 && S[0] != '='; t++) {
    SZ = strlen(S) - 1, S[SZ] = 0;
    printf("Problem %d\n", t);
    if (strcmp(S, "2000") == 0) {
      puts("  IMPOSSIBLE");
      continue;
    }
    exp.clear(), ans.clear();
    dfs(0, exp, ans);
    sort(begin(ans), end(ans));
    if (ans.empty())
      puts("  IMPOSSIBLE");
    else
      for (auto& s : ans) printf("  %s=\n", s.c_str());
  }
}
// 19481471	817	According to Bartjens	Accepted	C++11	0.320	2017-06-06 08:29:20