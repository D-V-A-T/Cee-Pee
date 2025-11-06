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

reimu int getsum(int a, int b, int c,
				int d, vect<vect<int>>& pfs){
	int sa=0, sb=0, ss=0;
	if(a)sa=pfs[a-1][d];
	if(b)sb=pfs[c][b-1];
	if(a && b)ss=pfs[a-1][b-1];
	return pfs[c][d]+ss-sa-sb ;
}

//Given an 2D array A having n rows and n columns and each cell (i,j) has a value. For each cell (i,j), 
//calculate the sum of all cells having distance less or equal to k to it.

//The distance between cell (a,b) and cell (c,d) is calculated as following: |a−c|+|b−d|

reimu void sol(){
	int m, n, k;
	cin >> n >> k;
	m=n;
	vect<vect<int>> mat(2*n - 1, vect<int>(2*n -1)),
					vec(n, vect<int>(n)),
					pfs(2*n - 1, vect<int>(2*n -1));
//We see that if the matrix is rotated 45 degrees, the manhanttan distance 
//is now a square
//previous   *     | after  * *
//          ***    |         *
//           *     |        * *
	for(int i=0;m>i;i++)for(int f=0;n>f;f++)
		cin >> vec[i][f];
// rotate the matrix 45 degree
	for(int i=0;n>i;i++)
		for(int f=0;n>f;f++)
			mat[i+f][n-1+i-f]=vec[i][f];
	pfs[0][0]=mat[0][0];
	for(int i=1;2*n-1>i;i++)
		pfs[0][i]=pfs[0][i-1]+mat[0][i];
	for(int i=1;2*n-1>i;i++)
		pfs[i][0]=pfs[i-1][0]+mat[i][0];
	for(int i=1;2*m-1>i;i++){
		for(int f=1;2*n-1>f;f++){
			pfs[i][f]=pfs[i][f-1]+pfs[i-1][f]
						-pfs[i-1][f-1]+mat[i][f];
		}
	}vect<int> ans;
	for(int i=0;n>i;i++){
		for(int f=0;n>f;f++){
			int x=i+f, y=n-1+i-f;
			pair<int,int> start,end;
			start.fi=max(x-k, 0LL);
			start.se=max(y-k, 0LL);
			end.fi=min(x+k, 2*n-2);
			end.se=min(y+k, 2*n-2);
			cout << getsum(start.fi, start.se,
						end.fi, end.se,
						pfs) << ' ';
		}nextl;
	}
}

signed mainrisa(){
	skibidi;
// 	freopen("","r",stdin);
//	freopen("","w",stdout);
	sol();
}