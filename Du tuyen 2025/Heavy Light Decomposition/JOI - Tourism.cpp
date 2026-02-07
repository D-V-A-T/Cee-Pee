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
#define ull unsigned long long

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
ll pm(ll a,const ll b=MOD){return ((a%b)+b)%b;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}   

int n, m, q;
int c[N], sz[N], dep[N], head[N], parent[N], in[N], spt[N][20];
vect<int> G[N], order;
vect<pii> stk[N];

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

    head[u] = chain_head == -1 ? u : chain_head;
    int fat = 0;

    for(int v : G[u]) if(v != par){
        if(sz[fat] < sz[v]) fat = v;
    }

    if(fat) HLD(fat, u, head[u]);

    for(int v : G[u]) if(v != par && v != fat) HLD(v, u, -1);
}

struct Seggs{
    int t[4 * N], lca[4 * N];
    Seggs(){
        memset(t, 0, sizeof t);
    }

    void upd(int i, int x, int l=1, int r=m, int id=1){
        if(l > i || r < i) return;
        if(l == r){
            t[id] += x;
            return;
        }
        int mid = (l + r)/2;
        upd(i, x, l, mid, id*2);
        upd(i, x, mid+1, r, id*2+1);
        
        t[id] = t[id * 2] + t[id*2 + 1];
    }

    int get(int i, int j, int l=1, int r=m, int id=1){
        if(l > j || r < i) return 0;
        if(i <= l && r <= j) return t[id];
        int mid = (l+r)/2;
        return get(i, j, l, mid, id*2) + get(i, j, mid+1, r, id*2+1);
    }
} sgt;

int dt[N][20], mask[N];

int get_lca(int u, int v){ 
    if(u == 0 || v == 0){
        cout << "PROBLEM\n";
        exit(0);
    } 
    while(head[u] != head[v]){ 
        if(dep[head[u]] > dep[head[v]]) u = parent[head[u]]; 
        else v = parent[head[v]]; 
    } 
    return dep[u] < dep[v] ? u : v; 
}

void dnc(int l, int r, int dep){
    if(l == r) return;

    int mid = (l+r)/2;

    dt[mid][dep] = c[mid];
    for(int i=mid-1; i>=l; i--) dt[i][dep] = get_lca(dt[i+1][dep], c[i]);

    dt[mid+1][dep] = c[mid+1];
    for(int i=mid+1; r>=i; i++) dt[i][dep] = get_lca(dt[i-1][dep], c[i]);

    for(int i = mid+1; r>=i; i++) mask[i] ^= (1<<dep);

    dnc(l, mid, dep+1);
    dnc(mid+1, r, dep+1);
}

void add(int x){
    int node = c[x];

    // cout << x << ' ' << node << ' ' << head[node] << el;

    while(node != 0){
        int contri = dep[node] - dep[head[node]] + 1, y, cy, curr_depth = 0;
        auto &st = stk[head[node]];
        
        while(st.size()){
            tie(y, cy) = st.back();
            curr_depth += cy;
            if(curr_depth <= contri) sgt.upd(y, -cy);
            else break;
            st.pob();
        }

        if(st.size()){
            tie(y, cy) = st.back();

            sgt.upd(y, -cy);
            sgt.upd(y, curr_depth - contri);

            // cout << "! " << curr_depth << ' ' << - cy << el;

            st.back().se = curr_depth - contri;
        }
        
        st.eb(x, contri);
        // cout << x << ' ' << contri << el;
        sgt.upd(x, contri);

        node = parent[head[node]];
    }
}


void sol(){
    cin >> n >> m >> q;
    for(int i=1; n>i; i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    // dep[1] = 1;
    prep(1, 0);
    HLD(1, 0, -1);

    for(int i=1; m>=i; i++) cin >> c[i];

    dnc(1, m, 0);

    auto get_range_lca = [&](int l, int r){
        if(l == r) return c[l];
        int dep = __builtin_ctzll(mask[l] ^ mask[r]);
        // cout << dt[l][dep] << ' ' << dt[r][dep] << ' '  << l << ' ' << r << ' ' << dep << el;
        return get_lca(dt[l][dep], dt[r][dep]);
        // return 0;
    };

    int ans[q];
    vect<pii> queries[m+5];
    for(int i=0; q>i; i++){
        int l, r;
        cin >> l >> r;
        queries[r].eb(l, i);
    }

    for(int r=1; m>=r; r++){
        add(r);

        for(auto [l, id] : queries[r]){
            // cout << "!!!! " << get_range_lca(l, r) << el;
            ans[id] = sgt.get(l, r) - (dep[get_range_lca(l, r)] - dep[1]);
        }   
    }

    for(int i : ans) cout << i << el;
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