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

const ll INF=1012762419733073422 , N=2e5+69, MOD=1e9+7;    

void ffopen(){
    if(fopen(FILE".inp", "r")){
        freopen(FILE".inp", "r", stdin);
        freopen(FILE".out", "w", stdout);
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

int n, q, S;
ll dist[N];
vect<pii> graph[N];

struct Seggs{
    set<int> t[N+N];
    void upd(int i, int j, int x, bool del, int l=1, int r=n, int id=1){
        auto &node = t[id];
        if(l > j || r < i)return;
        if(i <= l && r <= j){
            if(del && node.find(x) != node.end())node.erase(x); 
            else if(!del) node.insert(x);
            return;
        }
        int mid = (l+r)/2;
        upd(i, j, x, del, l, mid, id*2);
        upd(i, j, x, del, mid+1, r, id*2+1);
    }
    bool get(int p, vect<int>& v, int l=1, int r=n, int id=1){
        auto &node = t[id];
        if(l > p || r < p)return 0;
        if(l == r){       
            for(auto& i : node)v.eb(i);
            node.clear();
            return 1;
        }
        int mid = (l+r)/2;
        bool ispar = max(get(p, v, l, mid, id*2),  get(p, v, mid+1, r, id*2+1));
        if(ispar){
            for(auto& i : node)v.eb(i);
            node.clear();
            return 1;
        }else return 0;
    }
};


class DSU{
public:
    vector<int> par, len, mx;
    DSU(const int& n){
        par.rs(n+69);
        len.rs(n+69, 1);
        iota(bend(par), 0);
        mx = par;
    }int findpar(int u){
        if(u == par[u])
            return u;
        return u=findpar(par[u]);
    }void join(int u, int v){
        u=findpar(u);
        v=findpar(v);
        if(u != v){
            if(len[u] < len[v])swap(u, v);
            par[v]=u;
            len[u]+=len[v];
            mx[u] = max(mx[u], mx[v]);
        }
    }
};

struct fumo{
    ll u,d;
    bool operator < (const fumo& o) const{
        return d > o.d;
    }
};

struct fimi{
    int l,r,w,s;
};

struct fumi{
    int u,l,r,w;
} t3[N], t2[N];


void sol(){
    cin >> n >> q >> S;

    prq<fumo> pq;
    pq.push({S, 0});
    memset(dist, 14, sizeof dist);
    dist[S] = 0;

    Seggs sgt3;
    vect<fimi> v2[n+1];

    for(int i=0;q>i;i++){
        int t;cin >> t;
        if(t == 1){
            int u, v, w;cin >> u >> v >> w;
            graph[u].eb(v, w);
        }else if(t == 2){
            int l, r, u, w;
            cin >> u >> l >> r >> w;
            t2[i] = {i+n+5, l, r, w};
            v2[u].pb({l, r, w, i+n+5});
        }else{
            int l, r, u, w;
            cin >> u >> l >> r >> w;
            t3[i] = {u, l, r, w};
            sgt3.upd(l, r, i, 0);
        }
    }

    DSU A(n);

    while(pq.size()){
        auto [u, d] = pq.top();
        pq.pop();

        if(u > n){
            int l = t2[u-n-5].l, r = t2[u-n-5].r;
            for(int i=l;r>=i;i++){
                i = A.findpar(i);
                i = A.mx[i];
                if(i > r)break;
                if(dist[i] > d){
                    dist[i] = d;
                    pq.push({i, d});
                }
                A.join(i, i+1);
            }

            continue;
        }

        if(d > dist[u])continue;

        vect<int> q3;
        sgt3.get(u, q3);
        for(auto& i : q3)sgt3.upd(t3[i].l, t3[i].r, i, 1);

        for(auto [v, w] : graph[u]){
            int nd = w + dist[u];
            if(nd < dist[v]){
                dist[v] = nd;
                pq.push({v, nd});
            }
        }
        for(auto& i : q3){
            int nd = t3[i].w + dist[u], v = t3[i].u;
            if(nd < dist[v]){
                dist[v] = nd;
                pq.push({v, nd});
            }
        }

        for(auto[l, r, w, s] : v2[u]) pq.push({s, w + dist[u]});
    }

    for(int i=1;n>=i;i++)cout << (dist[i] < INF ? dist[i] : -1) << ' ';    
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