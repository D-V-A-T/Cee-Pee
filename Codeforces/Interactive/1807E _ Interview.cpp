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

void sol(){
	int n;
	cin >> n;
	int a[n];
	for(int& i : a)cin >> i;
	int l=0, r=n-1, pfs[n], ans;
	partial_sum(a,a+n,pfs);
	while(l <= r){
		int mid = (l+r)/2;
		cout << "? " << mid+1 << ' ';
		for(int i=0;mid>=i;i++)cout << i+1 << ' ';
		cout << endl;
		int x;cin >> x;
		if(x > pfs[mid]){
			ans = mid+1;
			r = mid-1;
		}else l = mid+1;
	}cout << "! " << ans << endl;

}


signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);cout.tie(NULL);
	IO();	
	int t=1;
	cin >> t;
	while(t--){sol();cout<<'\n';}	
}