// Compound Words, UVa 10391
// 陈锋
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    set<string> words;
    string word, left, right;
    while(cin>>word) words.insert(word);
    
    for(const auto& s : words) _for(j, 1, s.size()) {
        left.assign(s, 0, j);
        if(words.count(left)){
            right.assign(s, j, s.size() - j);
            if(words.count(right)) { cout<<s<<endl; break; }
        }
    }
        
    return 0;
}

// 13439548	10391	Compound Words	Accepted	C++	0.096	2014-04-03 13:59:40
