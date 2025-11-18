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
 
const ll INF=902337203695775807, N=3e5+69, MOD=1e9+7;    
 
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

int n, k, a[N];

struct Seggs{
    pii t[4*N];

    void build(int l=0, int r=n-1, int id=1){
        if(l == r){
            t[id] = {a[l], l};
            return;
        }
        int mid = (l+r)/2;
        build(l, mid, id*2);
        build(mid+1, r, id*2+1);
        t[id] = min(t[id*2], t[id*2+1]);
    }

    void upd(int p, int l=0, int r=n-1, int id=1){
        if(l > p || r < p) return;
        if(l == r){
            t[id] = {a[l], l};
            return;
        }
        int mid = (l+r)/2;
        upd(p, l, mid, id*2);
        upd(p, mid+1, r, id*2+1);
        t[id] = min(t[id*2], t[id*2+1]);
    }

    pii get(int i, int j, int l=0, int r=n-1, int id=1){
        if(l > j || r < i) return {INF, INF};
        if(i <= l && r <= j) return t[id];
        int mid = (l+r)/2;
        return min(get(i, j, l, mid, id*2), get(i, j, mid+1, r, id*2+1)); 
    }
} sgt;

struct Fick{
    vect<int> bit;
    Fick(){
        bit.rs(n+5);
    }
    void upd(int x, int v){
        for(;x<n;x|=x+1) bit[x] += v; 
    }
    int get(int x){
        int res = 0;
        for(;x>=0;x = (x & (x + 1)) - 1) res += bit[x];
        return res;
    }
};

void sol(){
    cin >> n >> k;
    for(int i=0;n>i;i++) cin >> a[i];
    vect<int> ans, dd(n+5, 1);
    
    sgt.build();
    Fick ft;
    for(int i=0;n>i;++i) ft.upd(i, 1);

    int l=0, r=0, cbd = 0;
    while(n > l){
        if(a[l] == INF){
            l++;
            continue;
        }
        if(l > r) r = l, cbd = 0;


        while(n > r+1 && cbd+dd[r] <= k){
            r++;
            cbd += dd[r];
        }
        while(r >= l && cbd > k){
            cbd -= dd[r];
            r--;
        }


        if(k == 0){
            for(int i=l;n>i;i++) if(dd[i]) ans.eb(a[i]);
            break;
        }else{
            int id, val;
            tie(val, id) = sgt.get(l+1, r);

            if(val < a[l]){
                ans.eb(val);
                a[id] = INF;
                sgt.upd(id);
                k -= ft.get(id)-1;

                cbd --;
                dd[id] = 0;
                ft.upd(id, -1);
            }
            else {
                ans.eb(a[l]);
                l++;

                cbd--;
                dd[l] = 0;
                ft.upd(l, -1);
            }
        }
    }   

    for(int i : ans) cout << i << ' ';
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