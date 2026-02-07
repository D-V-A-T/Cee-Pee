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

const ll N = 3e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

vector<int> adj[N];
int n, q, tin[N], tout[N], timer = 0, depth[N], by_tin[N], b[S][N], lz[S][MAX_BLOCK], ANS[N];
int max_depth = 0;

void DFS(int u, int par){
    tin[u] = timer++;
    max_depth = max(max_depth, depth[u]);

    for(int v : adj[u]) if(v != par){
        depth[v] = depth[u] + 1;
        DFS(v, u);
    }

    tout[u] = timer++;
}

void update_rem(int rem, int l, int r, int z){

    int block_l = l / S, block_r = r / S;
    int lim_l = min(n, (block_l + 1) * S), lim_r = min(n, (block_r + 1) * S);

    if(block_l == block_r){
        for(int i = l ; r >= i; i++) b[rem][i] += z;
    } else{
        for(int i = l ; lim_l > i; i++) b[rem][i] += z;

        for(int i = block_l + 1; block_r > i; i++) lz[rem][i] += z;

        for(int i = block_r * S; r >= i; i++) b[rem][i] += z;
    }
}

vect<int> bucket[S];

struct update{
	int u, x, y, z, id;
};

struct query{
	int u, id;
};

void solve_for_x(int x, const vect<update>& up, const vect<query>& qu){
	if(up.empty()) return;

	const int S = 545, MAX_BLOCK = N / S + 2;
	
	int fumo[N], st_pos[N], ed_pos[N], position[N], lz[MAX_BLOCK], a[N];
	memset(st_pos, -1, sizeof st_pos);
	memset(a, 0, sizeof a);
	memset(lz, 0, sizeof lz);

	
	for(int i=0; n>i; i++){
		int v = by_tin[i];
		bucket[depth[v] % x].eb(v);
	}
	
	
	int ptr = 0;
	for(int i = 0; x > i; i++){
		for(int v : bucket[i]){
			if(st_pos[i] == -1) st_pos[i] = ptr;
			ed_pos[i] = ptr;
			fumo[ptr] = v;
			position[v] = ptr++;
		}
	}

	ptr = 0;
	for(auto [u, x, y, z, id] : up){
		
        while(ptr < qu.size() && qu[ptr].id < id){
			ANS[qu[ptr].id] += a[position[qu[ptr].u]] + lz[position[qu[ptr].u] / S];
			ptr++;
		}
	
		
		if(st_pos[y] == -1) continue;
		
		
		int left = lwb(fumo + st_pos[y], fumo + ed_pos[y] + 1, tin[u], [&](const int& e, const int& val){
			return tin[e] < val;
		}) - fumo;
 		
 		
		int right = lwb(fumo + st_pos[y], fumo + ed_pos[y] + 1, tout[u], [&](const int& e, const int& val){
			return tin[e] < val;
		}) - fumo - 1;
	
		if(left <= right){
			
			int block_l = left / S, block_r = right / S;
			int lim_l = min(n, (block_l + 1) * S), lim_r = min(n, (block_r + 1) * S);
			
			if(block_l == block_r){
				for(int i = left; right >= i; i++) a[i] += z;
			}else{
				for(int i = left; lim_l > i; i++) a[i] += z;
				
				for(int i = block_l + 1; block_r > i; i++) lz[i] += z;
				
				for(int i = block_r * S; right >= i; i++) a[i] += z;
			}
		}
	}
	
    while(ptr < qu.size()){
        ANS[qu[ptr].id] += a[position[qu[ptr].u]] + lz[position[qu[ptr].u] / S];
		ptr++;
    }
	
	for(int i = 0 ; x > i; i++) bucket[i].clear();
}

void sol(){
    cin >> n >> q;

    for(int i=2; n>=i; i++) {
        int u = i, v;
        cin >> v;
        adj[v].eb(u);
    }

    DFS(1, 0);


    iota(by_tin, by_tin+n, 1);
    sort(by_tin, by_tin+n, [](const int& u, const int& v){
        return tin[u] < tin[v];
    });

    int tour[n];
    iota(tour, tour + n, 1);
    sort(tour, tour + n, [](const int& u, const int& v){
        return depth[u] != depth[v] ? depth[u] < depth[v] : tin[u] < tin[v];
    });


    int sp[n+1], ep[n+1], vert_pos[n+1];
    memset(sp, -1, sizeof sp);
    for(int i=0; n>i; i++){
        if(sp[depth[tour[i]]] == -1) sp[depth[tour[i]]] = i;
        ep[depth[tour[i]]] =  i;
        vert_pos[tour[i]] = i;
    }

    const int S2 = 567, MAX_BLOCK2 = N / S2 + 2;
    int Bt[MAX_BLOCK2], dih[MAX_BLOCK2], pre[n+1], suf[n+1];
    memset(Bt, 0, sizeof Bt);
    memset(pre, 0, sizeof pre);
    memset(suf, 0, sizeof suf);
    memset(dih, 0, sizeof dih);

    auto upd_block = [&](int l, int r, int z){
        if(l > r) return;
        dih[l] += z;
        if(r+1 < MAX_BLOCK2) dih[r+1] -= z;
    };

    auto skibidi = [&](){
        Bt[0] += dih[0];

        for(int i = 1; MAX_BLOCK2 > i; i++) {
            dih[i] += dih[i-1];
            Bt[i] += dih[i];
        }
		
		fill(dih, dih + MAX_BLOCK2, 0);
    };

    // deb;
    
    vect<update> smol_updates[S];
    vect<query> queries;
	
	int idx = 0;

    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int sr, x, y, z;
            cin >> sr >> x >> y >> z;

            if(x < S){
                // depth[node] - depth[sr] = y (mod x)
                // depth[node] = y + depth[sr] (mod x)

                int D = (y + depth[sr]) % x;
	
				smol_updates[x].pb({sr, x, D, z, idx++});

            }else{
                // depth[node] = y + depth[sr] (mod x)
                int rem = (y + depth[sr]) % x;

                for(int i = 0; n >= i; i++){
                    if(i * x + rem > max_depth) break;

                    int potential = i * x + rem;

                    int left = lwb(tour + sp[potential], tour + ep[potential] + 1, tin[sr], [](const int& u, const int& val){
                        return tin[u] < val;
                    }) - tour;


                    int right = lwb(tour + sp[potential], tour + ep[potential] + 1, tout[sr], [](const int& u, const int& val){
                        return tin[u] < val;
                    }) - tour - 1;

                    if(left > right) continue;

                    int block_l = left / S2, block_r = right / S2;

                    if(block_l == block_r){
                        pre[right] += z;
                        if(left > 0 && (left-1) / S2 == block_l) pre[left-1] -= z;
                    }else{
                        pre[right] += z;
                        suf[left] += z;
                        upd_block(block_l + 1, block_r - 1, z);
                    }

                }
            }
        }else{

            int u; cin >> u;
			
			queries.pb({u, idx});

            int block = vert_pos[u] / S2;

            skibidi();

            ANS[idx] += Bt[block];

            int lim = min(n, S2 * (block + 1));

            for(int i = block * S2; lim > i; i++){
            	ANS[idx] += pre[i] * (i >= vert_pos[u]);
            	ANS[idx] += suf[i] * (i <= vert_pos[u]);
            }

            idx++;
        }
    }

    for(int i = 1; S > i; i++) solve_for_x(i, smol_updates[i], queries);

    for(auto [u, id] : queries) cout << ANS[id] << el;


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
