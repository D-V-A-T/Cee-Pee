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
#define FILE "tem"
 
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

int p3[100];

void sol(){
    int n, k;
    cin >> n >> k;

    vect<int> tem(40);
    int tn = n, buy = 0;
    for(int i=36;i>=0;i--){
        tem[i] = tn / p3[i];
        buy += tem[i];
        tn -= tem[i] * p3[i];
    }

    if(buy > k){
        cout << "-1\n";
        return;
    }

    for(int i=36;i>=0;i--){
        if(i>0 && tem[i]){
            // buy - change + 3 * change <= k
            int l = 0, r = tem[i], change;
            while(l <= r){
                int mid = (l+r)/2;
                if(buy - mid + 3*mid <= k){
                    change = mid;
                    l = mid+1;
                }else r = mid-1;
            }
            buy += change * 2;
            tem[i-1] += change * 3; 
            tem[i] -= change;
        }
    }

    int ans = 3 * tem[0];
    for(int i=1;36>=i;i++){
        ans += p3[i-1] * (i + 9) * tem[i];
    }
    cout << ans << el;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();

    p3[0] = 1;
    for(int i=1;36>=i;i++) p3[i] = p3[i-1] * 3;

    int t=1;
    cin >> t;
    while(t--)sol();
}
