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
#define FILE "skibiditoilet"
 
const ll INF=902337203695775807, N=5e5+69, MOD=1e9+7;    
 
void ffopen(){
    if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
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

struct fumo{
	int val, st, ed, curr;
	bool operator < (const fumo& o) const{
		return val < o.val;
	}
};

int lg2[N];
pii spt[N][20];

void sol(){
	int n, k, L, R;
	cin >> n >> k >> L >> R;
	
	prq<fumo> pq;
	
	int a[n+1], pfs[n+1];
	a[0] = pfs[0] = 0;
	
	spt[0][0] = {0, 0};
	for(int i=1;n>=i;i++){
		cin >> a[i];
		pfs[i] = pfs[i-1] + a[i];
		spt[i][0] = {pfs[i], i};
	}
	
	for(int b=1;20>b;b++){
		for(int i=0;n+1>=i+(1<<b);i++){
			spt[i][b] = min(spt[i][b-1], spt[i + (1<<(b-1))][b-1]);
		}
	}
	
	auto get = [&](int l, int r){
		int b = lg2[r-l+1];
		return min(spt[l][b], spt[r - (1<<b) + 1][b]);
	};	
	
	for(int i=L;n>=i;i++){
		int st = max(0ll, i-R), ed = i-L;
		pii p = get(st, ed);
		pq.push({pfs[i] - p.fi, st, ed, p.se});
	}
	
	int ans = 0, got = 0;
	while(got<k){
		auto [val, st, ed, curr] = pq.top();
		pq.pop();
		ans += val;
		got++;
		
		if(st < curr){
			int ned = curr-1;
			pii p = get(st, ned);
			int nwval = val + (get(st, ed).fi) - p.fi;
			pq.push({nwval, st, ned, p.se});
		}
		
		if(curr < ed){
			int nst = curr+1;
			pii p = get(nst, ed);
			int nwval = val + (get(st, ed).fi) - p.fi;
			pq.push({nwval, nst, ed, p.se});
		}
	}
	
	cout << ans;
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);cout.tie(NULL);
	lg2[0] = lg2[1] = 0;
	for(int i=2;N>i;i++) lg2[i] = lg2[i/2] + 1;
	int t=1;
	// cin >> t;
	while(t--) sol();
}