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

inline int B(int a, int b){
    int res = 1;
    a %= MOD;
    while(b){
        if(b&1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

const int max_mat_sz = 6;
int mat_sz = 5;

struct StaticMatrix{
    ll mat[max_mat_sz][max_mat_sz];
    size_t n = mat_sz;

    StaticMatrix(){
        memset(mat, 0, sizeof mat);
    }

    auto & operator [](int id){
        return mat[id];
    }

    const auto & operator [](int id) const{
        return mat[id];
    }

    StaticMatrix operator * (const StaticMatrix& o) const{
        StaticMatrix res;

        const auto &a = mat, &b = o.mat;
        auto &c = res.mat;

        for(size_t i=0; n>i; i++){
            for(size_t j=0; n>j; j++){
                for(size_t k=0; n>k; k++){
                    c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % (MOD-1);
                }
            }
        }

        return res;
    }

    StaticMatrix operator ^ (ll b) const{
        StaticMatrix base = *this, res;
        res.make_identity();

        while(b){
            if(b&1) res = res * base;
            base = base * base;
            b >>= 1;
        }

        return res;
    }

    void make_identity(){
        memset(mat, 0, sizeof mat);
        for(int i=0; n>i; i++) mat[i][i] = 1;
    }

    void Fill(ll val){
        for(auto &i : mat) fill(i, i + mat_sz, val);
    }


    void print() const{
        for(size_t i=0; n>i; i++) for(size_t j=0; n>j; j++) cout << mat[i][j] << " \n"[j == n-1];
    }
};

struct Vector{
    ll vec[max_mat_sz];
    size_t n = mat_sz;

    Vector(){
        memset(vec, 0, sizeof vec);
    }

    auto & operator [] (int id){
        return vec[id];
    }

    const auto & operator [] (int id) const{
        return vec[id];
    }

    Vector operator * (const StaticMatrix& o) const{
        Vector res;
        for(size_t j=0; n>j; j++){
            for(size_t k=0; n>k; k++){
                res[k] = (res[k] + vec[j] * o.mat[j][k]) % (MOD-1);
            }
        }

        return res;
    }

    void Fill(ll val){
        fill(vec, vec+n, val);
    }

    void print(){
        for(size_t i=0; n>i; i++) cout << vec[i] << " \n"[i==n-1];
    }
};

vect<int> pr;
bool notprime[N];

void sol(){
    int n;
    cin >> n;
    
    vect<int> f(3);
    int c;
    cin >> f[0] >> f[1] >> f[2] >> c;

    int ans = 1;

    StaticMatrix sus;
    vect<vect<int>> base ={
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 2, 1}
    };

    for(int i=0; 5>i; i++) for(int j=0; 5>j; j++) sus[i][j] = base[i][j];

    if(n > 4) sus = sus ^ (n-3);

    for(int p : pr){
        Vector cac;

        while(f[0] % p == 0) cac[0]++, f[0] /= p;
        while(f[1] % p == 0) cac[1]++, f[1] /= p;
        while(f[2] % p == 0) cac[2]++, f[2] /= p;
        while(c % p == 0) cac[3]+=2, cac[4]++, c /= p;

        if(n <= 3) ans = ans * B(p, cac[n-1]) % MOD;
        else{

            cac = cac * sus;
            ans = ans * B(p, cac[2]) % MOD;
        }
    }

    vect<int> v;
    if(f[0] > 1) v.eb(f[0]);
    if(f[1] > 1) v.eb(f[1]);
    if(f[2] > 1) v.eb(f[2]);
    if(c > 1) v.eb(c);

    sort(bend(v));
    v.rs(unique(bend(v)) - v.begin());

    for(int p : v){
        Vector cac;

        while(f[0] % p == 0) cac[0]++, f[0] /= p;
        while(f[1] % p == 0) cac[1]++, f[1] /= p;
        while(f[2] % p == 0) cac[2]++, f[2] /= p;
        while(c % p == 0) cac[3]+=2, cac[4]++, c /= p;

        if(n <= 3) ans = ans * B(p, cac[n-1]) % MOD;
        else{
            cac = cac * sus;
            ans = ans * B(p, cac[2]) % MOD;
        }
    }

    cout << ans << el;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();

    notprime[0] = notprime[1] = 1;
    for(int i=2; N>i; i++){
        if(notprime[i]) continue;
        pr.eb(i);
        for(int j=i*i; N>j; j+=i) notprime[j] = 1;
    }

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