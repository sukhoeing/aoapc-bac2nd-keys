// UVa1663, Purifying Machine, ACM/ICPC Beijing 2005
// 陈锋
#include <cassert>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(int)(b); ++i)
using namespace std;

// 二分图最大基数匹配
template<int maxn>
struct BPM {
  int n, m;               // 左右顶点个数
  vector<int> G[maxn];    // 邻接表
  int left[maxn];         // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool T[maxn];           // T[i]为右边第i个点是否已标记

  int right[maxn];        // 求最小覆盖用
  bool S[maxn];           // 求最小覆盖用

  void init(int n, int m) {
    this->n = n, this->m = m;
    for (int i = 0; i < n; i++) G[i].clear();
  }
  void AddEdge(int u, int v) { G[u].push_back(v); }
  bool match(int u) {
    S[u] = true;
    for (size_t i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (!T[v]) {
        T[v] = true;
        if (left[v] == -1 || match(left[v])) {
          left[v] = u, right[u] = v;
          return true;
        }
      }
    }
    return false;
  }

  // 求最大匹配
  int solve() {
    fill_n(left, maxn, -1), fill_n(right, maxn, -1);
    int ans = 0;
    for (int u = 0; u < n; u++) { // 从左边结点u开始增广
      fill_n(S, maxn, 0), fill_n(T, maxn, 0);
      if (match(u)) ans++;
    }
    return ans;
  }
};

int countBit(int x, int w) {
  int b = 1, ans = 0;
  _for(i, 0, w) ans += ((b & x) != 0), b <<= 1;
  return ans;
}
string printbin(int x, int w) {
  string buf;
  for (int i = w - 1; i >= 0; i--) buf += (((1 << i)&x) > 0 ? 1 : 0) + '0';
  return buf;
}
const int MAXM = 1024 + 5;
BPM<MAXM> solver;
string S[MAXM];
int N, M, Set[MAXM];
int main() {
  string buf;
  set<int> vs; // verticles
  while (true) {
    cin >> N >> M;
    if (N == 0) break;
    int sz = 1 << N;
    fill_n(Set, sz, 0), solver.init(sz, sz);
    _for(i, 0, M) {
      cin >> buf;
      int x = -1, v = 0, bit = 1;
      _for(j, 0, buf.size()) {
        char c = buf[j];
        if (c == '*') x = j, bit = 1;
        else bit = c - '0';
        v = v * 2 + bit;
      }
      Set[v] = 1;
      if (x != -1) v &= ~(1 << (N - x - 1)), Set[v] = 1;
    }

    // 左边是偶数个1的串，右边是奇数个1的模板串
    int cnt = 0;
    _for(i, 0, sz) {
      if (!Set[i]) continue;
      cnt++;
      if (countBit(i, N) % 2 == 1) continue;
      _for(b, 0, N) {
        int j = (1 << b)^i;
        if (Set[j]) solver.AddEdge(i, j);
      }
    }
    cout << cnt - solver.solve() << endl;
  }
  return 0;
}
// 14805864 1663  Purifying Machine Accepted  C++ 0.162 2015-01-15 10:15:19