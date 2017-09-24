// UVa12568 Optimizing Key Signature
// 陈锋 C++11
#include <cassert>
#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#define _for(i,a,b) for(int i=a; i<(b); ++i)

using namespace std;
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for(int i = 0; i < v.size(); i++) {
    	if(i) os<<" ";
        os<<v[i];
    }
    return os;
}

typedef vector<int> IntVec;
typedef vector<char> ChVec;

vector<IntVec> bKey = { // b keySigs b调号作用的音符
	{0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0}, // B
	{0,1,0,0,1,0,0}, // B E
	{1,1,0,0,1,0,0}, // A B E
	{1,1,0,1,1,0,0}, // A B D E 
	{1,1,0,1,1,0,1}, // A B D E G
	{1,1,1,1,1,0,1}, // A B C D E G
	{1,1,1,1,1,1,1}, // A B C D E F G
}, sKey = { // # keySigs #调号作用的音符
	{0,0,0,0,0,0,0},	
	{0,0,0,0,0,1,0}, // F
	{0,0,1,0,0,1,0}, // C F
	{0,0,1,0,0,1,1}, // C F G
	{0,0,1,1,0,1,1}, // C D F G 
	{1,0,1,1,0,1,1}, // A C D F G
	{1,0,1,1,1,1,1}, // A C D E F G
	{1,1,1,1,1,1,1}, // A B C D E F G
};
struct Measure{
	ChVec acs; // 记号
	IntVec notes; // 音符，用 0~6对应记录A~G
	void addNote(const string& s){ // 增加一个音符
		char ch = s[0];
		if(ch == '#' || ch == 'b' || ch == 'n'){
			acs.push_back(ch);
			notes.push_back(s[1]-'A');
		} else {
			acs.push_back(0);
			notes.push_back(ch-'A');
		}
	}

	void restore(int m, char ACC){ // 根据调号把音节还原为0调号
		if (ACC == '#')  innerRestore(sKey[m], ACC);
		else  innerRestore(bKey[m], ACC);
	}

	void innerRestore(const IntVec& v, char ACC){
		ChVec kAcc(8, 0); // 小节内的变音记号
		_for(i, 0, acs.size()){
			int nt = notes[i];
			char& ac = acs[i];
			if(ac == 0){
				if(kAcc[nt]) ac = kAcc[nt]; // 小节前面有这个音符的变音记号
				else if(v[nt]) ac = ACC; // 用调号的变音记号
			}
            kAcc[nt] = ac;
		}
	}

	int apply(int m, char ACC) const {
		ChVec kAcc(8, 0); // 小节内的变音记号
        stringstream ss; // Debug
		auto debugOutNt = [&ss](char ac, int nt){ ss<<ac<<(char)(nt + 'A')<<" "; };	
		
		const IntVec& sAcc = ACC == '#' ? sKey[m] : bKey[m]; // 调号作用的所有音符
		int ans = 0;
		_for(i, 0, acs.size()){
			int nt = notes[i], ac = acs[i];
			if(ac == 0 || ac == 'n'){
                if(sAcc[nt]){ // 被调号覆盖
                    if(!kAcc[nt] || kAcc[nt] != 'n') // 前面没有n作为变音记号
                        kAcc[nt] = 'n', debugOutNt('n', nt), ans++;
                }
                else {
                    if(kAcc[nt] && kAcc[nt] != 'n') // 前面的变音记号不是n
                        kAcc[nt] = 'n', debugOutNt('n', nt), ans++;
                }
            } else if(ac == '#' || ac == 'b'){
				if(kAcc[nt]){ // 前面有变音记号
                    if(kAcc[nt] != ac) // 不一样
                        kAcc[nt] = ac, debugOutNt(ac, nt), ans++;
                } else if(ac != ACC || !sAcc[nt]) // 没被调号覆盖
                    kAcc[nt] = ac, debugOutNt(ac, nt), ans++;
			}
		}
		
        //cout<<ss.str();
		return ans;
	}
};

ostream& operator<<(ostream& os, const Measure& m){
	assert(m.acs.size() == m.notes.size());
	_for(i, 0, m.acs.size()) {
        int ac = m.acs[i];
        if(ac)os<<(char)ac;
        os<<(char)('A'+m.notes[i])<<" ";
    }
	return os<<" | ";
}

int main() {
	int T, m; char ACC; string buf; vector<Measure> measures; // 所有的音节
	cin>>T;
	_for(t, 1, T+1){
		cin>>buf; ACC = 0; measures.clear();
		measures.push_back(Measure());
		m = buf[0] - '0';
		if(m > 0) ACC = buf[1];
		while(cin>>buf && buf != "||") {
			if(buf == "|") { // 新的小节
				assert(!measures.empty());
				measures.push_back(Measure());
			}
			else measures.back().addNote(buf);
		}
		//cout<<"-----"<<measures<<"-------"<<endl;
        for(auto& me : measures) me.restore(m, ACC);
        //cout<<"|||--"<<measures<<"-------"<<endl;

		int minCnt = 0;
		vector<string> keys{"0"};
		for(const auto& m : measures) minCnt += m.apply(0, 0); // 0调号
		string ACCs = "#b";
		_for(i, 1, 8){
			for(auto acc : ACCs){
				int cnt = 0;
				for(const auto& m : measures) cnt += m.apply(i, acc);
				if(cnt > minCnt) continue;
				if(cnt < minCnt) keys.clear();
				minCnt = cnt;
				buf.clear(), buf += '0' + i, buf += acc;
				keys.push_back(buf);
			}
		}
		_for(i, 1, keys.size()) if(keys[i][0] != keys[i-1][0]) { keys.resize(i); break; }
		cout<<"Case "<<t<<": "<<minCnt<<endl;
		cout<<keys<<endl<<endl;
	}
  	return 0;
}
// 16227316	12568	Optimizing Key Signatur	Accepted	C++11	0.006	2015-10-07 22:36:25