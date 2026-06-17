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

int n, m, f, dist[N], ans[N];
vect<int> npp, dihsize, verts;
vect<pii> G[N];

struct DSU{
    vect<int> par, len;
    void init(int n){
        par.rs(n+5);
        len.rs(n+5, 1);
        iota(bend(par), 0);
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
};

void dickcha(){
    memset(dist, 5, sizeof dist);
    prq<pii, vect<pii>, greater<pii>> pq;
    for(int i : npp) dist[i] = 0, pq.push({0, i});

    while(pq.size()){
        auto [d, u] = pq.top();
        pq.pop();
        if(d > dist[u]) continue;

        for(auto [v, w] : G[u]){
            if(d + w < dist[v]){
                dist[v] = d + w;
                pq.push({d + w, v});
            }
        }
    }

    for(int i=1; n>=i; i++) dihsize.eb(dist[i]), verts.eb(i);
    sort(bend(dihsize));
    sort(bend(verts), [](int u, int v){
        return dist[u] > dist[v];
    });
    dihsize.rs(unique(bend(dihsize)) - dihsize.begin());
    f = dihsize.size();
}

struct query{
    int l, r, id, lo, hi;
};

void PBS(vect<query> ques){

    while("sussy"){
        DSU ds;
        ds.init(n);

        vect<query*> islands[n+1];

        bool imposter = 0;

        for(auto &qu : ques){
            auto &[l, r, id, lo, hi] = qu;
            if(lo <= hi){
                imposter = 1;
                int mid = (lo + hi) / 2;
                islands[mid].pb(&qu);
            }
        }


        if(!imposter) break;

        int ptr = 0;
        for(int i=f-1; i>=0; i--){
            while(ptr < n && dist[verts[ptr]] >= dihsize[i]){
                int u = verts[ptr];
                for(auto [v, w] : G[u]) if(dist[v] >= dihsize[i]) ds.join(u, v);
                ptr++;
            }

            for(auto &qu : islands[i]){
                auto &[l, r, id, lo, hi] = *qu;
                if(ds.findpar(l) == ds.findpar(r)){
                    ans[id] = dihsize[i];
                    lo = i+1;
                }else hi = i-1;
            }
        }

    }
}


void sol(){
    cin >> n >> m;

    for(int i=0; m>i; i++){
        int u, v, w;
        cin >> u >> v >> w;
        G[u].eb(v, w);
        G[v].eb(u, w);
    }

    int k;
    cin >> k;
    npp.rs(k);
    for(int &i : npp) cin >> i;

    dickcha();


    int q;
    cin >> q;
    vect<query> ques(q);
    for(int i=0; q>i; i++){
        cin >> ques[i].l >> ques[i].r;
        ques[i].lo = 0;
        ques[i].hi = f-1;
        ques[i].id = i;
    }

    PBS(ques);

    for(int i=0; q>i; i++) cout << ans[i] << el;
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