// Bug Hunt, ACM/ICPC Tokyo 2007, UVa1596
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
#include<map>
using namespace std;

struct Array {
    int size;
    map<int, int> values;
    void init(int sz) { 
        
        assert(sz>=0);
        // printf("init size = %d\n", sz);
        size = sz;
        values.clear();
    }
    
    Array(){ remove(); }
    
    void remove() { size = -1;  values.clear(); }
    
    bool exists() { return size >= 0; }
    
    bool getValue(int idx, int& v) {
        assert(exists());
        if(values.count(idx)) {
            v = values[idx];
            return true;
        }
        return false;
    }
    
    bool setValue(int idx, int v) {
        assert(exists());
        assert(idx >= 0);
        if(idx >= size) return false;
        
        values[idx] = v;
        return true;
    }
};

const int MAXA = 128;
Array arrays[MAXA];

bool eval(const char* s, int len, int& v) {
    // printf("eval %s, len = %d,\n", s, len);
    if(isdigit(s[0])) { 
        sscanf(s, "%d", &v); return true;
    }
    
    char a = s[0];
    assert(len > 3);
    assert(isalpha(a));
    assert(s[1] == '[');
    assert(s[len-1] == ']');
    
    Array& ary = arrays[a];
    if(!ary.exists()) return false;
    int idx;
    if(!eval(s+2, len-3, idx)) return false;
    return ary.getValue(idx, v);
}

int main()
{
    char line[128];
    int lineNum = 0, bugLine = 0;
    while(scanf("%s", line) == 1){
        // printf("e : %s\n", line);
        int expLen = strlen(line);
        if(line[0] == '.') {
            if(lineNum) printf("%d\n", bugLine);
            for(int i = 0; i < MAXA; i++) arrays[i].remove();
            lineNum = 0;
            bugLine = 0;
            continue; 
        }
        if(bugLine > 0) continue;
        
        const char *pEq = strchr(line, '=');
        if(pEq)
        {
            Array& ary = arrays[line[0]];
            int rv, index, lLen = pEq - line;
            if(ary.exists()
                && eval(pEq+1, expLen-lLen-1, rv)
                && eval(line+2, lLen-3, index)
                && ary.setValue(index, rv)) 
                lineNum++;
            else
                bugLine = lineNum+1;
        } else {
            char name; int sz;
            sscanf(line, "%c[%d]", &name, &sz);
            arrays[name].init(sz);   
            lineNum++;
        }
    }
    
    return 0;
}

/* 13455486	1596	Bug Hunt	Accepted	C++	0.019	2014-04-06 11:35:56 */