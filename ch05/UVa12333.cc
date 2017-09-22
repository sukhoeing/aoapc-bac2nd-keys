// Revenge of Fibonacci, ACM/ICPC Shanghai 2011, UVa12333
// 陈锋
#include<cassert>
#include<iostream>
#include<cstdio>
#include<ctime>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
#include<sstream>
using namespace std;

const int BASE = 10000;
template<int MaxNode, int Sigma_Size>
struct Trie {
    int ch[MaxNode][Sigma_Size], sz, val[MaxNode];
    Trie() { 
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        memset(val, 0, sizeof(val));
    }
    
    int idx(char c) const { return c - '0'; }
    
    void insert(const string& s, int v) {
        assert(v != 0);
        int u = 0, n = s.size();
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = v;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        
        if(!val[u]) val[u] = v;
        // cout<<"insert - "<<s<<",u = "<<u<<",v = "<<val[u]<<endl;
    }
    
    int getValue(const string& s) const {
        int v = -1, u = 0, n = s.size();
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) return v;
            u = ch[u][c];            
        }
        
        // cout<<"getValue "<<s<<",u = "<<u<<",v = "<<val[u]<<endl;
        if(val[u]) v = val[u];
        return v;
    }
};

template<int maxn>
struct bign{
    int len, s[maxn];
    bign() { memset(s, 0, sizeof(s)); len = 1; }
    bign(int num) { *this = num; }
    bign& operator=(int num) {
        assert(num >= 0);
        if(num == 0) { len = 1; return *this; }
        len = 0;
        while(num > 0) {
            // printf("s[%d] = %d\n", len, num%BASE);
            s[len++] = num % BASE;
            num /= BASE;
        }
        return *this;
    }
  
    bign& operator=(const bign& rhs){
        len = rhs.len;
        copy(rhs.s, rhs.s + rhs.len, s);
        return *this;
    }
};

const int MAXF = 100000, MAXLEN = 5300;
typedef bign<MAXLEN> BigFn;

inline void Add(const BigFn& a, const BigFn& b, BigFn& c) {
    int *cs = c.s, l = 0;
    int mLen = max(a.len, b.len);
    for(int i = 0, g = 0; g || i < mLen; i++) {
        int x = g;
        if(i < a.len) x += a.s[i];
        if(i < b.len) x += b.s[i];
        cs[l++] = x % BASE;
        g = x / BASE;
    }
    c.len = l;
}

ostream& operator<<(ostream &os, const BigFn& x) {
    char buf[8];
    stringstream ss;
    bool first = true;
    for(int i = x.len - 1; i >= 0; i--){
        if(first) {
            first = false;
            ss<<x.s[i];
        } else {
            sprintf(buf, "%04d", x.s[i]);
            ss<<buf;
        }
    }
        
    const string& s = ss.str();
    if(s.empty()) return os<<0;
    return os<<s;
}

string getPfx(const BigFn& f, int len = 41) {
    int ol = 0;
    char buf[8];
    stringstream ss;
    bool first = true;
    for(int i = 0; i < f.len; i++) {
        if(first) { first = false; sprintf(buf, "%d", f.s[f.len-i-1]); }
        else sprintf(buf, "%04d", f.s[f.len-i-1]);
        ss<<buf;
        ol += strlen(buf);
        if(ol >= len) break;
    }
    return ss.str();
}

BigFn f0 = 1, f1 = 1, f;
Trie<3817223, 10> pfxes;

int main()
{    
    for(int i = 2; i < MAXF; i++) {
        Add(f0, f1, f);
        string pfx = getPfx(f);
        pfxes.insert(pfx, i);
        f0 = f1;
        f1 = f;
    }   
    
    int T;
    scanf("%d", &T);
    char buf[64];
    for(int t = 1; t <= T; t++) {
        scanf("%s", buf);
        int ans = 0;
        string p(buf);
        if(p != "1") ans = pfxes.getValue(p);
        printf("Case #%d: %d\n", t, ans);
    }
    
    return 0;
}

/* Live Archive AC: 1431647	5711	Revenge of Fibonacci	Accepted	C++	3.102	2014-04-11 07:58:13 */