#ifdef ONLINE_JUDGE
 
#include<bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,popcnt,lzcnt,tune=native")
 
#endif 
 
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pii pair<int, int>
#define bend(v) v.begin(),v.end()
#define vect vector 
#define prq priority_queue
#define umap unordered_map
#define eb emplace_back
#define pb push_back
#define pob pop_back
#define ef emplace_front
#define pf push_front
#define pof pop_front
#define el "\n"
#define deb cout<<"\nok\n";return 
#define nextl cout<<"\n"
#define lwb lower_bound 
#define upb upper_bound
#define rs resize
#define popcnt __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define ll long long 
#define dbl long double

#define FILE "ijustwannabepartofyourskibidi"
void IO(){
    if(fopen(FILE".in", "r")){
        freopen(FILE".in", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }
    else if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }
}
 
const ll N = 1e5 + 1, MOD = 1e9 + 7, INF = 1000000000000000069;
 
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
 
ll rand(ll l, ll r){
    return uniform_int_distribution<ll>(l, r)(rng);
}
ll pm(ll a,const ll b=MOD){return ((a%b)+b)%b;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

struct Matrix{
    int n,m ;
    ll mat[2][2];

    Matrix(int n=2, int m=2){
        this->n = n;
        this->m = m;
		
		memset(mat, 0, sizeof mat);
        // mat.rs(n, vect<ll>(m));
    }

    auto & operator [] (int id){
        return mat[id];
    }

    const auto & operator [] (int id) const{
        return mat[id];
    }

    void make_identity(){
        assert(n == m);
        for(int i=0; n>i; i++) mat[i][i] = 1;
    }

    Matrix operator * (const Matrix& o) const{
        auto &a = mat;
        auto &b = o.mat;

        assert(m == o.n);
        int x = n, y = m, z = o.m;

        Matrix res(x, z);
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
    
    void print(){
    	for(int i=0; n>i; i++) for(int j=0; m>j; j++) cout << mat[i][j] << " \n"[j == m-1];
    }

};

Matrix A, B;
int n, q;
string s;

struct Seggs{
	Matrix ej[4 * N], rej[4 * N];
	bool lz[4 * N];
	
	Seggs(){
		memset(lz, 0, sizeof lz);
		build();
	}
	
	void build(int l=0, int r=n-1, int id=1){
		if(l == r){
			if(s[l] == 'A'){
				ej[id] = A;
				rej[id] = B;
			}else{
				ej[id] = B;
				rej[id] = A;
			}
			return;
		}
		
		int mid = (l+r)/2;
		
		build(l, mid, id*2);
		build(mid+1, r, id*2+1);
		
		ej[id] = ej[id*2] * ej[id*2 + 1];
		rej[id] = rej[id * 2] * rej[id*2+1];
	}
	
	void push(int l, int r, int id){
		if(lz[id]) swap(ej[id], rej[id]);
		
		if(l < r){
			lz[id * 2] ^= lz[id];
			lz[id * 2 + 1] ^= lz[id];
		}
		
		lz[id] = 0;
	}
	
	void upd(int i, int j, int l=0, int r=n-1, int id=1){
		push(l, r, id);
		if(l > j || r < i) return;
		if(i <= l && r <= j){
			lz[id] ^= 1;
			push(l, r, id);
			return;
		}
		
		int mid = (l+r)/2;
		upd(i, j, l, mid, id*2);
		upd(i, j, mid+1, r, id*2+1);
		
		ej[id] = ej[id*2] * ej[id*2+1];
		rej[id] = rej[id*2] * rej[id*2+1];
	}
	
	void get(int i, int j, Matrix &sus, int l=0, int r=n-1, int id=1){
		push(l, r, id);
		
		
		
		if(l > j || r < i) return;
		if(i <= l && r <= j){
			sus = sus * ej[id];
			return;
		}
		
		int mid = (l+r)/2;
		get(i, j, sus, l, mid, id*2);
		get(i, j, sus, mid+1, r, id*2+1);
	}
};

void sol(){
    cin >> n >> q;

    
    A.mat[0][0] = 1, A.mat[0][1] = 0;
    A.mat[1][0] = 1, A.mat[1][1] = 1;
    
    B.mat[0][0] = 1, B.mat[0][1] = 1;
    B.mat[1][0] = 0, B.mat[1][1] = 1;


    cin >> s;
    
    Seggs sgt;
    
    while(q--){
    	int t, l, r;
    	cin >> t >> l >> r;
    	l--, r--;
    	if(t == 1){
    		sgt.upd(l, r);
    	}else{
    		Matrix sus(1, 2);
    		int x, y;
    		cin >> x >> y;
    		sus.mat[0][0] = x, sus.mat[0][1] = y;
			
			sgt.get(l, r, sus);
			cout << sus[0][0] << ' ' << sus[0][1] << el;
    	}
    }

}
 
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    // cin >> t;
    while(t--) sol();
}
/*
                                                     ...-%%%%%%%%%%%...                               
                                             .:**#%=%%%%%+........-%%%%. .                            
                                        .%%%%%%=-..%#.               .#%%.                            
                                      %%%+..      .:                    *%%.                          
                                    .%%.          :.                     :%%%%%:.                     
                                   .%%.     ...  .:                    ::     .=%%%.                  
                                 ..%%.    #%#:%. :                   :..          =%%.                
                                %%+..:  .%*::::%-::::::-::::::..   .:-%%%%.        .*%%..             
                              .%#     :.%:::::::%%%%%%%%%%%%%+...%%%+::::%#.         .%%.             
                             .%%.  ..:.%=::::*%#***#%::::::::%%%%=:::::::%%.          .%%.            
                             =%%%...-%%%:::*%********%:::%%%****%::::::::%%            .%-            
                            .%::::%%***%=:%%**********%%********%:::::::=%-:.          .%..           
                            #%:::%#*****%%**********************%:::+%%%*%%-.:      .::..%%.          
                           .%%::%%*****==**==*****#************#%%%%#******%%..::::..     .%%.        
                         .%%#%+%%***************##*+=+*==********************%%.:.         .%%        
                        .%%***%%****************#**==**==******==**+=+********%%%%%%%%%     %%.       
                      .#%#*********************%%**************++************%%::::::%*   .%%%.       
                     .%%***************#*****%%%****************************%%::::::%% .-%%%.         
                    .#%***************#****%%--%*********%*****************%#::::-%%%%%%%%%%.         
                    .%%**************#**%%%----%********%%**************#***#%%%#**%#******%*         
                   .%%**************#%%%--.....%%*******%%**************#**********#%******%%.        
                   .%%*************%%...........%%******%-%*************#***********%%*****%%.        
                   .%%*************%%...%%%%%.....%%%%%%%.=%%%%%%%%##****#****##::::+%%*****%#        
                   .%%************%%...%.   %%.................%%%%-.....%*****#*****%%*****%%        
                   .#%#*#****#****%%:::%-  %%.................%.   #-....%*****#*#####%#****%%.       
                    .%%##****%%%**%%:::::##...................%=  .%+:::%#*****#:####*%%****%%.       
                     .+%%#**%%.#%%%%::::::........###+.:*##-....%%%:::::%*****##******%%****%%-       
                       ..%%*%%.......:::.......##..#*...#+..#*....:::::%******#*****##%%*****%%.      
                        .%%%%%................#-##=--##+-+###-#....:::%******#:###*::%%#*****%%.      
                      .%%****%%..............#----------------=*...#%#****##**##::#**%%*******%%.     
                      .%%%%%*=+%%*...........#-----------------#.....#%%%%%%+:##*##:*%%*******%%%.    
                        ..:*%====%%%%........#-----------------#:.........%#********%%*****%%%%%%.    
                          .%%=======*%%%%%%%.%%+----#-%------%%#.......%%%%::::::::%%==***#%###%%.    
                         ..%%=============+%%-:#%%%%-::%%%%%%::%%%%%%%%%=%%*******%%=====**%%###%%..  
                        -%%%%%%%%%%%%%%%%+%.%+:+%::%::::%::%:::%%#%... .%%******%%%========#%####%%.  
                      .%%++#############%%# ..%%.**%%#%%%%%%%#%***%.  :%%*****%%%=+%%%%%%%%%%#####%%. 
                    .%%++++*############*++%   .%************#****%.  #%*%%%%+++%%%%###############%%.
         .+%%%%%%%%%%####+##########*+++++%%. .%**#**********#****%   %%**%%%++++###################%:
      =%%%%######################++++++++%%*%.-%%#***********#****% .%****%%+++++###################%%
   .%%%#######################*%%%%%%%%.%%*#%+%###################%.%%***%%%+++++###################%%
  *%%######################+#%%++++++%*. =%*%. .:%%%%########%%%%%%%%%#*#%.%%++#####################%%
.%%%#####################%%%%%+++++++%-  %*#%%.          .%%%*++++++*%%%....%%#####################%%*
%%######%%%%%#%%%%%######%%.%*+++++++%.  %****#.        .%%+++*+++++*++%%...=%%###################%%%.
%%%%%%%%#-=##%...%%######%%.%%+++++++%%..*%***#%%%%%. ..%+++++++++++++++%%...%%##################%%%. 
.%:.             .#%#####%%.%%+++++++++%. %*********%%%%%++++++++++++++++%%...%%##############%%%%..  
                  :%#####%% .%%+++++++%%  .%%**********%%++++++++++++++++%%.....%#########%%%%%% .    
                 *%#####%%.  .%%+++++++%%:. .%%********%%++++++++++++++++%%....%%%%%%%%%%%%*..        
                 .%%##%%%     .%%*+++++++%%. ..#%%%#****%%+++++++++++++++%%%%%% . .....               
                 %%#%%%.       .:%%%%%%%%%%%...-%. ......%%+++++++++++++%%.                           
               ..%%%.              ...     .%%%#%%%=:#%%%%%%%%*++++++%%%#                             
                                                 .-%%+.  ... .%%%%%%%:.  
*/