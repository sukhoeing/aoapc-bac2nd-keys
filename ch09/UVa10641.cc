// UVa10641 Barisal Stadium
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
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;

const double eps = 1e-10;
int dcmp(double x) {
  if (fabs(x) < eps)
    return 0;
  else
    return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;

Vector operator+(const Vector& A, const Vector& B) {
  return Point(A.x + B.x, A.y + B.y);
}
Vector operator-(const Point& A, const Point& B) {
  return Point(A.x - B.x, A.y - B.y);
}
Vector operator*(const Vector& A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator/(const Point& A, double p) { return Vector(A.x / p, A.y / p); }
bool operator<(const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator==(const Point& a, const Point& b) {
  return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

double Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

const int MAXN = 30 + 2, MAXM = 1000 + 4, INF = INT_MAX;
int N, M, C[MAXM];
Point V[MAXN * 2], LT[MAXM], O;
int L[MAXM], R[MAXM], D[2 * MAXN];

bool canCover(const Point& lt, const Point& A, const Point& B) {
  return dcmp(Cross(B - A, lt - A) * Cross(B - A, O - A)) < 0;
}

void init() {
  _for(i, 0, M) {
    auto lt = LT[i];
    int &l = L[i], &r = R[i];
    l = -1, r = -1;
    _for(j, 0, N) {
      bool c1 = canCover(lt, V[(j - 1 + N) % N], V[j]),
           c2 = canCover(lt, V[j], V[j + 1]);
      if (!c1 && c2) l = j;
      if (c1 && !c2) r = j;
    }
    assert(l >= 0 && r >= 0);
    if (r < l) r += N;
  }
}

int solve() {
  int ans = INF;
  _for(i, 0, N) {
    fill_n(D, 2 * N + 1, INF);
    D[i] = 0;
    _for(j, i, i + N) _for(li, 0, M) {
      if (D[j] < INF && L[li] <= j && j <= R[li]) {
        int r = min(R[li], i + N);
        D[r] = min(D[r], D[j] + C[li]);
      }
      ans = min(ans, D[i + N]);
    }
  }
  return ans;
}

int main() {
  while (_ri1(N) == 1 && N) {
    O = {0, 0};
    _for(i, 0, N) {
      auto& v = V[i];
      scanf("%lf%lf", &(v.x), &(v.y));
      O = O + v, V[i + N] = v;
    }
    O = O / N;
    _ri1(M);
    _for(i, 0, M) {
      auto& lt = LT[i];
      scanf("%lf%lf", &(lt.x), &(lt.y));
      _ri1(C[i]);
    }
    init();
    int ans = solve();
    if (ans == INF)
      puts("Impossible.");
    else
      printf("%d\n", ans);
  }
  return 0;
}
// 20197303	10641	Barisal Stadium	Accepted	C++11	0.060 2017-10-18
// 06:45:47