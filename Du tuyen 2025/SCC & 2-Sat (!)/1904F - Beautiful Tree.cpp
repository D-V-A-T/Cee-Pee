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


const int N2 = N*2+5, SZ = 3e6;
#define idl (id+1)
#define idr (id+2*(mid-l+1))
int n, q, head[SZ], sz[SZ], P[SZ], dep[SZ], in[SZ];
basic_string<int> G[SZ], order;

void prep(int u, int par){
    sz[u] = 1;
    for(int v : G[u]) if(v != par) {
        prep(v, u);
        sz[u] += sz[v];
    }
}

void HLD(int u, int par, int head_chain){
    in[u] = order.size();
    order += (u);
    dep[u] = dep[par] + 1;
    P[u] = par;

    if(head_chain == -1) head_chain = u;
    head[u] = head_chain;

    pii fat = {0, 0};
    for(int v : G[u]) if(v != par){
        fat = max(fat, {sz[v], v});
    }

    if(fat.se) HLD(fat.se, u, head_chain);

    for(int v : G[u]) if(v != fat.se && v != par) HLD(v, u, -1);
}

vect<int> W[SZ], indeg(SZ), seen(SZ);


void add_edge(int u, int v){

    assert(max(u, v) < indeg.size());
    seen[u] = seen[v] = 1;
    W[u].eb(v);
    indeg[v]++;

}

int idx[SZ], pos[SZ], mxid = 0, susval[SZ], nodecnt = 0;


struct SigeonPex{

    void build(int par = 0, int l=0, int r=n-1, int id=1){
        // cout << id << ' ' << l << ' ' << r << el

        if(l == r){
            add_edge(par, id);
            add_edge(id, par+N2);

            pos[id] = l;
            idx[l] = id;

            nodecnt += 3;
            return;
        }

        int mid = (l+r)>>1;

        if(par != 0){
            add_edge(par, id);
            add_edge(id+N2, par+N2);
            nodecnt += 4;
        }

        build(id, l, mid, idl);
        build(id, mid+1, r, idr);
    }

    void connect(int x, int i, int j, bool sus, int l=0, int r=n-1, int id=1){
        if(i > j) return;

        if(l > j|| r < i) return;
        if(i <= l && r <= j){
            if(sus){
                if(pos[id] == -1){
                    add_edge(id+N2, idx[in[x]]);
                }
                else{
                    add_edge(id, idx[in[x]]);
                }
            }else{
                add_edge(idx[in[x]], id);
            }
            return;
        }

        int mid = (l+r)>>1;

        connect(x, i, j, sus, l, mid, idl);
        connect(x, i, j, sus, mid+1, r, idr);
    }  

} sp;

void MontagemHikari(int x, int u, int v, bool cac){
    while(head[u] != head[v]){
        if(dep[head[u]] < dep[head[v]]) swap(u, v);

        if(in[head[u]] <= in[x] && in[x] <= in[u]){
            sp.connect(x, in[head[u]], in[x]-1, cac);
            sp.connect(x, in[x]+1, in[u], cac);
        }else{
            sp.connect(x, in[head[u]], in[u], cac);
        }

        u = P[head[u]];
    }

    if(in[u] > in[v]) swap(u, v);

    if(in[u] <= in[x] && in[x] <= in[v]){
        sp.connect(x, in[u], in[x]-1, cac);
        sp.connect(x, in[x]+1, in[v], cac);
    }else{
        sp.connect(x, in[u], in[v], cac);
    }
}

vect<pii> op[2][SZ];

void sol(){
    cin >> n >> q;

    for(int i=1; n>i; i++){
        int u, v;
        cin >> u >> v;
        G[u] += (v);
        G[v] += (u);
    }

    memset(pos, -1, sizeof pos);
    prep(1, 0);
    HLD(1, 0, -1);



    sp.build();


    while(q--){
        int type, u, v, x;
        cin >> type >> u >> v >> x;
        MontagemHikari(x, u, v, type-1); 
    }

    queue<int> que;
    nodecnt = 0;
    for(int i=1; N2*2 > i; i++){
        nodecnt += seen[i];
        if(indeg[i] == 0 && seen[i]) que.push(i);
    }


    vect<int> topo, ans(n+5);
    int SUS = 0;
    while(que.size()){
        int u = que.front();
        topo.eb(u);
        if(pos[u] != -1) ans[order[pos[u]]] = ++SUS;
        que.pop();
        for(int v : W[u]) if(--indeg[v] == 0) que.push(v);
    }

    if(topo.size() != nodecnt){
        cout << "-1";
        return;
    }    
 
    for(int i=1; n>=i; ++i) cout << ans[i] << ' ';
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