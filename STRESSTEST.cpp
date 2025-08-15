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

bool pc(int n){ 
	for(int i=0;1>i;i++)cout << rand(1, 2e4) << ' ';
    return 0;
}

void FUNCTION(){
	//cout << 1 << el;
    int n = 1500;
    while(n--)cout << rand(-5000, 5000) << el;
}

signed main(){
    // FUNCTION();return 0;
    for(int i=1;i<=T;i++)
   { 
    	cout<<"Test: "<<i<<endl;
    	maketest();
    	system("working4.exe < inp.txt > outp.txt");
    	system("test.exe < inp.txt > ans.txt");
    	if(system("fc outp.txt ans.txt"))
    	{	
    		cout<<"WA"<<endl;
    		return 0;
		}
		cout<<"AC"<<endl;
	}
}