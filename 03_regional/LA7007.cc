// LA7007 Finding Competitive Products
// 陈锋
#include <cassert>
#include <cstring>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)

using namespace std;
const int MAXD = 8, MAXW = 15000 + 4, 
    MAXEP = 1500 + 4, MAXPP = 10000 + 4, MAX_SCORE = 256004;
int d, t, k, wSize, epSize, ppSize, m, topCnts[MAXPP];
struct Prod{ 
    int p[MAXD]; 
    void readIn(){ _for(i, 0, d) scanf("%d", &(p[i])); }
    inline int operator*(const Prod& rhs){ 
        return inner_product(p, p+d, rhs.p, 0); 
    }
};

Prod WS[MAXW], EP[MAXEP], PP[MAXPP];
vector<int> EP_Scores[MAXW];

int solve(){
    fill_n(topCnts, ppSize, 0);
    _for(wi, 0, wSize){
        vector<int> scores(EP_Scores[wi]), indice(scores.size(), -1);
        _for(pi, 0, ppSize){
            int ns = WS[wi]*PP[pi], maxS = scores.back();
            if(ns > maxS && scores.size() >= k) continue;
            if(ns >= maxS) {
                scores.push_back(ns), indice.push_back(pi);
                continue;
            }

            auto sit = lower_bound(scores.begin(), scores.end(), ns);
            indice.insert(indice.begin() + (sit-scores.begin()), pi);
            scores.insert(sit, ns);
            if(scores.size() >= k && scores[k] != scores[k-1])
                scores.resize(k), indice.resize(k);
        }
        
        _for(i, 0, scores.size()) if(indice[i] != -1) topCnts[indice[i]]++;
    }

    partial_sort(topCnts, topCnts + m, topCnts + ppSize, greater<int>());
    return accumulate(topCnts, topCnts + m, 0);
}

int main(){
    scanf("%d%d%d%d", &t, &d, &k, &wSize);
    _for(i, 0, wSize) WS[i].readIn();
    scanf("%d", &epSize);
    _for(i, 0, epSize) EP[i].readIn();
    _for(wi, 0, wSize){
        auto& mm = EP_Scores[wi];
        _for(ei, 0, epSize) mm.push_back(WS[wi]*EP[ei]);
        sort(mm.begin(), mm.end());
        if(mm.size() > k) mm.resize(k); // 去掉肯定不是前k的EP产品
    }

    _for(i, 0, t) {
        scanf("%d%d", &m, &ppSize);
        _for(pi, 0, ppSize) PP[pi].readIn();
        printf("%d\n", solve());
    }
    return 0;
}
// 1925709  7007    Finding Competitive Products    Accepted    C++11   14.839  2016-03-18 03:13:04