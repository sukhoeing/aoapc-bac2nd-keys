// LA4749 Game Simulator
// 陈锋 C++11
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)

// #define DEBUG ABC
using namespace std;
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	for(const auto& e : v) os<<e<<"";
	return os;
}
vector<int> PItoTeam = {0, 1, 0 ,1}; // 队员所在的队
vector<string> Players = {"Alice", "Bob", "Charles", "David"}; // 队员
unordered_map<string, int> PlayersIndice = { {"Alice", 0}, {"Bob", 1}, {"Charles", 2}, {"David", 3} }; // 队员的编号
unordered_map<char, int> Ranks = { {'A', 14}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13} };
const string SUITS = "HSCD", RankStr = "XX23456789TJQKA";
const int RJ = 16, BJ = 15; // 大小王的值
int getRankValue(char c){ // 牌的面值
	if(isdigit(c)) return c - '0';
	assert(Ranks.count(c));
	return Ranks[c];
}
char getRankCh(int r){ assert(r >= 2 && r <= 14); return RankStr[r]; } // 面值反推牌面字符

struct Card {
	int suit, rank; // 牌的种类，面值
	Card(const string& buf) { init(buf); }
	Card() { init(-1, -1); }
	Card& init(const string& buf) {
		assert(buf.length() == 2);
		suit = 'O';
		if (buf == "RJ") rank = RJ;
		else if (buf == "BJ") rank = BJ;
		else suit = buf[0], rank = getRankValue(buf[1]);
		return *this;
	}
	Card& init(int s, int r) { suit = s; rank = r; return *this; }
	string toString() const {
		if (rank == BJ) return "BJ";
		if (rank == RJ) return "RJ";
		string buf;
		buf += tolower(suit);
		buf += getRankCh(rank);
		return buf;
	}
	bool operator==(const Card& c) const { return suit == c.suit && rank == c.rank; }
	bool operator!=(const Card& c) const { return !(*this == c); }
};
ostream& operator<<(ostream& os, const Card& c) { return os << c.toString(); }
namespace std {
    template <> struct hash<Card> { // Card的hash函数
    public :
	    size_t operator()(const Card &c ) const { return hash<int>()(c.suit) ^ hash<int>()(c.rank); }
    };
};

unordered_map<Card, int> cardsOrder, hiddenCards; // 牌面大小的指数，底牌及其张数
/*
	生成每张牌的大小值
*/
void genCardOrders(int CR, const char suit) {    
	int order = 110; Card c;
    auto addCard = [](const Card& c, int order){
        assert(!cardsOrder.count(c));
        cardsOrder[c] = order;
        hiddenCards[c] = 2;
        #ifdef DEBUG
        //    cout<<"> "<<c.toString()<<" - "<<order<<endl;
        #endif
    };
    
	cardsOrder.clear(), hiddenCards.clear();
	addCard(c.init("RJ"), order--), addCard(c.init("BJ"), order--);
	if (suit == 'O') {
		for (auto s : SUITS) addCard(c.init(s, CR), order); // 4个常主
		order--;
	}
	else {
		addCard(c.init(suit, CR), order--); // 花色常主
		for (auto s : SUITS) if (s != suit) addCard(c.init(s, CR), order); // 非花色常主
		order--;
		for (int r = getRankValue('A'); r >= 2; r--) // 花色非常主
			if (r != CR) addCard(c.init(suit, r), order--);
	}

	for (int r = getRankValue('A'); r >= 2; r--) { // 副牌
		if (r == CR) continue;
		for (auto s : SUITS) 
            if (s != suit) addCard(c.init(s, r), order);
		order--;
	}
}

