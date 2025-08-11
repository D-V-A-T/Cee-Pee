#include<iostream>
#include<cstring>
#define int long long
using namespace std;

const int MOD=1e9+7;

void sol(){
	int n, k;
	cin >> n >> k;
	int dp[k+1], a[n];
	memset(dp, 0x3f, sizeof(dp));
	for(int& i : a)cin >> i;
	dp[0]=0;
	for(int i=1;k>=i;i++){
		for(int f : a){
			if(i-f >= 0) dp[i]=min(dp[i], dp[i-f]+1);
		}
	}cout << (dp[k] <= 1e6 ? dp[k] : -1);
}

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int t=1;
//	cin >> t;
	while(t--)sol();
}