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
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
#define FILE "ellencute"
 
const ll INF=902337203695775807, N=2e5+69, MOD=1e9+7;    
 
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

int n, k, q, nb;
vect<int> a, zip, b;
int spt[N][20];
map<int, int> single;

struct query{
    int t, l, r, x;
};

struct Seggs{
    int t[1000000], lz[1000000];
    Seggs(){
        memset(t, 5, sizeof t);
        memset(lz, -1, sizeof lz);
        build();
    }
    void build(int l=0, int r=nb-1, int id=1){
        if(l == r) {
            t[id] = b[l];
            return;
        }
        int mid = (l+r)/2;

        build(l, mid, id*2);
        build(mid+1, r, id*2+1);
        t[id] = min(t[id*2], t[id*2+1]);
    }
    void push(int l, int r, int id){
        if(lz[id] != -1){
            if(l < r) lz[id*2] = lz[id*2+1] = lz[id];
            t[id] = lz[id];
        }
        lz[id] = -1;
    }

    void upd(int i, int j, int x, int l=0, int r=nb-1, int id=1){
        push(l, r, id);
        if(l > j || r < i) return ;
        if(i <= l && r <= j) {
            lz[id] = x;
            push(l, r, id);
            return;
        }
        int mid = (l+r)/2;
        upd(i, j, x, l, mid, id*2);
        upd(i, j, x, mid+1, r, id*2+1);
        t[id] = min(t[id*2], t[id*2+1]);
    }

    int get(int i, int j, int l=0, int r=nb-1, int id=1){
        push(l, r, id);
        if(l > j || r < i)return 2e9;
        if(i <= l && r <= j) return t[id];
        int mid = (l+r)/2;
        return min(get(i, j, l, mid, id*2), get(i, j, mid+1, r, id*2+1));
    }
};

struct Masterbate{
    int t[1000000], lz[1000000];
    Masterbate(){
        memset(t, 5, sizeof t);
        memset(lz, -1, sizeof lz);
        build();
    }
    void build(int l=0, int r=zip.size()-1, int id=1){
        if(l == r) {
            t[id] = a[zip[l]%n];
            return;
        }
        int mid = (l+r)/2;

        build(l, mid, id*2);
        build(mid+1, r, id*2+1);
        t[id] = min(t[id*2], t[id*2+1]);
    }
    void push(int l, int r, int id){
        if(lz[id] != -1){
            if(l < r) lz[id*2] = lz[id*2+1] = lz[id];
            t[id] = lz[id];
        }
        lz[id] = -1;
    }

    void upd(int i, int j, int x, int l=0, int r=zip.size()-1, int id=1){
        push(l, r, id);
        if(l > j || r < i) return ;
        if(i <= l && r <= j) {
            lz[id] = x;
            push(l, r, id);
            return;
        }
        int mid = (l+r)/2;
        upd(i, j, x, l, mid, id*2);
        upd(i, j, x, mid+1, r, id*2+1);
        t[id] = min(t[id*2], t[id*2+1]);
    }

    int get(int i, int j, int l=0, int r=zip.size()-1, int id=1){
        push(l, r, id);
        // cout << "tg " << l << ' ' << r << ' ' << t[id] << el;
        if(l > j || r < i)return 2e9;
        if(i <= l && r <= j) return t[id];
        int mid = (l+r)/2;
        return min(get(i, j, l, mid, id*2), get(i, j, mid+1, r, id*2+1));
    }
};

int lg2(int x){
    return x<=0 ? 0 : 63 - __builtin_clzll(x);
}

void buildRMQ(){
    for(int i=0;n>i;i++) spt[i][0] = a[i];

    for(int b=1;20>b;b++){
        for(int i=0;n+1>i+(1<<b);i++){
            spt[i][b] = min(spt[i][b-1], spt[i+(1<<(b-1))][b-1]);
        }
    }
}

int gmin(int l, int r){
    int b = lg2(r-l+1);
    return min(spt[l][b], spt[r-(1<<b)+1][b]);
}

void sol(){
    cin >> n >> k;
    int MN = 2e9;
    a.rs(n);
    for(int& i : a) cin >> i, MN = min(MN, i);
    cin >> q;
    query que[q];

    buildRMQ();

    for(auto& i : que){
        cin >> i.t;
        if(i.t == 1){
            cin >> i.l >> i.r >> i.x;
            i.l--;i.r--;
        }else{
            cin >> i.l >> i.r;
            i.l--;i.r--;
        }
        zip.eb(i.l);
        zip.eb(i.r);
    }

    sort(bend(zip));
    zip.rs(unique(bend(zip)) - zip.begin());

    for(int i=0;zip.size()>i+1;i++){
        int cur = zip[i], nxt = zip[i+1];
        int l = pm(cur+1, n), r = pm(nxt-1, n);
        if(nxt-1 < cur+1){
            b.eb(2e9);
            continue;
        }
        if(nxt-1 - (cur+1) + 1 >= n) b.eb(MN);
        else {

            if(l <= r) b.eb(gmin(l, r));
            else b.eb(min(gmin(l, n-1), gmin(0, r)));
        }
    }
 
    nb = b.size();
    Seggs sgt;
    Masterbate ssgt;

    for(auto [t, l, r, x] : que){
        int nl = lwb(bend(zip), l) - zip.begin();
        int nr = lwb(bend(zip), r) - zip.begin();
        if(t == 1){
            if(nl < nr) sgt.upd(nl, nr-1, x);
            ssgt.upd(nl, nr, x);
        }else{
            
            int minsingle = min(ssgt.get(nl,nl), ssgt.get(nr, nr));
            if(l == r) cout << minsingle << el;
            else{
                cout << min(ssgt.get(nl, nr), sgt.get(nl, nr-1)) << el;
            }

        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen();
    int t=1;
    //cin >> t;
    while(t--)sol();
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