typedef vector<Card> VC;
typedef VC::iterator VCI;
typedef VC::const_iterator CVCI;
vector<VC> Tricks; // 打出来的牌
char mainSuit;
int dealer, CR0, CR1, CR, CT, FT;
bool isTrump(const Card& c) { return c.rank == BJ || c.rank == RJ || c.rank == CR || c.suit == mainSuit; } // 主牌吗
bool isTractor(CVCI left, CVCI right) { // 是否是拖拉机
	int len = right - left;
	if (len % 2 != 0 || len < 4) return false;
	bool trump = isTrump(*left);
	for (int i = 0; i < len; i += 2) {
		if (trump) { // 必须都是主牌
			if (!isTrump(left[i])) return false; 
		}
		else { // 或者是同色的副牌            
			if (left[i].suit != left->suit || isTrump(left[i])) return false; 
		}
		if (left[i] != left[i+1]) return false; // 必须都是对子
		if (i > 0) { // 大小值必须连续
			if (cardsOrder[left[i]] != cardsOrder[left[i - 1]] + 1) return false; 
		}
	}
	return true;
}
bool isSimpleThrow(const VC& cards) { // 是否都是主牌 或者 同色副牌
	if (cards.size() == 1) return true;
	bool trump = isTrump(cards[0]);
	for (const auto& c : cards) {
		if (trump) { // 都是主牌
			if (!isTrump(c)) return false; 
		}
		else { // 都是同色副牌
			if (isTrump(c) || c.suit != cards[0].suit) return false; 
		}
	}    
	return true;
}
void getStruct(VC& cards, vector< VC >& ans) { // 拆首牌的结构
	assert(isSimpleThrow(cards));
	ans.clear();
	if (cards.empty()) return;
	if (cards.size() >= 4) { // 找拖拉机
		int TLen = cards.size();
		if (TLen % 2) TLen--; // 拖拉机的长度
		while (TLen >= 4) {
			int i = cards.size();
			while (i >= TLen) {
				VCI l = cards.begin() + i - TLen, r = l + TLen;
				if (isTractor(l, r)) {
					ans.push_back(VC(l, r));
					cards.erase(l, r);
					i -= TLen;
				}
				else {
					i--;
				}
			}
			TLen -= 2;
		}
	}

	int i = cards.size() - 1;
	while (i >= 0) {
		if (i > 0 && cards[i] == cards[i - 1]) {
			VCI l = cards.begin() + i - 1, r = l + 2;
			ans.push_back(VC(l, r));
			cards.erase(l, r);
			i -= 2;
		}
		else {
			i--;
		}
	}

	for (int i = cards.size() - 1; i >= 0; i--) { // 单牌
		VCI l = cards.begin() + i;
		ans.push_back(VC(l, l+1));
	}
}
// 按照首牌的结构进行构造, DFS
bool getStructDfs(VC& cards, const vector<VC>& lead, vector<VC>& ans, int ti){
	if(ti == lead.size()) {
		assert(ans.size() == lead.size());
		return true;
	}
	assert(ti < lead.size());
	int sLen = lead[ti].size();
	assert(sLen > 0 && cards.size() >= sLen);
	if(sLen > 2) assert(isTractor(lead[ti].begin(), lead[ti].end()));
	for (int i = cards.size(); i >= sLen; i--) {
		VCI l = cards.begin() + i - sLen, r = l + sLen;
		if ((sLen > 2 && isTractor(l, r)) || (sLen == 2 && *l == *(l+1)) || sLen == 1) { // 拖拉机，对子，单牌
			VC tr(l, r);
			ans.push_back(tr);
			cards.erase(l, r);
			if (getStructDfs(cards, lead, ans, ti+1)) return true;
			ans.pop_back();
			cards.insert(cards.begin()+i-sLen, tr.begin(), tr.end());
		}
	}
	return false;
}
// 按照首牌的结构进行构造
bool getStruct(const VC& cards, const vector<VC>& lead, vector<VC>& ans){
	ans.clear();
	VC buf(cards.begin(), cards.end());
	return getStructDfs(buf, lead, ans, 0);
}

