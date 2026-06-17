#include<bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,popcnt,lzcnt,tune=native")

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

const ll N = 2.5e5 + 10, MOD = 1e9+7, INF = 1000000000000000069;

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

const int S = 214, MAX_BLOCK = N / S + 5;

int lz[MAX_BLOCK], zl[2][MAX_BLOCK];
int dih[N];
char cac[2][MAX_BLOCK][N*2];

void sol(){
    int n, q;
    cin >> n >> q;

    int a[n];

    for(int i=0; n>i; i++){
        cin >> a[i];
    }

    auto diddy_party = [&](int blkid, bool firsttime = 0){
        int l = blkid * S, r = min(n-1, l + S - 1);

        for(int i=l; r>=i; i++){
            a[i] += lz[blkid] + zl[i&1][blkid];

            if(!firsttime && i > l && -N <= dih[i] && dih[i] <= N) cac[i&1][blkid][dih[i] + N]--;

            if(i > l) dih[i] = a[i] - a[i-1];

            if(i > l && -N <= dih[i] && dih[i] <= N) cac[i&1][blkid][dih[i] + N]++;
        }
        
        lz[blkid] = zl[0][blkid] = zl[1][blkid] = 0;

    };

    auto get = [&](int i, int bi){
        return a[i] + lz[bi] + zl[i&1][bi];
    };

    auto cnt_epstein_islands = [&](int blkid){
        // sdih[0/1] + abs(lz[1/0]) - abs(lz[0/1]) = 0
        // sdih[0/1] - lz[1/0] + lz[0/1] <= x
        // sdih[0/1] <= x + lz[1/0] - lz[0/1]

        assert(blkid < (n-1)/S);


        int res = 0, l = blkid * S, r = l + S - 1;

        assert((r-l+1)%2 == 0);


        for(bool p : {0, 1}){
            int targ = 1 + zl[p^1][blkid] - zl[p][blkid];

            int lon = cac[p][blkid][targ + N];  

            targ = zl[p^1][blkid] - zl[p][blkid];

            lon += cac[p][blkid][targ + N];

            targ = -1 + zl[p^1][blkid] - zl[p][blkid];
            lon += cac[p][blkid][targ + N];

            res += (r-l+1)/2 - lon;

        }
        return res;
    };

    for(int i=0; (n-1)/S>=i; i++) diddy_party(i, 1);

    while(q--){
        string type;
        cin >> type;

        if(type[0] == 'F'){
            int l, r, d;
            cin >> l >> r >> d;
            l--, r--;

            int block_l = l / S, block_r = r / S;

            if(block_l == block_r){
                for(int i=l; r>=i; i++) a[i] -= d;
                diddy_party(block_l);
            }else{
                for(int i=l; (block_l+1)*S > i; i++) a[i] -= d;
                diddy_party(block_l);

                for(int i= block_l+1; block_r>i; i++) lz[i] -= d;

                for(int i=block_r*S; r>=i; i++) a[i] -= d;
                diddy_party(block_r);
            }
        }else if(type[0] == 'S'){
            int l, r;
            cin >> l >> r;
            l--, r--;

            int block_l = l / S, block_r = r / S;

            if(block_l == block_r){
                for(int i=l; r>=i; i+=2) a[i]--;
                diddy_party(block_l);
            }else{
                for(int i=l; (block_l+1)*S > i; i+=2) a[i]--;
                diddy_party(block_l);

                for(int i=block_l+1; block_r>i; i++) zl[l&1][i]--;

                for(int i=(block_r * S) + (l&1); r>=i; i+=2) a[i]--;
                diddy_party(block_r);
            }
        }else{
            int l, r;
            cin >> l >> r;
            l--, r--;


            int block_l = l / S, block_r = r / S;
            
            if(block_l == block_r){
                int res = 1;
                for(int i=l+1; r>=i; i++){
                    res += abs(get(i, block_l) - get(i-1, block_l)) > 1;
                }
                cout << res << el;
            }else{
                int res = 1;
                for(int i=l+1; (block_l+1)*S > i; i++){
                    res += abs(get(i, block_l) - get(i-1, block_l)) > 1;
                }

                int prev = get((block_l+1)*S-1, block_l);

                // cout << l << ' ' << r << ' ' << block_l << ' ' << block_r << el;

                // cout << "! " << res << el;


                for(int i=block_l+1; block_r > i; i++){
                    // cout << get(i*S, i) << ' ' <<  prev << ' ' << cnt_epstein_islands(i) << el;
                    if(abs(get(i*S, i) - prev) <= 1) {
                        res--;
                    }

                    res += cnt_epstein_islands(i);

                    prev = get((i+1)*S-1, i);
                }


                res -= abs(get(block_r*S, block_r) - prev) <= 1;
                // cout << "-1\n";

                res++;
                for(int i=block_r*S+1; r>=i; i++)
                    res += abs(get(i, block_r) - get(i-1, block_r)) > 1;

                // cout << "!!!" << res << el;

                cout << res << el;

            }
        }
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