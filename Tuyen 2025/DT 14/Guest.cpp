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
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
#define FILE "ellencute"
 
const ll INF=902337203695775807, N=2e5+69, MOD=1e9+7;    
 
void ffopen(){
    if(fopen(FILE".in", "r")){
        freopen(FILE".in", "r", stdin);
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

vect<pii> G[1005];
bool used[1005];

void sol(){
    int n;
    cin >> n;
    int a[n+1][n+1];
    for(int i=1;n>=i;i++){
        for(int j=i;n>=j;j++){
            int u = i-1, v = j;
            cin >> a[u][v];
            a[v][u] = a[u][v];
            G[u].eb(a[u][v], v);
            G[v].eb(a[u][v], u);
        }
    }

    used[0] = 1;
    prq<pii, vect<pii>, greater<pii>> pq;
    for(pii e : G[0]){
        pq.push(e);
    }

    int d, u;
    ll ans = 0;
    while(pq.size()){
        tie(d, u) = pq.top();
        pq.pop();
        if(used[u]) continue;
        used[u] = 1;
        ans += d;
        for(pii e : G[u]){
            if(!used[e.se]) pq.push(e);
        }
    }

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