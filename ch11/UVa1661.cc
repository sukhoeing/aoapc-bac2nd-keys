// UVa1661, ACM/ICPC NEERC 2007
// 陈锋
#include <cassert>
#include <cctype>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;
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

typedef long long int64;
int64 gcd(int64 a, int64 b) { return b==0 ? a : gcd(b, a%b); }
bool isNum(char t) { return t == 'X' || isdigit(t); }
struct Rational{
    Rational(int64 me=1,int64 de=1) {
        // cout<<"me = "<<me<<", de = "<<de<<endl;
        assert(de);
        this->de = de;
        this->me = me;
        reduce();
    }
	void reduce()
    {
        assert(de);
        if(me == 0) { de = 1; return; }
        if(de < 0) { de = -de; me = -me; };
        int64 g = gcd(me < 0 ? -me : me, de);
        me /= g;
        de /= g;
    }  
	
	friend ostream& operator<<(ostream& output, Rational& a);
	Rational operator+(Rational& A) { return Rational(me*A.de + A.me*de, de*A.de); }
	Rational operator-(Rational& A) { return Rational(me*A.de - A.me*de, de*A.de); }
    Rational operator*(Rational& A) { return Rational(me*A.me, de*A.de); }
    Rational operator/(Rational& A) { if(A.me == 0) return Rational(0); return Rational(me*A.de, de*A.me); }
	Rational operator-(){ return Rational(-me, de); }
    bool operator==(int x) { return (*this)==Rational(x); }
    bool operator!=(int x) { return !(*this==x); }
	bool operator<(const Rational& A) { return me*A.de < de*A.me; }
    Rational& operator=(const Rational& A){ me = A.me; de = A.de; return *this; }
    bool operator==(const Rational& A) { return de*A.me == me*A.de; }
    bool operator!=(const Rational& A) { return !(*this==A); }
 
    long long de, me; // 分母(denominator)，分子(member)
};

ostream& operator<<(ostream& os, Rational& a) { return os<<a.me<<'/'<<a.de; }

struct Node{
    Node *left, *right;
    char token;
    bool unknown;
    Rational value;
    void init() { left = right = NULL; unknown = true; }
    
    friend ostream& operator<<(ostream& os, Node*p);
    
    bool eval() {
        if(token == 'X') return unknown = true;
        if(isNum(token)) {
            unknown = false;
            assert('0' <= token && token <= '9');
            value = (int)(token - '0');
            this->left = NULL;
            this->right = NULL;
            return false;
        }
        
        assert(this->left);
        assert(this->right);
        left->eval(); 
        right->eval();
        unknown = left->unknown || right->unknown;        
        
        if(unknown) return true;
        
        switch(token) {
            case '+':
                value = (left->value + right->value);
                break;
            case '-':
                value = (left->value - right->value);
                break;
            case '*':
                value = (left->value * right->value);
                break;
            case '/':
                value = (left->value / right->value);
                break;            
        }
        left = NULL, right = NULL;
        return false;
    }
};

ostream& operator<<(ostream& os, Node *p){    
    if(!p) return os;
    
    bool isOp = !(isNum(p->token));
    if(isOp) os<<" (";
    os<<(p->left);
    if(p->unknown) os<<p->token;
    else os<<' '<<(p->value);
    os<<(p->right);  
    if(isOp) os<<") ";
    return os;
}

MemPool<Node> pool;

Node* newNode(char t) {
    Node *p = pool.createNew();
    p->init();
    p->token = t;
    return p;
}

Node* parse(const string& exp, int& end) {
    if(!end) return NULL;
    Node* p = newNode(exp[--end]);
    if(isNum(p->token)) return p;
    p->right = parse(exp, end);
    p->left = parse(exp, end);
    return p;
}

void solve(Node* p, Rational rv, bool& none, bool& multiple, Rational& result) {
    // cout<<"solve "<<p<<" = "<<rv<<endl;
    if(!(p->unknown)) {
        if(p->value == rv) multiple = true;
        else none = true;
        return;
    }
    
    char t = p->token;
    if(t == 'X') { result = rv; return; }    
    assert(!isNum(t));
    
    // cout<<"solve --"<<p<<endl;
    Node *pl = p->left, *pr = p->right;
    assert(pl); assert(pr);
    Rational& plv = pl->value, prv = pr->value;
    // cout<<"left = "<<pl<<" right = "<<pr<<endl;
    
    if(pl->unknown) {
        assert(!(pr->unknown));
        switch(t) {
            case '+':
                solve(pl, rv-prv, none, multiple, result);
                break;
            case '-':
                solve(pl, rv+prv, none, multiple, result);
                break;
            case '*':
                if(rv == 0) 
                {
                    if(prv != 0) solve(pl, rv, none, multiple, result);
                    else { multiple = true; return; }
                }
                else
                {
                    if(prv == 0) { none = true; return; }
                    solve(pl, rv/prv, none, multiple, result);
                }
                break;
            case '/':
                assert(prv != 0);
                if(rv == 0) solve(pl, 0, none, multiple, result);
                else solve(pl, rv*prv, none, multiple, result);
                break;
            default:
                assert(false);
        }
        return;
    }
    
    assert(pr->unknown);
    switch(t) {
        case '+':
            solve(pr, rv-plv, none, multiple, result);
            break;
        case '-':
            solve(pr, plv-rv, none, multiple, result);
            break;
        case '*':
            if(rv == 0)
            {
                if(plv == 0) { multiple = true; return; }
                else solve(pr, 0, none, multiple, result);                
            }
            else
            {
                if(plv == 0) { none = true; return; }
                else solve(pr, rv/plv, none, multiple, result);
            }
            break;
        case '/':
            if(rv == 0)
            {
                if(plv == 0) { multiple = true; return; }
                else { none = true; return; }
            }
            else 
            {
                if(plv == 0) { none = true; return;}
                else solve(pr, plv/rv, none, multiple, result);
            }
            break;
        default:
            break;
    }
}

int main(){
    string line, tokens;
    while(getline(cin, line)) {
        tokens.clear();
        pool.dispose();
        istringstream iss(line, istringstream::in);
        char t;
        while(iss>>t) tokens.push_back(t);
        
        int end = tokens.size();
        Node* root = parse(tokens, end);
        root->eval();
        
        bool none = false, multiple = false;
        Rational result;
        solve(root, 0, none, multiple, result);
        if(none) cout<<"NONE"<<endl;
        else if(multiple) cout<<"MULTIPLE"<<endl;
        else cout<<"X = "<<result<<endl;
    }
    return 0;
}
// 14805859	1661	Equation	Accepted	C++	0.019	2015-01-15 10:14:27