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

#define FILE "fakerfmvp"
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
ll pm(ll a,const int b=MOD){return (a%=b) < 0 ? a + b : a;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

bool infiniteloop = 0;
int n, m, p, par[N], visited[N], rt[N], dep[N], dpout[N];
pii dpin[N][2];
vect<int> D[N], C[N], U[N], G[N], T[N], grp[N];

void dihTree(int u, int root){
    visited[u] = 1;
    rt[u] = root;
    T[root].eb(u);

    for(int v : U[u]){
        if(!visited[v]){
            dep[v] = dep[u] + 1;
            par[v] = u;
            G[u].eb(v);
            dihTree(v, root);
        }else{
            if(v != par[u]) infiniteloop = 1;
        }
    }
}

void init(){
    infiniteloop = 0;
    fill(dep, dep+n+5, 0);
    fill(visited, visited+n+5, 0);

    for(int i=0; n>=i; i++){
        dpin[i][0] = dpin[i][1] = {0, 0};
        dpout[i] = 0;
        T[i].clear();
        D[i].clear();
        C[i].clear();
        U[i].clear();
        grp[i].clear();
        G[i].clear();
    }
}

void solve_tree1(int u){

    for(int v : G[u]){
        solve_tree1(v);
        dpin[u][1] = max(dpin[u][1], {dpin[v][0].fi + 1, v});

        if(dpin[u][0] < dpin[u][1]) swap(dpin[u][0], dpin[u][1]);
    }
}

void solve_tree2(int u){
    for(int v : G[u]){
        dpout[v] = dpout[par[v]] + 1;

        if(dpin[u][0].se != v) dpout[v] = max(dpout[v], dpin[u][0].fi+1);
        else dpout[v] = max(dpout[v], dpin[u][1].fi+1);

        solve_tree2(v);
    }
}

void sol(){
    cin >> n >> m >> p;

    init();

    for(int i=0; m>i; i++){
        int u, v;
        cin >> u >> v;
        U[u].eb(v);
        U[v].eb(u);
    }

    vect<int> dd(n+5), rr(n+5);
    vect<pii> dir;

    for(int i=0; p>i; i++){
        int u, v;
        cin >> u >> v;
        dir.eb(u, v);
        D[u].eb(v);
        C[v].eb(u);
    }

    int rtcnt = 0;
   
    for(int i=1; n>=i; i++) if(!visited[i]){
        dihTree(i, i);
        rtcnt++;
    }


    vect<int> topo, indeg(n+5);
    queue<int> que;

    for(auto e : dir){
        int u = rt[e.fi], v = rt[e.se];

        if(u == v){
            infiniteloop = 1;
        }

        indeg[v]++;
        C[u].eb(v);
    }

    if(infiniteloop){
        cout << "-1\n";
        return;
    }

    for(int i=1; n>=i; i++) if(i == rt[i] && indeg[i] == 0) que.push(i);

    while(que.size()){
        int u = que.front();
        topo.eb(u);
        que.pop();
        for(int v : C[u]) if(--indeg[v] == 0) que.push(v);
    } 

    if(topo.size() != rtcnt){
        cout << "-1\n";
        return;
    }

    int ans = 0;

    for(int i=1; n>=i ;i++){
        // cout << par[i] << ' ' << rt[i] << el;
    }

    for(int r : topo){

        // cerr << "! " << r << el;

        solve_tree1(r);

        // for(int i=1; n>=i; i++) cerr << dpin[i][0].fi << ' ' << dpin[i][0].se << el;

        solve_tree2(r);

        for(int u : T[r]){
            int valu = max(dpin[u][0].fi, dpout[u]);


            ans = max(ans, valu);
            for(int v : D[u]){
                dpin[v][1] = max(dpin[v][1], {valu+1, v});

                if(dpin[v][0] < dpin[v][1])
                    swap(dpin[v][0], dpin[v][1]);
            }
        }
    }

    cout << ans << el;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    cin >> t;
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