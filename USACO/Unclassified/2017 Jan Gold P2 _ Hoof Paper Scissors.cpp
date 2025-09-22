#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int dp[100069][21][3];

int main() {
    freopen("hps.in", "r", stdin);
	freopen("hps.out", "w", stdout);

	int n, k;
	cin >> n >> k;
	char a[n];for(char& i : a)cin >> i;
	unordered_map<char, int> mp = {{'P', 0}, {'S', 1}, {'H', 2}};
	
	auto win = [&mp](char c){
	    int x = mp[c];
	    for(auto& i : mp)if(i.se == (x+1)%3)return i.fi;
	};
	
	
	
	dp[0][0][mp[win(a[0])]]=1;
	for(int i=1;n>i;i++){
	    for(int j=0;k>=j;j++){
	        for(auto& p : mp){
	            dp[i][j][p.se] = dp[i-1][j][p.se] + (p.fi == win(a[i]));
	            if(j){
	                for(auto& f : mp)
	                    dp[i][j][p.se] = max(dp[i-1][j-1][f.se] + (f.fi == win(a[i])),
	                                    dp[i][j][p.se]);
	            }
	        }
	    }
	}
	cout << max({dp[n-1][k][0], dp[n-1][k][1], dp[n-1][k][2]});

}
