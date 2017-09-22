// Planning mobile robot on Tree (EASY Version), UVa12569
// 陈锋
#include <cassert>
#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
int readint() { int x; cin>>x; return x; }
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
const int MAXN = 16;

struct Node { // 表示路径的链表节点
    int from, to;
    Node* next;
};

struct State {
    Node* path; // 路径
    int g, len; // 状态压缩，路径长度
    State(int gi = 0, int li = 0, Node* pn = NULL) : g(gi), len(li), path(pn) {}
    inline bool operator[](size_t i) const { return g&(1<<(i+4)); } // 位置i上是否有石头
    inline void setRock(size_t i, bool val = true) { // 设置位置i上是否有石头
        if(val) g |= 1<<(i+4);
        else g &= ~(1<<(i+4));
    }
    // 机器人的位置操作
    inline int getP() const { return g&15; }
    inline void setP(int p) { g = ((g>>4)<<4)|p; }
};

vector<int> G[MAXN]; // 图的邻接矩阵表示
MemPool<Node> pool; // 链表节点分配
int n,m,S,T, O[MAXN], VIS[1<<19];
Node* newNode(Node* next = NULL, int u = -1, int v = -1) {
    Node* p = pool.createNew();
    p->next = next, p->from = u, p->to = v;
    return p;
}

ostream& operator<<(ostream& os, Node* p) {
    if(p == NULL) return os;
    os<<p->next<<p->from+1<<" "<<p->to+1<<endl;
    return os;
}

// 尝试移动在点from上的物体(机器人或者石头)
void tryMove(const State& s, int from, queue<State>& q) {
    int rp = s.getP();
    assert(from >= 0 && from < n);
    for(auto to : G[from]) {
        if(to == rp || s[to]) continue; // 目标点有石头或机器人
        int ng = s.g;
        if(from == rp) ng = ((s.g>>4)<<4)|to; // 移动机器人
        else ng ^= (1<<(from+4)), ng ^= (1<<(to+4)); // 移动石头
        if(VIS[ng]) continue; // 新的状态已经访问过
        VIS[ng] = 1;
        q.push(State(ng, s.len+1, newNode(s.path, from, to)));
    }
}

void solve() {
    State s;
    _for(i, 0, m) s.setRock(O[i]);
    s.setP(S);
    queue<State> q;
    q.push(s);
    VIS[s.g] = 1;
    while(!q.empty()) {
        const State& st = q.front();
        int rp = st.getP();
        if(rp == T) { // 到达目的地
            cout<<st.len<<endl<<st.path;
            return;
        }
        tryMove(st, rp, q); // 尝试移动移动机器人
        _for(i, 0, n) if(st[i]) tryMove(st, i, q); // 尝试移动石头
        q.pop();
    }
    cout<<"-1"<<endl;
}

int main()
{
    int K = readint();
    for(int t = 1; t <= K; t++) {
        memset(VIS, 0, sizeof(VIS));
        cin>>n>>m>>S>>T;
        --S; --T;
        cout<<"Case "<<t<<": ";
        _for(i,0,m) O[i] = readint()-1;
        _for(i,0,n) G[i].clear();

        _for(i, 0, n-1) {
            int u = readint()-1, v = readint()-1;
            G[u].push_back(v); G[v].push_back(u);
        }

        solve();
        pool.dispose();
        cout<<endl;
    }
    return 0;
}
// 15042256	12569	Planning mobile robot on Tree (EASY Version)	Accepted	C++	4.392	2015-02-26 03:58:34