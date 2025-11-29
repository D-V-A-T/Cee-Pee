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
#define pii pair<ll,int>
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

int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int n, A, B, C, D;
string s;
int nxt[1000005], pre[1000005];
ll dist[1000005];

void dickcha(){
    prq<pii, vect<pii>, greater<pii>> pq;
    pq.push({0, 1});
    dist[1] = 0;
    int u;
    ll d;
    while(pq.size()){
        tie(d, u) = pq.top();
        pq.pop();
        if(dist[u] < d) continue;

        if(u-1 > 0 && dist[u-1] > d + B) {
            dist[u-1] = d + B;
            pq.push({dist[u-1], u-1});
        }

        if(u+1 <= n && dist[u+1] > d+A){
            dist[u+1] = d + A;
            pq.push({dist[u+1], u+1});
        }

        if(nxt[u] != -1 && dist[nxt[u]] > d + C){
            dist[nxt[u]] = d + C;
            pq.push({dist[nxt[u]], nxt[u]});
        }

        if(pre[u] != -1 && dist[pre[u]] > d + D){
            dist[pre[u]] = d + D;
            pq.push({dist[pre[u]], pre[u]});
        }
    }
}

void sol(){
    fill(dist, dist+1000005, LLONG_MAX/2);
    memset(nxt, -1, sizeof nxt);
    memset(pre, -1, sizeof pre);
    cin >> n >> A >> B >> C >> D;
    vect<int> ch(200, -1);

    cin >> s;
    s = "$" + s;
    for(int i=1;n>=i;i++){
        pre[i] = ch[s[i]];
        ch[s[i]] = i;
    }

    fill(bend(ch), -1);
    for(int i=n;i>0;i--){
        nxt[i] = ch[s[i]];
        ch[s[i]] = i;
    }

    dickcha();
    cout << dist[n];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    //cin >> t;
    while(t--)sol();
}