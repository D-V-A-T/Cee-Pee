#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pii pair<ll, ll>
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

const ll N = 5e3 + 5, MOD = 1e9+7, INF = 1000000000000000069;

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

template<class T> struct Deque{
    T dq[N+1];

    int l = 0, r = 0;

    const auto &operator[](int id)const{return dq[id];}

    auto &operator[](int id){return dq[id];}

    auto &back(){return dq[r];}

    const auto &front()const{return dq[l];}

    void pof(){l++;}

    void pob(){r--;}

    int size()const{
        if(l > r) return 0;
        return r-l+1;
    }

    void pb(const T &x){dq[++r] = x;}
};

ll C[5005][5005];

void sol(){
    int n, m;
    cin >> n >> m;
    vect<ll> pfs(n+5);
    vect<pii> a(n+5);

    for(int i=1; n>=i; i++){
        cin >> a[i].fi >> a[i].se;
    }

    sort(a.begin()+1, a.begin()+n+1);

    for(int i=1; n>=i; i++) pfs[i] = pfs[i-1] + a[i].fi * a[i].se;

    auto S = [&](int l, int r){
        if(l > r) return 0ll;
        return pfs[r] - pfs[l-1];
    };

    for(int i=1; n>=i; i++){
        int los = 0, his = 0, med = i-1;

        for(int j=i; n>=j; j++){
            his += a[j].se;

            while(los < his){
                med++;
                his -= a[med].se;
                los += a[med].se;
            }

            C[i][j] = a[med].fi * los - S(i, med) + S(med+1, j) - a[med].fi * his;
        }
    }   

    auto E = [&](int l, int r){
        if(l > r) return 0ll;
        return C[l][r];
    };

    ll dp[2][n+5];
    
    for(int i=0; n>=i; i++) dp[0][i] = INF;
    dp[0][0] = 0;

    
    int prev = 0, curr = 1;
    Deque<array<int, 3>> dq; 

    for(int j=1; m>=j; j++){
        dq.l = 0;
        dq.r = -1;
        dq.pb({1, n, 0});

        dp[curr][0] = 0;

        for(int i=1; n>=i; i++){
            while(dq.size() && dq.front()[1] < i) dq.pof();

            int opt = dq.front()[2];

            dp[curr][i] = dp[prev][opt] + E(opt+1, i);

            while(dq.size()){
                int l = dq.back()[0], sus = dq.back()[2];

                if(dp[prev][i] + E(i+1, l) < dp[prev][sus] + E(sus+1, l)){
                    dq.pob();
                    continue;
                }

                int lo = l, hi = dq.back()[1], split = -1;

                while(lo <= hi){
                    int mid = (lo + hi) / 2;
                    
                    if(dp[prev][i] + E(i+1, mid) < dp[prev][sus] + E(sus+1, mid)){
                        hi = mid - 1;
                    }else{
                        split = mid;
                        lo = mid + 1;
                    }
                }

                assert(dq.size() > 0);

                dq.back()[1] = split;
                if(split + 1 <= n) dq.pb({split+1, n, i});

                break;
            }

        }

        swap(curr, prev);
    }

    cout << dp[prev][n];
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