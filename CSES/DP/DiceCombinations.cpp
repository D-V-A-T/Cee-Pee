#include<iostream>
#include<cstring>
#define int long long
using namespace std;

const int MOD=1e9+7;

void sol(){
	int n;
	cin >> n;
	int dp[n+1];
	memset(dp, 0, sizeof(dp));
	dp[0]=1;
	for(int i=1;n>=i;i++){
		for(int f=1;6>=f;f++){
			if(i-f >= 0)dp[i]=(dp[i]+dp[i-f])%MOD;
		}
	}cout << dp[n];
}

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int t=1;
//	cin >> t;
	while(t--)sol();
}