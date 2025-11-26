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

int squdigit(int n){
    int sum = 0;
    while(n){
        sum += sq(n%10);
        n /= 10;
    }return sum;
}

void sol(){
    int a, v, n, ans = 0;
    cin >> a >> v >> n;
    umap<int, int> seen;
    vect<int> p, cyc;
    while(!seen.count(a)){
        seen[a] = p.size();
        p.eb(a);
        a = squdigit(a);
    }


    for(int i=0;seen[a] > i && n>0;i++) ans += p[i] == v, n--;
    for(int i=seen[a];p.size()>i;i++) cyc.eb(p[i]);


    int full = count(bend(cyc), v);
    int cntfull = n / cyc.size();
    ans += full * cntfull;



    int remain = n - (cntfull * cyc.size());
    for(int i=0;remain>i;i++) ans += cyc[i%cyc.size()] == v;
    cout << ans << el;


}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    cin >> t;
    while(t--)sol();
}