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

const ll N = 3e5 + 69, MOD = 1e9+7, INF = 1000000000000000069;

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


int n, m;
vect<pii> G[N];
int visited[N], P[N];
set<pii> dt[N]; // dt[u] = {val, 1 / -1} -> u = val + (1/-1) * x 
vect<dbl> nums[N];
dbl X[N], val[N];

void DFS(int u, int PAR){
    visited[u] = 1;
    P[u] = PAR;

    pii curr = *dt[u].begin();

    for(auto [v, w] : G[u]){

        pii new_dt = {w - curr.fi, curr.se * -1};

        if(dt[v].size() < 2) dt[v].insert(new_dt);

        if(!visited[v]) DFS(v, PAR);
    }
}

void DFS2(int u){
    visited[u] = 1;

    for(auto [v, w] : G[u]){
        pii equa = *dt[v].begin();
        val[v] = (dbl)equa.fi + equa.se * X[P[v]];
        if(!visited[v]) DFS2(v);
    }
}

bool check(int u){
    visited[u] = 1;

    bool res = true;

    for(auto [v, w] : G[u]){
        if(val[u] + val[v] != w) return false;

        if(!visited[v])
            res = min(res, check(v));
    }

    return res;
}

void sol(){
    cin >> n >> m;
    for(int i=0;m>i;i++){
        int u, v, w;
        cin >> u >> v >> w;
        G[u].eb(v, w);
        G[v].eb(u, w);
    }

    fill(X, X+N, 69.67);
    for(int i=1;n>=i;i++){
        if(visited[i]) continue;
        dt[i].insert({0, 1});
        DFS(i, i);
    }


    for(int i=1;n>=i;i++){
        if(dt[i].size() > 1){
            pii equa1 = *dt[i].begin(), equa2 = *dt[i].rbegin();

            if(equa1.se == equa2.se){
                cout << "NO\n";
                return;
            }else{
                int x_side = equa1.se - equa2.se, var_side = equa2.fi - equa1.fi;
                X[P[i]] = (dbl)var_side / x_side;
            }
        }
    }

    for(int i=1;n>=i;i++){
        if(X[P[i]] == 69.67){
            pii equa = *dt[i].begin();
            if(equa.se == 1) {
                equa.fi *= -1;
                equa.se *= -1;
            }
            nums[P[i]].eb(equa.fi);
        }
    }

    for(int i = 1;n>=i;i++){
        auto &v = nums[i];
        if(v.size()){
            sort(bend(v));
            X[i] = v[v.size()/2];
        }
    }

    memset(visited, 0, sizeof visited);

    for(int i=1;n>=i;i++){
        if(!visited[i] && X[P[i]] != 69.67) DFS2(i);
    }

    memset(visited, 0, sizeof visited);

    bool ok = true;
    for(int i=1;n>=i;i++){
        if(!visited[i]) ok = min(ok, check(i));
    }

    if(ok){
        cout << "YES\n";
        for(int i=1;n>=i;i++) cout << val[i] << ' ';
    }else{
        cout << "NO\n";
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
