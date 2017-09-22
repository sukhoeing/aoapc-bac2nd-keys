// Updating a Dictionary, UVa12504
// 陈锋
#include<cassert>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
using namespace std;

typedef map<string, string> SDict;

ostream& operator<<(ostream& os, SDict& m) {
    os<<"[";
    for(SDict::iterator it = m.begin(); it != m.end(); it++)
        os<<"("<<it->first<<":"<<it->second<<") ";
    os<<"]";
    return os;
}

ostream& operator<<(ostream& os, const vector<string>& s) {
    bool first = true;
    for(int i = 0; i < s.size(); i++) {    
        if(first) first = false; 
        else os<<",";
        os<<s[i];
    }    
    return os;
}

void parse(SDict& m, const string& s) {
    // cout<<"start parse "<<s<<endl;
    m.clear();

    string key, value;
    bool k = true;
    for(size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if(c == '{') continue;
        else if(c == ':') { k = false; }
        else if(c == ',' || c =='}') {
            if(key.empty()) continue;
            m[key] = value;
            key.clear();
            value.clear();
            k = true;
        } else {
            if(k) key.push_back(c);
            else value.push_back(c);
        }
    }
    // cout<<"parse "<<s<<" --> "<<m<<endl;
}

int main()
{    
    SDict m1, m2;    
    string l1, l2;
    vector<string> added, deled, changed;
    int T;
    cin>>T;
    while(T--) {
        cin>>l1>>l2;
        added.clear();
        deled.clear();
        changed.clear();
        // cout<<l1<<endl;
        // cout<<l2<<endl;
        parse(m1, l1);
        parse(m2, l2);
        for(SDict::iterator it = m1.begin(); it != m1.end(); it++) {
            const string& k = it->first;
            if(m2.count(k)) {
                if(m2[k] != it->second)  changed.push_back(k);
            }
            else deled.push_back(k);            
        }
        
        for(SDict::iterator it = m2.begin(); it != m2.end(); it++) {
            const string& k = it->first;
            if(!m1.count(k)) added.push_back(k);
        }
        
        if(added.empty() && deled.empty() && changed.empty()) {
            cout<<"No changes\n"<<endl; 
            continue;
        }
        
        sort(added.begin(), added.end());
        sort(deled.begin(), deled.end());
        sort(changed.begin(), changed.end());
        if(!added.empty()) cout<<"+"<<added<<endl;
        if(!deled.empty()) cout<<"-"<<deled<<endl;
        if(!changed.empty()) cout<<"*"<<changed<<endl;
        cout<<endl;
    }
    
    return 0;
}

/* 13456689	12504	Updating a Dictionary	Accepted	C++	0.025	2014-04-06 15:08:08 */