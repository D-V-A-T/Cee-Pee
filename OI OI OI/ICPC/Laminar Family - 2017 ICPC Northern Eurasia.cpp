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

int n, k, parent[N], head[N], dep[N], sz[N], in[N];
vect<int> G[N], order;

void prep(int u, int par){
    sz[u] = 1;
    parent[u] = par;
    for(int v : G[u]) if(v != par){
        dep[v] = dep[u] + 1;
        prep(v, u);
        sz[u] += sz[v];
    }
}

void HLD(int u, int par, int chain_head){
    in[u] = order.size();
    order.eb(u);

    if(chain_head == -1) head[u] = u;
    else head[u] = chain_head;

    int fat = 0;
    for(int v : G[u]) if(v != par){
        if(sz[fat] < sz[v]) fat = v;
    }

    if(fat) HLD(fat, u, head[u]);

    for(int v : G[u]) if(v != par && v != fat){
        HLD(v, u, -1);
    }
}

struct Seggs{
    int t[4 * N], lz[4 * N];
    Seggs(){
        memset(t, -1, sizeof t);
        memset(lz, -1, sizeof lz);
    }

    void push(int l, int r, int id){
        if(lz[id] == -1) return;

        t[id] = lz[id];
        if(l < r){
            lz[id*2] = lz[id*2 + 1] = lz[id];
        }

        lz[id] = -1;
    }

    void upd(int i, int j, int x, int l=0, int r=n-1, int id=1){
        // cout << "why" << el;
        push(l, r, id);
        if(l > j || r < i) return;
        if(i <= l && r <= j){
            lz[id] = x;
            push(l, r, id);
            // cout << l << ' ' << r << ' ' << x << el;
            return;
        }

        int mid = (l + r) / 2;
        upd(i, j, x, l, mid, id*2);
        upd(i, j, x, mid+1, r, id*2+1);
    }

    int get(int p, int l=0, int r=n-1, int id=1){
        push(l, r, id);
        if(l > p || r < p) return -1;
        if(l == r) return t[id];

        int mid = (l + r) / 2;
        return max(get(p, l, mid, id*2), get(p, mid+1, r, id*2+1));
    }
} sgt;

int get_lca(int u, int v){

    while(head[u] != head[v]){  
        if(dep[head[u]] > dep[head[v]]) u = parent[head[u]];
        else v = parent[head[v]];
    }

    return (dep[u] > dep[v] ? v : u);
}

int get_len(int u, int v){
    return dep[u] + dep[v] - 2 * dep[get_lca(u, v)];
}

void sussy(int u, int v, int gay){
    int nig = -67;
    while(head[u] != head[v]){
        int l, r;
        if(dep[head[u]] > dep[head[v]]){
            l = in[u], r = in[head[u]];
            u = parent[head[u]];
        }
        else{
            l = in[v], r = in[head[v]];
            v = parent[head[v]];
        }

        if(l > r) swap(l, r);

        if(nig == -67) nig = sgt.get(l);

        if(sgt.get(l) != nig || sgt.get(r) != nig){
            cout << "No\n";
            exit(0);
        }

        sgt.upd(l, r, gay);
    }

    if(in[u] > in[v]) swap(u, v);


    // cout << in[u] << ' ' << in[v] << el;

    if(nig == -67) nig = sgt.get(in[u]);

    if(sgt.get(in[u]) != nig || sgt.get(in[v]) != nig) {
        // cout << u << ' ' << v << ' ' << sgt.get(in[v]) << ' ' << in[v] << ' ' << nig << el;
        cout << "No\n";
        exit(0);
    }


    sgt.upd(in[u], in[v], gay);
}

void sol(){
    cin >> n >> k;

    for(int i=1; n>i; i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    prep(1, 0);
    HLD(1, 0, -1);

    vect<pii> path;
    for(int i=0; k>i; i++){
        int u, v;
        cin >> u >> v;
        path.eb(u, v);
    }

    sort(bend(path), [](const pii &a, const pii &b){
        return get_len(a.fi, a.se) > get_len(b.fi, b.se);
    });

    for(int i=0; k>i; i++){
        // cout << path[i].fi << ' ' << path[i].se << el;
        sussy(path[i].fi, path[i].se, i+1);
        // cout << i << el;
    }

    cout << "Yes\n";
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