// UVa12538 Version Controlled IDE
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
#define _for(i, a, b) for (decltype(b) i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _zero(D) memset((D), 0, szof(D))
#define _init(D, v) memset((D), (v), szof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))

const int MAXN = (1 << 23), MAXQ = 50000 + 4;
struct Node;
typedef Node *PNode;
PNode NilNode, VER[MAXQ];
struct Node {
  PNode left, right;
  char label;  // user def label
  int key, sz;
  Node(char c = 0, int s = 1) : label(c), sz(s) {
    left = right = NilNode, key = rand();
  }
  PNode update() {
    sz = 1 + left->sz + right->sz;
    return this;
  }
};
Node Nodes[MAXN];
struct Treap {
  int bufIdx = 0, d;  // this problem need.
  PNode copyOf(PNode u) {
    if (u == NilNode) return u;
    auto ret = &Nodes[bufIdx++];
    *ret = *u;
    return ret;
  }
  PNode merge(PNode a, PNode b) {
    if (a == NilNode) return copyOf(b);
    if (b == NilNode) return copyOf(a);
    PNode ret;
    if (a->key < b->key)
      ret = copyOf(a), ret->right = merge(a->right, b);
    else
      ret = copyOf(b), ret->left = merge(a, b->left);
    return ret->update();
  }
  void split(PNode pn, PNode &l, PNode &r, const int k) {
    int psz = pn->sz, plsz = pn->left->sz;
    if (k == 0)
      l = NilNode, r = copyOf(pn);
    else if (psz <= k)
      l = copyOf(pn), r = NilNode;
    else if (plsz >= k)
      r = copyOf(pn), split(pn->left, l, r->left, k), r->update();
    else
      l = copyOf(pn), split(pn->right, l->right, r, k - plsz - 1), l->update();
  }

  PNode build(int l, int r, const char *s) {
    if (l > r) return NilNode;
    int m = (l + r) / 2;
    auto u = Node(s[m]);
    PNode a = copyOf(&u), p = build(l, m - 1, s), q = build(m + 1, r, s);
    p = merge(p, a), a = merge(p, q);
    return a->update();
  }
  PNode insert(const PNode ver, int pos, const char *s) {
    PNode p, q, r = build(0, strlen(s) - 1, s);
    split(ver, p, q, pos);
    return merge(merge(p, r), q);
  }
  PNode remove(PNode ver, int pos, int n) {
    PNode p, q, r;
    split(ver, p, q, pos - 1), split(q, q, r, n);
    return merge(p, r);
  }
  void print(PNode ver) {
    if (ver == NilNode) return;
    print(ver->left), d += (ver->label == 'c');
    putchar(ver->label);
    print(ver->right);
  }
  void debugPrint(PNode pn) {
    if (pn == NilNode) return;
    debugPrint(pn->left), putchar(pn->label), debugPrint(pn->right);
  }
  void traversal(PNode pn, int pos, int n) {
    PNode p, q, r;
    split(pn, p, q, pos - 1), split(q, q, r, n), print(q);
  }
  void init() {
    bufIdx = 0, d = 0, NilNode = &Nodes[bufIdx++], NilNode->sz = 0;
  }
};
Treap tree;
int main() {
  int n, opt, v, p, c, ver = 0;
  _ri1(n), tree.init();
  char s[128];
  VER[0] = NilNode;
  _for(i, 0, n) {
    _ri1(opt);
    switch (opt) {
      case 1:
        scanf("%d %s", &p, s), p -= tree.d;
        VER[ver + 1] = tree.insert(VER[ver], p, s), ver++;
        break;
      case 2:
        _ri2(p, c), p -= tree.d, c -= tree.d;
        VER[ver + 1] = tree.remove(VER[ver], p, c), ver++;
        break;
      case 3:
        _ri3(v, p, c), v -= tree.d, p -= tree.d, c -= tree.d;
        tree.traversal(VER[v], p, c), puts("");
        break;
      default:
        break;
    }
  }
  return 0;
}
// 2402212 6145 Version Controlled IDE Accepted C++11 0.396 2018-06-28 13:19:04