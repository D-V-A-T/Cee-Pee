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

const ll N = 2e6 + 10, MOD = 1e9+7, INF = 1000000000000000069;

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

int n, q;

struct SigeonPegg{
    ll t[2][N],ta;
    inline void add(int op,int x,ll v){while(x<=n) t[op][x]+=v,x+=(x&-x);}
    inline ll ask(int op,int x){ta=0;while(x) ta+=t[op][x],x^=(x&-x);return ta;}
    void upd(int l,int r,ll v){add(0,l,v),add(0,r+1,-v),add(1,l,v*(l-1)),add(1,r+1,-v*r);}
    ll get(ll l,ll r){return r*ask(0,r)-(l-1)*ask(0,l-1)-ask(1,r)+ask(1,l-1);}
};

struct query{
    int ed, l, r, type, id;

    bool operator < (const query &o) const{
        return ed < o.ed;
    }
};


ll ANS[N];

void sol(){
    cin >> n >> q;

    vect<int> pos[n+5];
    int a[n+5];

    for(int i=1; n>=i; i++){
        cin >> a[i];
        pos[a[i]].eb(i);
    }

    vect<query> que;
    que.reserve(2*N);

    int prev[n+5];
    memset(prev, -1, sizeof prev);

    for(int i=0; q>i; i++){
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        que.pb({y, l, r, 1, i});
        if(x-1 > 0) que.pb({x-1, l, r, -1, i});
    }

    sort(bend(que));
    set<pii> sech;
    sech.insert({0, 0});
    vect<int> lst(n+5, -1);

    SigeonPegg sig, pex;

    int ptr = 0;

    for(int i=1; n>=i; i++){
        if(lst[a[i]] == -1){
            auto ed = sech.end();
            ed--;
            int cac = (*ed).fi + 1;
                
            pex.upd(cac, i, i);
            sig.upd(cac, i, (ll)i*i);

            sech.insert({i, a[i]});            
        }else{
            auto it = sech.find(make_pair(lst[a[i]], a[i]));
            assert(it != sech.begin());

            auto pr = it, nxt = it;
            --pr;
            ++nxt;

            if(nxt != sech.end()){
                int cac = (*pr).fi + 1, sus = (*nxt).fi;

                pex.upd(cac, lst[a[i]], sus - lst[a[i]]);
                sig.upd(cac, lst[a[i]], (ll)(sus - lst[a[i]]) * i);
            }else{
                int cac = (*pr).fi + 1;
                pex.upd(cac, lst[a[i]], -lst[a[i]]);
                sig.upd(cac, lst[a[i]], -(ll)lst[a[i]] * i);
            }
            sech.erase(it);

            auto sus = sech.rbegin();
            int cac = (*sus).fi + 1;
            pex.upd(cac, i, i);
            sig.upd(cac, i, (ll)i * i);

            sech.insert({i, a[i]});
        }

        // if(i == 4){
        //     for(auto j : sech) cout << j.fi << ' ' << j.se << el;
        // }

        lst[a[i]] = i;

        while(ptr < que.size() && que[ptr].ed <= i){
            auto [ed, l, r, type, id] = que[ptr];

            ANS[id] += ((ll)pex.get(l, r) * (i+1) - sig.get(l, r)) * type;

            ptr++;
        }

        if(ptr >= que.size()) break;
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