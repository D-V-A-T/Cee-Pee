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

#define FILE "VENUE"
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

const ll N = 1e6 + 10, MOD = 1e9+7, INF = 1000000000000000069;

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

pii cac(set<int> &s){
    int x = *s.begin(), y = *s.rbegin();
    int mid = (x+y) / 2;
    return {max(mid - x, y - mid), mid};
}

void sol(){
    int n, m;
    cin >> n >> m;

    int a[n], b[n*2];

    for(int i=0; n>i; i++){
        cin >> a[i];
    }

    sort(a, a+n);
    for(int i=0; n>i; i++){
        b[i] = a[i];
        b[i+n] = a[i] + m;
    }

    set<int> s;

    int l = 0, r = 0;

    for(; r < n; r++){
        s.insert(b[r]);
    }
    r--;

    pii ans = cac(s);

    while(r+1 < n*2){
        s.insert(b[++r]);
        s.erase(b[l++]);

        // for(int i=l; r>=i; i++){
        //     cout << b[i] << ' ';
        // }nextl;

        ans = min(ans, cac(s));
    }

    cout << ans.fi << ' ' << (ans.se % m == 0 ? m : ans.se % m);

}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    // cin >> t;
    while(t--) sol();
}