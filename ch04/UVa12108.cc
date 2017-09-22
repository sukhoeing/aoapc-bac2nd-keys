// Extraordinarily Tired Students, ACM/ICPC Xi’an 2006, UVa12108
// 陈锋
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

struct Stu { int a, b, c; };
istream& operator>>(istream& is, Stu& s) { return is>>s.a>>s.b>>s.c; }

int n;
Stu stus[10+2];
set<string> es;

void encode(string& ans) {
    ans.clear();
    _for(i, 0, n) ans += (char)(stus[i].c + '0');
    return;
}

bool action(int kase, int t) {
    string e;
    encode(e);
    if(es.count(e)) {
        cout<<"Case "<<kase<<": -1"<<endl;
        return true;
    }
    es.insert(e);

    int wake = 0, sleep = 0;
    _for(i, 0, n) if(stus[i].c <= stus[i].a) wake++;
    sleep = n - wake;
    
    if(sleep == 0) {
        cout<<"Case "<<kase<<": "<<t<<endl;
        return true;
    }
    
    _for(i, 0, n){
        Stu& s = stus[i];
        s.c++;
        if(s.c == s.a + s.b + 1) s.c = 1;
        if(s.c == s.a + 1 && wake >= sleep) s.c = 1;
    }
    
    return false;
}

int main(){
    int k = 1;
    while(cin>>n && n) {
        es.clear();
        _for(i, 0, n) cin>>stus[i];
        int t = 1;
        while(true) if(action(k, t++)) break;
        k++;
    }
    return 0;
}
// LA 1492718	3785	Extraordinarily Tired Students	Accepted	C++	0.003	2014-07-22 06:39:50