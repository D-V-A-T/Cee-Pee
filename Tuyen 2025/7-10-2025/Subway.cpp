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
#define FILE "subway"
 
const ll INF=902337203695775807, N=2e5+69, MOD=1e9+7;    
 
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

namespace B3{
void sol(){
    int a, b, c;
    cin >> a >> b >> c;
    int coins = min(b, c/2) * 2;
    coins += a;
    if(coins >= c) cout << "YES\n";
    else cout << "NO\n";
}
};

namespace B1{
void sol(){
    int a, b, k;
    cin >> a >> b >> k;
    if(a < b) swap(a, b);
    if(k==1){
        if(a==b || b>=99) cout << "0\n";
        else cout << "-1\n";
        return;
    }

    int dih = a-b, ans = INF;   

    if(99 % k == 0){
        int tb = 99 / k;
        if(b >= tb){
            if(a - (b-tb) >= 99) ans = min(ans, b-tb);
        }
    }

    if(dih % (k-1) == 0 && dih >= k-1){
        int tb = dih / (k-1);
        if(dih + tb < 100 && b >= tb) ans = min(ans, b - tb); 
    }

    cout << (ans == INF ? -1 : ans) << el;

}
};

void sol(){
    B1::sol();
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    cin >> t;
    while(t--)sol();
}