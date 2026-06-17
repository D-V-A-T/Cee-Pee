#include<bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,popcnt,lzcnt,tune=native")

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

const ll N = 2e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

const int S = 318;

struct block{
    vect<int> v;
    bool rev=0;
    ll sum=0;

    int size() const {
        return v.size();
    }
};

void sol(){
    int n, q;
    cin >> n >> q;

    vect<block> decum;
    decum.reserve(N);

    vect<int> a(n);
    
    for(int &i : a) cin >> i;

    auto squirt_decum = [&](){
        decum.clear();
        assert(a.size() == n);
        for(int i=0; n>i; i++){
            if(decum.empty() || decum.back().v.size() > S) decum.pb({{a[i]}, 0, a[i]});
            else{
                decum.back().v.eb(a[i]);
                decum.back().sum += a[i];
            }
        }
    };

    squirt_decum();

    for(int qid=1; q>=qid; qid++){


        if(qid % S == 0){
            a.clear();
            for(auto &b : decum){
                if(b.rev) reverse(bend(b.v));
                for(int j : b.v) a.eb(j);
            }
            squirt_decum();
        }

        int type;
        cin >> type;

        if(type == 1){
            int l, r;
            cin >> l >> r;
            l--, r--;

            int block_l = -1, block_r, blkid = 0;

            block lb;

            bool open = 0;

            for(auto &b : decum){
                int sz = b.size();
                auto &v = b.v;
                if(l < b.size()){
                    if(r < b.size()){
                        // l, r are in the same block
                        if(b.rev) reverse(bend(b.v)), b.rev = 0;
                        reverse(v.begin()+l, v.begin()+r+1);

                        break;
                    }else{

                        // cerr << b.sum << el;

                        // for(int i : v) cerr << i << ' ';

                        if(b.rev) reverse(bend(v)), b.rev = 0;

                        for(int i=l; v.size()>i; i++){
                            lb.v.eb(v[i]);
                            lb.sum += v[i];
                            b.sum -= v[i];
                        }

                        // cerr << b.sum << el;

                        for(int _=0; lb.size()>_; _++) v.pob();

                        block_l = blkid + 1;

                        open = 1;

                        l = 1e9;
                    }
                }
                else if(r < b.size()){
                    block nw;

                    // cerr << r+1 << ' ' << v.size() << el;

                    if(b.rev) reverse(bend(v)), b.rev = 0;


                    for(int i=r+1; v.size()>i; i++){
                        nw.v.eb(v[i]);
                        nw.sum += v[i];
                        b.sum -= v[i];
                    }

                    for(int _=0; nw.size()>_; _++) v.pob();

                    decum.insert(decum.begin() + blkid+1, nw);

                    // for(int i : v) cerr << i << ' ';
                    // cerr << "| ";
                    // for(int i : nw.v) cerr << i << ' ';

                    block_r = blkid + 1;
                    break;
                }

                l -= sz;
                r -= sz;

                blkid++;
            }

            if(block_l == -1) continue;

            decum.insert(decum.begin() + block_l, lb);  

            // for(int i=block_l; block_r >= i; i++){
            //     for(int j : decum[i].v) cout << j << ' ';
            //     nextl;
            // }

            int s = block_l + block_r, mid = s / 2;
            for(int i=block_l; mid >= i; i++){  

                // cerr << i << ' ' << s-i << ' ' << block_l << ' ' << block_r << el;
                decum[i].rev ^= 1;
                if(s-i != i) decum[s - i].rev ^= 1;
                swap(decum[i], decum[s - i]);
            }
        }else{

            int l, r;
            cin >> l >> r;
            l--, r--;

            ll ans = 0;

            bool open = 0;

            for(auto &b : decum){
                auto &v = b.v;

                // cout << b.sum << el;

                if(l < v.size()){
                    if(b.rev) reverse(bend(v)), b.rev = 0;

                    if(r < v.size()){
                        

                        for(int i=l; r>=i; i++) ans += v[i];

                        break;
                    }else{
                        if(b.rev) reverse(bend(v)), b.rev = 0;

                        for(int i=l; v.size()>i; i++) ans += v[i];
                    }

                    open = 1;
                    l = 1e9;
                }else if(r < v.size()){
                    if(b.rev) reverse(bend(v)), b.rev = 0;

                    for(int i=0; r>=i; i++) ans += v[i];

                    break;
                }else if(open) {
                    ans += b.sum;
                }


                l -= b.size();
                r -= b.size();
            }

            cout << ans << el;
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