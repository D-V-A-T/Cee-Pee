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

const ll INF = 1e18+7, N = 2e6+69, MOD = 1e9+7;
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
	string ans;
	int pfs = 0, pre=0, cbd=1;
	for(int i=2;n>=i;i++){
		cout << "? " << 1 << ' ' << i << endl;
		int x;cin >> x;	
		if(!cbd){
			if(x > pfs) ans += '1';
			else ans += '0';
			pfs = x;
		}
		if(x>0 && cbd){

			// i-1-x so 1 o dau
			for(int j=0;i-pre-1-x>j;j++) ans += '1';
			for(int j=0;x>j;j++) ans += '0';
			ans += '1';
			pre = i;
			pfs = x;
			cbd=0;
		}
	}
	if(ans.size() < n)cout << "! IMPOSSIBLE" << endl;
	else cout << "! " << ans << endl;	
}


signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);cout.tie(NULL);
	IO();

	int t=1;
	cin >> t;
	while(t--){sol();cout<<'\n';}	
}