#ifdef ONLINE_JUDGE

#include<bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,popcnt,lzcnt,tune=native")

#endif 

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

const ll N = 1e5 + 1, MOD = 1e9+7, INF = 1000000000000000069;

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

const int S = 169;
const int MAX_BLOCK  = (N-1) / S + 2;

// int inv[N+2][MAX_BLOCK];
ll pfs[N+2][MAX_BLOCK], B[MAX_BLOCK][MAX_BLOCK], pfs_b[N], sfs_b[N];
int idx[N];


ll get(int i, int block_l, int block_r){
    if(block_l > block_r) return 0;
    return pfs[i][block_r] - (block_l ? pfs[i][block_l-1] : 0);
}

ll get_block(int block_i, int block_l, int block_r){
    if(block_l > block_r) return 0;
    return B[block_i][block_r] - (block_l ? B[block_i][block_l-1] : 0);
}

ll bit[N];

void UPD(int x, int v){
    for(;x>0;x-=x&-x) bit[x] += v;
}

ll GET(int x){
    ll res = 0;
    for(;N>x;x+=x&-x) res += bit[x];
    return res;
}

ll count_inv(int l, int r, vect<int>& a){
    ll res = 0;

    for(int i : a){
        res += GET(i);
        UPD(i, 1);
    }

    for(int i : a) UPD(i, -1);
    
    return res;
}

int upper[MAX_BLOCK], lower[MAX_BLOCK];

void sol(){
    int n, q;
    cin >> n >> q;
    int a[n], b[n];
    pii sus[n];
    for(int i=0; n>i; i++){
        cin >> a[i];
        b[i] = a[i];
        sus[i] = {a[i], i};
        idx[a[i]] = i;
    }

    for(int bl=0; (n-1)/S >= bl; bl++){
        int ed = min(n, (bl + 1) * S);
        vect<int> curr;
        for(int i=bl*S; ed>i; i++) curr.eb(a[i]);

        for(int i = bl * S; ed > i; i++){
            pfs_b[i] = 0;
            for(int j = i-1; j >= bl*S; j--){
                if(a[j] > a[i]) pfs_b[i]++;
            }
            if(i > bl*S) pfs_b[i] += pfs_b[i-1];
        }

        for(int i=ed-1; i>=bl*S; i--){
            for(int j=i+1; ed>j; j++){
                if(a[i] > a[j]) sfs_b[i]++;
            }

            if(i < ed-1) sfs_b[i] += sfs_b[i+1];
        }

        B[bl][bl] = pfs_b[ed-1];

        sort(b + bl * S, b + ed);

        lower[bl] = upper[bl] = bl * S;
    }

    sort(sus, sus+n);



    for(auto &[val, i] : sus){
        int block_i = i / S;
        for(int bl = 0; (n-1)/S >= bl; bl++){
            int ed = min(n, (bl + 1) * S), inv;

            while(upper[bl] < ed && b[upper[bl]] <= val) upper[bl]++;
            while(lower[bl] < ed && b[lower[bl]] < val) lower[bl]++;

            if(bl < block_i) // so so > a[i]
                inv = (ed - bl*S) - (upper[bl] - bl * S); 
            else if(bl > block_i) // so so < a[i]
                inv = lower[bl] - (bl * S);

            if(bl != block_i) B[block_i][bl] += inv;

            pfs[i][bl] = inv;
            if(bl) pfs[i][bl] += pfs[i][bl-1];
        }
    }

    for(int bl = 0; (n-1)/S >= bl; bl++) partial_sum(B[bl], B[bl] + MAX_BLOCK, B[bl]);


    ll ans = 0;
    while(q--){
        ll l, r;cin >> l >> r;

        l = ans ^ l, r = ans ^ r;
        // l = (ans + l) % n + 1, r = (ans + r) % n + 1;

        if(l > r) swap(l, r);
        // cout << l << ' ' << r << el;
        l--;r--;
        
        assert(0 <= l && l < n && 0 <= r && r < n);

        int block_l = l / S, block_r = r / S;
        int lim_l = min(n, (block_l+1) * S), lim_r = min(n, (block_r + 1) * S);
        vect<int> sad;
        ans = 0;    

        if(block_l == block_r){
            for(int i = l; r>=i; i++) sad.eb(a[i]);
            ans += count_inv(0, sad.size()-1, sad);
        }else{
            // cout << l << ' ' << r << ' ' << sfs_b[l] << ' ' << pfs_b[r] << el;
            ans += sfs_b[l] + pfs_b[r];

            for(int i=l; lim_l>i; i++){
                ans += get(i, block_l + 1, block_r - 1);
            }

            for(int i = block_l+1; block_r > i; i++) ans += get_block(i, block_l + 1, i);

            for(int i=block_r*S; r>=i; i++){
                ans += get(i, block_l + 1, block_r - 1);
            }

            // cout << "! " << ans << el;

            int lptr = block_l * S, rptr = block_r * S;
            int left_block_size = lim_l - l;

            // cout << lptr << ' ' << lim_l-1 << ' ' << rptr << ' ' << lim_r-1 << el;

            while(lptr < lim_l && rptr < lim_r){
                if(idx[b[lptr]] < l){
                    lptr++;
                    continue;
                }
                if(idx[b[rptr]] > r){
                    rptr++;
                    continue;
                }

                if(b[lptr] < b[rptr]) lptr++, left_block_size -- ;
                else{
                    ans += left_block_size;
                    rptr++;
                }
            }
        }

        

        cout << ans << el"\n";

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
