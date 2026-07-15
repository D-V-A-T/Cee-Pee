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
#define popcnt __builtin_popcountll
#define clz __builtin_clzll
#define ctz __builtin_ctzll
#define ull unsigned long long
#define ll long long 
#define dbl long double
#define int long long

#define FILE "TRAVEL"
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

const ll N = 3e5 + 10, MOD = 1e9+7, INF = 1000000000000000069;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll rand(ll l, ll r){
    return uniform_int_distribution<ll>(l, r)(rng);
}
ll pm(ll a,const int b=MOD){return (a%=b) < 0 ? a + b : a;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int n, F[N];
pii dp[N][2];
vect<int> G[N];

int B(int a, int b=MOD-2){
    int res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}


void init(int u){

    dp[u][0].se = dp[u][1].se = 1;
    dp[u][0].fi = dp[u][1].fi = 0;
}

void dfs(int u, int par){

    init(u);

    vect<pii> dih;
    int childcnt = G[u].size() - (par>0);
    dp[u][1].se = F[childcnt];
    vect<pii> sus;

    int I = B(childcnt);

    int cac = 1e9;

    for(int v : G[u]) if(v != par) {
        dfs(v, u);

        dp[u][1].se = dp[u][1].se * dp[v][1].se % MOD;
        dp[u][1].fi += dp[v][1].fi + 2;

        sus.eb(dp[v][0].fi - dp[v][1].fi - 1, dp[v][0].se * B(dp[v][1].se) % MOD);

        cac = min(cac, sus.back().fi);
    }

    if(sus.empty()) return;

    dp[u][0].fi = dp[u][1].fi + cac;

    dp[u][0].se = 0;



    for(pii i : sus){
        if(i.fi == cac){

            // if(u == 2) cout << "+\n";

            dp[u][0].se = (dp[u][0].se + dp[u][1].se * I % MOD * i.se % MOD) % MOD; 
        }
    }


    // if(u == 3){
    //     cout << "! " << dp[u][1].se << ' ' << dp[u][1].se * childcnt << ' ' << childcnt << el;
    // }
}

vect<int> cand;

pii diameter(int u, int par, int dep){
    pii vert = {dep, u};
    for(int v : G[u]) if(v != par){
        vert = max(vert, diameter(v, u, dep+1));
    }
    return vert;
}

void sub12(){
    int ans = 1e9, ways = 0;
    for(int i : cand){
        dfs(i, 0);

        // cout << i << ' ' << dp[i][0].fi << ' ' << dp[i][0].se << el;

        if(dp[i][0].fi < ans){
            ans = dp[i][0].fi;  
            ways = dp[i][0].se;
        }else if(dp[i][0].fi == ans){
            ways = (ways + dp[i][0].se) % MOD;
        }
    }

    int dih = diameter(diameter(1, 0, 0).se, 0, 0).fi;

    cout << min(2*(n-1) - dih, ans) << el << ways << el;
}

void Sub3(){
    dfs(2, 0);
    cout << dp[2][0].fi << el << dp[2][0].se * (n-1) % MOD << el;
}



void sol(){
    cin >> n;

    bool sub3 = 1;

    for(int i=1; n>i; i++){
        int u, v;
        cin >> u >> v;

        if(min(u, v) != 1) sub3 = 0;

        G[u].eb(v);
        G[v].eb(u);
    }   


    if(sub3){
        Sub3();
        return;
    }

    if(n <= 3000){
        for(int i=1; n>=i; i++) cand.eb(i);
        sub12();
        return;
    }

    int d1 = diameter(1, 0, 0).se, d2 = diameter(d1, 0, 0).se;
    cand.eb(d1);
    cand.eb(d2);
    sub12();

}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();

    F[0] = 1;
    for(int i=1; N>i; i++) F[i] = F[i-1] * i % MOD;

    int t = 1;
    // cin >> t;
    while(t--) sol();
}