// Angles and Squares, ACM/ICPC Beijing 2005, UVa1643
// 陈锋
#include<cassert>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<functional>
#include<algorithm>
#include<string>
#include<vector>
#include<set>
using namespace std;

struct Point{
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) {}
};
typedef Point Vector;

Vector operator+ (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator- (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator* (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
bool operator== (const Point& a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool operator< (const Point& p1, const Point& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }
bool operator> (const Point& p1, const Point& p2) { return !(p2<p2); }

istream& operator>>(istream& is, Point& p) { return is>>p.x>>p.y; }

int N;
Point A, B;
vector<double> Edges;

int main()
{           
    cout<<showpoint<<fixed<<setprecision(3);
    while(true) {
        cin>>N;
        if(!N) break;
        cin>>A>>B;
        double sl = 0, aa = 0;
        for(int i = 0; i < N; i++) {
            double l;
            cin>>l;
            sl+=l;
            aa += l*l/2;
        }
        double p = fabs(1/(A.x/A.y/(1+A.x/A.y) - B.x/B.y/(1+B.x/B.y)));
        // cout<<"p = "<<p<<", aa = "<<aa<<endl;
        double ans = p*sl*sl/2 - aa;
        cout<<ans<<endl;
    }
    return 0;
}
// 13740230	1643	Angle and Squares	Accepted	C++	0.012	2014-06-11 02:51:00
/*
推理过程
Cx/Cy = Ax/Ay
Dx/Dy = Bx/By
Cx+Cy = Bx+By = P

Cx/(P-Cx) = Ax/Ay
Cx = (P-Cx)*(Ax/Ay) 
Cx*(1+Ax/Ay) = P*Ax/Ay
Cx = P*Ax/Ay/(1+Ax/Ay)
Dx = P*Bx/By/(1+Bx/By)

Cx-Dx = l
P(Ax/Ay/(1+Ax/Ay) - Bx/By(1+Bx/By)) = sl
P*Ax/Ay/(1+Ax/Ay) - P*Bx/By/(1+Bx/By) = l
P(Ax/Ay(1+Ax/Ay) - Bx/By(1+Bx/By)) = l
*/