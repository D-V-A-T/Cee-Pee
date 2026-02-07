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

#define FILE "newbarn"
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

const ll N = 1e5 + 5, MOD = 1e9+7, INF = 1000000000000000069;

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



int n, q, sz[N], dep[N], del[N], tin[N], ans[N], visited[N];
vect<int> G[N], QT[N];

void prep(int u, int par){
    sz[u] = 1;
    for(int v : G[u]) if(!del[v] && v != par){
        dep[v] = dep[u] + 1;
        prep(v, u);
        sz[u] += sz[v];
    }
}

int get_centroid(int u, int par, int tr_sz){
    for(int v : G[u]) if(v != par && !del[v]){
        if(sz[v] * 2 > tr_sz) return get_centroid(v, u, tr_sz);
    }
    return u;
}

struct Fick{
    int bit[N];
    vect<int> v;

    Fick(){
        fill(bit, bit+N, -1e9);
        v.reserve(1.67e6);
    }

    int get(int exist){
        int res = -1e9;
        for(; exist>0; exist -= exist & -exist) res = max(res, bit[exist]);
        return res;
    }

    void upd(int vert){
        int exist = tin[vert];
        for(; exist<N; exist += exist & -exist) bit[exist] = max(bit[exist], dep[vert]), v.eb(exist); 
    }

    void clear(){
        while(v.size()){
            bit[v.back()] = -1e9;
            v.pob();
        }
    }
} ft;

void dfs(int u, int par, bool upd){
    if(upd){
        ft.upd(u);
    }else{
        for(int id : QT[u]){
            ans[id] = max(ans[id], dep[u] + ft.get(id) - 2);
        }
    }

    for(int v : G[u]) if(v != par && !del[v]){
        dfs(v, u, upd);
    }
}

void solve(int u){
    visited[u] = 1;

    dep[u] = 1;
    prep(u, 0);
    u = get_centroid(u, 0, sz[u]);

    dep[u] = 1;
    prep(u, 0);
    ft.clear();
    ft.upd(u);

    for(int v : G[u]) if(!del[v]){
        dfs(v, u, 0);
        dfs(v, u, 1);
    }

    for(int id : QT[u]){
        ans[id] = max(ans[id], dep[u] + ft.get(id) - 2);
    }
    ft.clear();
    for(int i=G[u].size()-1; i>=0; i--){
        int v = G[u][i];

        if(!del[v]){
            dfs(v, u, 0);
            dfs(v, u, 1);
        }
    }

    del[u] = 1;

    for(int v : G[u]) if(!del[v]) solve(v);
}

void sol(){
    cin >> q;

    int curr_node_cnt = 0;
    vect<int> queries;
    for(int i=1; q>=i; i++){
        char type; int node;
        cin >> type >> node;

        if(node == -1){
            tin[++curr_node_cnt] = i;
        }else{
            if(type == 'B'){
                curr_node_cnt++;
                tin[curr_node_cnt] = i;
                G[node].eb(curr_node_cnt);
                G[curr_node_cnt].eb(node);
            }else{
                queries.eb(i);
                QT[node].eb(i);
            }
        }
    }

    for(int i=1; curr_node_cnt>=i; i++) if(!visited[i]){
        solve(i);
    }

    for(int i : queries) cout << ans[i] << el;
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