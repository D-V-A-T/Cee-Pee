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
#define int long long

#define FILE "yinyang"
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

int n, sz[N], dep[N], pf[N], del[N], ans = 0, same = 0;
vect<pii> G[N];

struct DataStructure{
    int pos[N], neg[N];
    vect<int> ps, ng;
    DataStructure(){
        memset(pos, 0, sizeof pos);
        memset(neg, 0, sizeof neg);
        ps.reserve(1e6);
        ng.reserve(1e6);
    }

    void add(int x){
        if(x < 0) neg[-x]++, ng.eb(x);
        else pos[x]++, ps.eb(x);
    }

    void del(int x){
        if(x < 0) neg[-x]--;
        else pos[x]--;
    }

    int get(int x){
        if(x < 0) return neg[-x];
        else return pos[x];
    }

    void clear(){
        for(int i : ng) neg[-i] = 0;
        for(int i : ps) pos[i] = 0;
        ng.clear();
        ps.clear();
    }
} sack, global;

void prep(int u, int par, bool sus){

    sz[u] = 1;

    for(auto [v, w] : G[u]) if(v != par && !del[v]){
        dep[v] = dep[u] + 1;
        if(sus) pf[v] = pf[u] + w;
        prep(v, u, sus);
        sz[u] += sz[v];
    }
}

int get_centroid(int u, int par, int tr_sz){
    for(auto [v, w] : G[u]) if(v != par && !del[v]){
        if(sz[v] * 2 > tr_sz) return get_centroid(v, u, tr_sz);
    }
    return u;
}

void dfs(int u, int par, int type){
    // pf[u] + pf[x] = 0
    // pf[x] = pf[rt]


    // type: 1 -> update
    // type: 2 -> del
    // type: 3 -> query

    if(type == 1){
        if(sack.get(pf[u])){
            global.add(pf[u]);            
        }
    }else if(type == 2){
        if(sack.get(pf[u])) global.del(pf[u]);
    }else{
        if(sack.get(pf[u])) same += global.get(-pf[u]);
        ans += global.get(-pf[u]);

        // paths from root
        ans += pf[u] == 0 && sack.get(pf[u]) > 1;
    }

    sack.add(pf[u]);  

    for(auto [v, w] : G[u]) if(v != par && !del[v]){
        dfs(v, u, type);
    }

    sack.del(pf[u]);
}

void solve(int u){
    dep[u] = 0;
    pf[u] = 0;
    prep(u, 0, 0);

    u = get_centroid(u, 0, sz[u]);
    pf[u] = 0;
    dep[u] = 0;
    prep(u, 0, 1);

    
    global.clear();
    sack.clear();

    sack.add(pf[u]);

    for(auto [v, w] : G[u]) if(!del[v]){
        dfs(v, u, 1);
    }

    for(auto [v, w] : G[u]) if(!del[v]){
        dfs(v, u, 2);
        dfs(v, u, 3);
        dfs(v, u, 1);
    }

    del[u] = 1;
    for(auto [v, w] : G[u]) if(!del[v]) solve(v);
}

void sol(){
    cin >> n;
    for(int i=1; n>i; i++){
        int u, v, w;
        cin >> u >> v >> w;
        if(w == 0) w = -1;
        G[u].eb(v, w);
        G[v].eb(u, w);
    }

    solve(1);
    cout << ans - same/2 << el;
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