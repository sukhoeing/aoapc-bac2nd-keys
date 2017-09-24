// UVa12415 - Digit Patterns
// 陈锋
#include <cassert>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <bitset>
#include <unordered_map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

typedef unsigned long long LL;
typedef std::vector<int> VI, *PVI;
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    bool first = true;
    for(const auto& e : v){
        if(first) first = false; else os <<" ";
        os<<e;
    }
    return os;
}
    
struct ExpNode{
    enum {A, STAR, OR, CONCAT};
    int type, val;
    ExpNode *l, *r;
    ExpNode(int type, ExpNode *l = nullptr, ExpNode *r = nullptr, int val = -1) 
        : type(type), l(l), r(r), val(val) {};
    ~ExpNode() {
        if(l) delete l;
        if(r) delete r;
    }
};

ostream& operator<<(ostream& os, ExpNode *pn) {
    if(!pn) return os;
    switch(pn->type) {
        case ExpNode::A:
            os<<(char)(pn->val);        
            break;
        case ExpNode::STAR:
            os<<"("<<pn->l<<")*";
            break;
        case ExpNode::OR:
            os<<'('<<pn->l<<')'<<'+'<<'('<<pn->r<<')';
            break;
        case ExpNode::CONCAT:
            os<<pn->l<<pn->r;
            break;
        default:
            assert(false);
    }
    
    return os;
}

struct RexParser{
    string rex;
    int p, n;
    void skip(char c) { p++; } // for debug purpose
    ExpNode *item() { // (u)* || u closure
        ExpNode *u;
        if(rex[p] == '(') 
            skip(rex[p]), u = expr(), skip(')');
        else 
            u = new ExpNode(ExpNode::A, nullptr, nullptr, rex[p++]);
        while(rex[p] == '*')
            skip(rex[p]), u = new ExpNode(ExpNode::STAR, u, nullptr);
        return u;
    }
    
    ExpNode *concat() { // u1u2u3...  concatenation
        ExpNode *u = item();
        while(p < n && rex[p] != ')' && rex[p] != '+')
            u = new ExpNode(ExpNode::CONCAT, u, item());
        return u;
    }
    
    ExpNode *expr() {
        ExpNode *u = concat();
        while(rex[p] == '+') {
            skip(rex[p]);
            u = new ExpNode(ExpNode::OR, u, concat());
        }
        
        return u;
    }
    
    ExpNode *parse(const string& str) {
        rex = str, n = rex.length(), p = 0;
        return expr();
    }
};

template<int MAXS>
struct NFA{
    struct Transition{
        int ch, next;
        Transition(int ch=0, int next=0):ch(ch),next(next){}
        bool operator<(const Transition& rhs) const {
            if(ch != rhs.ch) return ch < rhs.ch;
            return next < rhs.next;
        }
    };
        
    int n, MAXA; // num of states, alphabet size
    typedef bitset<MAXS> SSet;
    typedef std::vector<Transition> TVec;
    TVec trans[MAXS];
    vector<SSet> sNextCache[MAXS];

    void add(int s, int t, int c=-1) { trans[s].push_back(Transition(c, t)); }
    
    void process(ExpNode *u){
         int st = n++, m;
         switch(u->type) {
            case ExpNode::A:
                add(st, n, u->val);
                break;
            case ExpNode::STAR:
                process(u->l);
                add(st, st+1), add(st, n), add(n-1, st);
                break;
            case ExpNode::OR:            
                process(u->l);
                m = n;
                process(u->r);
                add(st, st+1), add(st, m), add(m-1, n), add(n-1, n);
                break;
            case ExpNode::CONCAT:
                add(st, st+1), process(u->l);
                add(n-1, n), process(u->r);
                add(n-1, n);
                break;
            default:
                assert(false);
         }
         n++; // state 'end'
    }
    
    void init(const string& rex, int maxa) {
        RexParser rp;
        ExpNode *p = rp.parse(rex);
        n = 0;
        _for(i, 0, MAXS) trans[i].clear();
        process(p);
        MAXA = maxa;
        delete p;
    }

