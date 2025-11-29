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
	
	set<int> avail, tr = {1};
	for(int i=2;n>=i;i++)avail.insert(i);
	vect<pii> ans;

	while(1){
		int l = 1, r = *avail.begin();
		while(l != r){
			cout << "? " << l << ' ' << r << endl;
			int mid;cin >> mid;

			if(mid == l){
				ans.eb(l, r);
				tr.insert(r);
				avail.erase(r);
				break;
			}

			if(tr.find(mid) != tr.end()){
				l = mid;
			}else r = mid;
		}
		if(avail.empty()){
			cout << "! ";
			for(pii i : ans)cout << i.fi << ' ' << i.se << ' ';
			cout << endl;
			return;
		}
	}

}


signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);cout.tie(NULL);
	IO();	
	int t=1;
	cin >> t;
	while(t--){sol();cout<<'\n';}	
}