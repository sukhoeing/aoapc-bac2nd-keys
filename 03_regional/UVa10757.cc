// UVa10757 - interpreting SQL
// 陈锋
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

template<typename T>
struct MemPool {
    std::vector<T*> buf;
    T* createNew() {
        buf.push_back(new T());
        return buf.back();
    }
    
    void dispose() {
        for(int i = 0; i < buf.size(); i++) delete buf[i];
        buf.clear();
    }
};
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
struct StrIComp{ // 字符串的大小写无关比较
    bool operator()(const string& s1, const string& s2) const {
		auto p1 = s1.begin(), p2 = s2.begin();
		while(p1 != s1.end() && p2 != s2.end()){
			char c1 = toupper(*p1++), c2 = toupper(*p2++);
			if(c1 != c2) return c1 < c2;
		}
		if(p1 == end(s1) && p2 == end(s2)) return false;
		if(p1 == end(s1)) return true;
		if(p2 == end(s2)) return false;
		return *p1 < *p2;
	}

	bool eq(const string& lhs, const string& rhs) {
		return strcasecmp(lhs.c_str(), rhs.c_str()) == 0;
	}
};

typedef vector<string> Row, StrVec;
typedef Row* PRow;

struct ExpNode;
ExpNode *createExpNode(const string&);

struct Table {
	int M, N;
	StrVec colNames;
	vector<char> colTypes;
	map<string, int, StrIComp> colIndice;
	vector<Row> rows;

	void buildIndice(){
		colIndice.clear();
		_for(i, 0, M) colIndice[colNames[i]] = i;
	}

	void buildIndice(const string& col, map<string, vector<int> >& indice) {
		_for(i, 0, rows.size()) indice[getValue(rows[i], col)].push_back(i);
	}

	const string& getValue(const Row& row, const string& col) {
		assert(colIndice.count(col));
		return row[colIndice[col]];
	}
};

istream& operator>>(istream& is, Table& t) {
	is>>t.M>>t.N;
	t.colIndice.clear(); t.colNames.resize(t.M); t.colTypes.resize(t.M);
	_for(i, 0, t.M) is >>t.colNames[i]>>t.colTypes[i];
	t.buildIndice();
	t.rows.clear();
	_for(i, 0, t.N){
		t.rows.push_back(Row());
		_for(j, 0, t.M){
			string v; is >> v;
			t.rows.back().push_back(v);
		}
	}
	return is;
}

StrVec OPs = { "<=", ">=", "<>", "<", ">", "=" };

struct ExpNode{
	string name;
	bool isNot;
	ExpNode *left, *right;
	ExpNode() : left(NULL), right(NULL), isNot(false) {}

	ExpNode* init(const string& n){ name = n; return this; }
	int findOp(const string& src, const string& op) {  // 操作符可能两边没有空格直接在Token内部
		assert(op.size() == 1 || op.size() == 2);
		bool inStr = false;
		_for(i, 0, src.size()) {
			char c = src[i], nc = 0;
			if (i + 1 < src.size()) nc = src[i + 1];
			if (inStr){ if (c == '\"') inStr = false; }
			else {
				if (c == '\"') inStr = true;
				else if (c == op[0]) {
					if (op.size() == 1 || nc == op[1]) return i;
				}
			}
		}

		return -1;
	}

    // 操作符可能两边没有空格直接在Token内部
	bool continueParse(){
		int x = -1;
		string op;
		for(const auto& s : OPs){
			x = findOp(name, s);
			if (x == -1) continue;
			assert(x > 0 && x+1 < name.size());
			op = s;
			break;
		}

		if (x == -1) return false;
		left = createExpNode(name.substr(0, x));
		right = createExpNode(name.substr(x + op.size()));
		name = op;
		return true;
	}

