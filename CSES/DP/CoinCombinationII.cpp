#include<iostream>
#include<cstring>
using namespace std;

const int MOD=1e9+7;

int p(int x){return x%2;}

void sol(){
    int n, k;
    cin >> n >> k;
    int a[n], dp[k+1];
    memset(dp, 0, sizeof(dp));
    for(int& i : a)cin >> i;
    dp[0]=1;
    for(int f=0;f<n;f++){
        for(int i = 1;i<=k;i++){
            if(i - a[f] >= 0) {
                dp[i] += dp[i-a[f]];
                dp[i] %= MOD;
            }
        }
    }
    cout << dp[k];
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int t=1;
//  cin >> t;
    while(t--)sol();
}