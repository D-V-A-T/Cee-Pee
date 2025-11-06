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
#include<bits/stdc++.h>
#define dbl long double
#define int long long
#define ll long long
using namespace std; 

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rand(int l,int r)
{
	return l+((rng()*1LL*rng()%(r-l+1)+(r-l+1))%(r-l+1));
}


const int T=10000;

void maketest()
{
	ofstream cout("inp.txt");
    int n = 4;
    cout << n << ' '  << rand(1, 72) << el;
    for(int i=0;20>i;i++)cout << "1 ";
}

signed main(){
    // FUNCTION();return 0;
    for(int i=1;i<=T;i++)
   { 
    	cout<<"Test: "<<i<<endl;
    	maketest();
    	system("./working4 < inp.txt > outp.txt");
    	system("./test < inp.txt > ans.txt");
    	if(system("diff outp.txt ans.txt"))
    	{	
    		cout<<"WA"<<endl;
    		return 0;
		}
		cout<<"AC"<<endl;
	}
}