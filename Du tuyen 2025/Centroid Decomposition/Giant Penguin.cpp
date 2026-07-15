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

int n, m, sz[N], idx[N], del[N], sus[N], dep[N], mn[N], ans[N], k;
int dist[36][N];
bool visited[N];
vect<int> G[N], T[N], E[N], vert, spec, add[N], query[N];


void prep(int u, int par){
    sz[u] = 1;
    for(int v : T[u]) if(v != par && !del[v]){
        prep(v, u);
        sz[u] += sz[v];
    }
}

int get_centroid(int u, int par, int rt){
    for(int v : T[u]) if(v != par && !del[v] && sz[v] * 2 > sz[rt]){
        return get_centroid(v, u, rt);
    }
    return u;
}

struct asdf{
    int id, u, bl;

    bool operator < (const asdf &o) const{
        return id < o.id;
    }
};

vect<pii> events;

bool comp(const pii &a, const pii &b){
    return abs(a.fi) < abs(b.fi);
}

void ADD_EVENT(int u){
    for(int id : add[u]) events.eb(-id, u);
    for(int id : query[u]) events.eb(id, u);
}

void dfsus(int u, int par, int x, int depth){
    sus[u] = x;
    vert.eb(u);
    dep[u] = depth;

    ADD_EVENT(u);

    for(int v : T[u]) if(v != par && !del[v]){
        dfsus(v, u, x, depth+1);
    }


}

void CLEAR(){

    for(int i : vert) sus[i] = 0, idx[i] = -1, mn[i] = 1e9;

    events.clear();
    vert.clear();
    spec.clear();
}

void BFS(int rt, int id){

    auto &dih = dist[id];

    queue<int> que;
    dih[rt] = 0;
    que.push(rt);

    while(que.size()){
        int u = que.front();
        que.pop();

        for(int v : G[u]) if(dih[v] > dih[u] + 1 && sus[v] && !del[v]) {
            dih[v] = dih[u] + 1;
            que.push(v);
        }
    }
}

void decompose(int u){
    prep(u, 0);
    u = get_centroid(u, 0, u);

    CLEAR();

    dep[u] = 0;
    vert.eb(u);
    ADD_EVENT(u);
    for(int v : T[u]) if(!del[v]) dfsus(v, u, v, 1);

    int ID = 0;
    
    if(k) idx[u] = spec.size(), spec.eb(u);
    sus[u] = u;
    for(int y : vert){
        for(int z : E[y]) {
            // cerr << "? " << y << ' ' << z << el;
            if(sus[y] != sus[z] && sus[y] && sus[z]){
                if(idx[y] == -1) idx[y] = spec.size(), spec.eb(y);
                if(idx[z] == -1) idx[z] = spec.size(), spec.eb(z);
            }
        }
    }

    ID = spec.size();   

    for(int i=0; ID>i; i++){
        for(int v : vert) dist[i][v] = 1e9;
        BFS(spec[i], i);
    }

    // for(int i : vert){
    //     cout << i << ' ' << sus[i] << el;
    
    // }

    // cout << "bfs: " << spec[1] << ' ' << dist[1][4] << el;

    // cout << "[]: ";
    // for(int i : spec) cout << i << ' ';
    // nextl;

    sort(bend(events), comp);

    int min_dep = 1e9;
    // cout << el << u << "  --------------------\n";
    for(const auto &[code, x] : events){

        bool type = code > 0;
        int timer = abs(code);

        // cout << timer << ' ' << x << ' ' << type << el;

        // if(u == 3) cout << timer << ' ' << x << ' ' << type 
        //     << ' ' << min_dep << ' ' << dep[x] << ' ' << dist[2][x] << el;
        if(type == 0){
            min_dep = min(min_dep, dep[x]);

            for(int i=0; ID>i; i++){
                mn[spec[i]] = min(mn[spec[i]], dist[i][x]);
            }
        }else{
            // cerr << dep[x] << ' ' << min_dep << el;
            ans[timer] = min(ans[timer], dep[x] + min_dep);

            for(int i=0; ID>i; i++){
                // if(mn[spec[i]] + dist[i][x] == 1){
                //     cout << "dit " << mn[spec[i]] << ' ' << dist[i][x] << ' ' << spec[i] << el;
                // }
                ans[timer] = min(ans[timer], mn[spec[i]] + dist[i][x]);
            }
        }
    }

    del[u] = 1;
    for(int v : T[u]) if(!del[v]) decompose(v);
}



void DFS(int u, int prev){
    visited[u] = 1;
    for(int v : G[u]){
        if(!visited[v]){
            T[u].eb(v);
            T[v].eb(u);


            DFS(v, u);
        }else if(v != prev) {
            E[u].eb(v);
            cerr << u << ' ' << v << el;
        }
    }
}

void sol(){
    cin >> n >> m >> k;

    for(int i=0; m>i; i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    DFS(1, 0);

    int q = m;
    cin >> q;    

    // add[1].eb(0);

    for(int i=1; q>=i; i++){
        int type, u;
        cin >> type >> u;

        if(type == 1) add[u].eb(i);
        else query[u].eb(i);
    }

    memset(ans, 0x3f, sizeof ans);
    memset(idx, -1, sizeof idx);
    memset(mn, 0x3f, sizeof mn);
    decompose(1);

    for(int i=1; q>=i; i++) if(ans[i] != ans[0]) cout << ans[i] << el;
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