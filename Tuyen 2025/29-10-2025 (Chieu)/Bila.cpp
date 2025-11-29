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
#define int unsigned short
#define ll long long
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
#define FILE "ellencute"
 
const ll INF=902337203695775807, N=2e5+69, MOD=1e9+7;    
 
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

const char dx[] = {1, -1, 0 ,0}, dy[] = {0, 0, 1, -1};
int n, m, a[126][126], memo[126][126];

bool safe(int x, int y){
    return 1<=x && x<=n && 1<=y && y<=m;
}
    
int F(int x, int y){

    if(memo[x][y]) return memo[x][y];

    int mn = 65535, mx = 0;
    for(int i=0;4>i;i++){
        int nx = dx[i] + x, ny = dy[i] + y;
        if(safe(nx, ny) && a[nx][ny] < a[x][y]) mn = min(mn, a[nx][ny]);
    }

    for(int i=0;4>i;i++){
        int nx = dx[i] + x, ny = dy[i] + y;
        if(safe(nx, ny) && a[nx][ny] == mn) mx = max(mx, F(nx, ny));
    }

    return memo[x][y] = mx + 1;
}

void sol(){
    cin >> n >> m;
    for(int i=1;n>=i;i++) for(int j=1;m>=j;j++) cin >> a[i][j];

    pii ans = {0, 0};
    for(int i=1;n>=i;i++){
        for(int j=1;m>=j;j++){
            if(F(i, j) > ans.fi) ans.fi = F(i, j), ans.se = a[i][j];
            else if(F(i,j) == ans.fi) ans.se = min(ans.se, a[i][j]);
        }
    }

    cout << ans.fi << ' ' << ans.se;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    //cin >> t;
    while(t--)sol();
}