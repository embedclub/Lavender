#include<iostream>  
#include<string.h>  
using namespace std;  
int a[100][100];  
int dp[100][100];  
int m,n;  
  
void dp_fun(int x, int y)
{
	dp[x][y] = a[x][y];
	int max = 0;
	if(x > 0 && max < dp[x-1][y])
	{
		max = dp[x-1][y];
	}
	

}
