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

const ll N = 3e5 + 10, MOD = 1e9+7, INF = 1000000000000000069;

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

int n, sz[N], dep[N], del[N];
vect<int> G[N], ans(N, 1);

void prep(int u, int par){
    sz[u] = 1;
    for(int v : G[u]) if(v != par && !del[v]){
        dep[v] = dep[u] + 1;
        prep(v, u);
        sz[u] += sz[v];
    }
}

int get_centroid(int u, int par, int rt){
    for(int v : G[u]) if(v != par && !del[v] && sz[v]*2 > sz[rt])
        return get_centroid(v, u, rt);
    return u;
}

void dfsus(int u, int par, int dep, vect<pii> &vec){
    vec.eb(dep, sz[u]);
    for(int v : G[u]) if(v != par && !del[v]){
        dfsus(v, u, dep+1, vec);
    }
}

vect<pii> balo[N];

struct comp{
    bool operator()(int a, int b){
        if(!balo[a].empty() && !balo[b].empty())
            return balo[a].back() < balo[b].back();
        return balo[a].size() > balo[b].size();
    }
};

void decompose(int u){
    prep(u, 0);
    u = get_centroid(u, 0, u);
    prep(u, 0);

    cerr << "! " << u << el;

    prq<int, vect<int>, comp> pq;

    auto print = [](prq<int, vect<int>, comp> pq){
        while(pq.size()){
            cerr << "? " << pq.top() << ' ' << balo[pq.top()].back().fi << el;
            pq.pop();
        }
    };

    for(int v : G[u]) if(!del[v]){
        balo[v].clear();
        dfsus(v, u, 1, balo[v]); 
        sort(bend(balo[v]), greater<pii>());

        auto &vec = balo[v];
        for(int i=1; vec.size()>i; i++){
            vec[i].se = max(vec[i-1].se, vec[i].se);
        }
        reverse(bend(vec));


        // cout << v << ": ";
        // for(pii i : vec) cout << "(" << i.fi << ' ' << i.se << "), ";
        // nextl;


        pq.push(v);
    }

    auto update = [&](int i){
        while(true && pq.size()){
            int x = pq.top();
            if(balo[x].empty()){
                pq.pop();
                continue;
            }
            pq.pop();
            if(balo[x].back().se < i/2){
                balo[x].pob();
                pq.push(x);
            }
            else{
                pq.push(x);
                break;
            }
        }
    };

    for(int i=2; sz[u]>=i; i+=2){
        update(i);

        if(pq.empty()){
            continue;
        }

        // if(i == 6){
        //     print(pq);
        //     cerr << "--------------\n";
        // }
        int x = pq.top();
        pq.pop();
        update(i);

        if(pq.empty()){
            if(sz[u] - sz[x] >= i/2) {
                ans[i] = max(ans[i], balo[x].back().fi + 1);
            }
            pq.push(x);
            continue;
        }

        int y = pq.top();

        // if(i == 6){
        //     print(pq);
        //     cerr << balo[5].size() << el;
        //     cerr << x << ' ' << y << el;
        //     cerr << balo[x].back().fi << ' ' << balo[y].back().fi << el;
        // }

        ans[i] = max(ans[i], balo[x].back().fi + balo[y].back().fi + 1);
        pq.push(x);
    }

    del[u] = 1;
    for(int v : G[u]) if(!del[v]) decompose(v);

}

void sol(){
    cin >> n;

    for(int i=1; n>i; i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    decompose(1);

    for(int i=1; n>=i; i++) cout << ans[i] << el;
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