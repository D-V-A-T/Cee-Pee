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
#define ull unsigned long long

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

const ll N = 1e5 + 69, MOD = 1e9+7, INF = 1000000000000000069;

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

int n, q, k, op[N], parent[N], depth[N], heavy[N], head[N], pos[N], sub_size[N];
pair<int, ull> tmp[N];
ull val[N];
const ull full_bits = ULLONG_MAX;
vect<int> tour, G[N];

void turn_on(ull& num, int l, int r){
    int mask = ((1 << (r - l + 1)) - 1) << l;    
    num |= mask;    
}

void turn_off(ull& num, int l, int r){
    int mask = ((1 << (r - l + 1)) - 1) << l;
    num &= ~mask;   
}

struct node{
    ull l0, r1, l1, r0;

    node(){
        l0=0, l1=full_bits, r0=0, r1=full_bits;
    }

    void reset(){
        l0=0, l1=full_bits, r0=0, r1=full_bits;
    }

};

struct Seggs{
    node t[4 * N];

    Seggs(){
        build();
    }

    node merge(node left, node right, int left_op, int right_op){
        node res;

        ull zero_l, one_l, zero_r, one_r;
        
        zero_l = left.l0;
        ull curr_zero = ~zero_l;
        ull curr_one = zero_l;
        ull final = (curr_zero & right.l0) 
                |   (curr_one & right.l1);
        res.l0 = final;

        one_l = left.l1;
        curr_zero = ~one_l;
        curr_one = one_l;
        final = (curr_zero & right.l0)
            |   (curr_one & right.l1);
        res.l1 = final;

        zero_r = right.r0;
        curr_zero = ~zero_r;
        curr_one = zero_r;
        final = (curr_zero & left.r0) 
            |   (curr_one & left.r1);
        res.r0 = final;

        one_r = right.r1;
        curr_zero = ~one_r;
        curr_one = one_r;
        final = (curr_zero & left.r0) 
            |   (curr_one & left.r1);
        res.r1 = final;

        
        return res;

    }

    void build(int l=0, int r=n-1, int id=1){
        if (l == r){
            // cout << l << ' ' << tour[l] << el;
            if(op[l] == 1){
                t[id].l1 &= val[l];
                t[id].l0 &= val[l];
                t[id].r1 &= val[l];
                t[id].r0 &= val[l];
            }
            if (op[l] == 2){
                t[id].l1 |= val[l];
                t[id].l0 |= val[l];
                t[id].r1 |= val[l];
                t[id].r0 |= val[l];
            }

            if(op[l] == 3){
                t[id].l1 ^= val[l];
                t[id].l0 ^= val[l];
                t[id].r1 ^= val[l];
                t[id].r0 ^= val[l];
            }

            return;
        }   

        int mid = (l + r) / 2;
        build(l, mid, id*2);
        build(mid+1, r, id*2+1);


        t[id] = merge(t[id*2], t[id*2+1], op[mid], op[mid+1]);


    }

    void upd(int p, int l=0, int r=n-1, int id=1){
        if(l > p || r < p) return;
        if (l == r){
            t[id].reset();
            if(op[l] == 1){
                t[id].l1 &= val[l];
                t[id].l0 &= val[l];
                t[id].r1 &= val[l];
                t[id].r0 &= val[l];
            }
            if (op[l] == 2){
                t[id].l1 |= val[l];
                t[id].l0 |= val[l];
                t[id].r1 |= val[l];
                t[id].r0 |= val[l];
            }

            if(op[l] == 3){
                t[id].l1 ^= val[l];
                t[id].l0 ^= val[l];
                t[id].r1 ^= val[l];
                t[id].r0 ^= val[l];
            }
            return;
        }   

        int mid = (l + r) / 2;
        upd(p, l, mid, id*2);
        upd(p, mid+1, r, id*2+1);

        t[id] = merge(t[id*2], t[id*2+1], op[mid], op[mid+1]);
    }

