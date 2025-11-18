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
 
const ll INF=902337203695775807, N=2e4, MOD=1e9+7;    
 
void ffopen(){
    if(fopen(FILE".in", "r")){
        freopen(FILE".in", "r", stdin);
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

const int SZ = 1e4+1;
int n, C, k;
vect<int> G[N], ans;
vect<pii> ss[N];
int dep[N], cd[N], sz[N], cnt[N], fumo[N], depthForBFS = -1;
// cd[i] : number of nodes with depth i

vect<int> compress(const vect<int>& a){
    map<int, int> cnt;
    for(int i : a) cnt[i]++;

    vect<int> v;
    for(auto& i : cnt){
        int b = 0, s = 0, lst = 0;
        while(s + (1<<b) <= i.se){
            s += 1<<b;
            v.eb((1<<b) * i.fi);
            lst = s;
            b++;
        }
        if(i.se-lst > 0) v.eb((i.se - lst) * i.fi);
    }

    return v;
}

void preDFS(int u, int par){
    for(int v : G[u]) if(v != par){
        dep[v] = dep[u] + 1;
        preDFS(v, u);
        sz[u] += sz[v];        
        ss[u].eb(v, sz[v]);
    }

    sz[u]++;
    cd[dep[u]]++;
    if(C == 1) fumo[u] = dep[u];
}

void preBFS(int u, int par){
    for(int v : G[u]) if(v != par){
        preBFS(v, u);
        sz[u] += sz[v];        
        ss[u].eb(v, sz[v]);
    }

    sz[u] += dep[u]==depthForBFS;
}

struct node{
    int u, par;
    bitset<SZ> F;
};

void DFS(int xxx, int yyy, bitset<SZ> F){

    stack<node> st;
    st.push({xxx, yyy, F});

    while(st.size()){

        auto [u, par, F] = st.top();

        st.pop();

        if(C==2 && dep[u] > depthForBFS) continue;

        vect<int> ws;
        for(auto [v, w] : ss[par]) if(v != u) ws.eb(w);

        ws = compress(ws);

        for(int w : ws) F |= F << w;

        bool condition = C==1 ? fumo[u] <= k : dep[u] == depthForBFS;

        if(condition && F[k - fumo[u] - (C==2)]) ans.eb(u);

        for(int v : G[u]) if(v != par){
            st.push({v, u, F});
        }
    }
}

void sol(){
    cin >> C >> n >> k;
    bitset<SZ> F;F[0] = 1;

    for(int i=1;n>i;i++){
        int u, v;cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    dep[1] = 1;
    preDFS(1, 0);
    int tmp = 0;
    for(int i=1;n>=i;i++){
        if(tmp + cd[i] >= k){
            depthForBFS = i;
            break;
        }
        tmp += cd[i];
    }

    if(C == 2){
        for(int i=0;n>=i;i++){
            sz[i] = 0;
            ss[i].clear();
        }
        preBFS(1, 0);
        partial_sum(cd, cd+N, cd);
        for(int i=1;n>=i;i++) fumo[i] = cd[dep[i]-1];
    }


    DFS(1, 0, F);

    sort(bend(ans));
    for(int i : ans) cout << i << ' ';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    //cin >> t;
    while(t--)sol();
}