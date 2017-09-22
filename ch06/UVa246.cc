// 10-20-30, ACM/ICPC World Finals 1996, UVa246
// 陈锋
#include <cassert>
#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>
#include <list>
#include <set>
using namespace std;

#define _for(i,a,b) for( int i=(a); i<(b); ++i)
const int CN = 52;
int readint() { int x; cin>>x; return x; }

typedef deque<int> Pile;

Pile cards;
Pile allPiles[7];
list<Pile*> piles;
set<string> phases;

// 对整体状态进行编码
void encode(string& ans) {
    ans.clear();
    for(auto& pp : piles) {
        Pile& p = *pp;
        for(auto c : p) ans += (char)c;
        ans += '|';
    }
    for(auto c : cards) ans += (char)c;
}

// 10-20-30操作
void procPile(Pile& p) {
    int n = p.size();
    if(n < 3) return;
    if ((p[0] + p[1] + p.back()) % 10 == 0) {
        cards.push_back(p[0]), cards.push_back(p[1]), cards.push_back(p.back());
        p.pop_front(), p.pop_front(), p.pop_back();
        procPile(p);
        return;
    } 

    if ((p[0] + p[n-2] + p[n-1]) % 10 == 0) {
        cards.push_back(p[0]), cards.push_back(p[n-2]), cards.push_back(p[n-1]);
        p.pop_front(), p.pop_back(), p.pop_back();
        procPile(p);
        return;
    } 
    
    if ((p[n-3] + p[n-2] + p[n-1]) % 10 == 0) {
        cards.push_back(p[n-3]), cards.push_back(p[n-2]), cards.push_back(p[n-1]);
        p.pop_back(), p.pop_back(), p.pop_back();
        procPile(p);
        return;
    }
}

bool simulate(int time) {
    if(piles.empty()) {
        cout<<"Win : "<<time<<endl;
        return false;
    }
    
    if(cards.empty()) {
        cout<<"Loss: "<<time<<endl;
        return false;        
    }

    string pha;
    encode(pha);
    if(phases.count(pha)) {
        cout<<"Draw: "<<time<<endl;
        return false;
    }
    else phases.insert(pha);
    
    int c = cards.front();
    cards.pop_front();
    piles.push_back(piles.front());
    piles.pop_front();
    
    Pile& p = *(piles.back());
    p.push_back(c);
    procPile(p);
    if(p.empty()) piles.pop_back();
    
    return true;
}

int main()
{
    while(true) {
        cards.clear(), piles.clear(), phases.clear();
        _for(i, 0, CN) {
            int c = readint();
            if(c == 0) return 0;
            cards.push_back(c);
        }
        
        _for(i, 0, 7) { // 各个牌堆初始化
            Pile& p = allPiles[i];
            p.clear(), p.push_back(cards.front());
            cards.pop_front(), piles.push_back(&p);
        }
        
        int t = 7;
        while(true) if(!simulate(t++)) break;
    }
    return 0;
}

// 16758794	246	10-20-30	Accepted	C++11	0.016	2016-01-26 13:02:34