#include<iostream>

using namespace std;

#define MAX_N 100
#define MAX_M 100
int arr[MAX_M][MAX_N] = {0};
int dp[MAX_M][MAX_N] = {0};
int main(){
	int m, n;
	cin>> m >> n;
	int i, j;
	for(i = 1; i <= m; i++){
		for(j = 1; j <= n; j++){
			cin >> arr[i][j];
		}
	}
	for(i = 1; i <= m; i++){
		for(j = 1; j <= n; j++){
			dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] + arr[i][j] : dp[i][j-1] + arr[i][j];	
		}
	}
	cout<<dp[m][n]<<endl;
	return 0;	
}
