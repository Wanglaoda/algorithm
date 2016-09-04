#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 100010;
int l[MAXN], r[MAXN], h[MAXN];

int main()
{
    int n;
    while(cin>>n&&n)
    {
        int i;
        for(i=1; i<=n; ++i)
        {
            scanf("%d", &h[i]);
            l[i]=r[i]=i;
        }

        for(i=2; i<=n; ++i)
            while (l[i] > 1 && h[i] <= h[l[i] - 1])
                l[i] = l[l[i] - 1];
        for(i=n-1; i>=1; --i)
            while (r[i] < n && h[i] <= h[r[i] + 1])
                r[i] = r[r[i] + 1];
        __int64 ans=0;
        for(i=1; i<=n; ++i)
            ans=max(ans, (__int64)(r[i]-l[i]+1)*h[i]);

        cout<<ans<<endl;
    }
    return 0;
}