#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int dp[25][15005];
int c[25],w[25];

int main()
{
    int n ,m ,i ,j ,k;

    while(cin>>n>>m){
        for(i=1;i<=n;i++)
            cin>>c[i];
        for(i=1;i<=m;i++)
            cin>>w[i];

        memset(dp,0,sizeof(dp));
        dp[0][7500]=1;

        for(i=1;i<=m;i++){
            for(j=0;j<=15000;j++)
                if(dp[i-1][j])
                    for(k=1;k<=n;k++)
                        dp[i][j+w[i]*c[k]] += dp[i-1][j];
        }

        cout<<dp[m][7500]<<endl;
    }
}