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
#define clz __builtin_clzll
#define ctz __builtin_ctzll
#define ll long long 
#define dbl long double
#define int long long

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

int n, m, sz;
const int segsize = 5e6;
vect<int> zip;

struct Seggs{
    int t[segsize], lz[segsize];

    void init(){
        fill(t, t + 4 * sz + 5, -1e15);
        fill(lz, lz + 4 * sz + 5, 0);
    }

    void push(int l, int r, int id){
    	t[id] += lz[id];

        if(l < r){
            lz[id*2] += lz[id];
            lz[id*2+1] += lz[id];
        }

        lz[id] = 0;
    };

    void set_val(int p, int val, bool sus = 0, int l=0, int r=sz-1, int id=1){
    	push(l, r, id);
    	if(l > p || r < p) return ;
    	if(l == r){
    		t[id] = max(t[id], val);

    		return;
    	}

    	int mid = (l + r) / 2;

    	set_val(p, val, sus, l, mid, id*2);
    	set_val(p, val, sus, mid+1, r, id*2+1);

    	t[id] = max(t[id*2], t[id*2+1]);
    }

   	void upd(int i, int j, int val, int l=0, int r=sz-1, int id=1){
   		push(l, r, id);

   		if(l > j || r < i) return;
   		if(i <= l && r <= j){
   			lz[id] += val;
   			push(l, r, id);
   			return;
   		}

   		int mid = (l + r) / 2;
   		upd(i, j, val, l, mid, id*2);
   		upd(i, j, val, mid+1, r, id*2+1);

   		t[id] = max(t[id*2], t[id*2+1]);
   	}

    int get(int i, int j, int l=0, int r=sz-1, int id=1){
        push(l, r, id);

        if(l > j || r < i) return -INF;

        if(i <= l && r <= j) return t[id];

        int mid = (l + r) / 2;
        return max(get(i, j, l, mid, id*2), get(i, j, mid+1, r, id*2+1));
    }
} sgt, sgt2;

void sol(){
    cin >> n >> m;
    vect<pii> a(n);
    zip.clear();

    for(int i=0; n>i; i++){
        cin >> a[i].fi >> a[i].se;

        zip.eb(a[i].fi);
        zip.eb(a[i].fi - 1);
    }

    sort(bend(zip));
    zip.rs(unique(bend(zip)) - zip.begin());
    sz = zip.size();

    int ans = 0;

    sgt.init();
    sgt2.init();


    auto gz = [&](int x){
    	return lwb(bend(zip), x) - zip.begin();
    };

    for(int i=0; zip.size()>i; i++) {
    	if(zip[i] < a[0].fi) sgt2.set_val(i, 0, 1), sgt.set_val(i,  -zip[i] * m);
    	else sgt2.set_val(i, a[0].se - zip[i] * m  + zip[i] * m, 1), sgt.set_val(i, a[0].se - zip[i] * m);

    	// cout << "!! " << i << ' ' << a[0].se - zip[i] * m * 2 << el;

    }
    // cout << sgt2.t[1] << el;

    // nextl;deb;
   		// cout << sgt2.t[1] << ' ' << sgt.get(0, 0) << el;

    // cout << "? " <<  sgt.get(gz(a[0].fi), zip.size() - 1) << el;

    ans = max(0ll, sgt.t[1]);


    for(int i=1; n>i; i++){

    	// do nothing
    	// _____

    	// spare
    	int spare = sgt.get(gz(a[i].fi), zip.size() - 1);


    	// kill



    	int kill = max(sgt2.get(0, gz(a[i].fi)) - a[i].fi * m  + a[i].se, sgt.get(gz(a[i].fi), zip.size()-1) + a[i].se);

    	// cout << spare << ' ' << kill << ' ' << sgt.get(gz(10), gz(10)) << el;

    	// cout << i << ' ' << sgt.get(gz(a[i].fi), zip.size() - 1) << ' ' << spare << ' ' << kill << el;

    	// cout << spare << ' ' << sgt.get(gz(a[i].fi), zip.size()-1) << el;
    	// cout << spare << ' ' << kill << ' ' <<  sgt.get(gz(a[i].fi), zip.size()-1) + a[i].se << el;

    	sgt.upd(gz(a[i].fi), zip.size() - 1, a[i].se);
    	sgt2.upd(gz(a[i].fi), zip.size() - 1, a[i].se);



    	sgt.set_val(gz(a[i].fi), kill);
    	sgt2.set_val(gz(a[i].fi), kill + (a[i].fi) * m);

    	sgt.set_val(gz(a[i].fi - 1), spare);
    	sgt2.set_val(gz(a[i].fi - 1), spare + (a[i].fi-1) * m, 1);

    	// if(i == n-2) cout << ' ' << kill << ' ' << sgt.get(gz(a[i].fi), gz(a[i].fi)) << el;


    	ans = max(ans, max(kill, spare));


    }


    cout << ans << el;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    int t = 1;
    cin >> t;
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