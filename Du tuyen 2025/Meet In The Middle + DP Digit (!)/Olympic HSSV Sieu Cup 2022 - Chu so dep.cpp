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
ll pm(ll a,const ll b=MOD){return ((a%b)+b)%b;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int okay[5000];

int E(int num){
    if(num == 0) return 0;
    vect<int> x(20);
    int len = 0;
    while(num){
        x[len++] = num % 10;
        num /= 10;
    }

    const int full = (1<<len) - 1;

    ll dp[5000][12][2];
    memset(dp, 0, sizeof dp);
    dp[0][11][0] = 1;

    for(int d=9; d>=0; d--){


        for(int mask=full; mask>=0; mask--){
            
            int cac = ~mask & full;

            for(int sm=cac; sm>0; sm = (sm-1) & cac){
                if(!okay[sm] || (d==0 && sm>mask)) continue;


                int nmask = mask | sm;

                if(d == 0 && popcnt(nmask+1) != 1) continue;

                // if(mask == 10 && nmask == full && d == 0){
                //     cerr << "!" << d << ' ' << dp[mask][11][0] << el;
                // }

                int D = -1;

                for(int i=len-1; i>=0; i--) if(sm>>i&1) {
                    if(d != x[i]) {

                        D = i;
                        break;
                    }
                }

                for(int diff=0; 12>diff; diff++){

                    int dih = D;
                    if(diff != 11) dih = max(dih, diff);
                    if(D == -1) dih = diff;

                    
                   

                    if(dih == diff){
                        dp[nmask][diff][0] += dp[mask][diff][0];
                        dp[nmask][diff][1] += dp[mask][diff][1];

                        // if(nmask == 10 && diff == 11 && d == 1){
                        //     cout << mask << ' ' << dp[mask][diff][0] << ' ' << "cac\n";
                        // }
                    }else{ 
                        // if(mask == 10 && nmask == full && d == 0 && diff == 11){
                        //     cerr << "cac" << ' ' << dih << ' ' << dp[mask][diff][0] << el;
                        // }
                        dp[nmask][dih][d > x[dih]] += dp[mask][diff][0] + dp[mask][diff][1];
                    

                    }
                }
            }
        }

        // cout << dp[10][11][0];
        // exit(0);
    }

    ll res = 0;

    for(int mask=1; full>=mask; mask++){
        if(popcnt(mask+1) != 1) continue;

        // bitset<10> b = mask;
        // cout << b << el;

        for(int diff=0; 12>diff; diff++){
            res += dp[mask][diff][0];

            // if(dp[mask][diff][0]) cout << "add " << mask << ' ' << diff << el;

            if(mask != full) res += dp[mask][diff][1];
        }
    }

    // cout << "! " << res << el;

    // cerr << "\n----------------\n";

    return res;
}

void sol(){
    int n, k, l, r;
    cin >> n >> k >> l >> r;

    vect<int> mp(2048);

    for(int i=0, x; n>i; i++)  cin >> x, mp[x]++;

    for(int mask=0; 5000 > mask; mask++) if(mp[popcnt(mask)]){
        int lst = -1e9, good = 1;

        for(int i=0; 11>i; i++) if(mask>>i&1){
            if(i - lst < k) good = 0;
            lst = i;
        }

        if(good) okay[mask] = 1;
    }

    // E(1012);

    cout << E(r) - E(l-1) << el;
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
