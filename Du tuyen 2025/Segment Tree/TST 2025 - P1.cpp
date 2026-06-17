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

const ll N = 4e5 + 10, MOD = 1e9+7, INF = 1000000000000000069;

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

struct Fick{
    ll bit[N];

    Fick(){
        init();
    }

    void init(){
        memset(bit, 0, sizeof bit);
    }

    void upd(int i, int x){
        for(; N>i; i+=i&-i) bit[i] += x; 
    }

    int f(int i){
        int res = 0;
        for(; i>0; i-=i&-i) res += bit[i];
        return res;
    }

    ll get(int l, int r){
        return f(r) - f(l-1);
    }
} ft;

int n, q, res[N*3], a[N], medcnt[N*3];
vect<int> cacs[N];

struct query{
    int l, r, k, id;

    bool operator < (const query &o) const{
        if(id == -1) return 0;
        if(o.id == -1) return 1;

        return res[id] < res[o.id];
    }
};

int ptr = -1;

void PBS(vect<query> &queries, int l=1, int r=n){
    int mid = (l+r)>>1;


    while(ptr < mid){
        ++ptr;
        for(auto &i : cacs[ptr]) ft.upd(i, 1);

    }

    while(ptr > mid){
        for(auto &i : cacs[ptr]) ft.upd(i, -1);
        --ptr;
    }

    if(l == r){

        for(auto &qu : queries){

            // cout << qu.l << ' ' << qu.r << ' ' << qu.k << ' ' << mid << el;

            res[qu.id] = mid;
            int val = ft.get(qu.l, qu.r);
            medcnt[qu.id] = val - qu.k;
        }
        return;
    }

    vect<query> left, right;

    for(auto &qu : queries){
        // cerr << qu.l << ' ' << qu.r << ' ' << ft.get(qu.l, qu.r) << el;
        if(ft.get(qu.l, qu.r) >= qu.k) left.pb(qu);
        else right.pb(qu);
    }

    queries.clear();

    PBS(left, l, mid);
    PBS(right, mid+1, r);
}

void sol(){
    cin >> n >> q;

    vect<int> zip, unzip(n+5);
    vect<ll> pfs(n+5);

    for(int i=1; n>=i; i++){
        cin >> a[i];
        pfs[i] = a[i] + pfs[i-1];
        zip.eb(a[i]);
    }

    sort(bend(zip));
    zip.rs(unique(bend(zip)) - zip.begin());

    auto gz = [&](int x){
        return lwb(bend(zip), x) - zip.begin() + 1;
    };

    for(int i=1; n>=i; i++){
        cacs[gz(a[i])].eb(i);
        unzip[gz(a[i])] = a[i];
    }

    vect<query> oq, queries;
    queries.reserve(N*3);
    oq.reserve(N);

    int idx = -1;

    for(int i=0; q>i; i++){
        int l, r;
        cin >> l >> r;

        int mid = (r-l+2)>>1;

        if((r-l+1)&1){
            if(r-l+1 > 1){
                queries.pb({l, r, mid-1, ++idx});
                queries.pb({l, r, mid, ++idx});
                queries.pb({l, r, mid+1, ++idx});

                oq.pb({l, r, i, idx-2});

            }else oq.pb({l, r, i, -1});
        }else{
            queries.pb({l, r, mid, ++idx});
            queries.pb({l, r, mid+1, ++idx});
            oq.pb({l, r, i, idx-1});
        }


    }


    PBS(queries);
    sort(bend(oq));

    auto gs = [&](int l, int r){
        return pfs[r] - pfs[l-1];
    };

    ft.init();

    ptr = 0;

    ll ANS[q];

    for(int i=0; q>i; i++){
        int l = oq[i].l, r = oq[i].r;

        if(l == r){
            ANS[oq[i].k] = 0;
            continue;
        }

        while(ptr <= res[oq[i].id]){
            for(int p : cacs[ptr]){
                ft.upd(p, unzip[ptr]);
            }
            ptr++;
        }

        if((r-l+1)&1){
            int x1 = unzip[res[oq[i].id]];
            int x2 = unzip[res[oq[i].id+1]];
            int x3 = unzip[res[oq[i].id+2]];

            // cout << res[oq[i].id] << ' ' << unzip[] << ' ' << x3 << ' ' << l << ' ' << r << el;

            ll smol = ft.get(l, r) - medcnt[oq[i].id] * x1;
            ll big = gs(l, r) - x2 - smol;

            // cout << (2*big - x3) - (2*smol - x1) + max(abs(x1-x2), abs(x3-x2))
            // << ' ' << oq[i].id << el;


            ANS[oq[i].k] = (2*big - x3) - (2*smol - x1) + max(abs(x1-x2), abs(x3-x2));

        }else{
            int x1 = unzip[res[oq[i].id]];
            int x2 = unzip[res[oq[i].id+1]];

            ll smol = ft.get(l, r) - medcnt[oq[i].id] * x1;
            ll big  = gs(l, r) - smol;

            // cout << x1 << ' ' << x2 << el;
            // cout << smol << ' ' << big << el;

            ANS[oq[i].k] = (2*big-x2) - (2*smol-x1) ;
        }
    }

    for(int i=0; q>i; i++) cout << ANS[i] << el;
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