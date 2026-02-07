#include<bits/stdc++.h>
#define ll long long
#define vect vector 
using namespace std;

const int MOD = 1e9+7;

struct DynamicMatrix{
	vect<vect<ll>> mat;
	size_t n, m;

	DynamicMatrix(int n, int m){
		this -> n = n;
		this -> m = m;
		mat.resize(n, vect<ll>(m));
	}

	auto & operator [](int id){
		return mat[id];
	}

	const auto & operator [] (int id) const{
		return mat[id];
	}

	DynamicMatrix operator * (const DynamicMatrix &o) const{
		const auto &a = mat;
		const auto &b = o.mat;

		assert(m == o.n);
		signed x = n, y = m, z = o.m;

		DynamicMatrix res(n, o.m);
		auto &c = res.mat;

		for(size_t i=0; x>i; i++){
			for(size_t j=0; y>j; j++){
				for(size_t k=0; z>k; k++){
					c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % MOD;
				}
			}
		}

		return res;
	}

	DynamicMatrix operator ^ (ll b) const{
		assert(n == m);
		DynamicMatrix base = *this;

		DynamicMatrix res(n, n);
		res.make_identity();


		while(b){
			if(b&1) res = res * base;
			base = base * base;
			b >>= 1;
		}

		return res;
	}

	void Fill(ll val){
		mat.assign(n, vect<ll>(m, val));
	}

	void make_identity(){
		assert(n == m);
		mat.assign(n, vect<ll>(m, 0));
		for(size_t i=0; n>i; i++) mat[i][i] = 1;
	}

	void print() const{
		for(size_t i=0; n>i; i++) for(size_t j=0; m>j; j++) cout << mat[i][j] << " \n"[j == m-1];
	}
};
