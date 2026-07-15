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

#define FILE "SLIME"
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

void sol(){
    int n, k, X;
    cin >> n >> k >> X;

    array<int, 4> a[n];

    map<int, int> mp;

    for(auto &i : a){
        cin >> i[0] >> i[1] >> i[2] >> i[3];

        int st = i[3] + X / i[0] + (X % i[0] != 0);
        int peak = i[3] + i[2] / i[0] + (i[2] % i[0] != 0);
        // peak - y * i[1] < X
        // (peak - X) / i[1] < y
        int ed = ((peak-i[3]) * i[0] - X) / i[1];
        // while((peak-i[3]) - ed * i[1] >= X) ed++;
        // cout << st << ' ' << peak << ' ' << ed <<  el;
        ed = peak + ed;

        if(st > ed) continue;

        // cout << st << ' ' << ed << el;

        mp[st]++;
        mp[ed+1]--;
    }

    int pfs = 0, ans = 0;
    pii prev = {-1, -1};
    for(auto &i : mp){
        i.se += pfs;
        pfs = i.se;

        if(prev.se >= k){
            if(i.se >= k) ans += i.fi - prev.fi;
            else ans += i.fi - prev.fi - 1;
        }else{
            if(i.se >= k) ans++;
        }

        prev = i;
    }

    cout << ans;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    // cin >> t;
    while(t--) sol();
}