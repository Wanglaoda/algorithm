#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;

struct POINT
{
	int x,y;
	double angle;
}point[10010],stack[10010];
int n, top;
typedef struct POINT Point;

//欧氏距离
double Distance(Point p1, Point p2)
{
	return sqrt((double)((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

//叉积 op_sp × op_ep
double multily(Point sp, Point ep, Point op)
{
	return (double)((sp.x - op.x) * (ep.y - op.y) - (ep.x - op.x) * (sp.y - op.y));
}

//比较函数从小到大
int cmp(const void *a, const void *b)
{
	Point *c = (Point *)a;
	Point *d = (Point *)b;
	if (c->angle > d->angle)
	{
		return 1;
	}
	else if(c->angle < d->angle)
	{
		return -1;
	}
	else
		return (c->x * c->x + c->y * c->y) < (d->x * d->x + d->y * d->y) ? -1 : 1;
}

//求凸包
void Graham_scan()
{
	int i;
	stack[0] = point[0];
	stack[1] = point[1];
	stack[2] = point[2];
	for (i = 3; i < n; ++ i)
	{
		while (multily(point[i], stack[top], stack[top - 1]) > 0)
		{
			top --;
		}
		stack[++ top] = point[i];
	}
}

//求出凸包的面积
double getArea1()
{
	double sum = 0.0;
	int i;
	for (i = 0; i <= top; ++ i)
	{
		sum += (double)(stack[i].x * stack[(i + 1) % (top + 1)].y - stack[i].y * stack[(i + 1) % (top + 1)].x);
	}
	return sum / 2.0;
}

int main()
{
	double area1;
	int i, k;

	while(scanf("%d", &n) != EOF)
	{
		top = 2;
		k = 0;

		for (i = 0; i < n; ++ i)
		{
			scanf("%d %d", &point[i].x, &point[i].y);
		}
		for (i = 1; i < n; ++ i)
		{
			if (point[i].y < point[k].y || (point[i].y == point[k].y && point[i].x < point[k].x))
			{
				k = i;
			}
		}
		if (k)
		{
			Point tmp = point[0];
			point[0] = point[k];
			point[k] = tmp;
		}

		for (i = 1; i < n; ++ i)
		{
			point[i].angle = atan2((double)(point[i].y - point[0].y), (double)(point[i].x - point[0].x));
		}
		qsort(point + 1, n - 1, sizeof(point[0]),cmp);
		Graham_scan();

		area1 = fabs(getArea1());
		printf("%d\n", (int)(area1/50.0));

	}
	return 0;
}