	bool eval(Table *pt, Row& row) {
		bool ans;
		string lv, rv;
		if (left) {
			assert(right);
			lv = left->getValue(pt, row);
			rv = right->getValue(pt, row);
		}
		long li = 0, ri = 0;
		bool digit = !lv.empty() && isdigit(lv[0]);
		if (digit) {
			assert(!rv.empty() && isdigit(rv[0]));
			li = atol(lv.c_str()), ri = atol(rv.c_str());
		}

		if (name == "AND") ans = left->eval(pt, row) && right->eval(pt, row);
		else if (name == "OR") ans = left->eval(pt, row) || right->eval(pt, row);
		else if (name == "<") ans = digit ? li<ri : lv<rv;
		else if (name == "<=") ans = digit ? li<=ri : lv<=rv;
		else if (name == ">") ans = digit ? li>ri : lv>rv;
		else if (name == ">=") ans = digit ? li>=ri : lv>=rv;
		else if (name == "<>") ans = digit ? li!=ri : lv!=rv;
		else if (name == "=") ans = digit ? li==ri : lv==rv;
		else {
			if (continueParse()) ans = this->eval(pt, row);
			else assert(false);
		}

		if (isNot) ans = !ans;
		return ans;
	}

	string getValue(Table *pt, Row& row) {
		assert(!name.empty());
		if ((name == "AND" || name == "OR") && left && right) return "";
		if (name[0] == '\"') {
			assert(name.size() >= 2 && name[name.size() - 1] == '\"');
			return name.substr(1, name.size() - 2);
		}
		else if (isdigit(name[0])) {
			assert(all_of(begin(name), end(name), 
				[](char c){ return isdigit(c); }));
			return name;
		}
		else if (isalpha(name[0])){
			if (continueParse()) return getValue(pt, row);
			return pt->getValue(row, name);
		}
		return "";
	}
};

struct RowComp {
	const StrVec *ns;
	const vector<bool> *as;
	const vector<char> *types;
	Table *pt;
	int M;
	RowComp(Table* pTable, const StrVec *cols, const vector<bool> *ascs, const vector<char> *colTypes)
		: ns(cols), as(ascs), types(colTypes), M(cols->size()), pt(pTable) {
		assert(cols->size() == ascs->size());
		assert(cols->size() == colTypes->size());
	}

	bool operator() (const PRow &lhs, const PRow &rhs) const {
		_for(i, 0, M) {
			const string &lv = pt->getValue(*lhs, ns->at(i)), 
				&rv = pt->getValue(*rhs, ns->at(i));
			if (lv == rv) continue;
			if (types->at(i) == 'I') 
				return as->at(i) == (atol(lv.c_str()) < atol(rv.c_str()));
			return as->at(i) == (lv < rv);
		}
		return false;
	}
};

Table TS[24];
map<string, Table*, StrIComp> tables;
MemPool<Table> tablePool;
MemPool<ExpNode> nodePool;
StrIComp siCmp;
int K;

ExpNode *createExpNode(const string& n) { return nodePool.createNew()->init(n); }

ExpNode *parseWhere(const StrVec& tokens, int L, int R) {
	if (L == R) return NULL;
	if (L + 1 == R) return createExpNode(tokens[L]);	
	assert(R <= tokens.size());
	ExpNode *ep = NULL;

	int i1 = -1, i2 = -1, dep = 0, isNot = (tokens[L] == "NOT") ? 1 : 0;

	for (int i = R - 1; i >= L; i--) {
		const string& t = tokens[i];
		if (t == ")") dep++;
		else if (t == "(") dep--;
		else if (!dep && (t == "AND" || t == "OR"))
			i1 = i;
		else if (!dep && (find(OPs.begin(), OPs.end(), t) != OPs.end())) {
			i2 = i;
		}
	}

	if (i1 == -1 && i2 == -1){ // 在括号里面 
		ep = parseWhere(tokens, L + isNot + 1, R - 1);
		ep->isNot = isNot;
	}
	else if (i1 >= 0){ // 有一个AND 或者 OR
		assert(i1);
		ep = createExpNode(tokens[i1]);
		ep->left = parseWhere(tokens, L, i1);
		ep->right = parseWhere(tokens, i1 + 1, R);
	}
	else if (i2 >= 0) {
		assert(i2);
		ep = createExpNode(tokens[i2]);
		ep->left = parseWhere(tokens, L + isNot, i2);
		ep->right = parseWhere(tokens, i2 + 1, R);
		ep->isNot = isNot;
	}

	return ep;
}

