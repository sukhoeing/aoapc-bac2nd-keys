// Parentheses Balance, UVa673
// 陈锋
#include<cassert>
#include<cstdio>
#include<cmath>
#include<functional>
#include<algorithm>
#include<cstring>
#include<stack>
using namespace std;

bool isCorrect(const char* s) {
    int len = strlen(s);
    stack<char> st;
    for(int i = 0; i < len; i++)
    {
        char c = s[i];
        if(c == '(' || c == '[') st.push(c);
        else 
        {
            assert(c == ')' || c == ']');
            if(st.empty()) return false;
            char t = st.top();
            if(c == ')') { 
                if(t == '(') st.pop();
                else break; 
            }
            else if(c == ']') { 
                if(t == '[') st.pop(); 
                else break; 
            }
        }
    }
    
    return st.empty(); 
}

int main()
{
    int n;
    char buf[256];
    scanf("%d\n", &n);
    while(n--) {
        gets(buf);
        if(isCorrect(buf)) puts("Yes");
        else puts("No");
    }
    return 0;
}
// 14804426	673	Parentheses Balance	Accepted	C++	0.046	2015-01-15 02:59:49