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

#define FILE "INTERSECT"
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

const ll N = 3e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

int intersex(pii a, pii b){
    if(a.fi > b.fi) swap(a, b);
    if(a.se < b.fi) return 0;
    if(a.se >= b.se) return b.se - b.fi;
    return a.se - b.fi;
}

void sol(){
    int n, k;
    cin >> n >> k;

    ll dp[2][k+n+5];
    pii a[n][2];
    memset(dp, 0x3f, sizeof dp);


    int cac = 0, add = 0;

    for(auto &i : a){
        cin >> i[0].fi >> i[0].se >> i[1].fi >> i[1].se;
        if(i[0].fi > i[1].fi) swap(i[0], i[1]);

        int is = intersex(i[0], i[1]);
        cac += is;

        if(is){
            add += max(i[0].se, i[1].se) - i[0].fi - is;
        }
    }

    // cout << cac << ' ' << add << el;
    
    // cout << "! " << k << el;


    for(int i=0; min(cac, k) >=i; i++) dp[0][i] = 0;

    // cout << "! " << k << el;



    for(int i=1; k>=cac+i && add>=i; i++){
        dp[0][cac+i] = i;
    }



    int curr = 0, nxt = 1;

    // deb;

    for(int i=0; n>i; i++){
        if(intersex(a[i][0], a[i][1])) continue;

        memset(dp[nxt], 0x3f, sizeof dp[nxt]);

        for(int j=0; k>=j; j++){
            pii mx = {a[i][0].fi, max(a[i][0].se, a[i][1].se)};
            int val = mx.se - mx.fi;

            int sus = a[i][1].fi - a[i][0].se;

            val = min(val, k - j);

            // if(i == 1){
            //     cout << val << ' ' << sus << ' ' << k-j << ' ' << val + sus + 1 + dp[curr][j] << ' ' << dp[curr][j] << el;
            // }

            dp[nxt][j] = min(dp[nxt][j], dp[curr][j]);
            dp[nxt][j + val] = min(dp[nxt][j + val], dp[curr][j] + val + sus);
        }


        // cerr << dp[curr][7] << el;

        swap(curr, nxt);
    }


        // cout << dp[curr][1] << ' ' << k << el;
    int ans = 1e9;

    for(int i=1; k>=i; i++){
        ans = min(ans, dp[curr][i] + (k - i) * 2);
        // if(dp[curr][i] + (k-i)*2 == 5) cout << i << ' ' << dp[curr][i] << el;

    }

    cout << ans << el;

}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    // cin >> t;
    while(t--) sol();
}