ExpNode *parseWhere(const StrVec& whereTokens) {
	StrVec tokens;
	for (int wi = 0; wi < whereTokens.size(); wi++){
		const string& buf = whereTokens[wi];
		bool inStr = false;
		string t;
		_for(i, 0, buf.size()){
			char c = buf[i], nc = 0;
			if (i + 1 < buf.size()) nc = buf[i + 1];
			if (inStr) {
				if (c == '\\') {
					assert(i + 1 < buf.size());
					assert(nc == '\\' || nc == '\"');
					t.push_back(nc), i++;
				}
				else if (c == '\"') {
					assert(!t.empty());
					t += c; tokens.push_back(t); t.clear();
					inStr = false;
				}
				else t.push_back(c);
			}
			else {
				if (c == '\"') {
					inStr = true; t += c;
				}
				else if (c == '(' || c == ')') {
					if (!t.empty()) tokens.push_back(t);
					t.clear(); t += c;
					tokens.push_back(t); t.clear();
				}
				else t.push_back(c);
			}
		}

		if (!t.empty()) tokens.push_back(t);
	}
    
	if (tokens.empty()) return NULL;
	return parseWhere(tokens, 0, tokens.size());
}

Table* getJoinTable(const StrVec& tokens, int L, int R) {
	if (L + 1 == R) return tables[tokens[L]];

	int SZ = tokens.size(), dep = 0, ji = SZ, oi = SZ;
	_for(i, L, R){
		const string& t = tokens[i];
		string nt;
		if (i + 1 < R) nt = tokens[i + 1];
		if (t == "(") dep++;
		else if (t == ")") dep--;
		else if (!dep && siCmp.eq(t, "INNER") && siCmp.eq(nt, "JOIN")) {
			assert(ji == SZ);
			ji = i;
		}
		else if (!dep && t == "ON") {
			oi = i;
			assert(oi + 1 < R);
		}
	}

	if (ji == SZ) {
		assert(tokens[L] == "(" && tokens[R - 1] == ")");
		return getJoinTable(tokens, L + 1, R - 1);
	}

	assert(oi + 1 < R);
	assert(ji < oi);
	Table *plt = getJoinTable(tokens, L, ji), *prt = getJoinTable(tokens, ji + 2, oi), *pt = tablePool.createNew();
	assert(oi + 2 == R);
	const string& t = tokens[oi + 1];
	size_t ep = t.find('='); assert(ep != string::npos);
	string n1 = t.substr(0, ep), n2 = t.substr(ep + 1);
	pt->M = plt->M + prt->M; pt->N = 0;
	pt->colNames.resize(pt->M); pt->colTypes.resize(pt->M);
	copy(plt->colNames.begin(), plt->colNames.end(), pt->colNames.begin());
	copy(plt->colTypes.begin(), plt->colTypes.end(), pt->colTypes.begin());
	copy(prt->colNames.begin(), prt->colNames.end(), pt->colNames.begin() + plt->M);
	copy(prt->colTypes.begin(), prt->colTypes.end(), pt->colTypes.begin() + plt->M);
	pt->buildIndice();

	map<string, vector<int> > rcIndice;
	prt->buildIndice(n2, rcIndice);
	for(Row& lr : plt->rows){
		const string& v = plt->getValue(lr, n1);
		if (!rcIndice.count(v)) continue;

		for(auto& rri : rcIndice[v]) {
			pt->rows.push_back(lr);
			Row& nr = pt->rows.back();
			Row& rr = prt->rows[rri];
			assert(prt->getValue(rr, n2) == v);
			_for(m, 0, prt->M) nr.push_back(rr[m]);
			pt->N++;
		}
	}
	return pt;
}

void parseOrderTokens(const StrVec& orderTokens, const Table* pt,
	StrVec& cols, vector<bool>& ascs, vector<char>& types) {
	StrVec tokens;
	for(auto t : orderTokens){
		if (t[t.size() - 1] == ',') t.erase(t.size() - 1);
		tokens.push_back(t);
	}

	if (tokens.empty()) return;

	_for(i, 0, tokens.size()) {
		const string& t = tokens[i];
		bool isAsc = true;
		if (i + 1 < tokens.size()) {
			const string& at = tokens[i + 1];
			if (at == "DESCENDING") { isAsc = false; i++; }
			else if (at == "ASCENDING") i++;
		}
		cols.push_back(t);
		ascs.push_back(isAsc);
		types.push_back(pt->colTypes[pt->colIndice.find(t)->second]);
	}
}

