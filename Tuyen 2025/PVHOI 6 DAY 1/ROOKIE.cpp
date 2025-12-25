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
#define popcnt __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define ll long long 
#define dbl long double


#define FILE "ROOKIE"
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

const ll N = 3e5 + 69, MOD = 1e9+7, INF = 1000000000000000069;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll rand(ll l, ll r){
    return uniform_int_distribution<ll>(l, r)(rng);
}
ll pm(ll a,const ll b=MOD){return ((a%b)+b)%b;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int r, c, q;

namespace sub12{
vect<vect<int>> a, b;
void update(){
    fill(b.begin(), b.end(), vect<int>(c, 0));
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(!a[i][j]) continue;

            for(int k = j-1; k>=0; k--){
                if(a[i][k]) break;
                b[i][k]++;
            }
            for(int k = j+1; k<c; k++){
                if(a[i][k]) break;
                b[i][k]++;
            }
            for(int k = i-1; k>=0; k--){
                if(a[k][j]) break;
                b[k][j]++;
            }
            for(int k = i+1; k<r; k++){
                if(a[k][j]) break;
                b[k][j]++;
            }
        }
    }
}
void solve(){
    a.rs(r, vect<int>(c)), b.rs(r, vect<int>(c));
    while(q--){
        int x, y;
        cin >> x >> y;
        x--;y--;
        a[x][y] ^= 1;

        update();

        int ans = 0;
        for(auto& i : b) ans += count(bend(i), 1);
        cout << ans << el;
    }
}
}

namespace sub3{
void solve(){
    int active = 0;
    vect<int> cbd(max(r,c) + 5);
    while(q--){
        int x, y;
        cin >> x >> y;
        x--; y--;

        if(!cbd[x]){
            active ++;
            cbd[x] = 1;
        } else{
            active --;
            cbd[x] = 0; 
        }

        cout << active * (c + r - 2) - (active) * (active - 1) * 2 << el;   
    }
}
}

struct Fick{
    vect<int> bit;
    int sz;
    Fick(int n ){
        sz = n + 5;
        bit.rs(sz);
    }

    int getBigger(int x){
        int res = 0;
        for(;x<sz;x+=x&-x) res += bit[x];
        return res;
    }

    void updBigger(int x, int v){
        for(;x>0;x-=x&-x) bit[x] += v;
    }

    int getSmaller(int x){
        int res = 0;
        for(;x>0;x-=x&-x) res += bit[x];
        return res;
    }

    void updSmaller(int x, int v){
        for(;x<sz;x+=x&-x) bit[x] += v;
    }
};

namespace sub456{
void solve(){
    vect<int> cnt_y(c+5);
    set<int> pos[6], y_range[c+2];

    Fick big(c), smol(c), col_min(r+5), col_max(r+5);

    while(q--){
        int x, y;
        cin >> x >> y;

        auto &st = y_range[y];
        if(st.size()){
            int mn = *st.begin(), mx = *st.rbegin();
            col_min.updBigger(mn, -1);
            col_max.updSmaller(mx, -1);
        }

        if(pos[x].find(y) != pos[x].end()){
            if(cnt_y[y] == 1){
                big.updBigger(y, -1);
                smol.updSmaller(y, -1);
            }
            cnt_y[y]--;

            pos[x].erase(y);
            st.erase(x);
        }
        else {
            if(cnt_y[y] == 0){
                big.updBigger(y, 1);
                smol.updSmaller(y, 1);
            }
            cnt_y[y]++;
            pos[x].insert(y);
            st.insert(x);
        }

        if(st.size()){
            int mn = *st.begin(), mx = *st.rbegin();
            col_min.updBigger(mn, 1);
            col_max.updSmaller(mx, 1);
        }

        int ans = 0;
        for(int i=1;r>=i;i++){
            if(pos[i].empty()){
                ans += col_min.getBigger(i+1) + col_max.getSmaller(i-1);                

                continue;
            }

            int lo = *pos[i].begin(), hi = *pos[i].rbegin();

            int left = lo - 1, right = c - hi;
            ans += left - smol.getSmaller(lo-1) + right - big.getBigger(hi+1);

        }

        cout << ans << el;

    }
}
}

void sol(){
    cin >> r >> c >> q;

    if(max(r, c) <= 90 && q <= 9000) sub12::solve();
    else if(r <= 5) sub456::solve();
    else sub3::solve();

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
