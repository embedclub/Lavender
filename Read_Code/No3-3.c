#include<iostream>  
#include<string.h>  
using namespace std;  
int a[100][100];  
int dp[100][100];  
int m,n;  
  
void dp_fun(int x,int y)  
{  
    dp[x][y] = a[x][y];  
    int max = 0;  
    if(x > 0 && max < dp[x-1][y])  
    {  
        max = dp[x-1][y];  
    }  
    if(y > 0 && max < dp[x][y-1])  
    {  
        max = dp[x][y-1];  
    }  
    dp[x][y] += max;  
    if(x<m-1)  
    {  
        dp_fun(x+1,y);  
    }     
    if(y<n-1)  
    {  
        dp_fun(x,y+1);  
    }  
    return;  
}   
  
int main()   
{  
    memset(dp,0,sizeof(dp));   
    cin>>m>>n;  
    for(int i=0;i<m;i++)  
    {  
        for(int j=0;j<n;j++)  
        {  
            cin>>a[i][j];  
        }  
    }     
    dp_fun(0,0);  
    for(int i=0;i<m;i++)  
    {  
        for(int j=0;j<n;j++)  
        {  
            cout<<dp[i][j]<<"\t";  
        }  
        cout<<endl;  
    }  
    return 0;  
}  