void readAllTokens(StrVec& cols, StrVec& fromTokens, StrVec& orderTokens, StrVec& whereTokens){
	StrVec tokens;
	string line, buf;
	getline(cin, line);
	while (true) {
		getline(cin, line);
		if (line.empty()) break;
		stringstream ss(line);
		while (ss >> buf) {
			while (!buf.empty() && buf[0] == '('){
				tokens.push_back("(");
				buf.erase(0, 1);
			}

			int rp = 0;
			while (!buf.empty() && buf[buf.size() - 1] == ')') {
				rp++;
				buf.erase(buf.size() - 1, 1);
			}

			if (!buf.empty()) tokens.push_back(buf);
			for (int i = 0; i < rp; i++) tokens.push_back(")");
		}
	}

	int SZ = tokens.size(), oi = SZ, fi = SZ, wi = SZ;

	for (int i = SZ - 1; i >= 0; i--) {
		const string& t = tokens[i];
		string nt;
		if (i + 1 < SZ) nt = tokens[i + 1];
		if (t == "ORDER" && nt == "BY") {
			assert(oi == SZ);
			assert(i + 2 < SZ);
			oi = i;
			if (wi >= oi) wi = SZ;
		}
		else if (siCmp.eq(t, "WHERE") && i-1 > 0 && i+1 < oi && wi == SZ) {
			bool inOp = find_if(begin(OPs), end(OPs), [&tokens,&i](const string& op){
				return op == tokens[i-1] || op == tokens[i+1];
			}) != end(OPs);

			if (!inOp) wi = i;
		}
		else if (siCmp.eq(t, "FROM") && i + 1 < wi && fi == SZ) fi = i;
	}
	assert(fi < SZ && siCmp.eq(tokens[fi], "FROM"));

	_for(i, 1, fi) {
		string t = tokens[i];
		if (t != "*" && t[t.size() - 1] == ',') cols.push_back(t.substr(0, t.size() - 1));
		else cols.push_back(t);
	}

	fromTokens.assign(tokens.begin()+fi+1, tokens.begin() + min(wi, oi));
	if (wi < SZ) whereTokens.assign(tokens.begin() + wi + 1, tokens.begin() + oi);
	if (oi < SZ) orderTokens.assign(tokens.begin() + oi + 2, tokens.end());
}

int main(){
	int T; cin>>T;

	bool first = true;
	while (T--) {
		if (first) first = false; else cout << endl;
		tables.clear();
		cin>>K;
		_for(i, 0, K) {
			auto& t = TS[i]; string name;
			cin >> name >> t;
			tables[name] = &(t);
		}

		StrVec cols, fromTokens, orderTokens, whereTokens, orderCols;
		readAllTokens(cols, fromTokens, orderTokens, whereTokens);

		Table* pt = getJoinTable(fromTokens, 0, fromTokens.size());
		ExpNode *pe = parseWhere(whereTokens);
		vector<PRow> resultRows;
		for(auto& r : pt->rows)
            if (!pe || pe->eval(pt, r)) resultRows.push_back(&(r));

		vector<bool> orderAscs; vector<char> orderColTypes;
		parseOrderTokens(orderTokens, pt, orderCols, orderAscs, orderColTypes);
        if(!orderCols.empty())
            stable_sort(resultRows.begin(), resultRows.end(), 
            	RowComp(pt, &orderCols, &orderAscs, &orderColTypes));

		if (cols[0] == "*"){ assert(cols.size() == 1); cols = pt->colNames; }
        
		cout << cols.size() << " " << resultRows.size() << endl;

		for(auto& c : cols) {
			assert(pt->colIndice.count(c));
			c = pt->colNames[pt->colIndice[c]];
		}

		for(const auto& col : cols) cout<<col<<endl;
		for(auto pr : resultRows){
			_for(i, 0, cols.size()){
				if (i) cout << " ";
				cout<<pt->getValue(*pr, cols[i]);
			}
			cout<<endl;
		}
	}

	tablePool.dispose(), nodePool.dispose();
	return 0;
}

// 14578099	10757	Interpreting SQL	Accepted	C++	0.336	2014-11-24 14:03:41