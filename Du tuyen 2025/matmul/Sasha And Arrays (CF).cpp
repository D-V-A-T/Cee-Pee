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

const ll N = 1e5 + 10, MOD = 1e9+7, INF = 1000000000000000069;

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

const int max_mat_sz = 2;
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

        c[0][0] = (c[0][0] + a[0][0] * b[0][0]) % MOD;
        c[0][0] = (c[0][0] + a[0][1] * b[1][0]) % MOD;
        c[0][1] = (c[0][1] + a[0][0] * b[0][1]) % MOD;
        c[0][1] = (c[0][1] + a[0][1] * b[1][1]) % MOD;
        c[1][0] = (c[1][0] + a[1][0] * b[0][0]) % MOD;
        c[1][0] = (c[1][0] + a[1][1] * b[1][0]) % MOD;
        c[1][1] = (c[1][1] + a[1][1] * b[1][1]) % MOD;
        c[1][1] = (c[1][1] + a[1][0] * b[0][1]) % MOD;

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

StaticMatrix sus;

pair<ll,ll> fib(int x){
    Vector v;
    v[0] = 0, v[1] = 1;
    v = v * (sus ^ (x-1));
    return {v[0], v[1]};
}

struct node{
    ll f0, f1;
    StaticMatrix sigeon;

    node(){
        f0 = f1 = 0;
        sigeon.make_identity();
    }

    node operator + (const node &o) const{
        node res;
        res.f0 = (f0 + o.f0) % MOD;
        res.f1 = (f1 + o.f1) % MOD;
        return res;
    }

    void apply(){
        ll t0 = f0, t1 = f1;
        f0 = (t0 * sigeon[0][0] + t1 * sigeon[1][0]) % MOD;
        f1 = (t0 * sigeon[0][1] + t1 * sigeon[1][1]) % MOD;
        sigeon.make_identity();
    }
};

int n, a[N];

struct Seggs{
    node t[4*N];
    ll lz[4*N];

    Seggs(){
        memset(lz, 0, sizeof lz);
        build();
    }

    void build(int l=1, int r=n, int id=1){
        if(l == r){
            tie(t[id].f0, t[id].f1) = fib(a[l]);
            return;
        }

        int mid = (l + r)>>1;
        build(l, mid, id<<1);
        build(mid+1, r, id<<1|1);

        t[id] = t[id<<1] + t[id<<1|1];
    }

    void push(int l, int r, int id){
        if(!lz[id]) return;

        t[id].sigeon = t[id].sigeon * (sus ^ lz[id]);
        t[id].apply();

        if(l < r){
            lz[id<<1] += lz[id];
            lz[id<<1|1] += lz[id];
        }

        lz[id] = 0;
    }

    void upd(int i, int j, ll x, int l=1, int r=n, int id=1){
        push(l, r, id);
        if(l > j || r < i) return;
        if(i <= l && r <= j){
            lz[id] += x;
            push(l, r, id);
            return;
        }

        int mid = (l + r)>>1;
        upd(i, j, x, l, mid, id<<1);
        upd(i, j, x, mid+1, r, id<<1|1);

        t[id] = t[id<<1] + t[id<<1|1];
    }

    ll get(int i, int j, int l=1, int r=n, int id=1){
        push(l, r, id);
        if(l > j || r < i) return 0;
        if(i <= l && r <= j) return t[id].f1;
        int mid = (l + r) >> 1;
        return (get(i, j, l, mid, id<<1) + get(i, j, mid+1, r, id<<1|1)) % MOD;
    }
};

void sol(){
    int q;
    cin >> n >> q;

    sus[0][0] = 0, sus[0][1] = sus[1][0] = sus[1][1] = 1;


    // cout << fib(2).fi << ' ' << fib(2).se << el;
    // return;

    for(int i=1; n>=i; i++) cin >> a[i];
    Seggs sgt;

    while(q--){
        int type;
        cin >> type;
        if(type==1){
            int l, r, x;
            cin >> l >> r >> x;
            sgt.upd(l, r, x);
        }else{
            int l, r;
            cin >> l >> r;
            cout << sgt.get(l, r) << el;
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