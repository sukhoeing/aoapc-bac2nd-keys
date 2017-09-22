// Exchange, ACM/ICPC NEERC 2006, UVa1598
// 陈锋
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <queue>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;

struct Order {
    bool buy;
    int size, price;
};

ostream& operator<<(ostream& os, const Order& o) { 
    return os<<"("<<o.price<<","<<o.size<<")"; 
}

const int MAXN = 10000 + 10;
int n, orderIndice[MAXN], canceled[MAXN];
vector<Order> orders;

template<typename Compare>
struct OrderQueue {
    typedef set<int, Compare> _IntSet;
    _IntSet eles;
    void erase(int x) { eles.erase(eles.find(x)); }
    bool empty() const { return eles.empty(); }
    int top() const { return *eles.begin(); }
    int pop() {
        int ans = *eles.begin();
        eles.erase(eles.begin());
        return ans;
    }
    void push(int oi) { eles.insert(oi); }
    int size() const { return eles.size(); }
    void clear() { eles.clear(); }
    int topPrice() { return orders[top()].price; }
    int topSize() { 
        int tp = topPrice(), ans = 0;
        for(auto i : eles){
            const Order& o = orders[i];
            if(o.price == tp) ans += o.size;
            else break;
        }
        return ans;
    }
};

struct BuyOrderCompare {
    bool operator() (int i, int j) {
        const Order &oi = orders[i], &oj = orders[j];
        return oi.price > oj.price || (oi.price == oj.price && i < j);
    }
};

struct SellOrderCompare {
    bool operator() (int i, int j) {
        const Order &oi = orders[i], &oj = orders[j];
        return oi.price < oj.price || (oi.price == oj.price && i < j);
    }
};

template<typename T>
ostream& operator<<(ostream& os, const OrderQueue<T> oq) {
    if(oq.eles.empty()) os<<"[]";
    for(auto i : oq.eles) os<<orders[i];            
    return os;
}

OrderQueue<BuyOrderCompare> buyQueue;
OrderQueue<SellOrderCompare> sellQueue;

void cancel(int ci) {
    int oi = orderIndice[ci];
    if(canceled[oi]) return;
    const Order& o = orders[oi];
    if(o.buy) buyQueue.erase(oi);
    else sellQueue.erase(oi);
    canceled[oi] = 1;
}

void trade(int oi) {
    Order& o = orders[oi];
    if(o.buy) {
        if(sellQueue.empty() || o.price < sellQueue.topPrice()) {
            buyQueue.push(oi);
            return;
        }
        
        int askPrice;
        while(!sellQueue.empty() && o.size > 0 && 
            o.price >= (askPrice = sellQueue.topPrice())) {
            int toi = sellQueue.top();
            Order& to = orders[toi];
            int tradeSize = min(o.size, to.size);
            cout<<"TRADE "<<tradeSize<<" "<<askPrice<<endl;
            to.size -= tradeSize;
            o.size -= tradeSize;
            sellQueue.pop();
            if(to.size == 0) canceled[toi] = 1;
            else sellQueue.push(toi);
        }
        
        if(o.size > 0) buyQueue.push(oi);
        else canceled[oi] = 1;
        return;
    }
    
    if(buyQueue.empty() || o.price > buyQueue.topPrice()) {
        sellQueue.push(oi);
        return;
    }
    
    int bidPrice;
    while(!buyQueue.empty() && o.size > 0 
        && o.price <= (bidPrice = buyQueue.topPrice())) {
        int toi = buyQueue.top();
        Order& to = orders[toi];
        
        int tradeSize = min(o.size, to.size);
        cout<<"TRADE "<<tradeSize<<" "<<bidPrice<<endl;
        to.size -= tradeSize;
        o.size -= tradeSize;
        buyQueue.pop();
        if(to.size == 0) canceled[toi] = 1;
        else buyQueue.push(toi);
    }
    
    if(o.size > 0) sellQueue.push(oi);
    else canceled[oi] = 1;
}

void quote() {
    int bidSize = 0, bidPrice = 0, askSize = 0, askPrice = 99999;
    
    if(!buyQueue.empty()) { bidSize = buyQueue.topSize(); bidPrice = buyQueue.topPrice(); }
    if(!sellQueue.empty()) { askSize = sellQueue.topSize(); askPrice = sellQueue.topPrice(); }
    
    cout<<"QUOTE "<<bidSize<<" "<<bidPrice<<" - "<<askSize<<" "<<askPrice<<endl;
}

void dbgPrintState() {
    cout<<"Buy Queue: "<<buyQueue<<endl;
    cout<<"Sell Queue: "<<sellQueue<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    string cmd;
    bool first = true;
    while(cin>>n) {
        if(first) first = false;
        else cout<<endl;    
        fill_n(orderIndice, n, -1), fill_n(canceled, n, 0);
        orders.clear(), buyQueue.clear(), sellQueue.clear();

        _for(i, 0, n){
            cin>>cmd;
            if(cmd == "CANCEL") {
                int x; cin>>x;
                cancel(x-1);
                quote();
                continue;
            }
            
            Order o;
            cin>>o.size>>o.price;
            o.buy = (cmd == "BUY");
            orderIndice[i] = orders.size();
            orders.push_back(o);
            trade(orderIndice[i]);
            quote();
        }
    }
    
    return 0;
}

// UVa : 13495076	1598	Exchange	Accepted	C++	2.482	2014-04-14 11:37:45
// La: 1432757	3706	Exchange	Accepted	C++	4.226	2014-04-14 11:36:25