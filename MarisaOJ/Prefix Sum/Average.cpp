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
#define double long double
#define reimu inline 
#define skibidi ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;

const int INF=9223372036854775807;
int MOD=1e9+7;	

reimu int pw(int a, int b){
	int res=1;
	for(int i=0;b>i;i++)res*=a;
	return res;
}

reimu int posmod(int a,int b){
	return ((a%b)+b)%b;
}

reimu int __lcm(int a,int b){
	return a*b/__gcd(a,b);
}

//Given array A. Find the number of subarrays whose average is k

reimu void sol(){
	int n, k;
	cin >> n >> k;
	vect<int> v(n), pfs(n);
	umap<int,int> cntpfs;
	for(int i=0;n>i;i++){
		cin >> v[i];
//  if we subtract k from every elements, the problem turns into find the
//  number of subarrays whose sum is 0
		v[i]-=k;
	}pfs[0]=v[0];
	cntpfs[0]++;
	int ans=0;
	for(int i=0;n>i;i++){
		if(i)pfs[i]=pfs[i-1]+v[i];
		ans+=cntpfs[pfs[i]];
		cntpfs[pfs[i]]++;
	}cout << ans;
}

signed mainrisa(){
	skibidi;
// 	freopen("","r",stdin);
//	freopen("","w",stdout);
	sol();
}