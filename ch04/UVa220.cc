// Othello, ACM/ICPC World Finals 1992, UVa220
// 陈锋
#include<cassert>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<set>
using namespace std;

// x in [left, right]
bool inRange(int x, int left, int right) {
    if(left > right) return inRange(x, right, left);
    return left <= x && x <= right;
}

struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) {}
};

ostream& operator<<(ostream& os, const Point& p) { return os<<'('<<p.x<<','<<p.y<<')'; }
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { 
    for(int i = 0; i < v.size(); i++) {
        if(i) os<<' ';
        os<<v[i];
    }
    return os;
}

typedef Point Vector;

Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator- (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator* (const Vector& A, int p) { return Vector(A.x*p, A.y*p); }
bool operator== (const Point& a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool operator< (const Point& p1, const Point& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }

const int N = 8, White = 'W', Black = 'B', Empty = '-';
Vector DIRS[N];
inline bool valid(const Point& p) { return inRange(p.x, 1, N) && inRange(p.y, 1, N); }

char Board[N+1][N+1], Player;

char playerChange(char c) {
    if(c == White) return Black;
    assert(c == Black);
    return White;
}

void print_board() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++)
            cout<<Board[i][j];
        cout<<endl;
    }
}

bool canMove(const Point& p, const Vector& dir) {
    Point pn = p + dir;
    char c, pc = playerChange(Player);
    int sz = 0;
    while(valid(pn)){ 
        c = Board[pn.x][pn.y];
        if(c == pc) {
            sz++; 
            pn = pn + dir;
        }
        else break;
    }
    if(!sz) return false;
    if(!valid(pn)) return false;
    return c == Player;
}

void move(const Point& p, const Vector& dv) {
    Board[p.x][p.y] = Player;
    Point pn = p + dv;    
    char pc = playerChange(Player);
    assert(Board[pn.x][pn.y] == pc);
    while(Board[pn.x][pn.y] == pc) {
        Board[pn.x][pn.y] = Player;
        pn = pn + dv;
    }
    assert(Board[pn.x][pn.y] == Player);
}

void move(int r, int c) {
    Point p(r, c);
    bool m = false;
    for(int d = 0; d < N; d++) {
        const Vector& dv = DIRS[d];
        if(canMove(p, dv)){
            m = true;
            move(p, dv);
        }        
    }
        
    Player = playerChange(Player);
    if(m)  return;
    
    for(int d = 0; d < N; d++) {
        const Vector& dv = DIRS[d];
        if(canMove(p, dv)) move(p, dv);
    }
    Player = playerChange(Player);    
}

void listAllMoves() {
    vector<Point> moves;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++)
        {
            Point p(i, j);
            if(Board[i][j] != Empty) continue;
            for(int d = 0; d < N; d++)
                if(canMove(p, DIRS[d])){
                    moves.push_back(p);
                    break;
                }
        }
    }
    
    if(moves.empty()) cout<<"No legal move."<<endl;
    else cout<<moves<<endl;
}

int main()
{     
    int T;
    cin>>T;
    DIRS[0].x = 1; DIRS[0].y = 0;
    DIRS[1].x = 1; DIRS[1].y = 1;
    DIRS[2].x = 0; DIRS[2].y = 1;
    DIRS[3].x = -1; DIRS[3].y = 1;
    DIRS[4].x = -1; DIRS[4].y = 0;
    DIRS[5].x = -1; DIRS[5].y = -1;
    DIRS[6].x = 0; DIRS[6].y = -1;
    DIRS[7].x = 1; DIRS[7].y = -1;
    
    bool first = true;
    while(T--) {
        if(first) first = false; else cout<<endl;
        string line;
        memset(Board, 0, sizeof(Board));
        for(int i = 1; i <= N; i++) {
            cin>>line;
            for(int j = 1; j <= N; j++)
                Board[i][j] = line[j-1];
        }
        cin>>Player;
        while(true) {
            cin>>line;
            if(line == "Q") {
                print_board();
                break;
            } 
            if(line == "L"){
                listAllMoves();
            }else{
                assert(line.size() == 3 && line[0] == 'M');
                move(line[1] - '0', line[2] - '0');
                int w = 0, b = 0;
                for(int i = 1; i <= N; i++) {
                    for(int j = 1; j <= N; j++) {
                        char c = Board[i][j];
                        if(c == White) w++;
                        else if(c == Black) b++;
                    }
                }
                cout<<"Black - "<<setw(2)<<b<<" White - "<<setw(2)<<w<<endl;
            }
        }
    }
    return 0;
}
/*13520046	220	Othello	Accepted	C++	0.009	2014-04-19 13:59:09*/