// Intersecting Dates World Finals 2004 – Prague LA2997
// 陈锋
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#define _for(i,a,b) for( int i=(a); i<(b); ++i)
#define _rep(i,a,b) for( int i=(a); i<=(b); ++i)
using namespace std;
typedef vector<int> IVec;

int readint(){ int x; cin>>x; return x; }
int MDays[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; // 每个月的天数
bool isLeap(int y) { return (y%4==0 && y%100!=0) || y%400==0; }
int getMonthDay(int y, int m){ // y年的m月有共有几天
    assert(m>=1 && m<=12);
    return MDays[m] + ((m == 2 && isLeap(y)) ? 1 : 0);
}

struct Date {
    int year, month, day;
    bool operator<(const Date& d) const {
        if(year != d.year) return year < d.year;
        if(month != d.month) return month < d.month;
        return day < d.day;
    }
    
    bool operator==(const Date& d) const 
    { return year == d.year && month == d.month && day == d.day; }
    bool operator!=(const Date& d) const 
    { return !(*this == d); }
    
    Date(int x) : year(x/10000), month((x%10000)/100), day(x%100){} // x == YYYYMMDD
    Date(int y, int m, int d) : year(y), month(m), day(d) {
        int md = getMonthDay(y, m);
        assert(y >= 1700); assert(d >= 1 && d <= md);
    }
    
    Date& operator++() {
        if(++day > getMonthDay(year, month)){ // 下月
            day = 1;
            if(++month > 12) month = 1, ++year; // 下一年
        }    
        return *this;
    }        
};

ostream& operator<<(ostream& os, const Date& d) { return os<<d.month<<'/'<<d.day<<'/'<<d.year; }

vector<Date> allDates;
map<Date, int> dateIndice; // 每个日期的编号

void init() {
    Date d1(1700, 1, 1), d2(2100, 12, 31), d = d1;
    while(true){
        dateIndice[d] = allDates.size();
        allDates.push_back(d);
        if(d == d2) break;
        ++d;
    }
}

int main(){
    init();
    IVec dates(allDates.size()); // 所有日期是否已知的标志位
    set<int> uDates; // 未知数据的日期的编号
    for(int d1i, d2i, NX, NR, k = 1; cin>>NX>>NR && (NX || NR); k++){
        if(k > 1) cout<<endl;
        cout<<"Case "<<k<<":"<<endl;
        fill(dates.begin(), dates.end(), 0);
        uDates.clear();

        auto readDates = [&d1i, &d2i](){ // 读取两个日期，并且记录其编号到d1i, d2i
            cin>>d1i>>d2i;
            Date d1(d1i), d2(d2i);
            d1i = dateIndice[d1], d2i = dateIndice[d2];
            assert(d1i <= d2i);            
        };

        _for(i, 0, NX){
            readDates();
            _rep(j, d1i, d2i) dates[j] = 1; // 已知日期
        }
        
        _for(i, 0, NR){
            readDates();
            _rep(j, d1i, d2i) if(!dates[j]) uDates.insert(j); // 未知日期编号
        }
        
        if(uDates.empty()) {
            cout<<"    No additional quotes are required."<<endl;
            continue;
        }

        IVec range;
        auto outRange = [&range](){
            cout<<"    "<<allDates[range.front()];
            if(range.back() != range.front()) cout<<" to "<<allDates[range.back()];
            cout<<endl;
        };
        for(auto d : uDates){ // 对每个连续区间进行输出
            if(!range.empty() && d != range.back() + 1) outRange(), range.clear();                
            range.push_back(d);
        }
        outRange();       
    }
    return 0;
}

// LA2997: 1489168	2997	Intersecting Dates	Accepted	C++	0.489	2014-07-19 06:54:34