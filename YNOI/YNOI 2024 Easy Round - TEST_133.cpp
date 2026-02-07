#ifdef ONLINE_JUDGE

#include<bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,popcnt,lzcnt,tune=native")

#endif 

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

const ll N = 5e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

const int S = sqrt(N), MAX_BLOCK = N / S + 2;

int n, q;

ll curr_add[MAX_BLOCK], max_add[MAX_BLOCK];

void sol(){
    cin >> n >> q;
    pair<ll, ll> a[n], b[n];
    ll pfmx[n];
    // {curr_val, max_val}

    for(auto& i : a) cin >> i.fi, i.se = i.fi;

    auto rebuild_block = [&](int block_num){
        int st = block_num * S, ed = min(n, (block_num+1) * S);
        copy(a + st, a + ed, b + st);
        sort(b + st, b + ed);
        pfmx[st] = b[st].se;
        for(int i = st + 1; ed > i; i++) pfmx[i] = max(pfmx[i-1], b[i].se);  
    };

    for(int bl = 0; (n-1) / S >= bl; bl++) rebuild_block(bl);

    while(q--){
        int t, l, r, x;
        cin >> t >> l >> r >> x;
        l--, r--;
        int block_l = l / S, block_r = r / S;
        int lim_l = min(n, (block_l + 1) * S), lim_r = min(n, (block_r + 1) * S);

        // cout << a[2].fi << ' ' << a[2].se << el;

        if(t == 1){

            if(block_l == block_r){


                for(int i = block_l * S; lim_l > i; i++) {
                    a[i].se = max(a[i].se, a[i].fi + max_add[block_l]);

                    if(l <= i && i <= r){
                        a[i].se = max(a[i].se, a[i].fi + curr_add[block_l] + x);
                        a[i].fi += x;
                    }

                    a[i].fi += curr_add[block_l];
                }
                curr_add[block_l] = max_add[block_l] = 0;

                rebuild_block(block_l);
            }else{
                for(int i = block_l * S; lim_l > i; i++) {
                    a[i].se = max(a[i].se, a[i].fi + max_add[block_l]);

                    if(l <= i){
                        a[i].se = max(a[i].se, a[i].fi + curr_add[block_l] + x);
                        a[i].fi += x;
                    }
                    
                    a[i].fi += curr_add[block_l];
                }
                curr_add[block_l] = max_add[block_l] = 0;
                rebuild_block(block_l);

                for(int i = block_l + 1; block_r > i; i++){
                    curr_add[i] += x;
                    max_add[i] = max(max_add[i], curr_add[i]);
                }

                for(int i = block_r * S; lim_r > i; i++){
                    a[i].se = max(a[i].se, a[i].fi + max_add[block_r]);

                    if(i <= r){
                        a[i].se = max(a[i].se, a[i].fi + curr_add[block_r] + x);
                        a[i].fi += x;
                    }

                    a[i].fi += curr_add[block_r];
                }
                curr_add[block_r] = max_add[block_r] = 0;
                rebuild_block(block_r);

                // cout << l << ' ' << block_l << ' ' << r << ' ' << block_r << el;
            }
        }else{
            ll ans = -INF;
            if(block_l == block_r){
                for(int i = l; r >= i; i++){
                    a[i].se = max(a[i].se, a[i].fi + max_add[block_l]);
                    if(a[i].fi + curr_add[block_l] < x) ans = max(ans, a[i].se);
                }
            }else{
                for(int i = l; lim_l > i; i++){
                    a[i].se = max(a[i].se, a[i].fi + max_add[block_l]);
                    if(a[i].fi + curr_add[block_l] < x) ans = max(ans, a[i].se);
                }

                for(int i = block_l + 1; block_r > i; i++){
                    int p = lwb(b + i * S, b + (i + 1) * S, make_pair(x - curr_add[i], -INF)) - b - 1;
                    
                    // cout << pfmx[p] << el;

                    if(p >= i * S) ans = max(ans, max(pfmx[p], b[p].fi + max_add[i]));
                }

                for(int i = block_r * S; r >= i; i++){
                    a[i].se = max(a[i].se, a[i].fi + max_add[block_r]);
                    if(a[i].fi + curr_add[block_r] < x) ans = max(ans, a[i].se);
                }
            }       
            
            if(ans == -INF) cout << "-inf\n";
            else cout << ans << el;
        }
        
        // cout << a[2].fi << el;
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
