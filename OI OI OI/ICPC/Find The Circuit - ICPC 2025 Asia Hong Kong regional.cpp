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

const ll N = 5e5 + 5, MOD = 1e9+7, INF = 1000000000000000069;

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

vect<int> G[N];

namespace Alob{

	void sol(){
		int n, m;
		cin >> n >> m;
		vect<pii> edges;
		for(int i=0; m>i; i++){
			int u, v;
			cin >> u >> v;
			G[u].eb(v);
			G[v].eb(u);
			edges.eb(u, v);
		}
		
		int k, par[n+1];
		cin >> k;
		int cyc[k], nxt[n+1], pre[n+1];

		queue<int> que;
		vect<bool> visited(n+5), incyc(n+5);
		vect<pii> dih;
		vect<int> pos(n+5);

		for(int i=0; k>i; i++){
			cin >> cyc[i];
			que.push(cyc[i]);
			incyc[cyc[i]] = 1;
			if(i) dih.eb(cyc[i-1], cyc[i]), nxt[cyc[i-1]] = cyc[i], pos[cyc[i]] = i;
		}

		dih.eb(cyc[k-1], cyc[0]);
		nxt[cyc[k-1]] = cyc[0];
		pre[cyc[0]] = cyc[k-1];

		for(int i=1; k>i; i++) pre[cyc[i]] = cyc[i-1];


		
		while(que.size()){
			int u = que.front();
			que.pop();

			if(visited[u]) continue;
			visited[u] = 1;

			for(int v : G[u]) if(!visited[v]){
				if(!incyc[v]) dih.eb(v, u);
				else{
					assert(incyc[u]);
					if(v != nxt[u] && v != pre[u]){
						if(pos[u] < pos[v]) dih.eb(u, v);
						else dih.eb(v, u);
					}
				}
				que.push(v);
			}
		}

		for(pii i : dih) cout << i.fi << ' ' << i.se << el;
	}

}
namespace Bice{
	vect<int> del(N), dist(N, 1e9), sussy, visited(N), nxt(N), pre(N);

	void dfs(int u, int st){
		visited[u] = 1;	


		assert(G[u].size() > 0);

		int cdist = -1;

		for(int v : G[u]) if(!del[v]) {

			
			if(!visited[v]) nxt[u] = v, dfs(v, st);
			
			if(nxt[u] == 0) nxt[u] = v, cdist = dist[v];
			
			// if(u == 100) cout << dist[pre[u]] << ' ' << dist[v] << el;
			
			if(dist[v] > cdist && dist[v] < dist[pre[u]]){
				nxt[u] = v, cdist = dist[v];
			}
		
			if(v == st) nxt[u] = v, dist[u] = 1;
		}

		// cout << u << ' ' << cdist + 1 << el;
		pre[nxt[u]] = u;
		dist[u] = cdist + 1;
	}

	void sol(){
		int n, m;
		cin >> n >> m;
		vect<int> in(n+5);
		vect<pii> edges;
		for(int i=0; m>i; i++){
			int u, v;
			cin >> u >> v;
			edges.eb(u, v);
			in[v] ++;
		}
		
		// shuffle(bend(edges), rng);

		for(pii e : edges) G[e.fi].eb(e.se);

		queue<int> que;
		for(int i=1; n>=i; i++) if(in[i] == 0) que.push(i);
		while(que.size()){
			int u = que.front();
			que.pop();
			del[u] = 1;

			for(int v : G[u]) if(--in[v] == 0) que.push(v);
		}

		int livecnt = 0;
		for(int i=1; n>=i; i++) livecnt += !del[i];
		
		vect<int> cum(n+5);
		
		for(pii i : edges){
			if(del[i.fi] || del[i.se]) continue;
			cum[i.se] ^= i.fi;
		}
		
		int st;
		for(int i=1; n>=i; i++){
			if(!del[i] && in[i] == 1) st = i, que.push(i);		
		}
		
		while(que.size()){
			int u = que.front();
			que.pop();
			
			nxt[cum[u]] = u;
			
			for(int v : G[cum[u]]) if(!del[v]){
				if(v == u) continue;
				
				in[v] --;
				cum[v] ^= cum[u];
				
				if(in[v] == 1) que.push(v);
			}
		}
		
		cout << st << ' ';
		int curr = nxt[st];
		while(curr != st){
			cout << curr << ' ';
			curr = nxt[curr];
		}
		
	}
};

void sol(){
	int type;
	cin >> type;
	if(type == 1) Alob::sol();
	else Bice::sol();
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