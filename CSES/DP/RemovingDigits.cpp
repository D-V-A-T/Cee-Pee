#include<iostream>
#include<cstring>
using namespace std;

const int MOD=1e9+7;

int dp[3000001];

bool check(int x, int a){
    while(x){
        if(x%10 == a)return 1;
        x/=10;
    }return 0;
}

void sol(){
    int n;
    cin >> n;
    memset(dp, 0x3f, sizeof(dp));
    dp[n]=0;
    for(int i=n;i>=0;i--){
        for(int f=1;9>=f;f++){
            if(check(i+f, f))dp[i]=min(dp[i], dp[i+f]+1);
        }
    }cout << dp[0];
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int t=1;
//  cin >> t;
    while(t--)sol();
}