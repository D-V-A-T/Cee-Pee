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
#define int long long
typedef array<int, 3> AI3;

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

const ll N = 1.5e5 + 5, MOD = 998244353, INF = 1000000000000000069;

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

const int S = 388, MAX_BLOCK = N / S + 5;


vect<int> a, p, before[N], after[N];
int sus[MAX_BLOCK][MAX_BLOCK], in[N], n, q;
ll lz[MAX_BLOCK], sum[MAX_BLOCK], ANS[N];

struct query{
    int type, l, r, v;
} que[N];

void suscalc(int blkid){
    int l = blkid * S, r = min(n-1, l+S-1);

    memset(sus[blkid], 0, sizeof sus[blkid]);
    for(int i=l; r>=i; i++){
        sus[blkid][p[i] / S] ++;
    }
    
    for(int i=1; (n-1)/S>=i; i++) sus[blkid][i] += sus[blkid][i-1]; 
}

void TungTung(int l, int r, int v){ // query type 1
    int block_l = l/S, block_r = r/S;

    if(block_l == block_r){
        for(int i=l; r>=i; i++){
            a[p[i]] += v;
            sum[p[i] / S] += v;
        }
    }else{

        for(int i=l; (block_l+1)*S >i; i++) a[p[i]] += v, sum[p[i] / S] += v;

        for(int i=block_l+1; block_r>i; i++) lz[i] += v;

        for(int i=block_r*S; r>=i; i++) a[p[i]] += v, sum[p[i] / S] += v;
    }
}

int Hikari(int l, int r){ // query type 2
    int block_l = l / S, block_r = r / S;

    ll ans = 0;

    if(block_l == block_r){
        for(int i=l; r>=i; i++) ans += a[i] + lz[in[i]];
    }else{
        for(int i=l; (block_l+1) * S > i; i++) ans += a[i] + lz[in[i]];


        for(int i=block_l+1; block_r > i; i++) ans += sum[i];

        if(block_r - block_l > 1)   
            for(int i=0; (n-1)/S>=i; i++)
                ans += lz[i] * (sus[i][block_r-1] - sus[i][block_l]);
            

        for(int i=block_r*S; r>=i; i++) ans += a[i] + lz[in[i]];
    }

    return ans;
}

void Neckhurt(int x, int y){
    int block_x = x / S, block_y = y / S;
    in[p[x]] = block_y;
    in[p[y]] = block_x;

    for(int i=block_x*S; min(n, (block_x+1)*S) > i; i++) a[p[i]] += lz[block_x], sum[p[i] / S] += lz[block_x];
    lz[block_x] = 0;

    for(int i=block_y*S; min(n, (block_y+1)*S) > i; i++) a[p[i]] += lz[block_y], sum[p[i] / S] += lz[block_y];
    lz[block_y] = 0;

    swap(p[x], p[y]);

    suscalc(block_x);
    suscalc(block_y);
}

bool visited[N];

void SigeonPex(int qid){
    if(qid > q) return;

    auto &Q = que[qid];
    int type = Q.type, l = Q.l, r = Q.r, v = Q.v;


    // cerr << qid << el;

    if(visited[qid]) return;

    assert(!visited[qid]);
    visited[qid] = 1;

    for(int nq : before[qid]) SigeonPex(nq); //cerr << qid << ' ' << nq << el;

    if(type == 1){
        TungTung(l, r, v);
    }else if(type == 2){
        ANS[qid] = Hikari(l, r);
    }else if(type == 3){
        Neckhurt(l, r);
    }

    // if(qid == 4){
    //     for(int i : after[qid]) cout << i << ' ';
    //     nextl;
    // }

    for(int nq : after[qid]) SigeonPex(nq);

    if(type == 1){
        TungTung(l, r, -v);
    }else if(type == 3){
        Neckhurt(l, r);
    }
}

void sol(){
    cin >> n >> q;

    a.rs(n);
    p.rs(n);

    for(int &i : a) cin >> i;
    for(int &i : p) cin >> i, i--;

    for(int i=0; n>i; i++){
        in[p[i]] = i / S;
        sum[i / S] += a[i];
    }

    for(int i=0; (n-1)/S>=i; i++) suscalc(i);

    int nearestnotsus[N], par[N];
    nearestnotsus[0] = 0;

    for(int qid=1; q>=qid; qid++){
        int type;
        cin >> type;

        if(type == 1){
            int l, r, v;
            cin >> l >> r >> v;
            l--, r--;

            que[qid] = {type, l, r, v};
        }else if(type == 2){
            int l, r;
            cin >> l >> r;
            l--, r--;
            que[qid] = {type, l, r, 0};
            
        }else if(type == 3){
            int x, y;
            cin >> x >> y;
            x--, y--;
            que[qid] = {type, x, y, 0};
        }else{
            int x;
            cin >> x;
            que[qid] = {type, 0, 0, 0};



            if(x == qid){
                after[x-1].eb(x);
            }
            else if(que[x].type < 4) before[x].eb(qid);
            else{
                after[x-1].eb(qid);
            }
        }

        if(type < 4){
            nearestnotsus[qid] = qid;
            after[qid-1].eb(qid);
        }else{
            nearestnotsus[qid] = nearestnotsus[qid-1];
        }

    }

    memset(ANS, -1, sizeof ANS);
    for(int i=1; q>=i; i++) if(!visited[i]){
        // cout << i << el;
        SigeonPex(i);
    }

    for(int i=1; q>=i; i++) if(ANS[i] != -1) cout << ANS[i] << el;

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