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
 
ll n, m;
vect<int> a;
map<int, array<int, 3>> cache;
 
ll F(ll k, int dist, int cac){
    if((dbl)LLONG_MAX / cac < k-1) return INF+5;
    if(k >= dist) return dist + (k-1)*cac;
    ll b = dist % k;
    ll a = k - b, len = (dist - b) / k;
    return a*len*len + b*(len+1)*(len+1) + (k-1)*cac;
}
 
array<int, 3> E(int cac){
    if(cache.count(cac)) return cache[cac];
    ll res = 0, mincnt = 0, maxcnt = 0;
    for(int i=1; n>=i; i++){
        int dist = a[i] - a[i-1];
 
        if(dist == 1 || cac > dist * dist){
            if(dist == 1) res++;
            else res += dist * dist;
            continue;
        }
 
        ll l = 1, r = dist+1, sus = INF, mxc = dist, mnc = 0;
        while(l <= r){
            int mid = (l + r) / 2;
 
            if(F(mid, dist, cac) < sus){
                sus = F(mid, dist, cac);
                mxc = mid-1;
            }
            else if(F(mid, dist, cac) == sus){
                mxc = max(mxc, mid-1);
            }    

            if(F(mid, dist, cac) >= F(mid+1, dist, cac) && F(mid, dist, cac) < INF) 
                l = mid + 1;
            else r = mid - 1;
        }



        l=1, r=dist+1, sus = INF;
        while(l <= r){
            int mid = (l + r) / 2;
 
            if(F(mid, dist, cac) < sus){
                sus = F(mid, dist, cac);
                mnc = mid-1;
            }
            else if(F(mid, dist, cac) == sus){
                mnc = min(mnc, mid-1);
            }    

            if(F(mid, dist, cac) <= F(mid+1, dist, cac)) 
                r = mid - 1;
            else l = mid + 1;
        }   


        // if(F(mnc+1, dist, cac) >= F(mnc, dist, cac)){
        //     cerr << mnc << ' ' << mxc << ' ' << dist << ' ' << cac
        //     << ' ' << F(mnc+1, dist, cac) << ' ' << F(mnc, dist, cac) << el;
        // }
        // assert(F(mnc+1, dist, cac) < F(mnc, dist, cac));

        // cerr << mnc << ' ' << mxc << el;
        
        // cerr << "! " << mxc << el;
        mincnt += mnc;
        maxcnt += mxc;
        res += sus;
 
        // cerr << c << ' ' << cac << ' ' << dist << ' ' << F(c+1, dist, 0) << el;
    }

 
    return cache[cac] = {res, mincnt, maxcnt};
}
 
void sol(){
    cin >> n;

 
    a.eb(0);
    for(int i=0; n>i; i++){
        int x; cin >> x;
        a.eb(x);
    }
    sort(bend(a));


    // cout << concac << el;
 
    cin >> m;
 
    int l = 0, r = 1e18;
    ll ans = INF;

    vect<int> cacs;

    while(l <= r){
        int mid = (l + r) / 2;


        // cout << E(mid).se << el;

        // cout << mid << ' ' << E(mid)[0] - E(mid)[2] * mid << ' ' << E(mid)[1] << el;


        // cacs.eb(mid);

        // cerr << E(mid)[0]  << ' ' << m << el;

        // cout << E(mid)[0] - E(mid)[2] * mid << ' ' << m << el;


        if(E(mid)[0] - E(mid)[2] * mid <= m){
            l = mid + 1;

            // E(mid).fi - mid * k <= m

            // (E(mid).fi - m) / mid <= k

            // cerr << "dit\n";
            if(mid == 0){
                ans = E(mid)[1];

                continue;
            }

            int cand = ceil((dbl)(E(mid)[0] - m) / mid);
            // assert(mid != 0);

            if(cand < E(mid)[1]) cand = E(mid)[1];
            if(cand > E(mid)[2]) cand = E(mid)[2];

            // cout << mid << ' ' << E(mid)[0] << ' ' << E(mid)[1] << ' ' << E(mid)[2] << el;

            // cout << mid << ' ' << E(mid)[2] << el;
            ans = min(ans, cand);

            // cerr << (ll)ceil((dbl)(E(mid).fi - m) / mid) << el;
        }else{
            r = mid - 1;
        }
    }

    cout << ans << el;

    // int eos = E(opt).se;
    
    // for(int t=0; 5>=t; t++){
    //     if(cc())
    // }
    
    // cout << opt << ' ' << E(opt).fi - E(opt).se * opt << ' ' << E(opt).se << el;
 
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