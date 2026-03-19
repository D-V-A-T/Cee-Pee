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
inline ll pm(ll a, const int b = MOD){
    a %= b;
    return a < 0 ? a + b : a;
}
inline ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

template<typename T, size_t B = 32>
struct BTree {
    struct Node {
        bool leaf = true;
        int sz = 0;
        T key[B];
        Node* ch[B + 1];

        Node(bool leaf = true) : leaf(leaf), sz(0) {
            memset(ch, 0, sizeof(ch));
        }
    };

    Node* root;

    BTree() {
        root = new Node(true);
    }

    int find_pos(Node* v, const T& x) {
        return std::lower_bound(v->key, v->key + v->sz, x) - v->key;
    }

    void split_child(Node* v, int i) {
        Node* u = v->ch[i];
        Node* w = new Node(u->leaf);

        int mid = B / 2;

        w->sz = u->sz - mid - 1;

        for (int j = 0; j < w->sz; j++)
            w->key[j] = u->key[mid + 1 + j];

        if (!u->leaf)
            for (int j = 0; j <= w->sz; j++)
                w->ch[j] = u->ch[mid + 1 + j];

        u->sz = mid;

        for (int j = v->sz; j > i; j--)
            v->ch[j + 1] = v->ch[j];

        v->ch[i + 1] = w;

        for (int j = v->sz - 1; j >= i; j--)
            v->key[j + 1] = v->key[j];

        v->key[i] = u->key[mid];
        v->sz++;
    }

    void insert_nonfull(Node* v, const T& x) {
        int i = v->sz - 1;

        if (v->leaf) {
            while (i >= 0 && v->key[i] > x) {
                v->key[i + 1] = v->key[i];
                i--;
            }
            v->key[i + 1] = x;
            v->sz++;
        } else {
            int pos = find_pos(v, x);

            if (v->ch[pos]->sz == B - 1) {
                split_child(v, pos);
                if (x > v->key[pos]) pos++;
            }

            insert_nonfull(v->ch[pos], x);
        }
    }

    void insert(const T& x) {
        if (root->sz == B - 1) {
            Node* s = new Node(false);
            s->ch[0] = root;
            root = s;

            split_child(s, 0);
            insert_nonfull(s, x);
        } else {
            insert_nonfull(root, x);
        }
    }

    bool lower_bound(const T& x, T &res) {
        Node* v = root;
        bool found = false;

        while (true) {
            int pos = find_pos(v, x);

            if (pos < v->sz) {
                res = v->key[pos];
                found = true;
            }

            if (v->leaf) break;
            v = v->ch[pos];
        }

        return found;
    }

    T get_min() {
        Node* v = root;
        while (!v->leaf) v = v->ch[0];
        return v->key[0];
    }

    bool empty() {
        return root->sz == 0;
    }
};

#define pil pair<int, ll>

const int S = 2067;
int spf[N], seen[N], timer = 1;
pil C[N]; // minimum cost to have an element divisble by i

ll E(vect<pil> &a){
	int n = a.size();
	reverse(bend(a));
	
	ll ans = INF;
	
	vect<int> smol;
	BTree<int> big;
	
	auto add_num = [&](int x, ll cost, bool added_one){
		while(x > 1){
			int p = spf[x];
			while(x % p == 0) x /= p;
			
			if(seen[p] != timer && !added_one) {
				seen[p] = timer;
				
				if(p < S) smol.eb(p);
				else big.insert(p);
			}
			
			if(C[p].fi != timer){
				C[p] = {timer, cost};
			}else{
				// should take care of when add 0 or 2 numbers
				ans = min(ans, C[p].se + cost), C[p].se = min(C[p].se, cost); 
				// cout << C[p].se << ' ' << cost << el;
			}
		}
	};
	
	
	for(auto i : a){
		int x = i.fi, cost = i.se;
		
		// use some operations on i
        // !!! optimize : only do on the element with minimum cost
		
		for(int j : smol) ans = min(ans, (ll)cost * pm(j - x, j));
		
		if(!big.empty()){
			int curr = big.get_min(), sus = x / curr;
			
			while("sussy"){				
				ans = min(ans, (ll)(curr - (x - sus * curr)) * cost);
				
				if(sus == 0) break;
				
				// floor(A / nxt) = sus - 1
				sus = sus - 1;
				curr = (x / (sus + 1)) + 1;
				
				int nxt;
				if(!big.lower_bound(curr, nxt)) break;
				curr = nxt;
			}
		}
		
		
		add_num(x, 0, 0);		
		add_num(x+1, cost, 1);
	}
	
	timer++;
	return ans;
}

void sol(){
	int n;
	cin >> n;
	vect<pil> a(n);
	for(auto &i : a) cin >> i.fi;
	for(auto &i : a) cin >> i.se;
	
	cout << min(E(a), E(a)) << el;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    IO();
    
    iota(spf, spf + N, 0);
    
    for(int i=2; N>i*i; i++){
    	if(spf[i] != i) continue;
    	for(int j=i*i; N>j; j+=i) spf[j] = min(spf[j], i);
    }
    
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