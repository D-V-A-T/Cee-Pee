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

vect<int> P[10005], G[10001], D[10001];
int n, m, dp[101][10001], ans = 0;
// dp[i][j] : xet subtree i, co bao nhieu cach de dinh i co so chia het cho i

void DFS(int u, int par){
    for(int v : G[u]) if(v != par)
        DFS(v, u);
    

    int total = 0;
    for(int i=2;m>=i;i++){
        ll ways = 1;
        int sz = P[i].size();
        for(int v : G[u]) if(v != par){
            ll w = 0;
            for(int mask=1;1<<sz >mask;mask++){
                int lcm = 1;
                for(int j=0;sz>j;j++){
                    if(mask&(1<<j)){
                        lcm = __lcm(lcm, P[i][j]); 
                    }
                }

                w += popcnt(mask)&1 ? dp[v][lcm] : -dp[v][lcm];
                w = pm(w);
            }
            ways = ways * w % MOD;
        }

        if(u == 1) ans = (ans + ways) % MOD;

        for(int d : D[i]) dp[u][d] = (dp[u][d] + ways) % MOD;
    }
}


void sol(){
    cin >> n >> m;
    for(int i=1;n>i;++i){
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

    for(int i=1;1e4>=i;i++) for(int j=i;1e4>=j;j+=i) D[j].eb(i);

    for(int i=2;1e4>=i;i++){
        if(P[i].size()) continue;
        for(int j=i;1e4>=j;j+=i) P[j].eb(i);
    }

    int t=1;
    //cin >> t;
    while(t--)sol();
}