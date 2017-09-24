// LA7036 Puzzle & Dragons
// 陈锋 g++11 4.8.2
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
  Point& operator=(const Point& p){ x = p.x; y = p.y; return *this; }
};
typedef Point Vector;
Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }

struct Path {
	int combo, drop, length;
	Point start;
	char solution[16];
	void init(int len = 0, const char* str = nullptr){
		start.x = 0, start.y = 0, combo = 0, drop = 0, length = len;
		if(str) memcpy(solution, str, len);
		solution[len] = 0;
	} 	

	bool operator<(const Path& p) const {
		if(combo != p.combo) return combo < p.combo;
		if(drop != p.drop) return drop < p.drop;
		return length > p.length;
	}
};

const int N = 5, M = 6;
const vector<Vector> DIRS = {{0,1}, {0,-1}, {1,0}, {-1,0}};
const char op[5] = "RLDU";
char Buf[N][M+1], Grid[N][M+1], sol[11];
bool ELIM[N][M];
Path ans;
bool valid(const Point& p){ return p.x >= 0 && p.x < N && p.y >= 0 && p.y < M; }

// dfs消除点p周围所有颜色为c的格子，返回被消除的数量
int eliminate(const Point& p, char c){
	if(!valid(p)) return 0;
	if(Buf[p.x][p.y] != c || !ELIM[p.x][p.y]) return 0;
	Buf[p.x][p.y] = ' ', ELIM[p.x][p.y] = false;
	int res = 1;
	for(const auto& d : DIRS) res += eliminate(p + d, c);
	return res;
}
bool eliminate(int& combo, int& drop){ // 消除所有能消除的
	bool any = false;
	combo = drop = 0;
	_for(i, 0, N) _rep(j, 0, M-3){ // 3个一行
		char c = Buf[i][j];
		if(c == ' ') continue;
		if(c == Buf[i][j+1] && c == Buf[i][j+2]) 
			any = ELIM[i][j] = ELIM[i][j+1] = ELIM[i][j+2] = true;
	}

	_rep(i, 0, N-3) _for(j, 0, M){ // 3个一列
		if(Buf[i][j] == ' ') continue;
		if(Buf[i][j] == Buf[i+1][j] && Buf[i][j] == Buf[i+2][j])
			any = ELIM[i][j] = ELIM[i+1][j] = ELIM[i+2][j] = true;
	}
	if(!any) return false;
	_for(i, 0, N) _for(j, 0, M){
		if(!ELIM[i][j]) continue;
		combo++;
		drop += eliminate(Point(i,j), Buf[i][j]);
	}

	_for(j, 0, M){ // 上面的珠子往下平移
		int bottom = N-1;
		for(int i = N-1; i >= 0; i--){
			if(Buf[i][j] == ' ') continue;
			if(bottom != i){
				Buf[bottom][j] = Buf[i][j];
				Buf[i][j] = ' ';
			}
			bottom--;
		}
	}
	return true;
}
// 看看路径的消除结果
void tryPath(int step, const Point& st){
	Path res;
	res.init(step, sol);
	res.start = st;
	memcpy(Buf, Grid, sizeof(Grid));
	int combo, drop;
	while(eliminate(combo, drop)) res.combo += combo, res.drop += drop;
	if(ans.length == 0 || ans < res) ans = res;
}
// 寻找路径：(路径上下一个点，已经走出的步数, 上一个方向, 路径的起点)
void findPath(const Point& p, int step, int lastDir, const Point& st){
	tryPath(step, st);
	if(step >= 9) return;
	_for(i, 0, 4){
		if(step >= 2 && lastDir == (i^1)) continue; // 第2步就不能再回头走
		Point np = p + DIRS[i];
		if(!valid(np)) continue;
		swap(Grid[p.x][p.y], Grid[np.x][np.y]);
		sol[step] = op[i];
		findPath(np, step+1, i, st);
		swap(Grid[p.x][p.y], Grid[np.x][np.y]);
	}
}

int main(){
	int T; scanf("%d", &T);
	_for(t, 0, T){
		_for(i, 0, N) scanf("%s", Grid[i]);
		ans.init();
		// 遍历路径的起点
		_for(x,0,N) _for(y,0,M) findPath(Point(x,y), 0, 4, Point(x,y));
		printf("Case #%d:\n", t+1);
		printf("Combo:%d Length:%d\n%d %d\n%s\n", 
			ans.combo, ans.length, ans.start.x+1, ans.start.y+1, ans.solution);
	}

	return 0;
}
// 1887520	7036	Puzzle & Dragons	Accepted	C++11	14.522	2015-12-30 13:09:33