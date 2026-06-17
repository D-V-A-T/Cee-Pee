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

#define FILE "GIFT"
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
ll pm(ll a,const int b=MOD){return (a%=b) < 0 ? a + b : a;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int SUS = 0;

#define idl id+1
#define idr id+2*(mid-l+1) 

struct node{
    ll w, g, sus, susw;

    ll W(){
        return w + susw * SUS;
    }

    ll G(){
        return g + sus * SUS;
    }

    node operator + (const node &o) const{
        node res;
        res.g = g + o.g;
        res.w = w + o.w;
        res.susw = susw + o.susw;
        res.sus = sus + o.sus;
        return res;
    }

};

int n, q;
vect<pii> a;
vect<array<int, 3>> b;

struct Seggs{
    node t[2*N];

    Seggs(){
        build();
    }

    void build(int l=0, int r=n-1, int id=1){
        if(l == r){
            t[id] = {0, 0, 1, a[l].fi};
            return ;
        }

        int mid = (l + r) / 2;

        build(l, mid, idl);
        build(mid+1, r, idr);



        t[id] = t[idl] + t[idr];

        // if(l == 0 && r == 1){
        //     SUS = 4;    
        //     cout << t[id].susw << el;
        // }
    }

    void activate(int p, int l=0, int r=n-1, int id=1){
        if(l > p || r < p) return;
        if(l == r){
            // cout << "!! " << a[l].fi << ' ' << a[l].se << el;
            t[id] = {a[l].fi * a[l].se, a[l].se, 0, 0};
            return;
        }

        int mid = (l + r) / 2;
        activate(p, l, mid, idl);
        activate(p, mid+1, r, idr);

        t[id] = t[idl] + t[idr];
    }

    ll find(int x, int tw, int tg, int l=0, int r=n-1, int id=1){
        // total g[id] >= x


        // cerr << tw << ' ' << tg << ' ' << l << ' ' << r << el;

        if(l == r){


            int need = x - tg;
            // assert(need <= a[l].se);
            if(need <= a[l].se) return tw + need * a[l].fi;
            else return INT_MAX;
        }

        int mid = (l+r)>>1;

        // cerr << t[idl].W() << ' ' << t[idl].susw << el;

        if(tg + t[idl].G() >= x) return find(x, tw, tg, l, mid, idl);
        return find(x, tw + t[idl].W(), tg + t[idl].G(), mid+1, r, idr);
    }

};

struct query{
    int m, t, k, l=0, r=1e9, id;bool type;

    bool operator < (const query &o) const{
        return (l+r) < (o.l + o.r);
        // return k < o.k;
    }
};

ll ANS[N];

void PussyBreakerS(vect<query> queries){
    vect<query> tmp;
    tmp.reserve(N);

    Seggs sgt;

    // deb;
    while(!queries.empty()){
        int ptr = 0;
        tmp.clear();

        sgt.build();

        sort(bend(queries));
        for(auto &que : queries){
            int mid = (que.l+que.r)>>1;
            while(ptr < n && b[ptr][1] < mid){
                // cerr << b[ptr][1] << el;
                sgt.activate(b[ptr][2]);
                ptr++;
            }


            // mid = 3;

            SUS = mid;
            que.t = mid;


            // cout << que.l << ' ' << que.r << ' ' << sgt.find(que.t * que.k, 0, 0)
            // << ' ' << sgt.t[1].W() << el;

            // cout << que.t * que.k << ' ' << sgt.find(que.t * que.k, 0, 0) 
            // << ' ' << sgt.t[1].G() << el;

            if(que.t * que.k > sgt.t[1].G() || sgt.find(que.t * que.k, 0, 0) > que.m){
                que.r = mid - 1;
            }else{
                ANS[que.id] = mid;
                que.l = mid + 1;
            }


            // return;

            if(que.l <= que.r){
                tmp.eb(que);
            }
        }

        swap(tmp, queries);
    }
}

void sol(){
    cin >> n >> q;

    a.rs(n);
    b.rs(n);
    for(pii &i : a) cin >> i.fi;
    for(pii &i : a) cin >> i.se;
    sort(bend(a));

    for(int i=0; n>i; i++){
        b[i][0] = a[i].fi;
        b[i][1] = a[i].se;
        b[i][2] = i;
    }

    sort(bend(b), [](const array<int, 3> &x, const array<int, 3> &y){
        return x[1] < y[1];
    });

    
    vect<query> queries(q);
    for(int i=0; q>i; i++){
        int type;
        cin >> type;


        queries[i].type = type-1;
        if(type == 1){
            cin >> queries[i].m >> queries[i].k >> queries[i].t;
            queries[i].l = queries[i].r = queries[i].t;
            queries[i].id = i;
        }else{
            cin >> queries[i].m >> queries[i].k;
            queries[i].id = i;
        }
    }

    PussyBreakerS(queries);

    for(int i=0; q>i; i++){
        if(!queries[i].type) cout << !!(ANS[i]) << el;
        else cout << ANS[i] << el;
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
