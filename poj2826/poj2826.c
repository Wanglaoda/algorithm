#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

const double eps=1e-8;

struct point{
    double x;
    double y;
};

struct line{
    point a;
    point b;
}l1,l2;

double ans;

//求叉积
double xmult(point p0 ,point p1 ,point p2){
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
int dblcmp(double n){
    if(fabs(n)<eps) return 0;
    return n>0?1:-1;
 }
//判断是否相交，如何相交
int judge(line l1 ,line l2){
    double d1=dblcmp(max(l1.a.x,l1.b.x)-min(l2.a.x,l2.b.x));
    double d2=dblcmp(max(l2.a.x,l2.b.x)-min(l1.a.x,l1.b.x));
    double d3=dblcmp(max(l1.a.y,l1.b.y)-min(l2.a.y,l2.b.y));
    double d4=dblcmp(max(l2.a.y,l2.b.y)-min(l1.a.y,l1.b.y));
    double d5=dblcmp(xmult(l2.a,l1.a,l1.b));
    double d6=dblcmp(xmult(l2.b,l1.a,l1.b));
    double d7=dblcmp(xmult(l1.a,l2.a,l2.b));
    double d8=dblcmp(xmult(l1.b,l2.a,l2.b));
    if(d1>=0&&d2>=0&&d3>=0&&d4>=0){
        if(d5*d6>0||d7*d8>0) return 0;//不相交
        else if(d5==0&&d6==0) return 1;//共线相交
        else if(d5==0||d6==0||d7==0||d8==0) return 2;//端点相交
        else return 3;//规范相交
    }
    return 0;
}

//求斜率
bool getslope(line l ,double &k){
    double t=l.a.x-l.b.x;
    if(t==0) return false;
    k=(l.a.y-l.b.y)/t;
    return true;
}

//求线段交点
point getIntersect(line l1, line l2) {
    point p;
    double A1 = l1.b.y - l1.a.y;
    double B1 = l1.a.x - l1.b.x;
    double C1 = (l1.b.x - l1.a.x) * l1.a.y - (l1.b.y - l1.a.y) * l1.a.x;
    double A2 = l2.b.y - l2.a.y;
    double B2 = l2.a.x - l2.b.x;
    double C2 = (l2.b.x - l2.a.x) * l2.a.y - (l2.b.y - l2.a.y) * l2.a.x;
    p.x = (C2*B1 - C1*B2) / (A1*B2 - A2*B1);
    p.y = (C1*A2 - C2*A1) / (A1*B2 - A2*B1);
    if(p.x==-0) p.x=0;
    return p;
 }

 //求a,b两点中y坐标更大的点
 point getbiggerY(point a ,point b){
     point q;
     if (dblcmp(a.y-b.y) > 0) {
        q.x = a.x;
        q.y = a.y;
    } else {
        q.x = b.x;
        q.y = b.y;
    }
     return q;
 }

double getarea(point p ,point p1 ,point p2){
    point q;
    double a;
    if(dblcmp(p1.y-p2.y)>=0) {
        q.y = p2.y;
        q.x = p.x+(p1.x-p.x)*(p2.y-p.y) / (p1.y-p.y); //求另一点的坐标
        a=fabs(xmult(p, p2, q)) / 2; //叉积求面积
    }
    else {
        q.y = p1.y;
        q.x = p.x+(p2.x-p.x)*(p1.y-p.y) / (p2.y-p.y);
        a=fabs(xmult(p, p1, q)) / 2;
    }
    return a;
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        point p1 ,p2 ,p;
        cin>>l1.a.x>>l1.a.y>>l1.b.x>>l1.b.y;
        cin>>l2.a.x>>l2.a.y>>l2.b.x>>l2.b.y;
        if(judge(l1,l2)<=1)//是否相交
            ans=0；
        else{
            p1=getbiggerY(l1.a ,l1.b);
            p2=getbiggerY(l2.a ,l2.b);
            p=getIntersect(l1 ,l2); 
            if(!dblcmp(p.x-p1.x)&&!dblcmp(p.y-p1.y) || !dblcmp(p.x-p2.x)&&!dblcmp(p.x-p2.y))//开口方向
                   ans=0;
            else{
                double k1 ,k2;
                bool f1 ,f2;
                f1 = getslope(l1, k1);
                f2 = getslope(l2, k2);
                if (!dblcmp(k1) || !dblcmp(k2)) ans=0;
                else if (f1 && f2) {//如果两条线都不与y轴平行
                    if (dblcmp(k1*k2) > 0) { //当两条线段的斜率符号相同时，
                        int d1 = dblcmp(k1-k2);
                        int d2 = dblcmp(k2);
                        if (d1>0&&d2>0&&dblcmp(p2.x-p1.x)*dblcmp(p2.x-p.x)<=0
                            || d1<0&&d2>0&&dblcmp(p1.x-p2.x)*dblcmp(p1.x-p.x)<= 0
                            || d1>0&&d2<0&&dblcmp(p1.x-p2.x)*dblcmp(p1.x-p.x)<= 0
                            || d1<0&&d2<0&&dblcmp(p2.x-p1.x)*dblcmp(p2.x-p.x)<= 0)//覆盖情况
                            ans = 0;
                        else 
                          ans=getarea(p,p1,p2);
                        }
                    else 
                        ans=getarea(p,p1,p2);
                    }
                else 
                        ans=getarea(p,p1,p2);
            }
        }
        printf ("%.2lf\n", ans);
    }
    return 0;
}