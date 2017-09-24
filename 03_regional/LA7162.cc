// LA7162 Window Manager
// 陈锋 C++ 11
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
bool inRange(int x, int l, int r) { return  x >= l && x < r; }
bool intersect(int l1, int r1, int l2, int r2) { // [l1, r1) 和 [l2, r2)两个区间是否有公共点？
    assert(l1 < r1 && l2 < r2);
    return inRange(l1, l2, r2) || inRange(l2, l1, r1) || inRange(r1 - 1, l2, r2) || inRange(r2 - 1, l1, r1);
}

int XMAX, YMAX, cmdIdx, winIdx;
inline bool outOfBound(int px, int py) { 
    return !inRange(px, 0, XMAX) || !inRange(py, 0, YMAX); 
}
struct Window;
typedef vector<Window> VW;
typedef VW::iterator VWI;
struct Window {
    int x, y, w, h, idx, maxMove;
    Window(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
    bool containsPt(int px, int py) const { 
        return inRange(px, x, x + w) && inRange(py, y, y + h); 
    }
    bool overlap(const Window& w2) const { 
        return intersect(x, x + w, w2.x, w2.x + w2.w) && intersect(y, y + h, w2.y, w2.y + w2.h); 
    }
    bool outOfBound() const { 
        return ::outOfBound(x, y) || ::outOfBound(x, y + h - 1) 
        || ::outOfBound(x + w - 1, y) || ::outOfBound(x + w - 1, y + h - 1); 
    }
    bool VCross(int yl, int yr) { return intersect(yl, yr, y, y + h); } // [yl, yr)这个垂直区间和w所在的垂直区间有公共点吗？
    vector<VWI> crossWins;        
};

struct Command{
    string cmdText;
    int x, y, dx, dy, idx;
    Command(const string str, int _x, int _y, int _dx, int _dy) :
        cmdText(str), x(_x), y(_y), dx(_dx), dy(_dy), idx(cmdIdx++) {}
};

vector<Command> cmds;
VW wins;
void rotate90(int& px, int& py) { // 将整个图形旋转90度之后，px, py的新坐标是什么?
    int ny = px, nx = YMAX - py - 1; px = nx, py = ny;
}
void rotate90() { // 把整个图形旋转90
    for (auto& w : wins) {
        int nx = w.x, ny = w.y+w.h-1;
        rotate90(nx, ny);
        swap(w.w, w.h); w.x = nx, w.y = ny;
    }
    swap(XMAX, YMAX);
}

void init() { cmdIdx = 1; winIdx = 0; cmds.clear(); wins.clear(); }

VWI findWindow(int px, int py) {
    for(auto p = wins.begin(); p != wins.end(); p++)
        if (p->containsPt(px, py)) return p;
    return wins.end();
}

VWI findWindow(const Command& cmd, ostream& os){
    VWI pw = findWindow(cmd.x, cmd.y);
    if (pw == wins.end())
        os<<"Command "<<cmd.idx<<": " 
            <<cmd.cmdText<<" - no window at given position"<<endl;
    return pw;
}

bool windowFit(const Window& nw, int existWinIdx = -1) {
    return !nw.outOfBound() 
        && all_of(wins.begin(), wins.end(), [nw, existWinIdx](const Window & w) 
            { return w.idx == existWinIdx || !w.overlap(nw); });
}

void openWindow(const Command& cmd, ostream& errOs) {
    Window nw(cmd.x, cmd.y, cmd.dx, cmd.dy);
    if (!windowFit(nw)) {
        errOs<<"Command "<<cmd.idx<<": "<<cmd.cmdText<<" - window does not fit"<<endl;
        return;
    }
    nw.idx = winIdx++;
    wins.push_back(nw);
}
void resizeWindow(const Command& cmd, ostream& errOs) {
    VWI pw = findWindow(cmd, errOs);
    if (pw == wins.end()) return;
    Window nw(pw->x, pw->y, cmd.dx, cmd.dy);
    if (!windowFit(nw, pw->idx)) {
        errOs<<"Command "<<cmd.idx<<": "<<cmd.cmdText<<" - window does not fit"<<endl;
        return;
    }
    pw->w = cmd.dx, pw->h = cmd.dy;
}
void closeWindow(const Command& cmd, ostream& errOs) {
    VWI pw = findWindow(cmd, errOs);
    if (pw == wins.end()) return;
    wins.erase(pw);
}
void moveRight(VWI p, int dist) {
    for(auto p2 : p->crossWins){
        int p2d = p2->x - (p->x + p->w);
        assert(p2d >= 0);
        assert(p->VCross(p2->y, p2->y+p2->h));
        if(p2d < dist) moveRight(p2, dist-p2d);
    }
    p->x += dist;
}

void moveRight(const Command& cmd, ostream& os) {
    for(auto& w : wins) w.maxMove = 0, w.crossWins.clear();
    sort(wins.begin(), wins.end(), [](const Window & w1, const Window & w2)
        { return w1.x < w2.x || (w1.x == w2.x && w1.y < w2.y); });
    VWI pw = findWindow(cmd.x, cmd.y);
    assert(pw != wins.end());
    assert(cmd.dx > 0 && cmd.dy == 0);
    for (auto p = wins.end() - 1; p >= pw; p--){
        int move = XMAX - (p->x + p->w);
        for (auto p2 = p + 1; p2 < wins.end(); p2++) {
            int p2d = p2->x - (p->x + p->w);
            if (p2d >= 0 && p->VCross(p2->y, p2->y + p2->h)){
                move = min(move, p2d + p2->maxMove);
                p->crossWins.push_back(p2);
            }
        }
        p->maxMove = move;
    }
    int d = min(pw->maxMove, cmd.dx);
    moveRight(pw, d);
    if (d != cmd.dx)
        os<<"Command "<<cmd.idx<<": "<<cmd.cmdText<<" - moved "
            <<d<<" instead of "<<cmd.dx<<endl;
}

void moveWindow(const Command& cmd, ostream& os) {
    if (findWindow(cmd, os) == wins.end()) return;
    assert(cmd.dx == 0 || cmd.dy == 0);
    Command ncmd = cmd;
    int r = 0;
    if (cmd.dy == 0) {
        assert(cmd.dx);
        if (cmd.dx < 0) // 向左移动
            ncmd.dx = -cmd.dx, r = 2; // 右转180度
    } else {
        if (cmd.dy > 0) // 向下移动
            ncmd.dx = cmd.dy, ncmd.dy = 0, r = 3; // 右转270度
        else // 向上移动
            ncmd.dx = -cmd.dy, ncmd.dy = 0, r = 1; // 右转90度
    }

    _for(i, 0, r) rotate90(ncmd.x, ncmd.y), rotate90();
    moveRight(ncmd, os);
    _for(i, 0, (4 - r) % 4) rotate90();
}

void solve() {
    for (const auto& c : cmds) {
        if (c.cmdText == "OPEN") openWindow(c, cout);
        else if (c.cmdText == "CLOSE") closeWindow(c, cout);
        else if (c.cmdText == "RESIZE") resizeWindow(c, cout);
        else if (c.cmdText == "MOVE") moveWindow(c, cout);
    }
    cout << wins.size() << " window(s):" << endl;
    sort(wins.begin(), wins.end(),
        [](const Window & w1, const Window & w2){ return w1.idx < w2.idx; });
    for(const auto& w : wins) cout<<w.x<<" "<<w.y<<" "<<w.w<<" "<<w.h<<endl;
}

int main() {
    string line, buf;
    bool first = true;
    while (true) {
        if (!getline(cin, line)) { solve(); break; }
        stringstream ss(line);
        if (isdigit(line[0])) {
            if (first) first = false; else solve();
            ss>>XMAX>>YMAX;
            init();
        }
        else {
            int x, y, w, h;
            ss>>buf>>x>>y; if (buf != "CLOSE") ss>>w>>h;
            cmds.push_back(Command(buf, x, y, w, h));
        }
    }
    return 0;
}
// 1882578  7162    Window Manager  Accepted    C++11   0.122   2015-12-16 10:02:39