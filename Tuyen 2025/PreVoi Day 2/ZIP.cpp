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


#define FILE "ZIP"
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

int dt[101][101][27]; // dt[len][mod][character]

void sol(){
    int m, k, n;
    cin >> m >> k;
    string s;
    cin >> s;
    n = s.size();
    s = " " + s;

    for(int len=1;100>=len;len++){
        for(int i=1;n>=i;i+=len){
            for(int j=i;i+len-1>=j;j++){
                if(j > n) break;

                dt[len][j % len][s[j] - 'a']++;
            }
        }
    }

    while(m--){
        string w;
        cin >> w;
        int sz = w.size();
        w = " " + w;

        vect<int> v;

        int same = 0;

        for(int i=1;sz>=i;i++){
            int mod = i % sz;

            int max_possible = *max_element(dt[sz][mod], dt[sz][mod] + 27);

            same += dt[sz][mod][w[i] - 'a'];

            v.eb(max_possible - dt[sz][mod][w[i] - 'a']);
        }

        sort(bend(v), greater<int>());

        for(int i=0;min(v.size(), (size_t)k) > i;i++){
            same += v[i];
        }

        cout <<  n - same << el;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    // cin >> t;
    while(t--) sol();
}
