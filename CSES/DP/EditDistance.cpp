#include<bits/stdc++.h>
#define int long long
#define vect vector
using namespace std;
 
int32_t main(){
	string a, b;
	cin >> a >> b;
	int n=a.size(), m=b.size();
	a=' '+a;
	b=' '+b;
	vect<vect<int>> dp(n+1, vect<int>(m+1, 1e9));
	for(int i=0;n>=i;i++)
		for(int f=0;m>=f;f++){
			if(!i)dp[i][f]=f;
			if(!f)dp[i][f]=i;
			if(!i || !f)continue;
			if(a[i] == b[f])dp[i][f]=min(dp[i][f], dp[i-1][f-1]);
			dp[i][f]=min({dp[i][f], dp[i-1][f]+1, dp[i][f-1]+1, dp[i-1][f-1]+1});
		}
	cout << dp[n][m];
}