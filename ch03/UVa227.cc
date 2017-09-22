// Puzzle, ACM/ICPC World Finals 1993, UVa227
// 陈锋
#include <cassert>
#include <cctype>
#include <iostream>
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
Vector operator- (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator* (const Vector& A, int p) { return Vector(A.x*p, A.y*p); }
Vector operator/ (const Vector& A, int p) { return Vector(A.x/p, A.y/p); }
bool operator== (const Point& a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool operator< (const Point& p1, const Point& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }

const int GSize = 5;
vector<string> grid;
Point ePos;
map<char, Vector> DIRS = {{'A', Vector(-1, 0)},{'B', Vector(1, 0)},{'L', Vector(0, -1)},{'R', Vector(0, 1)},};
bool valid(const Point& p) { return p.x >= 0 && p.x < GSize && p.y >= 0 && p.y < GSize; }

void printGrid() {         
    _for(i, 0, GSize) {
        _for(j, 0, GSize) {
            if(j) cout<<' ';
            cout<<grid[i][j];
        }
        cout<<endl;
    }
}

bool tryMove(char cmd) {
    // cout<<"move "<<cmd<<":"<<endl;
    if(!DIRS.count(cmd)) return false;
    assert(DIRS.count(cmd));
    Point p = ePos + DIRS[cmd];
    if(!valid(p)) return false;
    swap(grid[p.x][p.y], grid[ePos.x][ePos.y]);
    ePos = p;    
    // printGrid();    
    return true;
}

int main(){    
    int t = 1;
    string line;
    while(true) {
        grid.clear();
        ePos.x = -1; ePos.y = -1;
        _for(i, 0, GSize){
            getline(cin, line);
            if(line == "Z") return 0;
            assert(line.size() == GSize);
            _for(j, 0, GSize){
                if(line[j] != ' ') continue;
                assert(ePos.x == -1 && ePos.y == -1); 
                ePos.x = i;
                ePos.y = j;
            }
            grid.push_back(line);
        }
        string moves;
        while(true) {
            getline(cin, line);
            assert(!line.empty());
            bool end = *(line.rbegin()) == '0';
            if(!end) moves.append(line);
            else moves.append(line, 0, line.size() - 1);
            if(end) break;
        }
        bool legal = true;
        for(const auto& m : moves) if(!tryMove(m)) { legal = false; break; }

        if(t > 1) cout<<endl;
        cout<<"Puzzle #"<<t++<<":"<<endl;
        if(legal) printGrid();
        else cout<<"This puzzle has no final configuration."<<endl;
    }
    return 0;
}
/* Live Archive 1439888	5166	Puzzle	Accepted	C++	0.109	2014-04-28 02:22:05 */