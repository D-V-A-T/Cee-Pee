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

const int S = 318, MAX_BLOCK = N / S + 2;

vect<int> blk[MAX_BLOCK];
int mn[MAX_BLOCK], mx[MAX_BLOCK], pos[N];

void sol(){
    int n, k;
    cin >> n >> k;
    vect<int> a(n);
    
    for(int &i : a) cin >> i;

    auto build = [&](){
        memset(mn, 5, sizeof mn);
        memset(mx, -1, sizeof mx);
        for(int i=0; n>i; i++){
            blk[i / S].eb(a[i]);
            mn[i / S] = min(mn[i / S], a[i]);
            mx[i / S] = max(mx[i / S], a[i]);
        }
    };

    auto recalc = [&](int id){
        mn[id] = MOD;
        mx[id] = -1;
        for(auto &i : blk[id]) mn[id] = min(mn[id], i), mx[id] = max(mx[id], i);
    };

    build();

    auto gud = [&](int a, int b){
        return abs(a - b) <= k;
    };


    for(int i=0; MAX_BLOCK > i; i++){
        auto &v = blk[i];
        for(int j=0; v.size() > j; ){
            int x1 = MOD, x2 = -1, best_pos = j;
            bool change = 0;

            // for(int f : blk[i]) cerr << f << ' ';
            // cerr << el;

            for(int f=j-1; f>=0; f--){
                x1 = min(x1, v[f]);
                x2 = max(x2, v[f]);

                if(gud(x2, v[j]) && gud(x1, v[j])){
                    if(v[f] > v[j]) best_pos = f;
                    continue;
                }


                int tmp = v[j];
                v.erase(v.begin() + j);
                v.insert(v.begin() + best_pos, tmp);
                change = 1;
                break;
            }

            // cout << j << ' ' << v[j] << ' ' << v.size() << el;

            if(change) {
                j++;
                continue;
            }

            int best_block = i;

            for(int f=i-1; f>=0; f--){
                if(gud(mx[f], v[j]) && gud(mn[f], v[j])){
                    if(mx[f] > v[j]) best_block = f;
                    continue;
                }

                auto &u = blk[f];
                int t1 = MOD, t2 = -1, bp = -1;
                for(int z=u.size()-1; z>=0; z--){
                    t1 = min(t1, u[z]);
                    t2 = max(t2, u[z]);

                    if(gud(t1, v[j]) && gud(t2, v[j])){
                        if(u[z] > v[j]) bp = z;
                        continue;
                    }

                    break;
                }

                if(bp == -1) break;

                // cout << "! " << v[j] << ' ' << bp  << el;

                int tmp = v[j];
                v.erase(v.begin() + j);
                u.insert(u.begin() + bp, tmp);
                change = 1;

                recalc(i);
                recalc(f);
                break;
            }

            if(change) continue;

            auto &u = blk[best_block];
            if(best_block != i){
                for(int f=u.size()-1; f>=0; f--){
                    x1 = min(x1, u[f]);
                    x2 = max(x2, u[f]);

                    if(gud(x1, v[j]) && gud(x2, v[j])){
                        if(u[f] > v[j]) best_pos = f;
                        continue;
                    }

                    break;
                }
            }

            // cout << "! " << j << ' ' << v[j] << ' ' << best_pos << ' ' << best_block << ' ' << v[j] << el;

            int tmp = v[j];
            v.erase(v.begin() + j);
            u.insert(u.begin() + best_pos, tmp);

            recalc(i);
            recalc(best_block);

            if(best_block == i) j++;
        }

        // cout << "\n===============\n";

        a.clear();
        for(auto &j : blk){
            for(auto &f : j) a.eb(f);
            j.clear();
        }
        build();
    }

    for(auto &j : blk){
        for(auto &f : j) cout << f << el;
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