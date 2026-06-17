#include<bits/allocator.h>
#pragma GCC optimize("unroll-loops")

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

const ll N = 3e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

namespace k1s{
int continuity(int x){
    int res = 0, curr = 0;
    while(x){
        if(x&1) curr++;
        else curr = 0;
        res = max(res, curr);
        x>>=1;
    }
    return res;
}

bool comp(int x, int y){
    return continuity(x) != continuity(y) ? continuity(x) < continuity(y) : x < y;
}

void sol(){
    int n;
    cin >> n;
    int a[n];
    for(int &i : a) cin >> i;
    
    sort(a, a+n, comp);
    
    for(int i : a) cout << i << ' ';
}
};

namespace pancake{
int move_cnt;
vect<vect<int>> dit;

void sol(){
    int n, m;
    cin >> m >> n;
    vect<int> st[n+5];

    move_cnt = 0;
    
    for(int i=1; n>=i; i++){
        st[i].rs(m);
        for(int &j : st[i]) cin >> j;
    }
    
    auto diddle = [&](int a, int b, int k){
        if(k == 0) return;
        dit.pb({a, k, b});
        move_cnt++;  

        // return;

        reverse(st[a].end() - k, st[a].end());
        while(k--){
            st[b].eb(st[a].back());
            st[a].pob();
        }  

        for(auto &i : st) assert(i.size() <= m);
    };

    auto diddlelvlmax = [&](){
        for(auto i : st){
            for(auto j : i) cerr << j << ' ';
            cerr<<el;
        }
        // exit(0);
    };
    
    for(int num=1; n>=num; num++){
        
        vect<int> nig;

        for(int i=num; n>=i; i++){
            int sz = st[i].size(), sus = 0;
            for(int j=1; sz>=j; j++){
                if(st[i][sz - j] == num){
                    diddle(i, n+1, j-sus);
                    if(j-1-sus > 0) diddle(n+1, i, j-sus-1);
                    
                    sus++;
                }
            }
            diddle(n+1, i, sus);
            nig.eb(sus);


        }
        
        for(int i=num; n>=i; i++){
            diddle(i, n+1, nig[i - num]);
        }
        
        for(int i=num+1; n>=i; i++){
            diddle(num, i, nig[i - num]);
        }



        diddle(n+1, num, m);



    }

    // assert(move_cnt <= 9 * m * n);
    cout << move_cnt << el;
    for(auto v : dit) cout << v[0] << ' ' << v[1] << ' ' << v[2] << el;

    // diddlelvlmax();
}
}

namespace accumulatedmax{
void sol(){
    int n, k;
    cin >> n >> k;

    int a[n];
    for(int &i : a) cin >> i;

    map<int, int> cnt;
    multiset<int> ms;

    auto add = [&](int x, bool diddlable){
        auto it = ms.find(cnt[x] * x);
        if(it != ms.end()) ms.erase(it);
        cnt[x]++;
        ms.insert(cnt[x] * x);
    };

    auto del = [&](int x){
        auto it = ms.find(cnt[x] * x);
        if(it != ms.end()) ms.erase(it);
        cnt[x]--;
        ms.insert(cnt[x] * x);
    };

    int l=0, ans = 0;
    for(int r=0; n>r; r++){

        if(r < k) add(a[r], 1);
        else add(a[r], 0);

        if(r-l+1 > k){
            del(a[l++]);
        }

        if(r-l+1 == k) ans += *ms.rbegin();
    }

    cout << ans;
}
}

