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

const int max_mat_sz = 1<<7;
int mat_sz = 2;

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
                    c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % MOD;
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
                res[k] = (res[k] + vec[j] * o.mat[j][k]) % MOD;
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

int n, m;

bool getbit(int x, int b){
    return x>>b&1;
}


void E(int i, int mask, int nmask, vect<int> &sus){
    if(i==n) {
        sus.eb(nmask);
        return;
    }
    if(getbit(mask, i)) return (void)E(i+1, mask, nmask, sus);
    E(i+1, mask|(1<<i), nmask|(1<<i), sus);
    if(i+1 < n && !getbit(mask, i+1)) E(i+2, mask|(1<<i)|(1<<(i+1)), nmask, sus);
}

int F(Vector st, int p, const StaticMatrix &sus){
    st = st * (sus ^ p);
    return st[0];
}

void sol(){
    cin >> n >> m;

    mat_sz = 1<<n;


    StaticMatrix sus;

    vect<int> nxt[1<<n];


    for(int mask=0; 1<<n >mask; mask++){
        E(0, mask, 0, nxt[mask]);
        for(int nmask : nxt[mask]){
            sus[mask][nmask]++;
        }
    }

    map<int, int> cac;

    int k;
    cin >> k;
    for(int i=0; k>i; i++){
        int x, y;
        cin >> x >> y;
        x--;
        cac[y] |= 1<<x;
    }

    Vector v;
    v[cac[1]] = 1;

    int lst = 1;

    for(auto &[col, state] : cac){
        if(col == 1) continue;

        v = v * (sus ^ (col - lst - 1));

        vect<int> dp(1<<n);

        for(int mask=0; 1<<n >mask; mask++){
            for(int nm : nxt[mask]){
                if(nm & state) continue;
                dp[nm | state] = (dp[nm | state] + v[mask]) % MOD;
            }
        }

        copy(bend(dp), v.vec);

        lst = col;
    }

    v = v * (sus ^ (m - lst + 1));

    cout << v[0] << el;
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