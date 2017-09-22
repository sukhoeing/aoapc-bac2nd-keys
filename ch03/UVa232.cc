// Crossword Answers, ACM/ICPC World Finals 1994, UVa232
// 陈锋
#include <cassert>
#include <cctype>
// #include <iostream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
};
typedef Point Vector;
Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
int R, C;
const int MAXC = 16;
char grid[MAXC][MAXC];

inline bool valid(const Point& p) { return p.x >= 0 && p.x < R && p.y >= 0 && p.y < C; }
int main(){    
    char buf[MAXC]; int bufLen;
    const Vector dLeft(0, -1), dUp(-1, 0), dRight(0, 1), dDown(1, 0);
    for(int t = 1; scanf("%d%d", &R, &C) == 2 && R; t++) {
        vector<Point> eligible;
        vector<int> down, across;
    
        if(t > 1) puts("");
        printf("puzzle #%d:\n", t);
        _for(i, 0, R){
            scanf("%s", grid[i]);
            _for(j, 0, C){
                if(grid[i][j] == '*') continue;
                Point p(i, j), left = p + dLeft, up = p + dUp;
                bool isCross = !valid(left) || grid[left.x][left.y] == '*';
                bool isDown = !valid(up) || grid[up.x][up.y] == '*';
                if(isCross) across.push_back(eligible.size());                
                if(isDown) down.push_back(eligible.size());
                if(isCross || isDown) eligible.push_back(p);
            }
        }
        
        puts("Across");
        for(auto n : across){
            bufLen = 0, memset(buf, 0, sizeof(buf));
            Point p = eligible[n];
            while(valid(p) && grid[p.x][p.y] != '*') {
                buf[bufLen++] = grid[p.x][p.y];
                p = p + dRight;
            }
            printf("%3d.%s\n", n+1, buf);
        }        
        puts("Down");
        for(auto n : down){
            bufLen = 0, memset(buf, 0, sizeof(buf));
            Point p = eligible[n];
            while(valid(p) && grid[p.x][p.y] != '*') {
                buf[bufLen++] = grid[p.x][p.y];
                p = p + dDown;
            }
            printf("%3d.%s\n", n+1, buf);
        }        
    }
    return 0;
}
// LiveArchive : 1440032	5171	Crossword Answers	Accepted	C++	0.138	2014-04-28 12:18:19
