// Searching the Web, ACM/ICPC Beijing 2004, UVa1597
// 陈锋
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<sstream>
#include<set>
#include<vector>
#include<map>
using namespace std;

typedef vector<int> IntVec;
typedef set<int> IntSet;

IntSet emptyIntSet;

struct Doc {
    IntSet lines;
    map<string, IntSet> words;
    
    void AddLine(const string& s, int l) {
        lines.insert(l);
        string w;
        for(int i = 0; i < s.size(); i++) {
            char c = s[i];
            if(isalpha(c)) w.push_back(tolower(c));
            else if(!w.empty()) { words[w].insert(l); w.clear(); }
        }
        if(!w.empty()) { words[w].insert(l); }
    }
    
    const IntSet& FindWord(const string& w) {
        if(!words.count(w)) return emptyIntSet;
        return words[w];
    }
};

vector<Doc> docs;
vector<string> Lines;

ostream& operator<<(ostream& os, const IntSet& lines) {
    for(IntSet::const_iterator cit = lines.begin(); cit != lines.end(); cit++)
        os<<Lines[*cit]<<endl;
    return os;
}

void parseQuery(const string& q, vector<string>& ws) {
    ws.clear();
    stringstream ss(q);
    string w;
    while(ss>>w) ws.push_back(w);
}

void doQuery(const vector<string>& qWs) {
    assert(!qWs.empty());
    const string& A = qWs.front();
    const string& B = qWs.back();
    bool isAnd = (qWs.size()==3 && qWs[1]=="AND"), first = true, match;
    stringstream ss;
    switch(qWs.size()) {
        case 1:
            for(int i = 0; i < docs.size(); i++) {
                Doc& a = docs[i];
                const IntSet& ans = a.FindWord(A);
                match = !ans.empty();
                if(!match) continue;
                
                if(first) first = false; else ss<<"----------"<<endl;
                ss<<ans;
            }
            break;
        case 2:
            assert(A == "NOT");
            for(int i = 0; i < docs.size(); i++) {
                Doc& a = docs[i];
                const IntSet& ans = a.FindWord(B);
                match = ans.empty();
                if(!match) continue;
                
                if(first) first = false; else ss<<"----------"<<endl;
                ss<<a.lines;
            }            
            break;
        case 3:
            assert(isAnd || (qWs[1] == "OR"));
            for(int i = 0; i < docs.size(); i++) {
                Doc& a = docs[i];
                const IntSet& ansA = a.FindWord(A);
                const IntSet& ansB = a.FindWord(B);
                if(isAnd) match = (!ansA.empty()) && (!ansB.empty());
                else match = (!ansA.empty()) || (!ansB.empty());
                if(!match) continue;
                
                IntVec ans(ansA.size() + ansB.size());
                IntVec::iterator st = set_union(ansA.begin(), ansA.end(),
                    ansB.begin(), ansB.end(), ans.begin());
                
                if(first) first = false; else ss<<"----------"<<endl;
                for(IntVec::iterator it = ans.begin(); it != st; it++)
                    ss<<Lines[*it]<<endl;
            }
            break; 
        default:
            assert(false);
            break;
    }
    const string& output = ss.str();
    if(output.empty()) cout<<"Sorry, I found nothing."<<endl;
    cout<<output<<"=========="<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int N, M;
    string line;
    cin>>N;
    getline(cin, line);
    docs.resize(N);
    
    for(int i = 0; i < N; i++) {
        Doc& d = docs[i];
        while(true) {
            getline(cin, line);
            if(line == "**********") break;
            Lines.push_back(line);
            d.AddLine(line, Lines.size()-1);
        }
    }
    
    cin>>M;
    getline(cin, line);
    vector<string> qWs;
    for(int i = 0; i < M; i++) {
        getline(cin, line);
        parseQuery(line, qWs);
        doQuery(qWs);
    }
    
    return 0;
}
// 14804244	1597	Searching the Web	Accepted	C++	1.956	2015-01-15 00:25:20