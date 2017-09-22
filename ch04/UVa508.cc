// Morse Mismatches, ACM/ICPC World Finals 1997, UVa508
// 陈锋
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

unordered_map<char, string> morse;
unordered_map<string, vector<string> > context;

// a是b的前缀
bool isPrefixOf(const string& a, const string& b){
    return a.size() < b.size() && b.compare(0, a.size(), a) == 0;
}

void solve(const string& m) {
    if(context.count(m)) {
        const auto& v = context[m];
        assert(!v.empty());
        cout<<v.front();
        if(v.size() > 1) cout<<"!";
        cout<<endl;
        return;
    }
        
    map<int, string> ans;
    for(const auto& p : context) {
        const string& cm = p.first;
        if(isPrefixOf(m, cm)) ans[cm.size() - m.size()] = p.second.front();
        else if(isPrefixOf(cm, m)) ans[m.size() - cm.size()] = p.second.front();
    }
    cout<<ans.begin()->second<<"?"<<endl;
}

int main(){     
    string C, M;
    while(cin>>C && C != "*"){
        cin>>M;
        assert(C.size() == 1);
        morse[C[0]] = M;
    }
    
    while(cin>>C && C != "*") {
        M.clear();
        for(auto c : C) M += morse[c];
        context[M].push_back(C);
    }
    
    while(cin>>M && M != "*") solve(M);
    
    return 0;
}

/* 13521708	508	Morse Mismatches	Accepted	C++	0.019	2014-04-19 23:22:42 */