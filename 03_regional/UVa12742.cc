// UVa12742	Mining in Starcraft
// 陈锋 C++11
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
#define _for(i,a,b) for( int i=(a); i<(b); ++i)

struct CMD {
	enum Type { Build = 0, Minearl = 1, Gas = 2 };
	int time, cmd, id;
	CMD(int t = 0, int c = Build, int i = 0) : time(t), cmd(c), id(i) {}
	bool operator<(const CMD& c) const {
		if (time != c.time) return time < c.time;
		if (cmd != c.cmd) return cmd < c.cmd;
		return id < c.id;
	}
};
ostream& operator<<(ostream& os, const CMD& c){
	os << c.time;
	if (c.cmd != CMD::Build) os << ' ' << c.id;
	return os << ' ' << c.cmd;
}
// 最长的挖矿时间，最大农民个数，因为需要挖气的次数G+1<14，所以写20了
const int MAXT = 50, MAXK = 20; 
// 挖矿单位时间，挖气单位时间，造1个农民所需时间, 目标的矿数，目标的气数
int t1, t2, t3, p1, p2; 
bool found = false;

int mineCnt[MAXT+4], gasTime[MAXK];
vector<int> newSCV[MAXT+4];
/*
	实际上是复杂的IDFS
	i : 对第i个农民开始挖气的时间进行决策
	G : 总共还要挖多少次气，对于i+1 ~ SCV的农民来说
	genCmds : 用来节省时间，是否生成命令序列
	M : 时间上限
	SCV : 要达到的农民的总的个数
	cmds : 所有的命令序列
*/
void dfs(int i, int G, bool genCmds, int TEnd, const int SCV, vector<CMD>& cmds) {
	if (i < SCV) { // g: 遍历，编号为i的农民要负责采几次气
		for(int g = (i == SCV-1 ? G : (i>=4));  g <= G && TEnd-t2*g >= 0; g++){
			gasTime[i] = TEnd - t2*g; // 农民i开始挖气的最晚时间
			dfs(i+1, G-g, genCmds, TEnd, SCV, cmds);
			if(found) return;
		}
		return;
	}

	if (genCmds) cmds.clear();
	fill_n(mineCnt, MAXT, 0);
	_for(t, 0, MAXT + 4) newSCV[t].clear();
	int sCnt = 4; // SCV 个数
	_for(i, 0, sCnt) newSCV[0].push_back(i);
	mineCnt[0] = 50; // 一开始有50的矿
	bool valid = true;
	int mineSum = 0, lastScvT = 0; // 总挖矿数；最后一个造出的
	_for(t, 0, TEnd+1) { // 对每一秒钟的情况进行模拟
		// 造不到提前预设好的农民个数了
		if (sCnt < SCV && t + t3 > TEnd) { valid = false; break; } 
		for (const auto id : newSCV[t]) { // 第t秒新造出来的农民id
			// id在在t到gast[id]秒之前全部挖矿
			for (int tid = t; tid + t1 <= gasTime[id]; tid += t1) { 
				mineCnt[tid+t1] += 8; // 挖到8个矿
				if (genCmds) cmds.push_back(CMD(tid, CMD::Minearl, id + 1));
			}
		}
		mineSum += mineCnt[t];
		// 农民还没造够，并且有矿，并且最后一个农民已经造好
		if (sCnt < SCV && mineSum >= 50 && lastScvT <= t) { 
			mineSum -= 50;
			// 造出来的农民来不及挖气了
			if (t + t3 > gasTime[sCnt]) { valid = false; break; } 
			lastScvT = t + t3;
			newSCV[t + t3].push_back(sCnt++); // 一有钱就造农民，贪心最优策略
			if (genCmds) cmds.push_back(CMD(t, CMD::Build, sCnt));
		}
	}
	// 农民数量一定要造够，主程序里面枚举了SCV个数，严格相等避免同一个方案考虑多次
	if (valid && mineSum >= p1 && sCnt == SCV) {
		found = true;
		if (genCmds) {
			_for(s, 0, SCV)
				for (int t = gasTime[s]; t < TEnd; t += t2)
					cmds.push_back(CMD(t, CMD::Gas, s + 1));
		}
	}
}

int main() {
	vector<CMD> cmds;
	for (int T = 1;  cin>>t1>>t2>>t3>>p1>>p2 && t1 > 0; T++) {
		// 向上取整，还需要挖多少次气
		int L = -1, R = MAXT, G = (p2+7) / 8; 
		bool last = false;
		while (true) {
			int M = last?R:(L+R) / 2; // 时间上限是M
			// 总共有多少个农民(包含预置的，剩下是要建造的)
			for (int SCV = 4; SCV <= max(G + 1, 4); SCV++) { 
				found = false;
				memset(gasTime, -1, sizeof(gasTime));
				dfs(0, G, last, M, SCV, cmds);
				if (found) break;
			}
			if (last) break;
			if (found) R = M; else L = M;
			if (L + 1 == R) last = true;
		}
		cout<<"Case "<<T<<": "<<R<<endl;
		sort(cmds.begin(), cmds.end());
		for(const auto& c : cmds) cout<<c<<endl;
		cout<<endl;
	}
	return 0;
}
//16492607	12742	Mining in Starcraft	Accepted	C++11	2.205	2015-11-26 02:07:13