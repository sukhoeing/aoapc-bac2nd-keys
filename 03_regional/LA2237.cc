// A Major Problem, World Finals 2001 Vancouver, LA2237
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

struct Scale {
    string key;
    vector<string> notes;
};
vector<string> Notes1 = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"}
             , Notes2 = {"B#","Db","D","Eb","Fb","E#","Gb","G","Ab","A","Bb","Cb"};
const int NCNT = 12, SCNT = 8;
map<string, Scale> scales; // 主调:音阶
int Step[] = {2,2,1,2,2,2,1};

void genScale(int cur, vector<string>& notes, 
    set<char>& letters, bool hasFlat, bool hasSharp) {
    assert(!hasFlat || !hasSharp);
    cur = (cur + NCNT) % NCNT;
    int n = notes.size();
    if(n == SCNT - 1 && letters.size() == SCNT - 1) {
        scales[notes[0]] = { notes[0], notes };
        return;
    }

    vector<string> tryNotes = { Notes1[cur], Notes2[cur] };    
    assert(n < SCNT);
    int next = cur + Step[n];
    for(const auto& note : tryNotes){
        char c0 = note[0], c1 = note[1];
        if(letters.count(c0)) continue;  // 字母没用过
        notes.push_back(note), letters.insert(c0); // 使用过的音符和字母
        if(note.size() != 2) { // 没有'#' 'b'
            genScale(next, notes, letters, hasFlat, hasSharp);
        } else {
            if(c1 == '#' && !hasFlat) // 有#了
                genScale(next, notes, letters, false, true);
            if(c1 == 'b' && !hasSharp) // 有b了
                genScale(next, notes, letters, true, false);
        }
        notes.pop_back(), letters.erase(c0);
    }
}

void generateScales() {
    vector<string> ns; set<char> ls;
    _for(i, 0, NCNT) genScale(i, ns, ls, false, false);
}

int main(){
    generateScales();    
    string sKey, tKey, note;
    char oBuf[512];
    vector<string> notes;        
    bool first = true;
    while(cin>>sKey && sKey != "*") {
        cin>>tKey, notes.clear();
        while(cin>>note && note != "*") notes.push_back(note);
        if(first) first = false; else cout<<endl;
        
        bool sKeyValid = scales.count(sKey), tKeyValid = scales.count(tKey);
        if(sKeyValid && tKeyValid) {
            cout<<"Transposing from "<<sKey<<" to "<<tKey<<":"<<endl;
            const Scale &ss = scales[sKey], &ts = scales[tKey];
            for(const auto& nt : notes){
                auto it = find(ss.notes.begin(), ss.notes.end(), nt);
                if(it == ss.notes.end())
                    cout<<"  "<<nt<<" is not a valid note in the "
                        <<ss.key<<" major scale"<<endl;
                else
                    cout<<"  "<<nt<<" transposes to "
                    <<ts.notes[it-ss.notes.begin()]<<endl;
            }
        } else if(!sKeyValid && !tKeyValid) {
            cout<<"Key of "<<sKey<<" is not a valid major key"<<endl;
        } else {
            cout<<"Key of "<<(sKeyValid?tKey:sKey)<<" is not a valid major key"<<endl;
        }
    }
    return 0;
}

// LA 1480023	2237	A Major Problem	Accepted	C++	0.099	2014-07-07 13:49:06