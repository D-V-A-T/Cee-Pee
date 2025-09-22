#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define umap unordered_map
#define uset unordered_set
#define bend(v) v.begin(),v.end()
#define pob pop_back
#define lwb lower_bound
#define upb upper_bound
#define dbl long double
#define vect vector
#define pof pop_front
#define prq priority_queue
#define nextl cout << '\n'
#define el '\n'
#include<bits/stdc++.h>
#include <iostream>
#define int long long
#define mainrisa main
#define skibidi ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;

const int INF=9223372036854775807;
int MOD=1e9+7;	

int pw(int a, int b){
	int res=1;
	for(int i=0;b>i;i++)res*=a;
	return res;
}

int posmod(int a,int b){
	return ((a%b)+b)%b;
}

int __lcm(int a,int b){
	return a*b/__gcd(a,b);
}

void sol(){
	int q;
	cin >> q;
	umap<int, pair<int,int>> xorv; 
	umap<int,int> cnt;
	multiset<int> ms, nms, val;
	while(q--){
		int t;cin >> t;
		if(t==1){
			int x;cin >> x;
			xorv[x]={-1,-1};
			if(!cnt[x] && ms.size()){
				auto nupb=ms.upb(x), nlwb=nms.upb(-x);
				if(nupb != ms.end() && nlwb != nms.end()){
					int u=*nupb,l=abs(*nlwb);
					if(val.find(u^l)!=val.end())val.erase(val.find(u^l));
					val.insert(u ^ x);
					val.insert(l^x);
					xorv[x]={l,u};
					xorv[l].se=x;
					xorv[u].fi=x;
				}if(nupb == ms.end()){
					int l=abs(*nlwb);
					val.insert(l ^ x);
					xorv[x]={l, -1};
					xorv[l].se=x;
				}if(nlwb == nms.end()){
					int u=*nupb;
					val.insert(u ^ x);
					xorv[x]={-1, u};
					xorv[u].fi=x;
				}
			}else if(cnt[x] >= 1){
				val.insert(0);
			}
			ms.insert(x);
			nms.insert(-x);
			cnt[x]++;
		}else if(t==2){
			int x;cin >> x;
			cnt[x]--;
			if(!cnt[x]){
				int a=-1,b=-1;
				if(xorv[x].fi>-1)a=x ^ xorv[x].fi;
				if(xorv[x].se>-1)b=x ^ xorv[x].se;
				auto ita=val.find(a), itb=val.find(b);
				if(ita!=val.end())val.erase(ita);
				if(itb!=val.end())val.erase(itb);
				auto nupb=ms.upb(x), nlwb=nms.upb(-x);
				if(nupb == ms.end()){
					if(ms.size()-1){
						xorv[abs(*nlwb)].se=-1;
					}
				}if(nlwb == nms.end()){
					if(ms.size()-1){
						xorv[*nupb].fi=-1;
					}
				}if(nlwb != nms.end() && nupb != ms.end()){
					int u=*nupb,l=abs(*nlwb);
					xorv[u].fi=l;
					xorv[l].se=u;
					val.insert(u^l);
				}
			}else if(cnt[x] >= 1)val.erase(val.find(0));
			ms.erase(ms.find(x));
			nms.erase(nms.find(-x));
		}else cout << *val.begin() << el;
	}
}

signed mainrisa(){
	skibidi;
// 	freopen("","r",stdin);
//	freopen("","w",stdout);
	sol();
}