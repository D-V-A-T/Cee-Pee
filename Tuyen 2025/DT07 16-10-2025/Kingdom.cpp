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
 
const ll INF=902337203695775807, N=1e4+69, MOD=1e9+7;    
 
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

int mid, col[N], visited[N], ok, cc[N], in[N];
vect<int> G[N];

int BFS(int source){
    memset(col, 0, sizeof col);
    memset(visited, 0, sizeof visited);

    queue<int> que;
    que.push(source);
    int mxc = 0;

    while(que.size()){
        int u = que.front();
        cc[u] = 1;
        que.pop();
        if(visited[u]) continue;
        visited[u] = 1;
        int c = 1;

        sort(bend(G[u]), [](int& a, int& b){
            return col[a] < col[b];
        });

        for(int v : G[u])
            if(col[v] == c) c++;

        for(int v : G[u]) if(!visited[v]) que.push(v);

        col[u] = c;
        mxc = max(mxc, c);
    }

    return mxc;
}

void sol(){
    int n, m;
    cin >> n >> m;  
    int mxd = 0;

    for(int i=0;m>i;i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
        in[u]++;
        in[v]++;
        mxd = max({mxd, in[u], in[v]});
    }

    queue<int> que;

    int ans = 1e9, start;
    for(int i=1;n>=i;i++) if(in[i] == mxd) start = i;
    int fumo = 1;
    for(int i=start;n>=i;i++) if(!cc[i]){
        fumo = max(fumo, BFS(i));
    }
    for(int i=start;i>=1;i--)if(!cc[i]){
        fumo = max(fumo, BFS(i));
    }


    cout << fumo;

    // cout << ans;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    //cin >> t;
    while(t--)sol();
}   