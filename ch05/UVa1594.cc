// Ducci Sequence, ACM/ICPC Seoul 2009, UVa1594
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
int readint() { int x; scanf("%d", &x); return x;}

int main(){
    int T = readint();
    vector<int> seq, zeroSeq;
    set< vector<int> > seqs;
    while(T--) {
        int n = readint();
        seq.clear(), zeroSeq.resize(n);
        _for(i, 0, n) seq.push_back(readint());
        
        bool zero = false, loop = false;
        seqs.clear(), seqs.insert(seq);
        do {
            if(seq == zeroSeq) { puts("ZERO"); break; }
            
            int a0 = seq[0];
            _for(i, 0, n) {
                if(i == n-1) seq[i] = abs(seq[i] - a0);
                else seq[i] = abs(seq[i] - seq[i+1]);
            }
            if(seqs.count(seq)) { puts("LOOP"); break; }
            seqs.insert(seq);
        } while(true);
    }
    
    return 0;
}

/* 13436405	1594	Ducci Sequence	Accepted	C++	0.868	2014-04-03 00:04:14 */