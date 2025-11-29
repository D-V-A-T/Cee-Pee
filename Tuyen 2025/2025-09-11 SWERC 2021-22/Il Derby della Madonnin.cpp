#include<bits/stdc++.h>
using namespace std; 
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define umap unordered_map
#define prq priority_queue
#define vect vector
#define rs resize
#define bend(v) v.begin(),v.end()
#define pob pop_back
#define pof pop_front
#define lwb lower_bound
#define upb upper_bound
#define pii pair<int,int>
#define nextl cout << '\n'
#define el '\n'
#define deb cout<<"\nok\n";return 
#define ll long long
#define int long long
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
#define FILE "ellencute"
 
const ll INF=902337203695775807, N=1e6+69, MOD=1e9+7;    
 
void ffopen(){
    if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
    }else if(fopen("ellencute.inp", "r")){
        freopen("ellencute.inp", "r", stdin);
        freopen("ellencute.out", "w", stdout);
    }
}

int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int bigtest;
struct Fick{
    vect<int> bit;
    int sz;
    void init(int n){
        sz = n+5;
        bit.assign(sz, 0);
    }
    int get(int x){
        int res = 0;
        for(;x<sz;x+=x&-x) res = max(res, bit[x]);
        return res;
    }
    void upd(int x, int v){
        for(;x>0;x-=x&-x) bit[x] = max(bit[x], v);
    }
};


struct bigBITch{
    vect<int> Z[N];
    Fick ft[N];

    void build(int x, int y){
        int tmp = x;
        for(;x<N;x+=x&-x) Z[x].eb(y);
        x = tmp;
        for(;x>0;x-=x&-x) Z[x].eb(y);
    }

    int GET(int x, int y){
        int res = 0, tmp=y, tx=x;
        for(;x<N;x+=x&-x){        
            y = lwb(bend(Z[x]), tmp) - Z[x].begin() + 1;   
            res = max(res, ft[x].get(y));
        }
        return res;
    }

    void UPD(int x, int y, int dpy){
        int tmp = y;
        for(;x>0;x-=x&-x){
            y = lwb(bend(Z[x]), tmp) - Z[x].begin() + 1;
            ft[x].upd(y, dpy);
        }
    }
} big ;

struct smolBITch{
    vect<int> Z[N];
    Fick ft[N];

    void build(int x, int y){
        int tmp = x;
        for(;x<N;x+=x&-x) Z[x].eb(y);
        x = tmp;
        for(;x>0;x-=x&-x) Z[x].eb(y);
    }

    int GET(int x, int y){
        int res = 0, tmp=y;
        for(;x>0;x-=x&-x){            
            y = lwb(bend(Z[x]), tmp) - Z[x].begin() + 1;
            res = max(res, ft[x].get(y));
            // if(tmp == -10) cout << x << el;
        }
        return res;
    }

    void UPD(int x, int y, int dpy){
        int tmp = y;
        for(;x<N;x+=x&-x){
            y = lwb(bend(Z[x]), tmp) - Z[x].begin() + 1;
            ft[x].upd(y, dpy);
        }
    }
} smol;

void sol(int tnum){

    int n, v;
    cin >> n >> v;
    pii a[n];
    vect<int> zip;
    for(pii& i : a) cin >> i.fi;


    for(pii& i : a){
        cin >> i.se;
        zip.eb(i.se);
    }   

    sort(bend(zip));
    zip.rs(unique(bend(zip)) - zip.begin());

    for(pii i : a){

        int fumo = i.se - v*i.fi, fumi = -i.se - i.fi*v;

        int x = lwb(bend(zip), i.se) - zip.begin() + 1;

        smol.build(x, fumo);
        big.build(x, fumi);
    }

    for(int i=0;N>i;i++){
        auto &b = big.Z[i];
        sort(bend(b));
        b.rs(unique(bend(b)) - b.begin());
        big.ft[i].init(b.size()+5);

        auto &s = smol.Z[i];
        sort(bend(s));
        s.rs(unique(bend(s)) - s.begin());
        smol.ft[i].init(s.size()+5);
    }

    int ans = 0;
    for(pii i : a){
        int dp=0;

        int x = lwb(bend(zip), i.se) - zip.begin() + 1; 

        dp = max({dp, big.GET(x, -i.se - v*i.fi),
                smol.GET(x, i.se - v*i.fi)})+1;

        if(dp==1 && i.fi*v < abs(i.se)) continue;
            

        ans = max(ans, dp);
        // cout << smol.GET(x, i.se - v*i.fi) << ' '  << dp << ' ' << i.se-v*i.fi << el;
        // cout << i.se - v*i.fi << ' ' << smol.GET(x, i.se - v*i.fi) << ' ' << dp << endl;

        big.UPD(x, -i.se - v*i.fi, dp);
        smol.UPD(x, i.se - v*i.fi, dp);
    }cout << ans;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1, tnum=1;
    // cin >> t;
    bigtest = t>99;
    while(t--)sol(tnum++);
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