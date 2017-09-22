// Alignment of Code, ACM/ICPC NEERC 2010, UVa1593
// 陈锋
#include <cassert>
#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <queue>
#include <iomanip>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

const int MAXN = 1024;
vector<string> LineWords[MAXN];
size_t WordLen[MAXN], MaxWords, LineCnt;

int main(){
    string line, word;
    MaxWords = 0; LineCnt = 0;
    fill_n(WordLen, MAXN, 0);
    while(getline(cin, line)) {
        stringstream ss(line);
        size_t wi = 0;
        while(ss>>word) {
            WordLen[wi] = max(WordLen[wi], word.size());
            wi++;
            LineWords[LineCnt].push_back(word);
        }
        MaxWords = max(MaxWords, wi);
        LineCnt++;
    }
    
    _for(i, 0, LineCnt){
        const auto& ws = LineWords[i];
        _for(j, 0, ws.size()) cout<<left<<setw(j < ws.size()-1 ? WordLen[j]+1 : 0)<<ws[j];
        cout<<endl;
    }
    
    return 0;
}

/* 13505067	1593	Alignment of Code	Accepted	C++	0.028	2014-04-16 14:42:46 */