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

const ll N = 1e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

const int S = 569, MAX_BLOCK = N / S + 5;

struct edge{
    int u, v, w, id;
    bool operator < (const edge &o) const{
        return w > o.w;
    }

};


const int NECKHURT = 5e4+2;
struct DSU{
    int par[NECKHURT], len[NECKHURT];
    DSU(){
        START();
    }

    void START(){
        iota(par, par+NECKHURT, 0);
        fill(len, len+NECKHURT, 1);
    }

    void init(int u, int w=1){
        par[u] = u;
        len[u] = w;
    }

    int findpar(int u){
        return par[u] == u ? u : par[u] = findpar(par[u]);
    }

    void join(int u, int v){
        u = findpar(u), v = findpar(v);
        if(u != v){
            if(len[u] < len[v]) swap(u, v);
            len[u] += len[v];
            par[v] = u;
        }
    }
} ds, ia;

vect<edge> QUERY, sus[N];
bool gay[N];
int ans[N], upd_cnt = 0;

void sol(){
    int n, m, q;
    cin >> n >> m;
    vect<edge> E(m);
    for(int i=0; m>i; i++){
        cin >> E[i].u >> E[i].v >> E[i].w;
        E[i].id = i;
    }

    vect<int> curr, change;
    vect<pii> revert;
    vect<edge> tmp;
    cin >> q;

    auto diddyparty = [&](){
        sort(bend(QUERY));
        curr.clear();

        change.clear();
        revert.clear();

        for(int i=0; m>i; i++){
            if(!gay[i]) curr.eb(i);
            else change.eb(i), revert.eb(i, E[i].w);
        }

        sort(bend(curr), [&E](int a, int b){
            return E[a].w > E[b].w;
        });

        ds.START();
        ia.START();

        int ptr = 0;
        for(auto [u, _, w, id] : QUERY){
            while(ptr < curr.size() && E[curr[ptr]].w >= w) {
                ds.join(E[curr[ptr]].u, E[curr[ptr]].v);
                ptr++;
            }

            for(edge &e : sus[id]){
                E[e.id].w = e.w;
            }

            for(int i : change){
                // if(id == 0) cerr << "x\n";
                if(E[i].w >= w){
                    int px = ds.findpar(E[i].u), py = ds.findpar(E[i].v);
                    ia.init(px, ds.len[px]);
                    ia.init(py, ds.len[py]);
                }
            }

            for(int i : change){
                if(E[i].w >= w){
                    int px = ds.findpar(E[i].u), py = ds.findpar(E[i].v);
                    ia.join(px, py);
                }
            }

            ans[id] = max(ia.len[ia.findpar(ds.findpar(u))], ds.len[ds.findpar(u)]);

            
            for(int i : change){
                if(E[i].w >= w){
                    int px = ds.findpar(E[i].u), py = ds.findpar(E[i].v);
                    ia.init(px, 0);
                    ia.init(py, 0);
                }
            }
            for(pii i : revert) E[i.fi].w = i.se;

        }
    };



    for(int i=0; q>i; i++){
        int type;
        cin >> type;
        if(type == 1){
            int id, nw;
            cin >> id >> nw;
            id--;

            if(upd_cnt >= S){
                diddyparty();

                for(edge &e : tmp){
                    E[e.id].w = e.w;
                }

                upd_cnt = 0;
                QUERY.clear();
                tmp.clear();
                memset(gay, 0, sizeof gay);
            }
            tmp.pb({E[id].u, E[id].v, nw, id});
            gay[id] = 1;
            upd_cnt ++;
        }else{
            int u, w;
            cin >> u >> w;
            QUERY.pb({u, -1, w, i});
            sus[i] = tmp;
        }
    }

    diddyparty();

    for(int i=0; q>i; i++) if(ans[i]) cout << ans[i] << el;
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