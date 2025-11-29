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

void sol(){
    int n, b, k;
    cin >> n >> b >> k;

    vect<int> preP(n+1), ans(n+1); // preP[i] : position of index i in the previous permutation
    iota(bend(preP), 0);

    int base = 1, a[n+1], impossible = 0;
    for(int i=1;k>=i;i++){
        int num = 0;
        for(int j=1;n>=j;j++){
            cin >> a[j];
        }
        for(int j=2;n>=j;j++){
            if(preP[a[j]] < preP[a[j-1]]) num++;
            if(num >= b) impossible = 1;
            ans[a[j]] += num * base;
        }
        for(int j=1;n>=j;j++) preP[a[j]] = j; 

        base *= b;
    }

    if(impossible){
        cout << "-1\n";
        return;
    }

    for(int i=1;n>=i;i++) cout << ans[i] << ' ';
    nextl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    cin >> t;
    while(t--)sol();
}