#include<bits/stdc++.h>
using namespace std; 
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define umap unordered_map
#define prq priority_queue
#define vect vector
#define rs resize
#define bend(v) v.begin(),v.end()
#define pob pop_back
#define pof pop_front
#define lwb lower_bound
#define upb upper_bound
#define pii pair<int,int>
#define nextl cout << '\n'
#define el '\n'
#define deb cout<<"\nok\n";return 
#define ll long long
#define int long long
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
#define FILE "ellencute"
 
const ll INF=902337203695775807, N=2e5+69, MOD=1e9+7;    
 
void ffopen(){
    if(fopen(FILE".in", "r")){
        freopen(FILE".in", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }
    else if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }else if(fopen("ellencute.inp", "r")){
        freopen("ellencute.inp", "r", stdin);
        freopen("ellencute.out", "w", stdout);
    }
}

int pm(int a,const int b=MOD){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int dp[N][2][5], ans = 0;
vect<int> G[N];

void DFS(int u, int par){

    int c1 = 0, c2 = 0, notchild = 0;
    for(int v : G[u]) if(v != par){
        DFS(v, u);

        int One = dp[v][0][1] + dp[v][1][1], Two = dp[v][0][2] + dp[v][1][2];

        ans = (ans + One * c2) % MOD;
        ans = (ans + Two * c1) % MOD;
        ans = (ans + dp[v][0][2]) % MOD; // choose u 
        ans = (ans + dp[v][0][1] * notchild) % MOD;

        notchild = (notchild + dp[v][0][1]) % MOD;
        c2 = (c2 + One * c1 + Two) % MOD;
        c1 = (c1 + One) % MOD;

        dp[u][1][2] = (dp[u][1][2] + dp[v][0][1]) % MOD;
    }

    dp[u][0][1] = c1;
    dp[u][0][2] = c2;
    dp[u][1][1] = 1;
}

void sol(){
    int n;
    cin >> n;
    for(int i=1;n>i;i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    DFS(1, 0);

    cout << ans;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    //cin >> t;
    while(t--)sol();
}