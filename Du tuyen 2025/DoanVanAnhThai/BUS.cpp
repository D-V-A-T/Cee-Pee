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

#define FILE "BUS"
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

int n, m, q, indeg[N], dist[N], visited[N];
vect<int> G[N];
vect<pii> E[N];

void sol(){
    cin >> n >> m >> q;

    vect<pii> edges;

    for(int i=0; m>i; i++){
        int u, v;
        cin >>u >> v;
        G[u].eb(v);
        G[v].eb(u);
        edges.eb(u, v);
    }

    queue<int> que;
    que.push(1);
    memset(dist, 5, sizeof dist);
    dist[1] = 0;

    while(que.size()){
        int u = que.front();
        que.pop();

        if(visited[u]) continue;
        visited[u] = 1;

        for(int v : G[u]) if(!visited[v]) {
            if(dist[v] > dist[u] + 1){
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }


    int ei = 0;
    map<pii, int> mp;

    for(int i=1; n>=i; i++){
        for(int j : G[i]){
            if(dist[j] == dist[i] + 1){
                E[i].eb(j, ++ei);
                mp[{i, j}] = ei;
                indeg[j]++;
            }
        }
    }

    int ans = n-1;

    vect<int> seen(m+5), used(m+5);


    while(q--){
        int idx;
        cin >> idx;
        idx--;

        // cerr << idx << ' ' << m << el;
        // assert(idx < seen.size());

        if(seen[idx]){
            cout << ans << el;
            continue;
        }
        seen[idx] = 1;

        int x = edges[idx].fi, y = edges[idx].se;
        if(dist[x] > dist[y]) swap(x, y);

        if(dist[x] + 1 != dist[y] || (indeg[x] <= 0 && x != 1)){
            cout << ans << el;
            continue;
        }


        assert(que.empty());

        if(--indeg[y] == 0) que.push(y);
        used[mp[{x, y}]] = 1;


        while(que.size()){
            int u = que.front();
            que.pop();
            ans--;
            // cerr << u << el;

            for(pii p : E[u]){
                int v = p.fi, idx = p.se;
                // cout << u << ' ' << v << ' ' << indeg[v] << el;
                if(used[idx]) continue;
                used[idx] = 1;
                if(--indeg[v] == 0){
                    que.push(v);
                }
            }
        }

        cout << ans << el;
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