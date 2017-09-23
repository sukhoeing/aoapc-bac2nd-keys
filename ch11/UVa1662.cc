// Brackets Removal, NEERC 2005, UVa1662
// 陈锋
#include <cassert>
#include <cctype>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
const int MAXN = 1024;

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

struct Node {
    char ch;
    Node *left, *right;
    bool enclose;
    int opLevel;
    void init(char c){ 
        left = right = NULL; ch = c; enclose = false; 
        opLevel = 0;
        if(ch == '*' || ch == '/') opLevel = 2;
        else if(ch == '+' || ch == '-') opLevel = 1;
    }
    const bool isOp() { return !islower(ch); }
};

string EX;
Node *pRoot;
MemPool<Node> nodePool;
Node* newNode(char c) {
    Node* ans = nodePool.createNew();
    ans->init(c);
    return ans;
}

ostream& operator<<(ostream& os, const Node* p) {
    if(!p) return os;
    if(p->enclose) os<<'(';
    os<<p->left<<p->ch<<p->right;
    if(p->enclose) os<<')';    
    return os;
}

void reverse(Node* p) {
    assert(p);
    assert(p->isOp());
    char c = p->ch;
    switch(c) {
        case '+' : p->ch = '-'; break;
        case '-' : p->ch = '+'; break;
        case '*' : p->ch = '/'; break;
        case '/' : p->ch = '*'; break;
        default:
            assert(false);
    }
    
    Node *pl = p->left, *pr = p->right;
    if(pl && pl->isOp() && pl->opLevel == p->opLevel) reverse(pl);
    if(pr && pr->isOp() && !pr->enclose && pr->opLevel == p->opLevel) reverse(pr);
}

void proc(Node* p) {
    // cout<<"proc "<<p<<endl;
    assert(p);
    if(!p->isOp()) return;
    Node *pl = p->left, *pr = p->right;
    if(pl && pl->isOp()){
        if(pl->opLevel >= p->opLevel) pl->enclose = false;  
        proc(pl);
    }
    
    if(pr && pr->isOp()) {
        if(pr->opLevel > p->opLevel) pr->enclose = false;
        else if(pr->opLevel == p->opLevel) {
            if((p->ch=='/' || p->ch == '-') && pr->enclose) {
                pr->enclose = false;
                reverse(pr);
            }
            pr->enclose = false;
        }
        proc(pr);
    }
}

Node* parse(int l, int r) {
    assert(l <= r);
    char lc = EX[l], rc = EX[r];
    if(l == r) return newNode(lc);

    int p = 0, c1 = -1, c2 = -1;
    _rep(i, l, r) {
        switch(EX[i]) {
            case '(' : p++; break;
            case ')' : p--; break;
            case '+' : case '-' : if(!p) c1 = i; break;
            case '*' : case '/' : if(!p) c2 = i; break;
        }
    }
    
    if(c1 < 0) c1 = c2;
    if(c1 < 0) {
        Node* ans = parse(l+1, r-1);
        ans->enclose = true;
        return ans;
    }
    
    Node *ans = newNode(EX[c1]), *ln = ans->left = parse(l, c1-1),
        *rn = ans->right = parse(c1+1, r);
    assert(ans->opLevel);
    if(!ln->isOp()) ln->enclose = false;
    if(!rn->isOp()) rn->enclose = false;
    return ans;
}

int main(){    
    while(cin>>EX) {
        nodePool.dispose();
        pRoot = parse(0, EX.size()-1);
        pRoot->enclose = false;
        proc(pRoot);
        cout<<pRoot<<endl;
    }
    return 0;
}

// 13761241	1662	Brackets Removal	Accepted	C++	0.029	2014-06-17 08:06:24