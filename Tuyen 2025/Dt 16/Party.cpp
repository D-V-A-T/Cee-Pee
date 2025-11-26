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
#define int long long
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
#define FILE "ellencute"
 
const ll INF=902337203695775807, N=2e5+69, MOD=1e9+7;    
 
void ffopen(){
    if(fopen(FILE".in", "r")){
        freopen(FILE".in", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }
    else if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
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


int B(int a, int b=MOD-2){
    int res = 1;
    while(b){
        if(b&1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int d[205], n, SUB1[205];
const int SUB2[] = {0,0,571428577,401574811,68575102,347470132,149707164,295038330,246944817,168459846,848759170,753916649,874259235,436845857,455803345,732110426,912252260,380931639,725126576,755085026,497747095,601032270,132018618,195747679,326166778,90750519,950969612,561147124,716973945,398359507,245333203,645374876,58517764,882537570,387870120,174478760,770163916,657328870,392199940,752435265,596273060,880391751,607922078,465118232,314990412,429160328,670114601,83625202,713881005,807523234,400261067,826581252,770146593,608067344,280418783,20107917,573628670,767615667,381834390,980680016};
vect<int> G[205];

void join(int u, int v){
    G[u].eb(v);
    G[v].eb(u);
}

void buildtree(int id){
    if(id > n) return;
    if(id*2 <= n) join(id, id*2);
    if(id*2+1 <= n) join(id, id*2+1);
    buildtree(id*2);
    buildtree(id*2+1);
}

void dfs(int u, int par){
    for(int v : G[u]) if(v != par){
        d[v] = d[u]+1;
        dfs(v, u);
    }
}

int tree_size(int dep, int max_dep){
    int len = max_dep - dep + 1;
    return pm(B(2, len) - 1);
}

ll lg2(ll i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void sol(){
    cin >> n;

    if(n <= 200) cout << SUB1[n] << el;
    else cout << SUB2[lg2(n)+1] << el;

}

void s1(){
    for(n=1;200>=n;n++){
        for(int i=0;n>=i;i++) G[i].clear();

        buildtree(1);

        int nu = 0, de = B(2, n) - 1;

        for(int i=1;n>=i;i++){
            d[i] = 0;
            dfs(i, 0);
            sort(d+1, d+n+1);
            for(int j=1;n>=j;j++) nu = (nu + d[j] * B(2, n-j)) % MOD;
        }

        SUB1[n] = nu * B(de) % MOD;

        // cout << nu << ' ' << de << el;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();

    s1();

    int t=1;
    cin >> t;
    while(t--)sol();
}