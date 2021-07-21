// Parentheses Balance, UVa673
// 陈锋
#include <bits/stdc++.h>
using namespace std;

inline bool match(char c1, char c2) {
  return (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']');
}

bool judge(const string &s) {
  stack<char> st;
  for (size_t i = 0; i < s.size(); i++) {
    char c = s[i];
    if (c == '(' || c == '[') {
      st.push(c);
      continue;
    }
    assert(c == ')' || c == ']');
    if (st.empty())
      return false;
    if (match(st.top(), c))
      st.pop();
    else
      break;
  }
  return st.empty();
}

int main() {
  int n;
  cin >> n, cin.ignore();
  for (string buf; n--;) {
    getline(cin, buf);
    cout << (judge(buf) ? "Yes" : "No") << endl;
  }
  return 0;
}
// 14804426	673	Parentheses Balance	Accepted	C++	0.046
// 2015-01-15 02:59:49