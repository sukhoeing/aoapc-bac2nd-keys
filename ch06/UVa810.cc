// A Dicey Problem, ACM/ICPC World Finals 1999, UVa810
// 陈锋
#include <cassert>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <set>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
int readint() { int x; cin >> x; return x; }
enum DIR{ UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };
const int MAXR = 12;
int R, C, M[MAXR][MAXR], dr[4] = { -1, 0, 1, 0 }, dc[4] = { 0, -1, 0, 1 };

template<typename T>
struct MemPool {
    vector<T*> buf;
    T* createNew() {
        buf.push_back(new T());
        return buf.back();
    }
    
    void dispose() {
        for(int i = 0; i < buf.size(); i++) delete buf[i];
        buf.clear();
    }
};

// [face,top] -> left
int DL[6][6] = {
	{ -1, 3, 5, 2, 4, -1 }, // 1
	{ 4, -1, 1, 6, -1, 3 }, // 2
	{ 2, 6, -1, -1, 1, 5 }, // 3
	{ 5, 1, -1, -1, 6, 2 }, // 4
	{ 3, -1, 6, 1, -1, 4 }, // 5
	{ -1, 4, 2, 5, 3, -1 } // 6
};

struct Stat {
	int r, c, face, top, back, bottom, left, right;
	Stat* prev;
	Stat() : prev(NULL) {}

	bool canMove(int dir);
	Stat* move(int dir);

	void init(int face, int top) {
		assert(face > 0 && face < 7);
		assert(top > 0 && top < 7);
		this->face = face;
		this->top = top;
		back = 7 - face;
		bottom = 7 - top;
		left = DL[face - 1][top - 1];
		assert(left > 0 && left < 7);
		right = 7 - left;
	}

	size_t hash() const {
		return 1000 * (r-1) + 100 * (c-1) + 10 * face + top;
	}
};
typedef Stat* PStat;
MemPool<Stat> pool;
struct PStatCmp {
	bool operator() (const PStat& lhs, const PStat& rhs) const {
		return lhs->hash() < rhs->hash();
	}
};

bool Stat::canMove(int dir) {
	assert(dir >= 0 && dir < 4);
	int nr = r + dr[dir], nc = c + dc[dir]; 
    if (nr < 1 || nr > R || nc < 1 || nc > C) return false;
    int m = M[nr][nc]; 
    if (m == 0) return false;
	return m == -1 || m == top;
}

PStat Stat::move(int d) {
	PStat ps = pool.createNew();
	ps->prev = this; ps->r = r + dr[d]; ps->c = c + dc[d];
	switch (d) {
	case UP:
		ps->init(bottom, face);
        assert(ps->left == left);
        assert(ps->right == right);
		break;
	case LEFT:
		ps->init(face, right);
        assert(ps->face == face);
		break;
	case DOWN:
		ps->init(top, back);
        assert(ps->left == left);
        assert(ps->right == right);
		break;
	case RIGHT:
		ps->init(face, left);
        assert(ps->face == face);
		break;
	default:
		assert(false);
	}

	return ps;
}

istream& operator>>(istream& is, Stat& s) {
	is >> s.r >> s.c >> s.top >> s.face;
	s.init(s.face, s.top);
	return is;
}

Stat* solve(const Stat& destS, PStat ps) {
	queue<PStat> q;
	set<PStat, PStatCmp> vis;
	q.push(ps); vis.insert(ps);
	while (!q.empty()) {
		PStat p = q.front(); q.pop();
		if (p->r == destS.r && p->c == destS.c) 
			return p;
		_for(d, 0, 4) {
			if (!p->canMove(d)) continue;
			PStat np = p->move(d);
			if (vis.count(np)) continue;
			vis.insert(np);
			q.push(np);
		}
	}
	return NULL;
}

int main()
{
	string name;
    deque<PStat> outQ;
    char buf[64];

	while (cin >> name && name != "END") {
		Stat s;
		cin >> R >> C >> s;
		_for(r, 1, R + 1) _for(c, 1, C + 1) cin >> M[r][c];
		cout << name << endl;
		Stat* ans = NULL;
		_for(i, 0, 4) {
			if (s.canMove(i)) {
				ans = solve(s, s.move(i));
				if (ans) break;
			}
		}
		if (ans) {
            outQ.clear(); 
            while(ans) { outQ.push_front(ans); ans = ans->prev; }
            _for(i, 0, outQ.size()) {
                if(i) {
                    cout<<",";
                    if(i%9 == 0) cout<<endl;
                }
                
                if(i%9 == 0) cout<<"  ";
                cout<<"("<<outQ[i]->r<<","<<outQ[i]->c<<")";
            }            
            cout<<endl;
        }
		else 
            cout << "  No Solution Possible" << endl;
		pool.dispose();
	}
	return 0;
}

// 1636401	LA5210	A Dicey Problem	Accepted	C++	0.039	2015-01-30 12:59:10