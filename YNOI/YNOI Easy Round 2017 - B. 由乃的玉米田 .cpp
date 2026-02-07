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

const ll N = 1e5+1, MOD = 998244353, INF = 1000000000000000069;

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

struct query{
    int l, r, x, type, id;
};

int n, q;
int a[N];
vect<string> ans(N, "yumi");
vect<int> divs[N];
const int SIZE = sqrt(1e5 * log2(1e5));

bool by_l(const query& a, const query& b){
    return a.l < b.l;
}

bool by_r(const query& a, const query& b){
    if(a.r != b.r) return a.r < b.r;
    if(a.l != b.l) return a.l > b.l;
    return a.id < b.id;
}

bool MO(const query& a, const query& b){
    if(a.l / 316 != b.l / 316) return a.l < b.l;
    else{
        if((a.l / 316) & 1) return a.r > b.r;
        else return a.r < b.r;
    }
}

void Query_4(vect<query> ranges, const vect<query>& ques){
    for(const auto& i : ques) ranges.pb(i);

    sort(bend(ranges), by_r);

    int mx = -1;

    for(auto [L, R, x, type, id] : ranges){
        if(id == -1) mx = max(mx, L);
        else if(L <= mx) ans[id] = "yuno";
    }
}

void sol(){
    cin >> n >> q;
    for(int i=1;n>=i;i++) cin >> a[i];

    vect<query> O_T, T, big_F, smol_F[SIZE+5];
    for(int i=0;q>i;i++){
        query que;
        cin >> que.type >> que.l >> que.r >> que.x;
        que.id = i;

        if(i == 0){
            cerr << que.type << ' ' << que.x << el;
        }

        if(que.type == 1 || que.type == 2){
            O_T.pb(que);
        }else if(que.type == 3){
            T.pb(que);
        }else{
            if(que.x < SIZE) smol_F[que.x].pb(que);
            else big_F.pb(que);
        }


    }

    sort(bend(O_T), MO);

    int l = 1, r = 0;
    bitset<2*N> po, ne;
    vect<int> cnt(N);

    for(auto [L, R, x, type, id] : O_T){
        while(r < R){
            r++;
            if(cnt[a[r]] == 0) po[a[r] + N] = ne[N - a[r]] = 1;
            cnt[a[r]]++; 
        }
        while(r > R){
            if(cnt[a[r]] == 1) po[a[r] + N] = ne[N - a[r]] = 0;
            cnt[a[r]]--;
            r--;
        }
        while(l < L){
            if(cnt[a[l]] == 1) po[a[l] + N] = ne[N - a[l]] = 0;
            cnt[a[l]]--;
            l++;
        }
        while(l > L){
            l--;
            if(cnt[a[l]] == 0) po[a[l] + N] = ne[N - a[l]] = 1;
            cnt[a[l]]++;
        }

        if(type == 1){
            if(((po << x) & po).any()) ans[id] = "yuno";
        }else{
            // a + b = x
            // a - x = -b
            if(((po >> x) & ne).any()) ans[id] = "yuno";
        }

    }

    vect<int> pos[N];
    for(int i=1;n>=i;i++){
        pos[a[i]].eb(i);
    }

    auto exist_in_range = [&](int L, int R, int d){
        int n1 = lwb(bend(pos[d]), L) - pos[d].begin();
        if(n1 < pos[d].size()) n1 = pos[d][n1];
        else return false;
        return n1 <= R;
    };

    for(auto [L, R, x, type, id] : T){
        for(int d : divs[x]){
            if(d * d > x) break;

            if(exist_in_range(L, R, d) && exist_in_range(L, R, x / d)){
                ans[id] = "yuno";
                break;
            }
        }
    }

    // a / b = x > SIZE

    // SIZE * N log + N * (1e5 / SIZE) 
    // SIZE * N log = N * (1e5 / SIZE)
    // SIZE ^ 2 = 1e5 / log 

    for(auto [L, R, x, type, id] : big_F){
        // a / b = x

        for(int b = 1; 1e5 >= b * SIZE; b++){
            if(x * b > 1e5) break;
            if(exist_in_range(L, R, b) && exist_in_range(L, R, b * x)){
                ans[id] = "yuno";
                break;
            }
        }
    }

    for(int xxx=1; SIZE>xxx; xxx++){
        if(smol_F[xxx].empty()) continue;

        vect<query> ranges;
        vect<int> ptr(N);
        for (int i = 1; i <= n; i++) {
            if (a[i] % xxx != 0) continue;

            int b = a[i] / xxx;
            auto &v = pos[b];
            int &p = ptr[b];

            while (p < v.size() && v[p] < i) {
                p++;
            }

            if (p < v.size()) {
                ranges.pb({i, v[p], -1, -1, -1});
            }

            if (p > 0) {
                ranges.pb({v[p - 1], i, -1, -1, -1});
            }
        }

        Query_4(ranges, smol_F[xxx]);
    }


    for(int i=0;q>i;i++) cout << ans[i] << el;

}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();

    for(int i=1;N>i;i++) for(int j = i; N>j;j+=i) divs[j].eb(i);

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
