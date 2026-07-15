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

#define FILE "netw"
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

const ll N = 1e5 + 10, MOD = 998244353, INF = 1000000000000000069;

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

int n, sz[N], dep[N], del[N], ANS[N];
vect<array<int, 3>> G[N];

void prep(int u, int par){
    sz[u] = 1;
    for(auto &[v, _, __] : G[u]) if(v != par && !del[v]){
        prep(v, u);
        sz[u] += sz[v];
    }
}

int get_centroid(int u, int par, int rt){
    for(auto &[v, _, __] : G[u]) if(v != par && !del[v] && sz[v]*2 > sz[rt]){
        return get_centroid(v, u, rt);
    }
    return u;
}

struct Fick{
    int bit[N];
    vect<int> cache;

    Fick(){
        memset(bit, 0, sizeof bit);   
        cache.reserve(N);
    }

    int get(int x){
        int res = 0;        
        for(;x>0; x-=x&-x) res = (res + bit[x]) % MOD;
        return res;
    }

    void upd(int x, int v, bool sus=1){
        if(sus) cache.eb(x);
        for(;x<N; x+=x&-x) bit[x] = (bit[x] + v) % MOD;
    }

    void clear(){
        while(cache.size()){
            int x = cache.back();
            for(;x<N;x+=x&-x) bit[x] = 0;
            cache.pob();
        }
    }
} ssq, ssm, smn;


struct Fick2{
    int bit[N];
    vect<int> cache;

    Fick2(){
        memset(bit, 0, sizeof bit);
        cache.reserve(N);
    }

    int get(int x){
        int res = 0;
        for(;x<N;x+=x&-x) res = (res + bit[x]) % MOD;
        return res;
    }

    void upd(int x, int v, bool sus=1){
        if(sus) cache.eb(x);
        for(;x>0;x-=x&-x) bit[x] = (bit[x] + v) % MOD;
    }

    void clear(){
        while(cache.size()){
            int x = cache.back();
            for(;x>0; x-=x&-x) bit[x] = 0;
            cache.pob();
        }
    }
} SQ, S, C;

void CLEAR(){
    SQ.clear();
    S.clear();
    C.clear();
    ssm.clear();
    smn.clear();
    ssq.clear();
}

inline void UPD(int u, int dep, int mn, int mz){
    ANS[u] = (ANS[u] + ssq.get(mz) 
                    + ssm.get(mz) * dep % MOD 
                    + smn.get(mz) * dep % MOD * dep % MOD) % MOD;

    ANS[u] = (ANS[u] + SQ.get(mz+1) * mn % MOD 
                    + S.get(mz+1) * dep % MOD * mn % MOD
                     + C.get(mz+1) * dep % MOD * dep % MOD * mn % MOD) % MOD;
}

void dfsus(int u, int par, int dep, int mn, int mz, bool first_time=1){
    
    if(!first_time){
        ANS[u] = (ANS[u] + dep*dep%MOD*mn%MOD) % MOD;
    }

    UPD(u, dep, mn, mz);

    for(auto &[v, w, z] : G[u]) if(v != par && !del[v]){
        dfsus(v, u, dep+1, min(mn, w), min(mz, z), first_time);
    }


}

void update(int u, int par, int dep, int mn, int mz){
    for(auto &[v, w, z] : G[u]) if(v != par && !del[v]){
        update(v, u, dep+1, min(mn, w), min(mz, z));
    }

    ssq.upd(mz, dep*dep % MOD * mn % MOD);
    ssm.upd(mz, mn*dep*2%MOD);
    smn.upd(mz, mn);

    SQ.upd(mz, dep*dep%MOD);
    S.upd(mz, dep*2%MOD);
    C.upd(mz, 1);
}   

void decompose(int u){
    prep(u, 0);
    u = get_centroid(u, 0, u);

    // cout << u << el;

    CLEAR();
    for(auto &[v, w, z] : G[u]) if(!del[v]){
        dfsus(v, u, 1, w, z);
        update(v, u, 1, w, z);
    }
    UPD(u, 0, 1e9, N-1);

    reverse(bend(G[u]));
    CLEAR();
    for(auto &[v, w, z] : G[u]) if(!del[v]){
        dfsus(v, u, 1, w, z, 0);
        update(v, u, 1, w, z);
    }

    del[u] = 1;
    for(auto &[v, w, z] : G[u]) if(!del[v]) decompose(v);

}

void sol(){
    cin >> n;

    vect<int> zip;

    for(int i=1; n>i; i++){
        int u, v, w;
        cin >> u >> v >> w;

        G[u].pb({v, w, 0});
        G[v].pb({u, w, 0});
        zip.eb(w);
    }

    sort(bend(zip));
    zip.rs(unique(bend(zip)) - zip.begin());

    for(int i=1; n>=i; i++){
        for(auto &[v, w, z] : G[i]){
            z = lwb(bend(zip), w) - zip.begin() + 1;
        }
    }

    decompose(1);

    for(int i=1; n>=i; i++) cout << ANS[i] << el;
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