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

void IO(){
    if(fopen("ellencute.inp", "r")) freopen("ellencute.inp", "r", stdin);
    else if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }
}

const ll INF = 1e18+7, N = 2e5+69, MOD = 1e9+7;
int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int adj[2002][2002], a[2002][2002];

void sol(){
    int n;
    cin >> n;
    cout << "? 1" << endl;

    vect<int> D(n+1, 1e9), cnt[n+1];
    D[0] = 1;

    int max_dep = 0;
    for(int i=1, j=1;n>=i;i++){
        cin >> D[i];
        a[1][i] = D[i];
        cnt[D[i]].eb(i);
        if(a[1][i] == 1)  adj[1][i] = adj[i][1] = 1;
    }

    int mn, c1=0, c0=0;

    for(int i=1;n>=i;i++){
        if(i&1)c1 += cnt[i].size();
        else c0 += cnt[i].size();
    }

    mn = c1<c0;

    for(int i=1;n>=i;i++){
        if(i%2 == mn){
            for(int j : cnt[i]){
                cout << "? " << j << endl;
                for(int f=1;n>=f;f++){
                    cin >> a[j][f];
                    if(a[j][f] == 1)
                        adj[j][f] = adj[f][j] = 1;
                }
            }
        }
    }

    cout << "!\n";
    for(int i=1;n>=i;i++) for(int j=i+1;n>=j;j++) if(adj[i][j])cout << i << ' ' << j << el;
    cout.flush();




}


signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();

    int t=1;
    // cin >> t;
    while(t--){sol();cout<<'\n';}   
}