// 一张牌有多少分呢？
int getScore(const Card& c){  return (c.rank == 5 || c.rank == 10 || c.rank == 13) ? (c.rank / 5) * 5 :  0; }
int getScore(const VC& cs){ int ans = 0; for(const auto& c : cs) ans += getScore(c); return ans; }
void toCards(const string& buf, VC& cards) { // 字符串解析成主牌
	assert(buf.length() % 2 == 0);
	cards.clear();
	Card c;
	for (int i = 0; i < buf.length(); i += 2) {
		c.init(buf.substr(i, 2));
		cards.push_back(c);
	}
}
void test(){ // 测试代码
    // 拖拉机判断测试
    VC ts;
    vector<string> tractors = {"CKCKCQCQCJCJCTCTC9C9C8C8C7C7C6C6C5C5C4C4C3C3C2C2"};
    for (const auto& s : tractors) {
        toCards(s, ts);
        sort(ts.begin(), ts.end(),
             [](const Card & c1, const Card & c2) { return (cardsOrder[c1] < cardsOrder[c2]); });
        cout << s << " is tractor ? - " << isTractor(ts.begin(), ts.end()) << endl;
    }
    
    // 首牌结构拆分测试
    tractors = {"CKCKCQCQCJCJCTCTC9C9C8C8C7C7C6C6C5C5C4C4C3C3C2C2" };
    vector< VC > ans;
    for(const auto& s : tractors){
        cout<<s<<" struct: "<<endl;
        toCards(s, ts);
        sort(ts.begin(), ts.end(),
             [](const Card & c1, const Card & c2) { return (cardsOrder[c1] < cardsOrder[c2]); });
        getStruct(ts, ans);
        for(auto& v : ans) cout<<v<<" | ";
        cout<<endl;
    }
}
void solve() {
    int tLead = dealer, ftScore = 0, w = 0;
   	vector<VC> st0, stf; // 首牌和跟牌的结构
    for(int i = 0; i < Tricks.size(); i += 4){
        VC p0(Tricks[i].begin(), Tricks[i].end());
        assert(isSimpleThrow(Tricks[i])); // 首牌结构一定是SimpleThrow(都是主牌或者同色的副牌)
        getStruct(p0, st0); // 拆分首牌的结构
        #ifdef DEBUG
        for(const auto& vv : st0) cout<<vv<<" | "; cout<<endl;
        #endif

        bool isLeadTrump = isTrump(Tricks[i][0]); // 首牌是主牌吗？
        int score = getScore(Tricks[i]), wp = 0, maxHornor = cardsOrder[st0.front().back()]; // 第wp个发牌的人是这一圈的赢家
		#ifdef DEBUG 
		cout<<tLead<<"->"<<Tricks[i]<<","<<maxHornor<<" ";
		#endif

		_for(pi, 1, 4){
            const VC& pCs = Tricks[i+pi];
            #ifdef DEBUG
            cout<<" | "<<(tLead+pi)%4<<"->"<<pCs<<",";
            #endif

            score += getScore(pCs);

            if(!isSimpleThrow(pCs)){
            	#ifdef DEBUG
            	cout<<" f-c-0-x";
            	#endif
             	continue; // 同时包含“主牌”和“副牌”或者是不同花色的副牌
            }

            if(isLeadTrump){
                if(!all_of(pCs.begin(), pCs.end(), isTrump)) {
                	#ifdef DEBUG
                	cout<<" f-c-1-x";
                	#endif
                	continue;
                }
            } else { // 如果首牌都是副牌并且之后某个人的跟牌包含同首牌不同颜色的副牌，这个人不是赢家
                if(!isTrump(pCs[0]) && pCs[0].suit != Tricks[i][0].suit) {
                	#ifdef DEBUG
                	cout<<" f-c-2-x";
                	#endif
                	continue;
                }                   
            }
            
            if(!getStruct(pCs, st0, stf)) continue; // 如果某人的跟牌无法构造成和首牌一样的结构，这个玩家也不能是赢家。
            int hornor = cardsOrder[stf.front().back()]; // 最长结构的最大牌
            
            #ifdef DEBUG
            cout<<"h:"<<hornor<<" ";
            #endif

            if(hornor > maxHornor){
            	wp = pi;
            	maxHornor = hornor;
            }
        }

        tLead = (tLead + wp) % 4; // 这一圈第几个人最大？
        if(PItoTeam[tLead] == FT) ftScore += score;
        w = st0[0].size();
        #ifdef DEBUG
       	printf("\nWinPlayer:%d, Team:%d, TScore:%d, FT:%d, w=%d\n\n", tLead, PItoTeam[tLead], score, ftScore, w);
        #endif
    }


    if(PItoTeam[tLead] == FT) // 计算底牌的得分
    	for(const auto& p : hiddenCards)
    		if(p.second > 0) {
    			ftScore += (1<<w)* p.second * getScore(p.first);
    			#ifdef DEBUG
    			cout<<" hidden : "<<p.first<<" &"<<p.second;    
    			#endif			
    		}

    int kCT = 0, kFT = 0, make = ftScore < 80;
    if(ftScore == 0) kCT = 3;
    else if(ftScore < 40) kCT = 2;
    else if(ftScore < 80) kCT = 1;
    else kFT = (ftScore - 80) / 40; // FT要升K级
    if(CT == 0)  CR0 += kCT, CR1 += kFT; // 队0是CT
    else CR0 += kFT, CR1 += kCT; // 队1是CT

    cout<<ftScore<<endl;
    if(CR0 > 14) cout<<"Winner: Team 1"<<endl;
    else if(CR1 > 14) cout<<"Winner: Team 2"<<endl;
    else {
    	cout<<getRankCh(CR0)<<" "<<getRankCh(CR1)<<" "; // 0, 1, 2, 3
    	if(make) dealer = (dealer + 2) % 4; // 保级
    	else dealer = (dealer + 1) % 4; // 下台了
    	cout<<Players[dealer]<<endl;
    }
}

int main() {
	int T; cin>>T;
	string buf, line; Card c;
	_rep(t, 1, T){
		cout<<"Case #" << t << ":" << endl;
		cin >> mainSuit >> buf; dealer = PlayersIndice[buf];
		CT = PItoTeam[PlayersIndice[buf]]; FT = !CT;
		cin>>buf; CR0 = getRankValue(buf[0]);
		cin>>buf; CR1 = getRankValue(buf[0]);
		CR = (CT == 0) ? CR0 : CR1;

		#ifdef DEBUG
		printf("-----CR0:%d, CR1:%d, CR:%d, suit:%c, dealer %s-%d, FT : %d, CT: %d\n", 
			CR0, CR1, CR, mainSuit, Players[dealer].c_str(), dealer, FT, CT);
		#endif
		getline(cin, line);
		assert(line.empty());
		Tricks.clear();
		genCardOrders(CR, mainSuit);
		while(getline(cin, line) && !line.empty()) {
			stringstream ss(line);
			VC ts;
			while (ss >> buf) {
				toCards(buf, ts);
                sort(ts.begin(), ts.end(), // 对所有的牌从小到大排序
                    [](const Card & c1, const Card & c2) { return (cardsOrder[c1] < cardsOrder[c2]); });
                Tricks.push_back(ts);
				for (const auto& c : ts) hiddenCards[c] = hiddenCards[c] - 1;
			}			
			assert(Tricks.size()%4 == 0);
		}
		solve();
	}
	return 0;
}
// 1879697	4749	Game Simulator	Accepted	C++11	0.006	2015-12-11 06:48:24