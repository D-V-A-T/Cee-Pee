#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, c;
vector<vector<int>> dp(1069, vector<int>(1069, -1e9));
vector<int> graph[1069];

int32_t main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    
    auto sq = [](int n){
        return n*n;
    };
    
    cin >> n >> m >> c;
    int a[n+1];
    for(int i=1;n>=i;i++)cin >> a[i];
    for(int i=0;m>i;i++){
        int u,v;cin >> u >> v;
        graph[u].push_back(v);
    }
    
    dp[1][0] = 0;
    for(int d=1;1000>=d;d++){
        for(int u=1;n>=u;u++){
            for(int v : graph[u]){
                dp[u][d] = max(dp[u][d], dp[v][d-1] + a[u] + c*(sq(d-1) - sq(d)));
                
            }
        }   
    }
    cout << *max_element(dp[1].begin(), dp[1].end());
}
