#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, k, dp[10069];

int32_t main() {
	freopen("teamwork.in", "r", stdin);
	freopen("teamwork.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	
	cin >> n >> k;
	int a[n];
	vector<int> pfs(n);
	for(int& i : a)cin >> i;
	partial_sum(a, a+n, pfs.begin());
	
	auto get = [&pfs](int l, int r){
	    return pfs[r] - (l ? pfs[l-1] : 0);
	};
	
	dp[0] = a[0];
	for(int i=1;n>i;i++){
	    int mx=-1;
	    for(int j=0;k>j;j++){
	        if(i-j < 0)break;
	        mx = max(mx, a[i-j]);
	   
	        if(i-j-1 < 0){
	            dp[i] = max(dp[i], mx*(j+1));
	            continue;
	        }
	        
	        dp[i] = max(dp[i], dp[i-j-1] + mx*(j+1));
	    }
	}
	cout << dp[n-1];
}
