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

const ll N = 1e5 + 5, MOD = 1e9+7, INF = 1000000000000000069;

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

int n, dep[N], sz[N], in[N], deep[N], deg[N], rt, sus[N], P[N];
vect<int> order;
vect<pii> G[N];

struct Seggs{
    int t[4 * N], lz[4 * N];
    Seggs(){
        memset(t, -5, sizeof t);
        memset(lz, -5, sizeof lz);
    }

    void push(int l, int r, int id){
        t[id] = max(t[id], lz[id]);

        if(l < r) {
            lz[id*2] = max(lz[id*2], lz[id]);
            lz[id*2+1] = max(lz[id*2+1], lz[id]);
        }

    }

    void upd(int i, int j, int x, int l=0, int r=n-1, int id=1){
        push(l, r, id);
        if(l > j || r < i) return;
        if(i <= l && r <= j){
            lz[id] = max(lz[id], x);
            push(l, r, id);
            return;
        }

        int mid = (l + r) / 2;

        upd(i, j, x, l, mid, id*2);
        upd(i, j, x, mid+1, r, id*2+1);
    }

    int get(int p, int l=0, int r=n-1, int id=1){
        push(l, r, id);
        if(l == r) return t[id];

        int mid = (l + r) / 2;

        if(mid+1 > p) return get(p, l, mid, id*2);
        else return get(p, mid+1, r, id*2+1);
    }
} sgt;

void prep(int u, int par){
    sz[u] = 1;
    in[u] = order.size();
    order.eb(u);
    deep[u] = dep[u];
    for(auto [v, w] : G[u]) if(v != par){
        dep[v] = dep[u] + w;
        prep(v, u);
        sz[u] += sz[v];
        deep[u] = max(deep[u], deep[v]);
    }
}

void dfs(int u, int par){
    vect<int> pfm, sfm, child;
    for(auto [v, w] : G[u]) if(v != par){
        dfs(v, u);
        pfm.eb(deep[v]);
        child.eb(v);
    }

    if(child.empty()) return;
    int m = child.size();
    sfm = pfm;

    for(int i=1; m>i; i++) pfm[i] = max(pfm[i], pfm[i-1]);
    for(int i=m-2; i>=0; i--) sfm[i] = max(sfm[i], sfm[i+1]);

    for(int i=0; m>i; i++){
        int x = -1e12, y = -1e12, v = child[i];
        if(i > 0) x = pfm[i-1];
        if(i+1 < m) y = sfm[i+1];

        sgt.upd(in[v], in[v] + sz[v] - 1, max(x, y) - 2 * dep[u]);
    }
}

void check(int u, int par){
    if(sus[u] < sus[par]) cerr << u << ' ' << par << el, rt = u;
    P[u] = par;
    for(auto [v, w] : G[u]) if(v != par) check(v, u);
}

int k, dih[N];

void solve(int u, int par, vect<int> &path){
    path.eb(u);

    // sus[u] - sus[anc] <= k <=> sus[anc] >= sus[u] - k
    int up = lwb(bend(path), sus[u] - k, [](int id, int val){
        return sus[id] < val;
    }) - path.begin();

    if(up < path.size()){
        dih[u]++;
        dih[P[path[up]]]--; 
    } 

    for(auto [v, w] : G[u]) if(v != par){
        solve(v, u, path);
    }

    path.pob();
}

void complete(int u, int par){
    for(auto [v, w] : G[u]) if(v != par) {
        complete(v, u);
        dih[u] += dih[v];
    }
}

void sol(){
    cin >> n;
    for(int i=1; n>i; i++){
        int u, v, w;
        cin >> u >> v >> w;
        deg[u]++, deg[v]++;
        G[u].eb(v, w);
        G[v].eb(u, w);
    }
    
    if(n == 2){
        int q; cin >> q;
        while(q--){
            cout << "2\n";
        }
        return;
    }

    for(int i=1; n>=i; i++) if(deg[i] > 1) rt = i;
    prep(rt, 0);
    dfs(rt, 0);

    // cout << "? " << sgt.get(in[2]) << el;

    for(int i=1; n>=i; i++) sus[i] = max(deep[i] - dep[i], dep[i] + sgt.get(in[i]));

    check(rt, 0);
    cerr << rt << el;
    cerr << "------------ \n";
    check(rt, 0);
    
    int q;
    cin >> q;

    while(q--){
        cin >> k;
        memset(dih, 0, sizeof dih);
        vect<int> tmp;
        solve(rt, 0, tmp);
        complete(rt, 0);
        cout << *max_element(dih, dih+N) << el;
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