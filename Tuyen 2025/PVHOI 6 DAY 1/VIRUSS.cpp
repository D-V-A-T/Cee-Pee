#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pii pair<int, int>
#define bend(v) v.begin(),v.end()
#define vect vector 
#define prq priority_queue
#define umap unordered_map
#define eb emplace_back
#define pb push_back
#define pob pop_back
#define ef emplace_front
#define pf push_front
#define pof pop_front
#define el "\n"
#define deb cout<<"\nok\n";return 
#define nextl cout<<"\n"
#define lwb lower_bound 
#define upb upper_bound
#define rs resize
#define popcnt __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define ll long long 
#define dbl long double


#define FILE "VIRUSS"
void IO(){
    if(fopen(FILE".in", "r")){
        freopen(FILE".in", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }
    else if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }
}

const ll N = 3e5 + 69, MOD = 1e9+7, INF = 1000000000000000069;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll rand(ll l, ll r){
    return uniform_int_distribution<ll>(l, r)(rng);
}
ll pm(ll a,const ll b=MOD){return ((a%b)+b)%b;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

void sol(){
    int n, e, k;
    cin >> n >> e >> k;
    int dp[n+2][k+2];

    for(auto& i : dp) fill(i, i+k+2, MOD);

    pii a[n+5];
    for(int i=1;n>=i;i++){
        cin >> a[i].fi >> a[i].se;
    }

    dp[0][0] = 0;
    for(int i=1;n>=i;i++){
        for(int j=0;k>=j;j++){
            // ko bo co gai thu i
            int start_time = max(a[i].fi, dp[i-1][j]);
            int end_time = start_time + a[i].se;
            dp[i][j] = start_time + a[i].se;

            if(j == 0) continue;    
            // bo co gai thu i
            dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
        }
    }

    int ans = 0;
    for(int i=0;n>=i;i++){
        for(int j=0;k>=j;j++){
            int lo = dp[i][j], hi = i + (k-j) + 1 <= n ? a[min(n, i + (k-j) + 1)].fi : e;
            // cout << i << ' ' << j << ' ' << hi << ' ' << lo << el;
            ans = max(ans, hi - lo);
        }
    }

    cout << ans << el;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    cin >> t;
    while(t--) sol();
}