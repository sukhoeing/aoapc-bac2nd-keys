// UVa10384 The Wall Pushers
// 陈锋
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;

const int R = 4, C = 6;
const string DC = "WNES"; // 0 1 2 3
int DX[] = { 0, -1, 0, 1 }, DY[] = { -1, 0, 1, 0 }, REVD[] = { 2, 3, 0, 1 };
int readint() { int x; cin >> x; return x; }

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	for(const T& e : v) os<<e;
	return os;
}
// 位运算封装，读写x的第b位
bool get(int x, int b) { return (x & (1 << b)) > 0; }
void set(int& x, int b, bool v) {
	if (v) x |= (1 << b);
	else x &= ~(1 << b);
}
int Vis[R][C], cells[R][C];
bool IsValid(int x, int y) { return x >= 0 && x < R && y >= 0 && y < C; }
bool isExit(int x, int y, vector<char>& path) {
    int p = cells[x][y];
    if (x == 0 && !get(p, 1)) { path.push_back(DC[1]); return true; } // 第一行
    if (y == 0 && !get(p, 0)) { path.push_back(DC[0]); return true; }// 第一列
    if (x == R - 1 && !get(p, 3)) { path.push_back(DC[3]); return true; } // 最后一行
    if (y == C - 1 && !get(p, 2)) { path.push_back(DC[2]); return true; } // 最后一列
    return false;
}

// 坐标，路径，步数，最大搜索深度
bool dfs(int x, int y, vector<char>& path, int d, const int maxd) {
	assert(IsValid(x, y));
	if (isExit(x,y,path)) return true;
	if (d >= maxd) return false;
    int& p = cells[x][y];
	_for (i, 0, 4) {
		int ax = x + DX[i], ay = y + DY[i];
		if (!IsValid(ax, ay) || Vis[ax][ay]) continue;
		int& np = cells[ax][ay];
        
        path.push_back(DC[i]);
        Vis[ax][ay] = 1;
        
		if (!get(p, i)) { // 这个方向没有墙
			if (dfs(ax, ay, path, d + 1, maxd)) return true;
		}
		else if (!(get(np, i))){ // 有墙，但是可以推过去
			set(p, i, 0);  set(np, i, 1); set(np, REVD[i], 0);
			int aax = ax + DX[i], aay = ay + DY[i]; // 推过去之后下一个受影响的位置
			if (IsValid(aax, aay)) set(cells[aax][aay], REVD[i], 1);
			if (dfs(ax, ay, path, d + 1, maxd)) return true;
			if (IsValid(aax, aay)) set(cells[aax][aay], REVD[i], 0);
			set(p, i, 1); set(np, i, 0); set(np, REVD[i], 1);
		}
        
        Vis[ax][ay] = 0;
        path.pop_back();
	}

	return false;
}

int main()
{
	int sx, sy;
	vector<char> path;
	while ((sy = readint()) && (sx = readint())) {
		_for(i, 0, R) _for(j, 0, C) cin>>cells[i][j];
		sx--; sy--;
		int maxd = 1;
		while (true) {
			memset(Vis, 0, sizeof(Vis));
			path.clear();
			Vis[sx][sy] = 1;
			if (dfs(sx, sy, path, 0, maxd)) break;
			Vis[sx][sy] = 0;
			maxd++;
		}

		cout << path << endl;
	}

	return 0;
}

// 14412024	10384	The Wall Pushers	Accepted	C++	0.015	2014-10-24 06:06:57