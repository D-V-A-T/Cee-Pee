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


#define FILE "CROSS"
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

const ll N = 3e5 + 69, MOD = 1e9+7, INF = 2e8;

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
vect<int> G[N];
int a[N];

namespace sub1{
void solve(){

    vect<int> pos(n+5);
    int ok = 0;

    for(int i=1;n>=i;i++){
        ok += a[i] > -1;
        if(a[i] == -1) continue;

        if(a[i] == 0){
            pos[i]++;
            continue;
        }

        if(i - a[i] >= 1) pos[i - a[i]]++;

        if(i + a[i] <= n) pos[i + a[i]]++;
    }

    vect<int> ans;
    for(int i=1;n>=i;i++) if(pos[i] == ok) ans.eb(i);
    cout << ans.size() << el;
    for(int i : ans) cout << i << ' ';
}
}

namespace sub23{

vect<int> sub2(int source){
    queue<int> bfs;
    bfs.push(source);

    vect<int> dist(n+5, INF), visited(n+5);
    dist[source] = 0;

    while(bfs.size()){
        int u = bfs.front();
        bfs.pop();

        if(visited[u]) continue;
        visited[u] = 1;

        for(int v : G[u]){
            if(dist[v] > dist[u] + 1){
                dist[v] = dist[u] + 1;
                bfs.push(v);
            }
        }
    }

    vect<int> res;

    for(int i=1;n>=i;i++) if(dist[i] == a[1]){
        res.eb(i);
    }
    return res;
}

int cbd[N];
void sub3(int source){
    queue<int> bfs;
    int visited[n+4], dist[n+4];

    memset(visited, 0, sizeof visited);
    memset(dist, 5, sizeof dist);

    bfs.push(source);
    dist[source] = 0;

    while(bfs.size()){
        int u = bfs.front();
        bfs.pop();

        if(visited[u]) continue;
        visited[u] = 1;

        for(int v : G[u]){
            if(dist[v] > dist[u] + 1){
                dist[v] = dist[u] + 1;
                bfs.push(v);
            }
        }        
    }

    for(int i=1;n>=i;i++) if(dist[i] == a[source]) cbd[i]++;
}

void solve(int subtask){
    vect<int> v, ans;
    for(int i=1;n>=i;i++){
        if(a[i] > -1) v.eb(i); 
    }

    if(subtask == 2){
        ans = sub2(1);
        if(a[1] == -1){
            ans.assign(n, 0);
            iota(bend(ans), 1);
        }
    }
    else{
        for(int i : v) sub3(i);

        for(int i=1;n>=i;i++) if(cbd[i] == v.size()) ans.eb(i);
    }

    cout << ans.size() << el;
    for(int i : ans) cout << i << ' ';
}
}

namespace gacha{
int dist[N], visited[N];

vect<int> E(int source, int type){
    fill(dist, dist+n+5, (int)2e8);
    fill(visited, visited+n+5, 0);

    queue<int> bfs;
    bfs.push(source);
    dist[source] = 0;

    while(bfs.size()){
        int u = bfs.front();
        bfs.pop();

        if(a[u] > -1 && dist[u] != a[u] && type == 2){
            return {};
        }

        if(visited[u]) continue;
        visited[u] = 1;

        for(int v : G[u]){
            if(dist[v] > dist[u] + 1){
                dist[v] = dist[u] + 1;
                bfs.push(v);
            }
        }
    }

    if(type == 1){
        vect<int> f;
        for(int i=1;n>=i;i++) if(dist[i] == a[source]) f.eb(i);
        return f;
    }else{
        return {69};
    }
}

void solve(){
    vect<int> v, ans;

    for(int i=1;n>=i;i++){
        if(a[i] > -1) v.eb(i);
    }

    shuffle(bend(v), rng);

    vect<int> best;
    for(int i=0; min((size_t)400, v.size()) > i;i++){
        vect<int> fumo = E(v[i], 1);

        if(best.empty() || (fumo.size() < best.size() && fumo.size()>0)) swap(best, fumo);

        if(best.size() > 0 && best.size() <= 300){
            break;
        }
    }

    for(int i : best) if(E(i, 2).size() == 1){
        ans.eb(i);
    }

    cout << ans.size() << el;
    for(int i : ans) cout << i << ' ';
}
}

void sol(){
    cin >> n >> m;
    bool sub1 = 1, sub2 = 1, sub3 = 1;
    for(int i=0;m>i;i++){
        int u, v;
        cin >> u >> v;
        if(u+1 != v) sub1 = 0;
        G[u].eb(v);
        G[v].eb(u);
    }

    int not_neg1_cnt = 0;
    for(int i=1;n>=i;i++){
        cin >> a[i];
        if(i > 1 && a[i] > -1) sub2 = 0;
        not_neg1_cnt += a[i] > -1;
    }

    sub3 = not_neg1_cnt <= 1000 || n <= 5000;

    if(sub1) sub1::solve();
    else if(sub2) sub23::solve(2);
    else if(sub3) sub23::solve(3);
    else gacha::solve();
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