// UVa1001,Say Cheese, ACM/ICPC World Finals 2001
// 陈锋
#include<cassert>
#include<cstdio>
#include<cmath>
#include<functional>
#include<algorithm>
#include<cstring>
#include<vector>
#include<set>
using namespace std;
const int MAXN = 100 + 5;
const double eps = 1e-8;
int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
double read_double(){ double x; scanf("%lf", &x); return x; }
const double PI = acos(-1.0);
struct Point3 {
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }   
};

typedef Point3 Vector3;

Vector3 operator + (const Vector3& A, const Vector3& B) { return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector3 operator - (const Point3& A, const Point3& B) { return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); }
double Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector3& A) { return sqrt(Dot(A, A)); }

void readPoint3(Point3& p) {
    p.x = read_double();
    p.y = read_double();
    p.z = read_double();
}

struct Sphere{ 
    Point3 center; double radius; 
    void readin() {
        readPoint3(center);
        radius = read_double();
    }
    
    double Distance(const Sphere& rhs) {
        double ans = Length(center - rhs.center) - radius - rhs.radius;
        if(dcmp(ans) < 0) ans = 0;
        return ans * 10;
    }
};

Sphere S[MAXN];
double d[MAXN][MAXN];

int main()
{           
    int n, t = 1;
    while(scanf("%d", &n) == 1 && n > 0) {
        for(int i = 0; i < n; i++) S[i].readin();
        readPoint3(S[n].center); S[n++].radius = 0;        
        readPoint3(S[n].center); S[n++].radius = 0;
        
        for(int i = 0; i < n; i++)
        {
            d[i][i] = 0;
            for(int j = i+1; j < n; j++)
            {
                d[i][j] = d[j][i] = S[i].Distance(S[j]);
                // printf("n = %d, %d - %d: %.2lf\n",n,i,j, d[i][j]);
            }
        }
        
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
        
        printf("Cheese %d: Travel time = %.0lf sec\n", t++, d[n-1][n-2]);
    }
    return 0;
}

// 14805850	1001	Say Cheese	Accepted	C++	0.036	2015-01-15 10:13:16