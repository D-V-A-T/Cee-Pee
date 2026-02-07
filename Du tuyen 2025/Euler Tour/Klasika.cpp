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

const ll N = 2e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

ll lg2(int x){
    return x ? 63 - clz(x) : -1;
}

struct edge{
    int v, w, id;
};

int n, q, sz[N], dep[N], pfs[N], in[N], tin[N], ans[N], exist[N];
vect<edge> G[N];
vect<int> order, tour;

void prep(int u){
    in[u] = order.size();
    tin[u] = tour.size();
    order.eb(u);
    tour.eb(u);

	sz[u] = 1;
	for(auto [v, w, id] : G[u]) {
		dep[v] = dep[u] + 1;
		pfs[v] = pfs[u] ^ w;
		
		prep(v);
        tour.eb(u);
		
		sz[u] += sz[v];
	}
}

bool on(int num, int b){
	return num & (1<<b);
}

struct Node{
	Node *nxt[2];
	int cnt, min_id;
	
	Node(){
		cnt = 0;
		min_id = 1e9;
		nxt[0] = nxt[1] = nullptr;
	}
};

#include<bits/stdc++.h>
using namespace std;

// ... (your existing defines and IO) ...
#define ll long long
#define N 200005
#define el "\n"

// Static Trie Implementation
struct StaticTrie {
    int nxt[N * 31][2]; // Space for bits * nodes
    int min_id[N * 31];
    int nodes_cnt = 0;

    StaticTrie() {
        memset(nxt, 0, sizeof(nxt));
        fill(min_id, min_id + N * 31, 1e9);
    }

    // Faster clear: only reset the nodes we actually used
    void clear() {
        for (int i = 0; i <= nodes_cnt; ++i) {
            nxt[i][0] = nxt[i][1] = 0;
            min_id[i] = 1e9;
        }
        nodes_cnt = 0;
    }

    void add(int num, int idx) {
        int cur = 0;
        min_id[cur] = min(min_id[cur], idx);
        for (int b = 30; b >= 0; b--) {
            int bit = (num >> b) & 1;
            if (!nxt[cur][bit]) nxt[cur][bit] = ++nodes_cnt;
            cur = nxt[cur][bit];
            min_id[cur] = min(min_id[cur], idx);
        }
    }

    int get(int val, int limit_id) {
        int cur = 0, res = 0;
        for (int b = 30; b >= 0; b--) {
            int mx = ((val >> b) & 1) ^ 1;
            // Go to the XOR-maximizing branch if it exists AND was added before the query
            if (nxt[cur][mx] && min_id[nxt[cur][mx]] < limit_id) {
                res |= (1 << b);
                cur = nxt[cur][mx];
            } else if (nxt[cur][mx ^ 1] && min_id[nxt[cur][mx ^ 1]] < limit_id) {
                cur = nxt[cur][mx ^ 1];
            } else break; 
        }
        return res;
    }
} T;

// ... (rest of your prep and solve logic) ...

vect<pii> QT[N];
void solve(int u, bool keep) {
    int fat = 0;
    for (auto& e : G[u]) if (sz[fat] < sz[e.v]) fat = e.v;

    // Standard DSU on Tree (Sack) logic
    for (auto& e : G[u]) if (e.v != fat) solve(e.v, 0);
    if (fat) solve(fat, 1);

    // Add light subtrees
    for (auto& e : G[u]) {
        if (e.v != fat) {
            for (int i = in[e.v]; i < in[e.v] + sz[e.v]; i++) {
                int z = order[i];
                T.add(pfs[z], exist[z]);
            }
        }
    }
    
    // Add current node
    T.add(pfs[u], exist[u]);

    // Answer queries at this node
    for (auto& qry : QT[u]) {
        ans[qry.second] = T.get(pfs[qry.first], qry.second);
    }

    if (!keep) T.clear();
}
struct Query{
    int a, b, id;
};


void sol(){
	cin >> q;

    int node_cnt = 1, timer = 0;
    exist[1] = 0;

    vect<Query> Q;
	
    for(int i=1; q>=i; i++){
        string type; int v, x;
        cin >> type >> v >> x;

        if(type == "Add"){
            exist[++node_cnt] = i;
            G[v].pb({node_cnt, x, i});
        }
        else{
            Q.pb({v, x, i});    
        }
    }
	
    prep(1);

    for(auto [a, b, id] : Q){
        QT[b].eb(a, id);
    }


    solve(1, 0);

    for(auto [a, b, id] : Q){
        cout << (ans[id]) << el;
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
