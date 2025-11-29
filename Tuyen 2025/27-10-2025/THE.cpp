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
#define FILE "the"
 
const ll INF=902337203695775807, N=3e5, MOD=998244353;    
 
void ffopen(){
    if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }else if(fopen("ellencute.inp", "r")){
        freopen("ellencute.inp", "r", stdin);
        freopen("ellencute.out", "w", stdout);
    }
}

int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

const int S = 600;
int pfs[S][N], ans[N];

void sol(){
    int n, k;
    cin >> n >> k;
    pfs[1][0] = 1;
    for(int i=1;n>=i;i++){
        vect<int> dp(S);
        for(int j=1;S>j;j++){
            dp[j] = pfs[j][i % (j+k-1)];    
            ans[i] = (ans[i] + dp[j]) % MOD;
        }
        for(int j=1;S>j;j++){
            pfs[j][i%(j+k-1)] += dp[j-1];
            pfs[j][i%(j+k-1)] %= MOD;
        }
    }
    for(int i=1;n>=i;i++) cout << ans[i] << ' ';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();

    int t=1;
    // cin >> t;
    while(t--)sol();
}