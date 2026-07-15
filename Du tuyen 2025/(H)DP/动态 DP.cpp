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

int n, q, in[N], dep[N], sz[N], head[N], parent[N], a[N], susval[N][2], chainlen[N];
int fatn[N];
vect<int> G[N], order;

void prep(int u, int par){
    parent[u] = par;
    for(int v : G[u]) if(v != par){
        dep[v] = dep[u] + 1;
        prep(v, u);
        sz[u] += sz[v];
    }
}

void HLD(int u, int par, int chain_head){
    if(chain_head == -1) chain_head = u;
    head[u] = chain_head;
    chainlen[chain_head]++;

    in[u] = order.size();
    order.eb(u);

    pii fat;
    for(int v : G[u]) if(v != par){
        fat = max(fat, {sz[v], v});
    }

    fatn[u] = fat.se;
    if(fat.se){
        HLD(fat.se, u, chain_head); 
    }


    for(int v : G[u]) if(v != par && v != fat.se){
        HLD(v, u, -1);
    }
}

struct Hikari{
    int sus[2][2];

    Hikari(){
        memset(sus, 0, sizeof sus);
    }

    Hikari operator + (const Hikari &o) const{
        Hikari res;
        auto &cac = res.sus;
        for(int i=0; 1>=i; i++){
            for(int j=0; 1>=j; j++){
                cac[i][j] = max({sus[i][0] + o.sus[1][j],
                                sus[i][1] + o.sus[0][j],
                                sus[i][0] + o.sus[0][j]});
            }
        }
        return res;
    }
};

#define idl (id+1)
#define idr (id+2*(mid-l+1))

struct BDSM{
    vect<Hikari> t;
    int len, L, R;

    void init(int _L, int _R){
        L = _L;
        R = _R;
        len = R - L + 1;
        t.rs(len*2 + 5);
        build(L, R, 1);
    }

    void build(int l, int r, int id=1){
        if(l == r){
            t[id].sus[1][1] = susval[order[l]][1];
            t[id].sus[0][0] = susval[order[l]][0];
            // cerr << 
            return ;
        }
        int mid = (l+r)/2;
        build(l, mid, idl);
        build(mid+1, r, idr);
        t[id] = t[idl] + t[idr];
        // cerr << "! " << l << ' ' << r << ' ' << t[idr].sus[0][0] << el;

    }

    void upd(int p, int l, int r, int id=1){
        if(l > p || r < p) return;
        if(l == r){
            t[id].sus[1][1] = susval[order[l]][1];
            t[id].sus[0][0] = susval[order[l]][0];
            return ;
        }

        int mid = (l+r)/2;
        upd(p, l, mid, idl);
        upd(p, mid+1, r, idr);
        t[id] = t[idl] + t[idr];
    }

    int val(int i){return max(t[1].sus[i][0], t[1].sus[i][1]);}
} chains[N];

void Koe(int u, int newval){
    int rt = u;
    newval = max(0ll, newval);

    int hu = head[u];   

    // cout << susval[u][1] << ' ' << newval << ' ' << a[u] << el;


    susval[u][1] += -a[u] + newval;


    int old[2] = {chains[hu].val(0), chains[hu].val(1)};
    chains[hu].upd(in[u], in[hu], in[hu] + chainlen[hu] - 1);

    int nxt = parent[hu];

    while(nxt != 0){
        susval[nxt][0] -= max(old[0], old[1]);
        susval[nxt][1] -= old[0];

        susval[nxt][0] += max(chains[hu].val(0), chains[hu].val(1));
        susval[nxt][1] += chains[hu].val(0);

        u = nxt;
        hu = head[u];
        old[0] = chains[hu].val(0);
        old[1] = chains[hu].val(1);
        chains[hu].upd(in[u], in[hu], in[hu] + chainlen[hu] - 1);

        // cout << hu << ' ' << chains[hu].val(0) << ' ' << chains[hu].val(1) << ' ' << old[0] << ' ' << old[1] << el;

        nxt = parent[hu];
    }

    // cerr << "reached! " << a[rt] << ' ' << rt << ' ' << newval << el;
    a[rt] = newval;
}

void dfs(int u, int par){
    susval[u][1] = a[u];

    if(fatn[u]) dfs(fatn[u], u);
    for(int v : G[u]) if(v != par && v != fatn[u]){
        dfs(v, u);
        susval[u][1] += chains[v].val(0);
        susval[u][0] += max(chains[v].val(0), chains[v].val(1));
    }

    if(u == head[u]){
        // cerr << u << ' ' << in[u] << ' ' << in[u] + chainlen[u] - 1 << el;
        chains[u].init(in[u], in[u] + chainlen[u] - 1);
    }


void sol(){
    cin >> n >> q;

    for(int i=1; n>=i; i++){
        cin >> a[i];
        if(a[i] < 0) a[i] = 0;
    }

    for(int i=1; n>i; i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    prep(1, 0);
    HLD(1, 0, -1);
    dfs(1, 0);

    // for(int i : order) cout << i << ' ';
    // cout << "\n----- \n";

    // for(int i=1; n>=i; i++){
    //     cout << susval[i][0] << ' ' << susval[i][1] << ' ' << head[i] << el;
    // }

    // cout << "st: " << max(chains[1].val(0), chains[1].val(1)) << el;


    while(q--){
        int u, x;
        cin >> u >> x;
        Koe(u, x);

        cout << max(chains[1].val(0), chains[1].val(1)) << el;
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