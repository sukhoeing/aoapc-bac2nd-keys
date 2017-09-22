// "Accordian" Patience, UVa 127
// 陈锋
#include<cassert>
#include<iostream>
#include<cmath>
#include<functional>
#include<algorithm>
#include<cstring>
#include<stack>
using namespace std;

ostream& operator<<(ostream& oss, const vector<int>& s) {
    for(vector<int>::const_iterator p = s.begin(); p != s.end(); p++) 
        oss<<' '<<*p;
    return oss;
}

const int PileCnt = 52;
struct Card { 
    char suit, rank; 
    Card(char r, char s) :suit(s), rank(r) {}
    bool match(const Card& rhs) const { return rank == rhs.rank || suit == rhs.suit; }
};
struct Pile {
    stack<Card> cards;
    Pile *prev, *next;    
    void init(){
        while(!cards.empty()) cards.pop();
        prev = nullptr; next = nullptr; 
    }
};

Pile piles[1+PileCnt], *head;

void connect(Pile* p1, Pile* p2) { if(p1) p1->next = p2; if(p2) p2->prev = p1; }

Pile* getLeft3(Pile* p) { // 得到左数第三个牌堆
    for(int i = 0; i < 3; i++) {
        p = p->prev;
        if(p == nullptr) return nullptr;
    }
    return p;
}

void solve() {
    Pile *from, *to, *cur;
    while (true){
        from = nullptr, to = nullptr;
        cur = head->next;
        while(cur) {
            assert(!cur->cards.empty());
            Pile* l3 = getLeft3(cur);
            if(l3 != nullptr && l3 != head) {
                assert(!l3->cards.empty());
                if(l3->cards.top().match(cur->cards.top())) 
                { from = cur; to = l3; break; }
            }
            Pile* l1 = cur->prev;
            if(l1 != head) {
                assert(!l1->cards.empty());
                if(l1->cards.top().match(cur->cards.top())) 
                { from = cur; to = l1; break; }
            }
            cur = cur->next;
        }
        
        if(from) assert(to); else break;        
        to->cards.push(from->cards.top());
        from->cards.pop();
        if(from->cards.empty()) connect(from->prev, from->next);
    }
}

int main() {
    string s;
    bool end = false;
    head = &(piles[0]);
    head->init();
    head->next = &(piles[1]);
    
    while(true) {
        for(int i = 1; i <= PileCnt; i++) {            
            if(cin>>s && s.size() == 2) {
                Pile& p = piles[i];
                p.init();
                p.prev = &(piles[i-1]);
                if(i+1 <= PileCnt) p.next = &(piles[i+1]);
                p.cards.push(Card(s[0], s[1]));
            }
            else return 0;                
        }
        solve();
        Pile *cur = head->next;
        vector<int> ps;
        while(cur) { 
            assert(!cur->cards.empty());
            ps.push_back(cur->cards.size());
            cur=cur->next;
        }
        cout<<ps.size()<<" pile"<<(ps.size() > 1 ? "s":"")<<" remaining:"<<ps<<endl;
    }
    return 0;
}

// 14804487	127	"Accordian" Patience	Accepted	C++	0.646	2015-01-15 03:19:49