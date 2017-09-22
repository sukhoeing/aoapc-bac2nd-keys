// The Domino Effect, ACM/ICPC World Finals 1991, UVa211
// 陈锋
#include<cassert>
#include<cstdio>
#include<cmath>
#include<functional>
#include<algorithm>
#include<sstream>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;

int readint() { int x; scanf("%d", &x); return x;}
// x in [left, right]
bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return left <= x && x <= right;
}
struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
};
typedef Point Bone;

const int ROW = 7, COL = 8, BoneCnt = 28;
int Grid[ROW][COL], Result[ROW][COL];
int boneIndice[ROW][ROW]; // 牌面为(x,y)的骨牌编号
Bone bones[BoneCnt];

// 跳到下一个格子，到行尾换行，走到最后一格就返回false
bool gotoNextCell(Point& pos){
    int r = pos.x, c = pos.y;    
    assert(inRange(r, 0, ROW-1));
    assert(inRange(c, 0, COL-1));
    c++;
    r += c / COL;
    c %= COL;
    if(r >= ROW) return false;
    pos.x = r; pos.y = c;
    return true;
} 

void initBones() { // 记录所有的骨牌及其编号
    int cur = 0;
    memset(boneIndice, -1, sizeof(boneIndice));    
    _for(i, 0, ROW) {
        _for(j, i, ROW) {
            Bone& b = bones[cur];
            b.x = i; b.y = j;
            boneIndice[i][j] = boneIndice[j][i] = cur++;
        }
    }
}

int isBone(int p1, int p2) { // 找到面值可能为(p1, p2)或者(p2, p2)的骨牌编号
    // if(p1 > p2) return findBone(p2, p1);
    return boneIndice[p1][p2] != -1;
}

// int findBone(int p1, int p2) { // 找到面值可能为(p1, p2)或者(p2, p2)的骨牌编号
    // if(p1 > p2) return findBone(p2, p1);
    // return boneIndice[p1][p2];
// }

// 决策到pos这个格子，已经使用的骨牌再usedBones中，已经找到ansCnt个答案
void solve(const Point& pos, set<int> usedBones, int& ansCnt) {
    if(usedBones.size() == BoneCnt) {
        ansCnt++;
        _for(i, 0, ROW) {
            printf(" ");
            _for(j, 0, COL) printf("%4d", Result[i][j]+1);
            printf("\n");
        }
        printf("\n");
        return;
    }
    
    int r = pos.x, c = pos.y;    
    assert(inRange(r, 0, ROW-1)); assert(inRange(c, 0, COL-1));
    
    Point np = pos;
    if(Result[r][c] != -1) { // 这个格子已经其它决策过的棋子占用了
        if(gotoNextCell(np)) solve(np, usedBones, ansCnt);
        return;
    }
    
    np = pos; 
    if(!gotoNextCell(np)) return; // 走到下一个格子
    
    // 水平放骨牌
    if(c+1 < COL && Result[r][c+1] == -1) {
        int b = findBone(Grid[r][c], Grid[r][c+1]);
        if(b != -1 && !usedBones.count(b)) {
            np = pos;
            usedBones.insert(b);
            Result[r][c] = Result[r][c+1] = b;
            assert(gotoNextCell(np));
            
            solve(np, usedBones, ansCnt);
            
            usedBones.erase(b);
            Result[r][c] = Result[r][c+1] = -1;
        }
    }
    
    // 垂直放骨牌
    if(r+1 < ROW) {
        assert(Result[r+1][c] == -1);
        int b = findBone(Grid[r][c], Grid[r+1][c]);
        if(b != -1 && !usedBones.count(b)) {
            np = pos;
            usedBones.insert(b);
            Result[r][c] = Result[r+1][c] = b;
            assert(gotoNextCell(np));
            
            solve(np, usedBones, ansCnt);
            
            usedBones.erase(b);
            Result[r][c] = Result[r+1][c] = -1;
        }
    }
}

int main()
{       
    initBones();
    int t = 1;
    while(true) {
        Point pos;
        if(scanf("%d", &(Grid[pos.x][pos.y])) != 1) break;
        while(gotoNextCell(pos)) Grid[pos.x][pos.y] = readint();
        
        if(t > 1) printf("\n\n\n");
        printf("Layout #%d:\n\n", t);
        _for(i, 0, ROW){
            _for(j, 0, COL) printf("%4d", Grid[i][j]);
            printf("\n");
        }
        printf("\nMaps resulting from layout #%d are:\n\n", t);
        
        int ansCnt = 0;
        memset(Result, -1, sizeof(Result));
        set<int> usedBones;
        solve(Point(), usedBones, ansCnt);
        printf("There are %d solution(s) for layout #%d.\n", ansCnt, t++);
    }
    return 0;
}
//14804534	211	The Domino Effect	Accepted	C++	0.556	2015-01-15 03:34:53