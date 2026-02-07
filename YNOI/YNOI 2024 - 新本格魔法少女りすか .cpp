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
#define ull unsigned long long

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

const ll N = 5e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

const int S = 336, MAX_BLOCK = N / S + 2;

int ED[MAX_BLOCK];
ll ans[N], block_pfs[MAX_BLOCK][MAX_BLOCK];

struct query{
	int len, id;
	vect<pii> ranges;
};

struct off_query{
	int l, id; bool del;int sub_id;
	
	// off_query(int l=0, int id=0, bool del=0, int sub_id=0): l(l), id(id), del(del), sub_id(sub_id) {}
	// off_query(const int& l, const int& r, const int& id, const bool& del, const int& sub_id): l(l), 

    bool operator < (const off_query& o) const{
		if(l / S != o.l / S || id == o.id) return l < o.l;
		return id < o.id;
    }
};

static const int MAXV = N; 
static const int Block = 64;

struct BIT {
    int n;
    ull base[(MAXV >> 6) + 5];
    int c[(MAXV >> 6) + 5];
    ull mask[Block];

    int lowbit(int x) { return x & -x; }

    void init(int sz) {
        n = (sz >> 6) + 1;
        mask[0] = 1;
        for (int i = 1; i < Block; i++)
            mask[i] = (mask[i - 1] << 1) | 1;
        clear();
    }

    void clear() {
        memset(base, 0, sizeof(base));
        memset(c, 0, sizeof(c));
    }

    // set position pos to 1
    void insert(int pos) {
        int p = (pos >> 6) + 1;
        int r = pos & (Block - 1);
        if ((base[p] >> r) & 1) return;

        base[p] ^= (1ULL << r);
        while (p <= n) c[p]++, p += lowbit(p);
    }

    // count of bits ≤ pos
    int query(int pos) {
        pos--;
        int p = pos >> 6;
        int r = pos & (Block - 1);
        int ans = __builtin_popcountll(base[p + 1] & mask[r]);
        while (p) ans += c[p], p -= lowbit(p);
        return ans;
    }
} T;

struct my_struct{
	int l, r, id;
	my_struct(int l, int r, int id): l(l), r(r), id(id) {}
};

int pfs[S][MAX_BLOCK];

inline int GET(int x) {
    return T.query(x);
}

inline void UPD(int x) {
    T.insert(x);
}

inline void RESET() {
    T.clear();
}


