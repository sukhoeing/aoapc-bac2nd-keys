// LA5174 Typesetting World Finals 1994
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
int readint() { int x; scanf("%d", &x); return x; }
using namespace std;

const int MAXN = 256 + 8, FCNT = 6;
const string SPACE = " ";
int Fonts[MAXN][FCNT+2];
typedef std::vector<string> StrVec;

int getWidth(int ft, int pt, const string& s) {
    int ans = 0;
    for(auto c : s) ans += (pt*Fonts[c][ft]+5)/10;
    return ans;
}

void solve(const StrVec& words, int LW) {
    // 行号，字体， 点数，已用的LineWidth(不包含最后的一个空格)，最后一个空格的大小
    int l = 1, ft = 1, pt = 10, lw = 0, lsw = getWidth(ft, pt, SPACE);
    StrVec lws;
    for(const auto& w : words) {
        assert(!w.empty());
        if(w[0] == '*') {
            if(w[1] == 'f') ft = w[2] - '0';
            if(w[1] == 's') sscanf(w.c_str(), "*s%d", &pt);
            continue;
        }
        
        int ww = getWidth(ft, pt, w); // 单词的宽度
        if(ww > LW) { // 单词整体一行放不下
            if(lw) // 当前不是新行，先换行
                printf("Line %d: %s ... %s (%d whitespace)\n", 
                    l++, lws.front().c_str(), lws.back().c_str(), LW-lw);

            printf("Line %d: %s (%d whitespace)\n", l++, w.c_str(), LW-ww); // 放完这个单词另起一行 
            lws.clear(); lw = 0;
            continue;
        }
        
        // 新行
        if(!lw) {
            lws.push_back(w); lw = ww; lsw = getWidth(ft, pt, SPACE);
            continue;
        }
        
        // 老行
        if(lw + lsw + ww > LW) { // 放不下另起一行
            printf("Line %d: %s ... %s (%d whitespace)\n", 
                l++, lws.front().c_str(), lws.back().c_str(), LW - lw);
            lws.clear(), lws.push_back(w), lsw = getWidth(ft, pt, SPACE), lw = ww;
            continue;            
        }
        
        // 放得下
        lws.push_back(w), lw += lsw + ww, lsw = getWidth(ft, pt, SPACE);
    }
    if(lw) 
        printf("Line %d: %s ... %s (%d whitespace)\n", 
            l++, lws.front().c_str(), lws.back().c_str(), LW - lw);
}

int main(){    
    StrVec words;
    char line[128]; string word;
    bool first = true;
    int N, L, W;
    while(scanf("%d", &N) == 1 && N) {
        if(first) first = false; else puts("");
        memset(Fonts, 0, sizeof(Fonts));
        _for(i, 0, N-1) { 
			scanf("%s", line);
            _rep(j, 1, FCNT) scanf("%d", &(Fonts[line[0]][j]));
        }
        _rep(j, 1, FCNT) scanf("%d", &(Fonts[' '][j]));
        
        for(int p = 1; scanf("%d%d", &L, &W) && L; p++){
            printf("Paragraph %d\n", p);
            gets(line);
            words.clear();
            _for(i, 0, L){
                gets(line);
                stringstream ss; ss<<line;
                while(ss>>word) words.push_back(word);
            }
            solve(words, W);
        }
    }
    return 0;
}
// 1622938	5174	Typesetting	Accepted	C++	0.016	2014-12-22 05:34:13