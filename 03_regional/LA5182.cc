// Theseus and the Minotaur (II) World Finals1995 Nashville, UVa243
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <sstream>
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
const int MAXN = 32;

struct Node{ // 洞穴
	bool candle, TVis[MAXN], MVis[MAXN]; // T点蜡烛, T和M给隧道加的标记
	vector<int> adjs; // 邻居洞穴的编号
	int id, lastMTarget; // M来过之后，最后去哪个洞穴
	Node() : candle(false), lastMTarget(-1) {
		fill_n(TVis, MAXN, false);
		fill_n(MVis, MAXN, false);
	}
};

struct State {
	int from, to;
	State(int f, int t) : from(f), to(t) {}
};
vector<Node> nodes;
char name(int node) { return node + 'A'; }

int findNext(Node* pN, int from, bool clockWise) {
	int SZ = pN->adjs.size(), x = -1;
	_for(i, 0, SZ)
		if (pN->adjs[i] == from) { x = i; break; }
	assert(x >= 0);

	int step = (clockWise ? -1 : 1);
	for (int i = (x + step + SZ) % SZ, cnt = 0; cnt < SZ; 
		i = (i + step + SZ) % SZ, cnt++) {
		int a = pN->adjs[i];
		if (clockWise) {
			if (!pN->MVis[a]) return a;
		}
		else {
			if (!pN->TVis[a]) return a;
		}
	}

	printf("from %c in %c, clock : %d\n", name(from), name(pN->id), clockWise);
	assert(false);
}

bool inSameEdge(const State& s1, const State& s2) {
	return (s1.from == s2.from && s1.to == s2.to) || (s1.from == s2.to && s1.to == s2.from);
}

bool Step(State& TS, State& MS) {
    Node* pM = &(nodes[MS.to]); // M进洞
    if(pM->candle) { // 有蜡烛
        pM = &nodes[MS.from]; // 掉头回之前的洞
        swap(MS.from, MS.to); // 掉头
    }
    Node* pT = &(nodes[TS.to]); // T进洞了
    if (pM == pT) { // 发现M，杀掉
		cout << "The Minotaur is slain in " << name(pM->id) << endl;
		return true;
	} else if(pT->lastMTarget >= 0) { // 发现M的踪迹，点蜡烛
        pT->candle = true;        
    }
    
    // T要进隧道了，洞中有M的踪迹，就跟去，否则逆时针找下一个出口
    TS.to = pT->lastMTarget >= 0 ? pT->lastMTarget : findNext(pT, TS.from, false);
    TS.from = pT->id;
    pT->TVis[TS.to] = true;
        
    MS.to = findNext(pM, MS.from, true); // 洞中顺时针找下一个出口
    MS.from = pM->id;    
	if (inSameEdge(TS, MS)) { // 隧道相遇 M杀T
		cout << "Theseus is killed between " << name(TS.from) << " and " << name(TS.to) << endl;
		return true;
	}
    pM->MVis[MS.to] = true;
    pM->lastMTarget = MS.to; // 记住洞中M走的最后一个出口
    
	return false;
}

int main(){
	string L;
	while (true) {
		nodes.clear(); nodes.resize(MAXN);
		while (true) {
			cin >> L;
			char c = L[0];
			if (c == '#') return 0;
			if (c == '@') {
				State TS(L[1]-'A', L[2]-'A'), MS(L[3]-'A', L[4]-'A');
				if (inSameEdge(TS, MS))
					cout << "Theseus is killed between "<<L[1]<<" and "<<L[2]<<endl;
				else {
					while (true) if (Step(TS, MS)) break;
				}
				break;
			}
			else {
				Node& n = nodes[c - 'A']; n.id = c - 'A';
				_for(i, 2, L.size()) n.adjs.push_back(L[i] - 'A');
			}
		}
	}
	return 0;
}

// 14701423	243	Theseus and the Minotaur (II)	Accepted	C++	0.489	2014-12-20 06:34:58