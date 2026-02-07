#include<bits/stdc++.h>
#define ll long long
#define vect vector 
using namespace std;

const int MOD = 1e9+7, max_mat_sz = 4;
int mat_sz = 2;

struct StaticMatrix{
	ll mat[max_mat_sz][max_mat_sz];
	size_t n = mat_sz;

	StaticMatrix(){
		memset(mat, 0, sizeof mat);
	}

	auto & operator [](int id){
		return mat[id];
	}

	const auto & operator [](int id) const{
		return mat[id];
	}

	StaticMatrix operator * (const StaticMatrix& o) const{
		StaticMatrix res;

		const auto &a = mat, &b = o.mat;
		auto &c = res.mat;

		for(size_t i=0; n>i; i++){
			for(size_t j=0; n>j; j++){
				for(size_t k=0; n>k; k++){
					c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % MOD;
				}
			}
		}

		return res;
	}

	StaticMatrix operator ^ (ll b) const{
		StaticMatrix base = *this, res;
		res.make_identity();

		while(b){
			if(b&1) res = res * base;
			base = base * base;
			b >>= 1;
		}

		return res;
	}

	void make_identity(){
		memset(mat, 0, sizeof mat);
		for(int i=0; n>i; i++) mat[i][i] = 1;
	}

	void Fill(ll val){
		for(auto &i : mat) fill(i, i + mat_sz, val);
	}


	void print() const{
		for(size_t i=0; n>i; i++) for(size_t j=0; n>j; j++) cout << mat[i][j] << " \n"[j == n-1];
	}
};

struct Vector{
	ll vec[max_mat_sz];
	size_t n = mat_sz;

	Vector(){
		memset(vec, 0, sizeof vec);
	}

	auto & operator [] (int id){
		return vec[id];
	}

	const auto & operator [] (int id) const{
		return vec[id];
	}

	Vector operator * (const StaticMatrix& o) const{
		Vector res;
		for(size_t j=0; n>j; j++){
			for(size_t k=0; n>k; k++){
				res[k] = (res[k] + vec[j] * o.mat[j][k]) % MOD;
			}
		}

		return res;
	}

	void Fill(ll val){
		fill(vec, vec+n, val);
	}

	void print(){
		for(size_t i=0; n>i; i++) cout << vec[i] << " \n"[i==n-1];
	}
};