// Stamps and Envelope Size, ACM/ICPC World Finals 1995, UVa242
// 陈锋
#include <cassert>
#include <functional>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
using namespace std;
int readint() { int x; scanf("%d", &x); return x; }

const int MAXN = 10 + 1, MAXS = MAXN, MAXC = MAXS * 100 + 100 + 4;
int S, N, DP[MAXC];

struct StampSet {
    vector<int> D;
    int maxCover;
    void output(){ for(auto e : D) printf("%3d", e); }
    StampSet& input(){
        D.clear(); maxCover = 0;
        int n = readint();
        while(n--) D.push_back(readint());
        sort(D.begin(), D.end());   
        return *this;     
    }
    void getMaxCover() {
        // cout<<"getMaxCover - "<<D<<endl;
        int i = 0;
        fill_n(DP, MAXC, 0);
        DP[i] = 0;
        while(true) {
            i++;
            int ans = INT_MAX;
            for(int j = 0; j < D.size() && D[j] <= i; j++)
                ans = min(ans, DP[i-D[j]] + 1);
            // cout<<"i = "<<i<<" d = "<<ans<<endl;
            if(ans > S) break;
            else DP[i] = ans;
        }
        maxCover = i - 1;
    }

    bool operator<(const StampSet& rhs) const {
        if(maxCover != rhs.maxCover) return maxCover > rhs.maxCover;
        if(D.size() != rhs.D.size()) return D.size() < rhs.D.size();
        for(int i = D.size()-1; i >= 0; i--)
            if(D[i] != rhs.D[i]) return D[i] < rhs.D[i];
        return true;
    }
};

StampSet C[MAXN];
int main() {
    while(scanf("%d", &S) && S) {
        N = readint();
        _for(i, 0, N) C[i].input().getMaxCover();
        auto mss = min_element(C, C+N);
        printf("max coverage = %3d :", mss->maxCover);
        mss->output();
        puts("");
    }
    return 0;
}
// 1910023  LA5181    Stamps and Envelope Size    Accepted    C++11   0.019   2016-02-14 07:58:54