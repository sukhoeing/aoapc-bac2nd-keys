// Borrowers, ACM/ICPC World Finals 1994, UVa230
// 陈锋
#include<cassert>
#include<cstdlib>
#include<iostream>
#include<functional>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<map>
#include<set>
using namespace std;

struct Book {
    string title, author;
    Book(const string& t, const string& a) : title(t), author(a) {}
    bool operator<(const Book& rhs) const { return author<rhs.author || (author==rhs.author && title<rhs.title); }
};

vector<Book> books;
map<string, int> bookIndice;
struct indexComp {
    bool operator() (const int& lhs, const int& rhs) const {
        return books[lhs] < books[rhs];
    }
};

set<int, indexComp> shelf, lib;

void borrow(const string& t) {
    assert(bookIndice.count(t));
    int idx = bookIndice[t];
    if(lib.count(idx)) {
        lib.erase(idx);
    }else {
        assert(shelf.count(idx));
        shelf.erase(idx);
    }
}

void retBook(const string& t) {
    assert(bookIndice.count(t));
    int idx = bookIndice[t];
    assert(!lib.count(idx));
    assert(!shelf.count(idx));
    
    shelf.insert(idx);
}

void shelve() {
    for(set<int>::iterator it = shelf.begin(); it != shelf.end(); it++) {
        int idx = *it;
        set<int>::iterator pit = lib.insert(idx).first;
        if(pit == lib.begin())
            cout<<"Put "<<books[idx].title<<" first"<<endl;
        else {
            pit--;
            cout<<"Put "<<books[idx].title<<" after "<<books[*pit].title<<endl;
        }
    }

    shelf.clear();
    cout<<"END"<<endl;
}

int main()
{
    string buf;
    while(true) {
        getline(cin, buf);
        if(buf == "END") break;
        int spos = buf.find(" by ");
        assert(spos != string::npos);
        string title = buf.substr(0, spos), author = buf.substr(spos + 4);
        int idx = books.size();
        // cout<<"title = "<<title<<endl;
        bookIndice[title] = idx;        
        books.push_back(Book(title, author));
    }
    for(int i = 0; i < books.size(); i++)
        lib.insert(i);
    
    string cmd, title;
    while(true) {
        getline(cin, buf);
        if(buf == "END") break;
        cmd = buf.substr(0, 6);
        if(cmd[0] == 'S') shelve();
        else {
            title = buf.substr(cmd.size() + 1, buf.size() - cmd.size() - 1);
            if(cmd[0] == 'B') borrow(title);
            else { assert(cmd[0] = 'R'); retBook(title); }
        }
    }
    
    return 0;
}
/* 13471076	230	Borrowers	Accepted	C++	0.015	2014-04-09 08:54:55 */