namespace stair{

const int SZ = 4002;
char c[SZ][SZ], sus[SZ][SZ];
int n, m, dp[2][SZ][SZ];

inline void maximize(int &a, const int &b){
    a = max(a, b);
}

inline int read(){
    char ch=getchar();int x=0,f=1;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')
    x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}

void sol(){
    cin >> n >> m;

    for(int i=1; n>=i; i++){
        for(int j=1; m>=j; j++){
            cin >> c[i][j];
        }
    }


    for(auto &j : dp[0]) for(auto &k : j) k=1;

    int ans = 1, ans2 = 0, ct[26];

    for(int i=1; n>=i; i++){
        int curr = 0, curr2 = 0;
        vect<int> nig;
        memset(ct, 0, sizeof ct);

        for(int j=1; m>=j; j++){

            char f = c[i][j] - 'A';
            if(!ct[f]){
                nig.eb(f);
            }

            curr2++;

            ct[f] = j;

            if(nig.size() > 2){

                if(ct[nig[0]] < ct[nig[1]]) swap(nig[0], nig[1]);
                if(ct[nig[1]] < ct[nig[2]]) swap(nig[2], nig[1]);


                curr2 = j - ct[nig[2]];
                ct[nig[2]] = 0;
                nig.pob();
            }

            if(nig.size() == 2){
                sus[i][j] = (nig[0]+'A') ^ (nig[1]+'A') ^ c[i][j];
            }else sus[i][j] = '#';


            if(c[i][j] == c[i][j-1]) curr++;
            else curr = 1;

            if(c[i][j] == c[i-1][j]){
                dp[0][i][j] = min(curr, dp[0][i-1][j] + 1); 
            }


            if(i > 1){
                // 1 colour this row
                char diddy = sus[i][j];
                if(c[i][j] != c[i-1][j]){
                    int x = min(curr, dp[0][i-1][j] + 1);
                    if(x > dp[1][i][j]){ // chinh chu cai thu hai trong bac thang lon nhat cua (i j)
                        dp[1][i][j] = x;
                        diddy = c[i-1][j];
                    }
                }

                if(curr > dp[0][i-1][j] + 1){
                    if((c[i][j] != c[i-1][j] && c[i][j] == sus[i-1][j]) || 
                        (c[i][j] == c[i-1][j] && sus[i-1][j] != c[i][j])){
                        int x = min(curr, dp[1][i-1][j] + 1);
                        if(x > dp[1][i][j]){
                            dp[1][i][j] = x;

                            diddy = c[i-1][j] ^ sus[i-1][j] ^ c[i][j];
                        }
                    }
                }


                // 2 colours this row
                if(sus[i][j] != '#'){
                    int minlen = j - ct[sus[i][j] - 'A'] + 1;

                    if(c[i-1][j] == sus[i][j] || c[i-1][j] == c[i][j]){
                        if(minlen > dp[0][i-1][j] + 1){  // 1-colour stair above cant be exented
                            
                        }else{
                            maximize(dp[1][i][j], min(curr2, dp[0][i-1][j] + 1));
                        }
                    }

                    if(min(c[i][j], sus[i][j]) == min(c[i-1][j], sus[i-1][j])
                        && max(c[i][j], sus[i][j]) == max(c[i-1][j], sus[i-1][j])){

                        maximize(dp[1][i][j], min(curr2, dp[1][i-1][j] + 1));
                    }

                }

                sus[i][j] = diddy;

            }


            ans = max(ans, dp[0][i][j]);
            if(dp[1][i][j] == 1) dp[1][i][j] = 0;
            ans2 = max(ans2, dp[1][i][j]);

        }
    }

    vect<int> cnt(n*m+5);
    auto range_add = [&](int l, int r){
        cnt[l]++;
        cnt[r+1]--;
    };

    int q;
    cin >> q;
    if(q==1){
        for(int i=1; n>=i; i++) for(int j=1; m>=j; j++) cnt[dp[0][i][j]]++;
        for(int i=n*m; i>0; i--) cnt[i] += cnt[i+1];

        cout << ans << el;
        for(int i=1; ans>=i; i++) cout << cnt[i] << ' ';
    }
    else{
        for(int i=1; n>=i; i++) for(int j=1; m>=j; j++){
            if(dp[1][i][j] > dp[0][i][j]){
                int l = dp[0][i][j]+1, r = dp[1][i][j];
                range_add(l, r);
            }
        }

        cout << ans2 << el;

        for(int i=1; ans2>=i; i++) cnt[i] += cnt[i-1], cout << cnt[i] << ' ';

    }
   
}
}

void sol(){
    stair::sol();
}

void maketest(){
    int n = rand(30, 50), m = rand(30, 50);
    ofstream cout("in.txt");

    cout << m << ' ' << n << el;

    vect<int> v;
    for(int i=0; n>i; i++) for(int j=0; m>j; j++) v.eb(i+1);
    shuffle(bend(v), rng);
    
    for(int i=0; n>i; i++){
        for(int j=0; m>j; j++) cout << v[i*m + j] << ' ';
        nextl;
    }
    cout << flush;
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