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

namespace D{

void sol(){
    int n, k;
    cin >> n >> k;

    vect<int> a(n), down(n);
    for(int &i : a) cin >> i;
    bool hihi = 0;

    for(int i=0; k>i; i++){
        int y;
        cin >> y;
        y--;
        if(a[y] == 1) hihi = 1;
        down[y] = 1;
    }

    if(hihi) for(int &i : a) i ^= 1;

    vect<int> st, sus;

    a.eb(0);
    down.eb(1);
    for(int i=0; n>=i; i++){
        if(st.empty() || a[i] != st.back()){
            st.eb(a[i]);
            sus.eb(down[i]);
        }else{
            sus.back() |= down[i];
        }
    }

    n = st.size();
    vect<int> dih;
    int sp;
    for(int i=0; n>i; i++){
        if(sus[i])  dih.eb(i), sp = i & 1;
    }


    auto calc = [&](int pos, int l, int r){
        // pos should be a special one
        if(r%2 == sp) r--;
        if(l%2 == sp) l++;
        return max({r - pos + 1, pos - l + 1, 0ll});
    };

    int epstein = 0, diddy = 0;

    for(int i=0; dih.size()>i; i++){
        int x = calc(dih[i], 0, dih[i]-1) ;
        if(i) x = calc(dih[i], dih[i-1], dih[i] - 1) ;


        epstein += x;
        diddy = max(diddy, x);
    }

    cout << max(epstein / 2, diddy) << el;
}
}

namespace E{
bool checker(vect<int> p, vect<int> q, vect<int> d){
    int n = p.size() - 1;
    for(int i=1; n>=i; i++){
        int sus = 0;
        for(int j=i+1; n>=j; j++){
            sus += p[j] > p[i] && q[j] > q[i];
        }

        if(sus != d[i]) return 0;
    }
    return 1;
}

void sol(){
    int n;
    cin >> n;
    vect<int> a(n+5), d(n+5), sperm(n+1);
    prq<int, vect<int>, greater<int>> pq;
    for(int i=1; n>=i; i++) cin >> a[i];
    for(int i=1; n>=i; i++){
        cin >> d[i];
        if(d[i] == 0) pq.push(i);
    }
    while(pq.size()){
        int idx = pq.top();
        pq.pop();
        sperm[idx] = n--;
        for(int i=idx; i>0; i--) if(a[idx] > a[i] && --d[i] == 0) pq.push(i);
    }    
    if(n > 0) cout << -1;
    else for(int i=1; sperm.size()>i; i++) cout << sperm[i] << ' ';
    nextl;
}
}


namespace F{
bool getbit(int num, int x){
    return num & (1ll<<x);
}

void sol(){
    int x1, x2;
    cin >> x1 >> x2;

    if(x1 == 1 || x1 > x2){
        cout << "1 1\n";
        return;
    }
    
    auto cnt = [&](unsigned num, unsigned lim){
        // x + y < lim, x ^ y = num
        // x + (x ^ num) < lim
        // <=> num + 2 * (x & (~num)) < lim
        // <=> (x & (~num)) < (lim - num) / 2

        unsigned L = (lim - num - 1) / 2;         
        unsigned sus = 0, sy = 0;
        unsigned free = __builtin_popcount(num);

        for(int b=30; b>=0; b--){

            if(!getbit(num, b)){
                if((sus | (1ll << b)) <= L){
                    sy = sy * 2 + 1;
                    sus |= (1ll << b);
                }else sy *= 2;
            }
        }

        return (sy+1) * (1ll << free);
    };

    int min_freq = 1e9, L = min(x1, x2);
    vect<int> cac;

    for(int nw = 0; L > nw; nw++){
        int ct = cnt(nw, x2);
        if(min_freq > ct){
            min_freq = ct;
            cac.clear();
            cac.eb(nw);
        }else if(min_freq == ct) cac.eb(nw);
    }

    for(int i : cac) {
        for(int x=0; x1 > x; x++){
            int y = x ^ i;
            if(x + y < x1){
                if(x > y) swap(x, y);
                cout << 1 + x << ' ' << x1 - y << el;
                return;
            }
        }
    }

    cout << "kys";
}
}

void sol(){
    
}


signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    cin >> t;
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