    VI ss, es; // starting and ending states
    void remove_epsilon() { // remove ε         
        VI reachable[MAXS], vis(MAXS, 0);
        _for(i, 0, n){ // BFS to find epsilon-closure for each state
            reachable[i].assign(1, i);
            queue<int> q; q.push(i);
            vis.assign(MAXS, 0), vis[i] = 1;
            while(!q.empty()) {
                int s = q.front(); q.pop();
                for(const auto& ts : trans[s]){
                    if(ts.ch != -1) continue;
                    int s2 = ts.next;
                    if(vis[s2]) continue;
                    reachable[i].push_back(s2);
                    vis[s2] = 1;
                    q.push(s2);
                }
            }
        }

        ss = reachable[0];
        _for(i, 0, n){ // merge transitions
            set<Transition> tr;
            for(auto& t : trans[i]) {
                if(t.ch == -1) continue;
                for(const auto r : reachable[t.next]) 
                    tr.insert(Transition(t.ch, r));
            }
            trans[i].assign(tr.begin(), tr.end());
        }

        buildNextCache();
    }

    void buildNextCache(){
        _for(s, 0, n+1){
            auto& sc = sNextCache[s];
            sc.clear(), sc.resize(MAXA);
            for(const auto& t : trans[s])
                if(t.ch != -1) sc[t.ch].set(t.next);
        }
    }

    void delta(int ch, const SSet& from, SSet& to) const { // δ
        to.reset();
        _for(s, 0, n+1) if(from.test(s)) to |= sNextCache[s][ch];
    }
};    

template<int MAXS>
ostream& operator<<(ostream& os, const NFA<MAXS>& nfa) {
    os<<"starting: "<<nfa.ss<<", n = "<<nfa.n<<endl;
    _for(s, 0, MAXS){
        const typename NFA<MAXS>::TVec& ts = nfa.trans[s];
        if(ts.empty()) continue;
        os<<s<<" : ";
        for(auto t : ts){
            os<<", -"<<(t.ch == -1 ? 'e' : (char)(t.ch));
            os<<"->"<<t.next;
        }
        os<<endl;
    }
    return os;
}

template<int MAXS>
struct HashDFA{
    typedef NFA<MAXS> TNFA;
    typedef typename TNFA::SSet SSet;
    static const LL HX = 433494437;
    unordered_map<LL, SSet> hashToS;
    vector< unordered_map<LL, LL> > trans;

    const TNFA *pnfa;
    LL init(TNFA *nfa) {
        hashToS.clear(), trans.clear(); 
        assert(nfa); pnfa = nfa;
        trans.resize(nfa->MAXA);
        SSet s0;
        for(auto s : nfa->ss) s0.set(s);
        LL hash = calcHash(s0);
        hashToS[hash] = s0;
        return hash;
    }

    inline LL calcHash(const SSet& s){
        LL ans = 0, X = 1;
        _for(i, 0, MAXS) if(s[i]) ans += i * X, X *= HX;
        return ans;
    }

    inline bool contains(LL hash, int s) {
        assert(hashToS.count(hash));
        return hashToS[hash].test(s);
    }

    inline LL delta(LL s, int ch) {
        auto& m = trans[ch];
        if(m.count(s)) return m[s];
        const SSet& v = hashToS[s];
        SSet next;
        pnfa->delta(ch, v, next);
        LL hash = calcHash(next);
        hashToS[hash] = next;
        return m[s] = hash;
    }
};

const int MAXR = 500+4, MAXS = MAXR*4;
int main() {
    int n; string rex, txt;
    RexParser parser; NFA<MAXS> nfa; HashDFA<MAXS> hDfa;
	while(cin>>n>>rex>>txt) {
        nfa.init(rex, n+'1');
        _for(i, 0, n) nfa.add(0, 0, i+'0');
        nfa.remove_epsilon();
        VI ans;
        LL hs = hDfa.init(&nfa);
        _for(i, 0, txt.size()){
            if(i && hDfa.contains(hs, nfa.n-1)) ans.push_back(i);
            hs = hDfa.delta(hs, txt[i]);
        }
        if(hDfa.contains(hs, nfa.n-1)) ans.push_back(txt.size());
        cout<<ans<<endl;
    }
	return 0;
}
// 17336512 12415   Digit Patterns  Accepted    C++11   4.120   2016-05-09 13:53:08