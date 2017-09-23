// UVa12566 - Melody “Creation”
// 陈锋 C++11
#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
/*
    为了保证字典序，选择从后向前递推
    状态 S ->{
        i - 已经确定i~N-1的每个音符以及是否变调，[0, i-1]还未确定
        j - 确定过的音符中出现了<=j次的 #/b
        k - 第i个音符在变调前是k个半音
    }
    dp[s] : 最少使用了几次变调，也就是几个'='?
    opt[s] : DP[s]是最优解时，第i位的音符字符串
    pj[j], pk[k] : DP[s]最优时，对应的i+1时的最优状态是 S(i+1, pj[j],pk[k])
*/
using namespace std;
const int MAXN = 104, INF = 0x3f3f3f3f, NS = 16;
vector<string> SYL[NS]; // 音高到音符的映射
unordered_map<string, int> STEP = { // 音符相对于1的音高
    {"1",  0}, {"#1", 1}, {"b2", 1}, {"2", 2}, {"#2", 3},
    {"b3", 3}, {"3", 4}, {"4", 5}, {"#4", 6}, {"b5", 6}, {"5", 7}, {"#5", 8},
    {"b6", 8}, {"6", 9}, {"#6", 10}, {"b7", 10}, {"7", 11}
};
void initSyls() { for (const auto& p : STEP) SYL[p.second].push_back(p.first); }
struct ACC { // 输入乐谱中的音符
    bool afterBar; // 是否在'|'之后
    int stepBefore, stepAfter; // 转调前后的音高(如果没有转调，二者相同)
    ACC() : afterBar(false), stepBefore(0), stepAfter(0) {}
};

int N, M;
vector<ACC> trans; // 输入的乐谱
int dp[MAXN][2 * MAXN][NS], pj[MAXN][2 * MAXN][NS], pk[MAXN][2 * MAXN][NS];
string opt[MAXN][2 * MAXN][NS];

void solve() {
    memset(dp, INF, sizeof(dp));
    memset(dp[N], 0, sizeof(dp[N])); // 还没确定任何音符，自然是0

    for (int i = N-1; i>=0; i--) _rep(j,0,M) _for(k,0,12) {
        // 依次考虑每个位置 j : 变调的次数，k : 12个音阶
        int delta = (trans[i + 1].stepBefore - trans[i].stepAfter + 12) % 12; // 音符之间的音阶
        if (j > 0 && dp[i][j - 1][k] != INF) {
            dp[i][j][k] = dp[i][j-1][k];
            opt[i][j][k] = opt[i][j-1][k];
            pj[i][j][k] = pj[i][j-1][k], pk[i][j][k] = pk[i][j-1][k];
        }

        for (const auto& sl : SYL[k]) { // 尝试step=k各种音符，进行变调
            string s = sl;
            int d = (sl.length() == 2), ni = i+1, nj = j-d, nk = (k+delta)%12;
            auto updateD = [&i, &j, &k, &s, &nj, &nk](int nd) { // 更新DP状态函数
                int &d = dp[i][j][k];
                if (nd < d || (nd == d && s <= opt[i][j][k]))
                    d = nd, opt[i][j][k] = s, pj[i][j][k] = nj, pk[i][j][k] = nk;
            };

            // 不变调，状态转移
            if (nj >= 0 && dp[ni][nj][nk] != INF) updateD(dp[ni][nj][nk]); 

            // 变调的状态转移
            _for(mk, 0, 12) for (const auto& msl : SYL[mk]) {                 
                s = sl + "=" + msl; // mk : 变调之后的音阶，msl变调后的音符
                ni = i+1, nj = j - (d+(msl.size()==2)), nk = (mk+delta)%12;
                if (nj >= 0 && dp[ni][nj][nk] != INF) updateD(dp[ni][nj][nk] + 1);
            }
        }
    }

    int ans = INF, k = 0;
    _for(i, 0, 12) {
        int d = dp[0][M][i];
        if (d == INF) continue;
        if (d < ans || (d == ans && opt[0][M][i] < opt[0][M][k])) ans = d, k = i;
    }

    function<void(int, int, int)> output = [&](int i, int j, int k) {
        if (i == N) return;
        cout << opt[i][j][k] << " ";
        if (trans[i].afterBar) cout << "| ";
        output(i + 1, pj[i][j][k], pk[i][j][k]);
    };
    output(0, M, k);
    cout << "||" << endl;
}

int main() {
    initSyls();
    int T; string s; ACC acc;
    scanf("%d", &T);
    _rep(t, 1, T) {
        cout << "Case " << t << ": "; cin >> M; trans.clear();
        while (cin >> s && s != "||") {
            if (s == "|") { trans.back().afterBar = true; continue; }
            size_t ep = s.find('=');
            if (ep != string::npos)
                acc.stepBefore = STEP[s.substr(0, ep)],
                acc.stepAfter = STEP[s.substr(ep + 1)];
            else
                acc.stepAfter = acc.stepBefore = STEP[s];
            trans.push_back(acc);
        }
        N = trans.size();
        trans.push_back(ACC());
        if (M > 2 * N) M = 2 * N; // 不可能超过2*N个符号
        solve();
    }
    return 0;
}
// 20051278	12566	Melody "Creation"	Accepted	C++11	0.130	2017-09-23 14:04:02