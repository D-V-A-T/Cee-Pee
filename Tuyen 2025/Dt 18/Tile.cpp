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

ll n, t;

void T1(){
    int F[n+5];
    memset(F, 0, sizeof F);
    F[0] = F[1] = 1;
    for(int i=2;n>=i;i++) F[i] = (F[i-1] + F[i-2]) % MOD;
    cout << F[n];    
}

void T2(){
    int F[n+5];
    memset(F, 0, sizeof F);
    F[0] = 1;
    for(int i=0;n>=i;i++)
        F[i+3] = 2 * F[i] % MOD;
    cout << F[n] << el;
}

using Matrix = vector<vector<ll>>;

Matrix mul(const Matrix &a, const Matrix &b) {
    int n = a.size();
    Matrix c(n, vector<ll>(n,0));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<n;k++) {
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    }
    return c;
}


vector<ll> mul(const Matrix &a, const vector<ll> &v) {
    int n = a.size();
    vector<ll> res(n,0);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            res[i] = (res[i] + a[i][j] * v[j]) % MOD;
    return res;
}

Matrix mat_pow(Matrix a, ll p) {
    int n = a.size();
    Matrix res(n, vector<ll>(n,0));
    for(int i=0;i<n;i++) res[i][i] = 1;
    while(p){
        if(p&1) res = mul(res,a);
        a = mul(a,a);
        p >>= 1;
    }
    return res;
}

void T3(){

    Matrix T = {
        {0,0,0,1},
        {1,0,1,0},
        {1,1,0,0},
        {1,1,1,1}
    };

    vector<ll> F1 = {1,0,0,1};

    if(n <= 1){
        cout << 1 << endl;
        return;
    }

    T = mat_pow(T, n-1);
    vector<ll> Fn = mul(T, F1);

    cout << Fn[3];
}

void sol(){
    cin >> n >> t;
    if(t == 1) T1();
    if(t == 2) T2();
    if(t == 3) T3();
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    //cin >> t;
    while(t--)sol();
}