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
#define vect vector
#define pof pop_front
#define dbl long double
#define nextl cout << '\n'
#define el '\n'
#include<bits/stdc++.h>
#include <iostream>
#define int long long
#define mainrisa main
#define reimu inline 
#define skibidi ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;

const int INF=9223372036854775807;
int MOD=1e9+7;

vect<int> fact(1e7+69);

reimu void initfact(int lim){
	fact[0]=1;
	int f=1;
	for(int i=1;lim>=i;i++){
		f*=i;
		fact[i]=f%MOD;
	//	factdiv[i]=binpow(fact[i],MOD-2,MOD);
		f%=MOD;
	}
}

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

reimu int mul(int a ,int b ,int c){
//	(a*b) % c
	if(!b)return 0;
	int t=mul(a ,b/2 ,c)%c;
	if(b%2)return ((2*t)%c + a%c)%c;
	else return (2*t)%c;
}

reimu int binpow(int a ,int b ,int c){
	int result = 1;
    a = a % c; 
    while (b > 0) {
        if (b % 2 != 0) {
            result = (result * a) % c;
        }
        a = (a * a) % c;
        b /= 2;
    }
    
    return result;
}

reimu int divineDivide(int a,int b, int c){
//	(a/b)%c
	return ((a%c)*binpow(b,c-2,c))%c;
}

reimu string BinominalCoefficient1(int n, int k){
	initfact(1e6);
	fact[0]=1;
	int f=1;
	for(int i=1;1e6>=i;i++){
		f*=i;
		fact[i]=f%MOD;
		f%=MOD;
	}int q;
	cin >> q;
	while(q--){
		int n,k;
		cin >> n >> k;
		cout << (fact[n] * binpow((fact[n-k]*fact[k])%MOD,MOD-2,MOD))%MOD << el;
	}return "";
}

reimu int ForkAndKnife(){
	initfact(1e6);
	int n,a,b;
	cin >> a >> b >> n;
	return mul(divineDivide(fact[a],(fact[a-n]*fact[n])%MOD,MOD),
			divineDivide(fact[b],(fact[b-n]*fact[n])%MOD,MOD),MOD);
}

reimu string BinominalCoefficient2(){
	int q;
	cin >> q;
	while(q--){
		int n,k;
		cin >> n >> k;
		int nu=1,de=1;
		for(int i=n-k+1;n>=i;i++){
			nu=(nu*i)%MOD;
		}for(int i=1;k>=i;i++){
			de=(de*i)%MOD;
		}cout << divineDivide(nu,de,MOD) << el;
	}return "";
}

reimu int Equation(){
	int n,k,p;
	cin >> n >> k >> p;
	int idk=k*p;
	if(idk > n)return 0;
	initfact(2e6);
	return divineDivide(fact[k+(n-idk)-1],(fact[k-1]*fact[n-idk])%MOD,MOD);
}

reimu int ArrayRearrangement(){
	int n;
	cin >> n;
	umap<int,int> hash_map;
	int ans=1;
	initfact(1e6);
	for(int i=0;n>i;i++){
		int x;cin >> x;
		hash_map[x]++;
	}ans=fact[n];
	for(auto i : hash_map){
		ans=divineDivide(ans,fact[i.se],MOD);
	}return ans;
}

reimu int ValueOfSubsequences(){
	int n,k;
	cin >> n >> k;
	vect<int> v(n);
	for(int i=0;n>i;i++)cin >> v[i];
	sort(bend(v));
	initfact(1e5+69);
	int ans=0;
	for(int i=n-1;i>=0;--i){
		if(i >= k-1){
			ans+=mul((v[i]%MOD),divineDivide(fact[i],
										(fact[k-1]*fact[i-(k-1)])%MOD,
											MOD),MOD);
			ans%=MOD;
		}else break;
	}return ans;
}

reimu int Inequality(){
	int n,k,ans=0;
	cin >> n >> k;
	initfact(2e6);
	for(int i=0;n>=i;i++){
		ans+=divineDivide(fact[i+k-1],
						(fact[k-1]*fact[i])%MOD,MOD);
		ans%=MOD;
	}return ans;
}

reimu int GrowingMushroom(){
	int n,m;
	cin >> n >> m;
	if(m==1)return n;
	initfact(1e6);
	int idk=(n-m)-(m-1);
	return divineDivide(fact[idk+(m+1)-1],
				(fact[(m+1)-1]*fact[idk])%MOD,MOD);
}

reimu int BinaryMatrix(){
	int m,n;
	cin >> m >> n;
	int flandre=binpow(2,n,MOD),scarlet=binpow(2,n,MOD)-1;
	int sakuya=binpow(2,m,MOD),izayoi=binpow(2,m,MOD)-1;
	int Reimu=binpow(flandre,m,MOD)-binpow(scarlet,m,MOD);
	int Hakurei=flandre-scarlet;
	int Marisa=binpow(sakuya,n,MOD)-binpow(izayoi,n,MOD);
	int Kirisame=sakuya-izayoi;
	int Gensokyo=binpow(2,m*n,MOD);
	return posmod(Gensokyo
				-divineDivide(Reimu,Hakurei,MOD)
				-divineDivide(Marisa,Kirisame,MOD),
				MOD);
}

reimu int countwaysbb(int m, int n, int k){
	if(m < k || n<k)return 0;
	int ckn=divineDivide(fact[n], fact[k]*fact[n-k],MOD);
	int ckm=divineDivide(fact[m], fact[k]*fact[m-k],MOD);
	return (ckn*ckm*fact[k])%MOD;
}

reimu int BrokenBoard(){
	MOD=1e5+3;
	initfact(2e3+69);
	int a,b,c,d,k,ans=0;
	cin >> a >> b >> c >> d >> k;
	for(int x=0;k>=x;x++){
		for(int y=0;y+x<=k;y++){
			int z=k-x-y;
			int ways1=countwaysbb(a,b,x);
			int ways2=countwaysbb(c,d,y);
			int ways3=countwaysbb(a-x,d-y,z);
			ans+=ways1*ways2*ways3;
			ans%=MOD;
		}
	}return ans;
}

reimu int TrianglesCounting(){
	int m,n,reimubestwaifu=0;
	cin >> m >> n;
	for(int x=2;m>=x;x++){
		for(int y=2;n>=y;y++){
			int marisa=2*(x*y - (__gcd(x-1, y-1)+1))
						+ 2*(x+y-4) + 4*(x-2)*(y-2);
			reimubestwaifu+=marisa*(m-x+1)*(n-y+1);
		}
	}return reimubestwaifu;
}

reimu string RestrictedPath(){
	MOD=998244353;
	initfact(5e5+69);
	int n,q;
	cin >> n >> q;
	while(q--){
		int x,y;
		cin >> x >> y;
		int down=n-x, total=n-x + n-y;
		int a=divineDivide(fact[total],
		 (fact[down]*fact[total-down])%MOD,MOD);
		down=n+1-x;
		int b=0;
		if(total-down >= 0)
			b=divineDivide(fact[total],
				 (fact[down]*fact[total-down])%MOD,MOD);
		cout << posmod(a-b,MOD) << el;
	}
	return "";
}

reimu void sol(){
	cout << RestrictedPath();
}

signed mainrisa(){
	skibidi;
// 	freopen("","r",stdin);
//	freopen("","w",stdout);
	sol();
}