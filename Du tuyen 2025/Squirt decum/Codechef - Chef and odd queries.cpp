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

const int S = 67;

int ANS[N], n, q;
vect<int> ed[N];

struct query{
    int p, delta, id;
    // count <= p * delta -> id
    bool operator < (const query & o) const{
        return p < o.p;
    }
};

struct Seggs{

    vect<query> t[4 * N];
    vect<int> ep[4 * N];

    void clear(){
        for(int i=1; 4*n>=i; i++) t[i].clear(), ep[i].clear();
    }

    void add(int i, int j, query q, int l=1, int r=n, int id=1){
        if(l > j || r < i) return;
        if(i <= l && r <= j){
            t[id].eb(q);
            return;
        }

        int mid = (l + r) / 2;
        add(i, j, q, l, mid, id*2);
        add(i, j, q, mid+1, r, id*2+1);
    }

    void SUS(int id){
        int lptr = 0;

        sort(bend(t[id]));
        for(query i : t[id]){
            while(lptr < ep[id].size() && ep[id][lptr] <= i.p) lptr++;
            ANS[i.id] += lptr * i.delta;
        }
    }

    void solve(int l=1, int r=n, int id=1){
        if(l == r){
            for(int i : ed[l]) ep[id].eb(i);
            sort(bend(ep[id]));
            SUS(id);
            return;
        }

        int mid = (l + r) / 2;
        solve(l, mid, id*2);
        solve(mid+1, r, id*2+1);

        int lptr=0, rptr = 0;
        while(lptr < ep[id*2].size() && rptr < ep[id*2+1].size()){
            if(ep[id*2][lptr] < ep[id*2+1][rptr]){
                ep[id].eb(ep[id*2][lptr++]);
            }else ep[id].eb(ep[id*2+1][rptr++]);
        }
        for(;lptr<ep[id*2].size();lptr++) ep[id].eb(ep[id*2][lptr]);
        for(;rptr<ep[id*2+1].size();rptr++) ep[id].eb(ep[id*2+1][rptr]); 

        SUS(id);
    }
} sgt;


void sol(){
    cin >> n;

    for(int i=0; n>=i; i++) ed[i].clear();

    vect<pii> seg(n);
    for(auto &i : seg){
        cin >> i.fi >> i.se;
        ed[i.fi].eb(i.se);
    }

    cin >> q;

    for(int i=0; q>i; i++) ANS[i] = 0;

    for(int _=0; q>_; _++){
        int len; cin >> len;
        vect<int> a(len);
        for(int &i : a) cin >> i;
        sort(bend(a));

        if(len > S){
            vect<int> pfs(n+1);
            for(int i : a) pfs[i] = 1;
            partial_sum(bend(pfs), pfs.begin());

            int ans = 0;
            for(auto i : seg){
                ans += (pfs[i.se] - pfs[i.fi - 1]) % 2 == 1;
            }
            ANS[_] = ans;

        }else{
            a.insert(a.begin()+0, 0);
            a.eb(n+1);

            for(int i=1; len>=i; i++){
                for(int j=i; len>=j; j+=2){
                    int l = a[i-1] + 1, r = a[j+1] - 1;

                    // cout << "{" << l << ' ' << a[i] << "} {" << a[j] << ' ' << r << "}\n";

                    sgt.add(l, a[i], {r, 1, _});
                    sgt.add(l, a[i], {a[j]-1, -1, _});
                }
            }
        }
    }

    sgt.solve();

    for(int i=0; q>i; i++){
        cout << ANS[i] << el;
    }

    sgt.clear();
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