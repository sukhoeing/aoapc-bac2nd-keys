// Network Mess, ACM/ICPC Tokyo 2005, UVa1667
// 陈锋
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <sstream>
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
int readint() { int x; scanf("%d", &x); return x; }

using namespace std;
const int MAXN = 64;
struct Node{ vector<Node*> nodes; };
typedef Node* PNode;
MemPool<Node> nodePool;
vector<int> M[MAXN];
int N, pa[MAXN];
int getPa(int i) { return i == pa[i] ? i : (pa[i] = getPa(pa[i])); }

// 建树, 叶子节点, 点到根节点的距离, 根节点指针, 父节点, 度数数组
void buildTree(const vector<int>& leaves, vector<int>& dist, PNode root, PNode fa, vector<int>& degs) {
    memset(pa, 0, sizeof(pa));
    for(const auto l : leaves) pa[l] = l;

    int isLeaf[MAXN]; // 直接的叶子
    memset(isLeaf, 0, sizeof(isLeaf));

    for(auto lit = begin(leaves); lit != end(leaves); lit++) {
        int li = *lit;
        if(dist[li] == 1) {  // 到根节点距离为1，就是直接的叶子节点
            root->nodes.push_back(nodePool.createNew());
            isLeaf[li] = 1;
            continue;
        }
        for(auto rit = lit+1; rit != end(leaves); rit++){
            int ri = *rit;
            if(dist[ri] == 1) continue;
            if(dist[li] + dist[ri] > M[li][ri]) pa[ri] = li; // 相同的子树
        }
    }

    for(auto i : leaves) dist[i]--;
    map<int, vector<int> > subTrees; // 每颗子树
    for(auto i : leaves) if(!isLeaf[i]) subTrees[getPa(i)].push_back(i);

    for(const auto& p : subTrees){
        root->nodes.push_back(nodePool.createNew());
        buildTree(p.second, dist, root->nodes.back(), root, degs);
    }
    
    if(fa && !root->nodes.empty()) degs.push_back(root->nodes.size() + 1);
}

int main(){
    while(scanf("%d", &N) == 1 && N){
        _for(i, 0, N){
            M[i].clear();
            _for(j, 0, N) M[i].push_back(readint()); 
        }
        vector<int> leaves, dist(M[0].begin(), M[0].end()), degs;
        _for(i, 1, N) leaves.push_back(i);

        buildTree(leaves, dist, nodePool.createNew(), NULL, degs);
        sort(degs.begin(), degs.end());
        bool first = true;
        for(auto d : degs){
            if(first) first = false; else printf(" ");
            printf("%d", d);
        }
        puts("");
        nodePool.dispose();
    }
    return 0;
}
// 16906647 1667    Network Mess    Accepted    C++11   0.000   2016-02-26 02:41:39