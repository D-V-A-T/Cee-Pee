#include<bits/stdc++.h>
using namespace std; 
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define umap unordered_map
#define prq priority_queue
#define vect vector
#define rs resize
#define bend(v) v.begin(),v.end()
#define pob pop_back
#define pof pop_front
#define lwb lower_bound
#define upb upper_bound
#define pii pair<int,int>
#define nextl cout << '\n'
#define el '\n'
#define deb cout<<"\nok\n";return 
#define ll long long
#define int long long
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
#define FILE "ellencute"
 
const ll INF=902337203695775807, N=4e5+69, MOD=1e9+7;    
 
void ffopen(){
    if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }else if(fopen("ellencute.inp", "r")){
        freopen("ellencute.inp", "r", stdin);
        freopen("ellencute.out", "w", stdout);
    }
}

int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

vect<int> G[N], order;
int in[N], out[N], inque[N], dep[N], id[N], ans = 0;
pii spt[N][21];
vect<pii> VT[N];

int lg2(int i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void Etour(int u, int par, int& timer){
    in[u] = ++timer;
    id[u] = order.size();
    order.eb(u);

    for(int v : G[u]) if(v != par){
        dep[v] = dep[u]+1;
        Etour(v, u, timer);
        order.eb(u);
    }

    out[u] = timer;
}

void prepLCA(){
    for(int i=0;order.size()>i;i++)
        spt[i][0] = {dep[order[i]], order[i]};
    
    for(int b=1;20>=b;b++){
        for(int i=0;order.size()>=i + (1<<b);i++){
            spt[i][b] = min(spt[i][b-1], spt[i+(1<<(b-1))][b-1]);
        }
    }
}

inline int LCA(int u, int v){
    int l = id[u], r = id[v];
    if(l > r) swap(l, r);
    int b = lg2(r-l+1);
    return min(spt[l][b], spt[r - (1<<b) + 1][b]).se;
}

inline int get_dist(int u, int v){
    return dep[u] + dep[v] - 2*dep[LCA(u,v)];
}

inline bool in_tree(int u, int v) {
  return in[u] < in[v] && out[u] >= out[v];
}


int DFS(int u, int total){
    int quenodes = 0;

    for(auto [v, w] : VT[u]){
        int sub = DFS(v, total);

        ans += ((total - sub) * sub % MOD) * w;
        ans = pm(ans);

        quenodes += sub;
        quenodes %= MOD;
    }

    quenodes += inque[u] * u;
    quenodes %= MOD;
    return quenodes;
}

void sol(){
    int n, q;
    cin >> n >> q;

    for(int i=1;n>i;i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    int timer = 0;dep[1] = 0;
    Etour(1, 0, timer);
    prepLCA();

    while(q--){
        int k, total = 0;
        cin >> k;
        vect<int> a(k);
        for(int& i : a) cin >> i, inque[i] = 1, total += i;
        total %= MOD;

        sort(bend(a), [](int u, int v){
            return in[u] < in[v];
        });

        int z = a.size();
        for(int i=0;z>i+1;i++) a.eb(LCA(a[i], a[i+1]));

        sort(bend(a), [](int u, int v){
            return in[u] < in[v];
        });
        a.rs(unique(bend(a)) - a.begin());

        stack<int> st;
        st.push(a[0]);

        for(int i=1;a.size()>i;i++){
            while(st.size() && !in_tree(st.top(), a[i])) st.pop();

            if(st.size())
                VT[st.top()].eb(a[i], get_dist(a[i], st.top()));

            st.push(a[i]);
        }

        ans = 0;
        int dsdsd = DFS(a[0], total);

        for(int i : a) VT[i].clear(), inque[i] = 0;

        cout << ans << el;

    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    //cin >> t;
    while(t--)sol();
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