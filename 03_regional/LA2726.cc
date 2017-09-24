// Combining Images World Finals 2003 Beverly Hills - LA2726
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
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
int HEX[16][4] = { // 16进制每个字符对应的二进制
    {0,0,0,0},{0,0,0,1},{0,0,1,0},{0,0,1,1},{0,1,0,0},{0,1,0,1},{0,1,1,0},{0,1,1,1},
    {1,0,0,0},{1,0,0,1},{1,0,1,0},{1,0,1,1},{1,1,0,0},{1,1,0,1},{1,1,1,0},{1,1,1,1}
};

char HEXC[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

const int MAXN = 2048;
typedef vector<int>::iterator IIter;

// HEX转二进制
void fromHex(vector<int>& bits, const string& s) {
    bits.clear();
    int sz = s.size(), h;
    bool p = true, first = true;
    for(auto c : s){
        if (isdigit(c)) h = c - '0';
        else { assert(isupper(c)); h = c-'A'+10; }
        if(first) { // 前4位的处理
            assert(h); first = false;
            _for(b, 0, 4){
                int x = HEX[h][b];
                if(p) { if(x) p = false; } // 前缀0遇到1
                else bits.push_back(x);
            }
        }
        else { _for(b, 0, 4) bits.push_back(HEX[h][b]); }        
    }
}       
    
string toHexStr(const vector<int>& bits) {
    int p = (bits.size() + 1) % 4, z = 1, i = 0, b = 0;
    string ans;
    if(p) { // 需要附加前缀
        while(i < p-1) z = (z<<1) + bits[i++];
        ans += HEXC[z], z = 0;
    }
    else b = 1;
    
    while(i < bits.size()){
        assert(b < 4);
        z = (z<<1) + bits[i++];
        if(++b == 4) ans += HEXC[z], z = 0, b = 0;
    }
    
    return ans;
}

struct Node {
    int flag, v; // 是否为单色，单色的颜色
    Node *children[4]; // 顺序的四个子方阵
    Node *init() { memset(children, 0, sizeof(children)); return this; }
};

MemPool<Node> nodes;
Node* newNode() { return nodes.createNew()->init(); }

Node* parseBits(const vector<int>& bits, int& b) {
    assert(b < bits.size());
    Node* p = newNode();
    p->flag = bits[b++];
    if(p->flag) { p->v = bits[b++]; return p; }
    _for(i, 0, 4) p->children[i] = parseBits(bits, b);
    return p;
}

Node* intersect(Node* p1, Node* p2) {
    assert(p1); 
    assert(p2);
    if(p1->flag && p2->flag) {
        Node* p = newNode();
        p->flag = 1, p->v = (p1->v && p2->v);
        return p;
    }
    if(p2->flag) return intersect(p2, p1);
    if(p1->flag) return p1->v?p2:p1;
    
    Node* p = newNode();
    p->flag = 1;
    _for(i, 0, 4){
        assert(p1->children[i]); assert(p2->children[i]);
		Node *cp = intersect(p1->children[i], p2->children[i]);
        p->children[i] = cp;
		if(p->flag) {
			if(i == 0) p->v = cp->v;
			if(cp->flag == 0 || p->v != cp->v) p->flag = 0;
		}
    }
    if(p->flag) memset(p->children, 0, sizeof(p->children));
    return p;
}
void toBits(Node* p, vector<int>& b) { // 四分树编码
    b.push_back(p->flag);
    if(p->flag) { b.push_back(p->v); return; }
    _for(i, 0, 4) toBits(p->children[i], b); // 递归子树编码
}

int main(){
    string s1, s2;
    vector<int> bits;
    for(int t = 1; cin>>s1>>s2 && s1 != "0"; t++) {
        if(t>1) cout<<endl;        
        fromHex(bits, s1);
        int b = 0;
        Node *p1 = parseBits(bits, b);        
        fromHex(bits, s2); b = 0;
        Node *p2 = parseBits(bits, b);
        Node *p3 = intersect(p1, p2);
        bits.clear();
        toBits(p3, bits);
        cout<<"Image "<<t<<":"<<endl<<toHexStr(bits)<<endl;
        nodes.dispose();   
    } 
    return 0;
}
// LA: 1490863	2726	Combining Images	Accepted	C++	0.019	2014-07-20 14:17:26