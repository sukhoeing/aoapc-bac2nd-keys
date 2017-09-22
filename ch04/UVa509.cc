// RAID!, ACM/ICPC World Finals 1997, UVa509
// 陈锋
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <bitset>
#include <functional>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int MAXD = 8;
int d, s, b, w;
char parity;
vector<int> disks[MAXD];

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for(int i = 0; i < v.size(); i++)
        os<<v[i]<<"";
    return os;
}

void tryRecover(const vector<int>& xPos, const vector<int>& pResult, string& content) {
    vector<int> pBits(w, parity == 'O');
    bool cErr = false;
    for(int i = 0; i < w; i++) {
        int xd = xPos[i];
        if(xd == -1) {
            if(pResult[i] != pBits[i]) {
                cErr = true;
                break;
            }
        }
        else {
            assert(disks[xd][i] == 'x');
            disks[xd][i] = pResult[i] ^ pBits[i];
        }
    }
    
    if(cErr) return;
    stringstream ss;
    ss<<uppercase<<hex;
        
    int bc = 0, pi = 0;
    bitset<4> bits;
    for(int i = 0; i < w; i += s) {
        for(int di = 0; di < d; di++) {
            if(di == pi) continue; // parity
            const vector<int>& disk = disks[di];
            for(int bi = i; bi < i + s; bi++) {
                if(bc == 4) {
                    bc = 0; 
                    ss<<bits.to_ulong();
                    bits.reset(); 
                }
                bits.set(4-bc-1, disk[bi]);
                bc++;
            }
        }
        pi = (pi+1)%d;
    }
    
    assert(bc <= 4 && bc > 0);
    ss<<bits.to_ulong();
    content = ss.str();
}

int main()
{
    string line;
    int t = 1;
    while(cin>>d && d > 0) {
        cin>>s>>b>>parity;
        w = s*b;
        vector<int> xPos(w, -1), pResult(w, 0);        
        
        bool unRecover = false, cError = false;
        for(int i = 0; i < d; i++) {        
            vector<int>& disk = disks[i];
            disk.clear();
            cin>>line;
            assert(line.size() == w);
            
            for(int x = 0; x < line.size(); x++) {
                if(unRecover) continue;                
                if(line[x] == 'x') {
                    disk.push_back('x');
                    if(xPos[x] != -1) unRecover = true;
                    else xPos[x] = i;
                } else {
                    int bit = line[x] - '0';
                    disk.push_back(bit);
                    pResult[x] ^= bit;
                }
            }
        }
        
        cout<<"Disk set "<<t++<<" is ";
        string content;
        if(!unRecover)
            tryRecover(xPos, pResult, content);
        
        if(content.empty())
            cout<<"invalid."<<endl;
        else
            cout<<"valid, contents are: "<<content<<endl;
    }
    return 0;
}

/* 13536535	509	RAID!	Accepted	C++	0.059	2014-04-23 08:40:00 */
