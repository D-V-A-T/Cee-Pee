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
#define popcnt __builtin_popcountll
#define clz __builtin_clzll
#define ctz __builtin_ctzll
#define ull unsigned long long
#define ll long long 
#define dbl long double
#define int long long

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

const ll N = 2e5 + 10, MOD = 1e9+7, INF = 1000000000000000069;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll rand(ll l, ll r){
    return uniform_int_distribution<ll>(l, r)(rng);
}
ll pm(ll a,const int b=MOD){return (a%=b) < 0 ? a + b : a;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int n, m, sz[N], del[N], cnt[N], city[N], dep[N], parent[N];
vect<int> G[N];

void prep(int u, int par){
    sz[u] = 1;
    for(int v : G[u]) if(v != par && !del[v]){
        prep(v, u);
        sz[u] += sz[v];
    }
}

void cac(int u, int par){
    parent[u] = par;
    for(int v : G[u]) if(v != par && !del[v]){
        dep[v] = dep[u] + 1;
        cac(v, u);
    }
}

int get_centroid(int u, int par, int rt){
    for(int v : G[u]) if(v != par && !del[v]){
        if(sz[v] * 2 > sz[rt]) return get_centroid(v, u, rt);
    }
    return u;
}

struct DSU{
    int par[N], len[N], high[N];
    vect<int> cache;

    DSU(){
        iota(par, par+N, 0);
        iota(high, high+N, 0);
        fill(len, len+N, 1);
    }

    int findpar(int u){
        return u == par[u] ? u : par[u] = findpar(par[u]);
    }

    void join(int u, int v){
        cache.eb(u);
        cache.eb(v);

        u = findpar(u), v = findpar(v);

        if(u != v){
            if(len[u] < len[v]) swap(u, v);
            len[u] += len[v];
            par[v] = u;
            int hu = high[u], hv = high[v];
            if(dep[hu] < dep[hv]) high[u] = hu;
            else high[u] = hv;
        }
    }

    int gethigh(int x){
        return high[findpar(x)];
    }

    void clear(){
        while(cache.size()){
            int x = cache.back();
            par[x] = x;
            len[x] = 1;
            high[x] = x;
            cache.pob();
        }
    }
} ds;

vect<int> vert[N];

vect<int> tree, tmp(N);

void dfsus(int u, int par, int rt=0){
    vert[city[u]].eb(u);
    tree.eb(u);
    tmp[city[u]]++;

    for(int v : G[u]) if(v != par && !del[v]){
        dfsus(v, u);
    }
}


void cclear(int u, int par){
    tmp[city[u]] = 0;
    while(vert[city[u]].size()) vert[city[u]].pob();
    for(int v : G[u]) if(v != par && !del[v]){
        cclear(v, u);
    }
}

int ans = 1e9;
bool seen[N];

void decompose(int u){
    prep(u, 0);
    u = get_centroid(u, 0, u);
    dep[u] = 0;
    cac(u, 0);

    // cout << "cent " << u << el;
    dep[0] = -1;

    for(;!seen[city[u]];){

        tree.clear();
        dep[u] = 0;
        dfsus(u, 0);

        bool skip = 0;


        if(cnt[city[u]] != vert[city[u]].size()) skip = 1;

        if(skip){
            cclear(u, 0);
            break;
        }

        seen[city[u]] = 1;


        ds.clear();

        vect<int> stk;

        int res = 0;

        // cout << vert[city[u]].size() << el;

        while(vert[city[u]].size()){
            stk.eb(vert[city[u]].back());
            vert[city[u]].pob();
        }

        while(stk.size()){
            int x = stk.back();
            stk.pob();

            // cerr << "! " << x << ' ' << parent[x] << el;

            if(cnt[city[x]] != tmp[city[x]]) skip = 1;


            while(x != 0){
                res += vert[city[x]].size() > 0;


                while(vert[city[x]].size()){
                    stk.eb(vert[city[x]].back());
                    vert[city[x]].pob();
                }

                ds.join(x, parent[x]);
                x = ds.gethigh(parent[x]);
            }
        }   

        // cout << u << ' ' << res << el;

        cclear(u, 0);
        if(!skip) ans = min(ans, res);
    }

    del[u] = 1;
    for(int v : G[u]) if(!del[v]) decompose(v);

}


void sol(){
    cin >> n >> m;


    for(int i=1; n>i; i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    for(int i=1; n>=i; i++) cin >> city[i], cnt[city[i]]++;

    decompose(1);

    cout << ans;
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