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
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
 
const ll INF=902337203695775807, N=2e5+69, MOD=1e9+7;    
 
void ffopen(const string& file){
    if(file.empty())return;
    freopen((file + ".inp").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}
 
int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}
 
 
int dp[1069][1<<10], n, m, k, block[1069];
 
namespace godSol{
vect<vect<int>> cbd(1<<10);
// dp[i][mask] : so cach lat gach de hang i la mask va hang 1 -> i-1 da dc lat kin
// cbd : chua cac mask cua hang i-1 de co the lat kin i-1 va thanh mask cua hang i
 
bool fimi(int pre, int mask){
	for(int i=0;n>i;i++){
		if(pre&(1<<i))continue;
		if(mask&(1<<i))mask ^= 1<<i;
		else return 0;
	}
	for(int i=0;n>i;i++){
		if((mask&(1<<i))){
			if(i+1 >= n || !(mask&(1<<(i+1))))return 0;
			mask ^= 1<<i;
			mask ^= 1<<(i+1);
		}
	}
	return 1;
}
 
void cvd(){
	for(int mask=0;1<<n >mask;mask++){
		for(int pre=0;1<<n >pre;pre++){
			if(fimi(pre, mask))cbd[mask].eb(pre);
		}
	}
}
 
void sol(){
    cvd();
    for(int i=0;k>i;i++){
    	int x,y;
    	cin >> x >> y;
    	block[y] |= 1<<(x-1);
    }
 
    auto prnt = [](int mask){
    	string res;
    	for(int i=n-1;i>=0;i--){
    		res += !!(mask&(1<<i)) + '0';
    	}return res;
    };
 
    auto ok = [](int i, int mask){
    	return !((block[i] | mask) ^ mask);
    };
 
    for(int mask=0;1<<n >mask;mask++){
    	if(!ok(1, mask))continue;
    	dp[1][mask] = 1;
    	int cmask = mask;
    	if(mask == block[1]) continue;
    	for(int i=0;n>i;i++){
			if((cmask&(1<<i))){
				if(i+1 >= n || !(cmask&(1<<(i+1)))){
					dp[1][mask] = 0;
					break;
				}
				
				cmask ^= 1<<i;
				cmask ^= 1<<(i+1);
			}
		}
    }
    for(int i=2;m>=i;i++){
    	for(int mask=0;1<<n >mask;mask++){
    		if(!ok(i, mask))continue;
    		for(int j : cbd[mask ^ block[i]]){
    			if(ok(i-1, j))	
    				dp[i][mask] = (dp[i][mask] + dp[i-1][j]) % MOD;
    		}
    	}
    }
	
	cout << dp[m][(1<<n) - 1];
}
};
 
void sol(){
    cin >> n >> m >> k;
    godSol::sol();
 
}
 
 
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen("");
    int t=1;
    //cin >> t;
    while(t--)sol();
}