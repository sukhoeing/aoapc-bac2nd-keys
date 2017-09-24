// UVa10155 - Green Eggs and Ham
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
template<typename T>
struct MemPool {
    std::vector<T*> buf;
    T* createNew() {
        buf.push_back(new T());
        return buf.back();
    }
    
    void dispose() {
        for(int i = 0; i < buf.size(); i++) delete buf[i];
        buf.clear();
    }
};
using namespace std;
typedef vector<string> SVec;

struct Box {
	int LVC, w, h;
	SVec grid;

	void setGrid(int width, int height) {
		assert(width > 0); assert(height > 0);
		grid.clear();
		w = width, h = height;
		grid.resize(h);
		_for(i, 0, h) grid[i].resize(w, ' ');
	}

	void setGrid(bool neg, const string& op) { // 设置操作符
		h = 1, LVC = 0;
		grid.clear(), grid.push_back(op);
		if (neg) grid[0].insert(0, "-");
		w = grid[0].size();
	}

	void addGroup(bool group, bool neg){ // 加括号
		_for(i, 0, h) {
			string& l = grid[i];
			if (neg) {
				if (i == LVC) l.insert(0, "-");
				else l.insert(0, " ");
			}
			if (group) {
				l.insert(0, "(");
				l.push_back(')');
			}
		}
		if (group) w += 2;
		if (neg) w += 1;
	}

	void copyTo(Box& b, int r, int c) {
		_for(i, 0, h) _for(j, 0, w) {
			assert(i + r < b.h); assert(j + c < b.w);
			b.grid[r+i][c+j] = grid[i][j];
		}
	}
};

ostream& operator<<(ostream& os, Box* p) {
	_for(i, 0, p->h) {
		assert(p->w == p->grid[i].size());
		os<<p->grid[i]<<endl;
	}
	return os;
}

struct Node {
	string op;
	bool inGroup, neg;
	Node *left, *right;
	Node() : inGroup(false), neg(false), left(NULL), right(NULL) { }
};

MemPool<Node> nodesPool;
MemPool<Box> boxPool;
map<string, int> ops{{"=",0},{"+",1},{"-",1},{"*",2},{"/",2},{"^", 3}}; // 运算符优先级
void tokenize(const string& s, SVec& ts) { // 词法分析
	string buf; ts.clear();
	for(auto c : s){
		if (isdigit(c) || c == '.') { buf += c; continue; }
		if (!buf.empty()) ts.push_back(buf);
		buf.clear();
		ts.push_back(string(1, c));
	}
	if (!buf.empty()) ts.push_back(buf);
}

bool isOp(const string& t) {
	assert(!t.empty());
	return !(t[0] == '.' || isalnum(t[0]));
}

Node* buildExpTree(const SVec& ts, int l, int r) {
	Node* p = nodesPool.createNew();
	assert(l <= r);
	if (l == r) {
		assert(ts[l][0] == '.' || isalnum(ts[l][0])); p->op = ts[l];
	}
	else if (l + 1 == r) {
		assert(ts[l] == "-"); p->op = ts[l + 1]; p->neg = true;
	}
	else {
		int i0 = -1, i1 = -1, i2 = -1, i3 = -1, dep = 0;
		string lt = "_";
		_for(i, l, r + 1) {
			const string& t = ts[i];
			if (t == "{" || t == "(") dep++;
			else if (t == "}" || t == ")") dep--;
			if (dep) continue;
			if (t == "=") i0 = i;
			else if (t == "+") i1 = i;
			else if (t == "-") { if (!isOp(lt)) i1 = i; }
			else if (t == "*" || t == "/") i2 = i;
			else if (t == "^") { if (i3 == -1) i3 = i; }
			lt = t;
		}

		if (i0 >= 0) {
			p->op = ts[i0]; 
			p->left = buildExpTree(ts, l, i0 - 1); 
			p->right = buildExpTree(ts, i0 + 1, r);
		}
		else if (i1 >= 0) {
			p->op = ts[i1]; 
			p->left = buildExpTree(ts, l, i1 - 1); 
			p->right = buildExpTree(ts, i1 + 1, r);
		}
		else if (i2 >= 0) {
			p->op = ts[i2]; 
			p->left = buildExpTree(ts, l, i2 - 1); 
			p->right = buildExpTree(ts, i2 + 1, r);
		}
		else if (i3 >= 0) {
			p->op = ts[i3]; 
			p->left = buildExpTree(ts, l, i3 - 1); 
			p->right = buildExpTree(ts, i3 + 1, r);
		}
		else if (ts[l] == "-"){
			p = buildExpTree(ts, l + 1, r);
			p->neg = true;
		}
		else {
			assert(ts[l] == "{" || ts[l] == "(");
			p->inGroup = (ts[l] == "(");
			p->left = buildExpTree(ts, l + 1, r - 1);
		}
	}
	return p;
}

Box* getBox(Node* p){
	assert(p);
	const string& o = p->op;
	Box* b = boxPool.createNew();
	if (o.empty()) { // 在括号里面
		assert(p->left); assert(!(p->right));
		b = getBox(p->left), b->addGroup(p->inGroup, p->neg);
	}
	else if (!isOp(o)) {
		b->setGrid(p->neg, o);
	}
	else {
		Box *lb = getBox(p->left), *rb = getBox(p->right);
		if (o == "/") {
			b->setGrid(max(lb->w, rb->w), lb->h + rb->h + 1);
			b->LVC = lb->h;
			int ls = b->w - lb->w; ls = ls / 2 + ls % 2; lb->copyTo(*b, 0, ls); // 分子
			int rs = b->w - rb->w; rs = rs / 2 + rs % 2; rb->copyTo(*b, b->LVC + 1, rs); // 分母
			b->grid[b->LVC].assign(b->w, '-');
		}
		else if (o == "^") {
			b->setGrid(lb->w + rb->w, lb->h + rb->h); b->LVC = lb->LVC + rb->h;
			lb->copyTo(*b, rb->h, 0); rb->copyTo(*b, 0, lb->w);
		}
		else {
			assert(ops.count(o));
			int lvc = max(lb->LVC, rb->LVC), h = lvc + max(lb->h - lb->LVC, rb->h - rb->LVC);
			b->setGrid(lb->w + rb->w + 3, h), b->LVC = lvc;
			lb->copyTo(*b, lvc - lb->LVC, 0), rb->copyTo(*b, lvc - rb->LVC, lb->w + 3);
			b->grid[b->LVC][lb->w + 1] = o[0];
		}
	}

	return b;
}

int main() {
	string line;
	SVec tokens;
    bool first = true;
	while (cin>>line) {
        if(first) first = false; else cout<<endl;        
		tokenize(line, tokens);
		Node* root = buildExpTree(tokens, 0, tokens.size() - 1);
		Box* bp = getBox(root);
		cout<<bp;
		nodesPool.dispose(), boxPool.dispose();
	}
	return 0;
}
// 14747927	10155	Green Eggs and Ham	Accepted	C++	0.016	2015-01-01 02:38:13