    void query(int i, int j, ull& zero, ull& one, bool merge_left, int l=0, int r=n-1, int id=1){


        if(l > j || r < i) return;
        if(i <= l && r <= j){

            if(merge_left){
                ull curr_zero = ~zero, curr_one = zero;
                ull final = (curr_zero & t[id].l0) | (curr_one & t[id].l1);
                zero = final;

                curr_zero = ~one, curr_one = one;
                final = (curr_zero & t[id].l0) | (curr_one & t[id].l1);
                one = final;

            } else{
                ull curr_zero = ~zero, curr_one = zero;
                ull final = (curr_zero & t[id].r0) | (curr_one & t[id].r1);
                zero = final;

                curr_zero = ~one, curr_one = one;
                final = (curr_zero & t[id].r0) | (curr_one & t[id].r1);
                one = final;
            }
            return;
            
        }
        int mid = (l+r)/2;

        if(merge_left){
            query(i, j, zero, one, merge_left, l, mid, id*2);
            query(i, j, zero, one, merge_left, mid+1, r, id*2+1);
        }else{
            query(i, j, zero, one, merge_left, mid+1, r, id*2+1);
            query(i, j, zero, one, merge_left, l, mid, id*2);
        }
    }

};


void DFS(int u){
    int max_sub_size = 0;
    sub_size[u] = 1;
    for(int v : G[u]) if (v != parent[u]){
        parent[v] = u;
        depth[v] = depth[u] + 1;

        DFS(v);

        sub_size[u] += sub_size[v];

        if (sub_size[v] > max_sub_size){
            max_sub_size = sub_size[v];
            heavy[u] = v;
        }   
    }
}

void decompose(int u, int h){
    head[u] = h;
    pos[u] = tour.size();
    tour.eb(u);

    if (heavy[u] != -1){
        decompose(heavy[u], h);
    }

    for (int v : G[u]) if (v != parent[u] && v != heavy[u]){
        decompose(v, v);
    }
}

void HLD(){
    memset(heavy, -1, sizeof heavy);
    DFS(1);
    decompose(1, 1);
}

ull query(int a, int b, ull z, Seggs& sgt){
    ull zero = 0, one = full_bits;

    vect<vect<int>> lz_query;

    while(head[a] != head[b]){
        if(depth[head[a]] >= depth[head[b]]){
            sgt.query(pos[head[a]], pos[a], zero, one, false);
            a = parent[head[a]];
        }else{
            lz_query.pb({pos[head[b]], pos[b], true});
            b = parent[head[b]];
        }
    }



    if (depth[a] >= depth[b]){
        sgt.query(pos[b], pos[a], zero, one, false);
    }else {
        sgt.query(pos[a], pos[b], zero, one, true);
    }
    
    reverse(bend(lz_query));
    for (auto& lq : lz_query){
        int l, r, b;
        l = lq[0], r = lq[1], b = lq[2];
        sgt.query(l, r, zero, one, b);
    }


    ull curr_num = 0, res = 0;
    for(int i=63;i>=0;i--){

        if (zero & (1ull<<i)) res ^= 1ull << i;
        else if((one & (1ull<<i)) && (curr_num + (1ull << i) <= z)){
            res ^= 1ull << i;
            curr_num += (1ull << i);
        }
    }

    return res;
}

void sol(){
    cin >> n >> q >> k;


    for(int i=1; n>=i; i++){
        cin >> tmp[i].fi >> tmp[i].se;
    }

    for(int i=1;n>i;i++){
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    // for(int i=0;5>=i;i++) cout << (((i | 1) ^ 7) ^ 6) << el;

    HLD();


    for(int i=1;n>=i;i++){
        tie(op[pos[i]], val[pos[i]]) = tmp[i];
    }

    Seggs sgt;
    while(q--){
        int t, a, b;
        ull z;
        cin >> t >> a >> b >> z;
        // cout << t << ' ' << a << ' ' << b << ' ' << z << el;
        // return;
        if(t == 1){
            cout << query(a, b, z, sgt) << el;
        }else{
            op[pos[a]] = b;
            val[pos[a]] = z;
            sgt.upd(pos[a]);
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