void sol(){
	int n, q;
	cin >> n >> q;
	
	T.init(N);


    const int lb = (n-1) / S;
	
	int a[n], b[n];
	pii c[n];
	for(int i=0; n>i; ++i){
		cin >> a[i];
		b[i] = a[i];
		c[i] = {a[i], i};
	}
	
	for(int i=0; lb >= i; ++i){
		int ed = min(n, (i + 1) * S);
		ED[i] = ed;
		sort(b + i * S, b + ed);
		sort(c + i * S, c + ed);
	}
	
	for(int blk = 0; lb >= blk; ++blk){
		int ed = min(n, (blk+1) * S);

		int ptr[MAX_BLOCK];

		for(int blj = 0; blk > blj; blj++) ptr[blj] = blj * S;
		
		for(int i = blk*S; ed > i; ++i){
			for(int blj = 0; blk > blj; ++blj){
				while(ptr[blj] < (blj+1) * S && b[i] > b[ptr[blj]]){
					++ptr[blj];
				}

				block_pfs[blk][blj] += ptr[blj] - blj * S;
			}
		}
	}
	
	for(int bli = 0; lb >= bli; ++bli){
		for(int blj = 0; bli >= blj; ++blj){			
			if(bli > 0) block_pfs[bli][blj] += block_pfs[bli - 1][blj];
			if(blj > 0) block_pfs[bli][blj] += block_pfs[bli][blj - 1];
			if(bli && blj) block_pfs[bli][blj] -= block_pfs[bli-1][blj-1];
		}
	}

	
	auto get = [&](int blk_l, int blk_r, int blj_l, int blj_r){
	    ll res = block_pfs[blk_r][blj_r];
	    if(blk_l > 0) res -= block_pfs[blk_l - 1][blj_r];
	    if(blj_l > 0) res -= block_pfs[blk_r][blj_l - 1];
	    if(blk_l > 0 && blj_l > 0)
	        res += block_pfs[blk_l - 1][blj_l - 1];

	    return res;
	};
	
	
	vect<my_struct> fb[q+5];
	vect<pii> info[N]; // id, sub_id, del
	int Q = 0;
	
	auto add_query = [&](int x, int id, int sub_id, bool del){
		info[x].eb(id * (del ? -1 : 1), sub_id);
	};
	
	auto starting_time = 1.0*clock()/CLOCKS_PER_SEC;
	
	for(int idx=1; q>=idx; ++idx){
		int len;
		cin >> len;
		vect<pii> ranges(len);
		
		fb[idx].reserve(len+1);
		
		for(int i=0; len>i; ++i){
			int l, r;
			cin >> l >> r;
			l--; r--;
			ranges[i] = {l, r};

			int block_l = l / S, block_r = r / S, lim_l = min(n, (block_l + 1) * S);
			
			
			
			if(block_l == block_r){
				for(int i = l; r >= i; ++i) ans[idx] += GET(a[i]);
				for(int i = l; r >= i; ++i) UPD(a[i]);
				
				
				add_query(r, idx, i, 0);
				if(block_l * S != l) add_query(l-1, idx, i, 1);
				
			}else{
				
				for(int i = l; lim_l > i; ++i) ans[idx] += GET(a[i]);
				for(int i = block_r * S; r >= i; ++i) ans[idx] += GET(a[i]);
				for(int i = l; lim_l > i; ++i) UPD(a[i]);
				for(int i = block_r * S; r >= i; ++i) UPD(a[i]);


				add_query(r, idx, i, 0);
				add_query(lim_l-1, idx, i, 0);
				if(block_l * S != l) add_query(l-1, idx, i, 1);
				
				if(block_l + 1 <= block_r - 1){
					for(const auto &[bl, br, f] : fb[idx]){
						ans[idx] += get(block_l + 1, block_r - 1, bl, br);
					}

					fb[idx].eb(block_l+1, block_r-1, i);
				}
			}

        	
		}
		RESET();		
    }
	
	
	auto ending_time = 1.0*clock()/CLOCKS_PER_SEC;
	
	cerr << "Online processing: " << ending_time - starting_time << el;

	int c_block = -1, ptr = 0, st = 0, ed = min(n, S);

	int lwbptr[MAX_BLOCK];
	
	// cerr << Q << el;
	// if(q > 5) return;
	
	for(int l=0; n>l; l++){
		// cout << "l: " << l << ' ' << type << el;
		if(l / S != c_block){
			ptr = 0;
			c_block = l / S;
			st = c_block * S;
			ed = min(n, st + S);


			for(int bl = 0; lb >= bl; ++bl) lwbptr[bl] = bl * S;

			for(int i = st; ed > i; ++i){

				for(int bl = 0; lb >= bl; ++bl){
					while(lwbptr[bl] < ED[bl] && b[lwbptr[bl]] < b[i]) ++lwbptr[bl];
					if(bl < c_block)
						pfs[c[i].se - st][bl] = lwbptr[bl] - bl * S;
					else
						pfs[c[i].se - st][bl] = ED[bl] - lwbptr[bl];
				}
			}

			for(int i = 0; ed - st > i; ++i){
				partial_sum(pfs[i], pfs[i] + MAX_BLOCK, pfs[i]);
				for(int bl=0; lb>=bl && i; ++bl) pfs[i][bl] += pfs[i-1][bl];
			}
		}
		
		for(const auto &[id, sub_id] : info[l]){
			int idx = abs(id);
			for(const auto &[bl, br, sid] : fb[idx]){
				if(sid == sub_id) continue;

				int res = pfs[l - st][br] - (bl ? pfs[l - st][bl-1] : 0);

				if(id < 0) ans[idx] -= res;
				else ans[idx] += res;
			}
		}
	
	}

    
    for(int i=1; q>=i; i++) cout << ans[i] << el;
}

signed main(){
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

