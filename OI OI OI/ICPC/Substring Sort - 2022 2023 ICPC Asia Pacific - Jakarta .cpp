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

const ll N = 1e5 + 5, MOD = 1e9+7, INF = 1000000000000000069;

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

const int S = 67, MAX_BLOCK = N / S + 5;

#define my_struct pair<string, char>

char order[MAX_BLOCK][3];
my_struct A[MAX_BLOCK], B[MAX_BLOCK], C[MAX_BLOCK];



void sol(){
	int n, q;
	cin >> n >> q;
	string a, b, c;
    cin >> a >> b >> c;
	
	
	for(int i=0; n>i; i++){
		A[i / S].fi += a[i];
		B[i / S].fi += b[i]; B[i / S].se = 1;
		C[i / S].fi += c[i]; C[i / S].se = 2;
	}
	
	
	auto build_block = [&](int i){

        order[i][A[i].se] = (A[i].fi > B[i].fi) + (A[i].fi > C[i].fi);
        order[i][B[i].se] = (B[i].fi > A[i].fi) + (B[i].fi > C[i].fi);
        order[i][C[i].se] = (C[i].fi > A[i].fi) + (C[i].fi > B[i].fi);
	};
	
	for(int i=0; MAX_BLOCK > i; i++){
		build_block(i);
	}

    int smolest = 0, biggest = 2;
	
	auto check_sus = [&](int l, int r, vect<char> &sus){
		int block_l = l / S, block_r = r / S, st = block_l * S;
		for(int i=l; r>=i; i++){
			vect<pair<char, char>> gay;
	
			if(sus[0] == 4) gay.eb(A[block_l].fi[i - st], 0);
			if(sus[1] == 4) gay.eb(B[block_l].fi[i - st], 1);
			if(sus[2] == 4) gay.eb(C[block_l].fi[i - st], 2);
			sort(bend(gay));

            // for(auto i : gay) cout << i.fi << el;
			
			while(gay.size() && gay.size() < 3) gay.eb(gay.back());
            if(gay.empty()) break;

			
			if(gay[0].fi != gay[2].fi){
				if(gay[0].fi < gay[1].fi){
                    sus[gay[0].se] = smolest++;				
				}
				
				if(gay[1].fi < gay[2].fi){
					sus[gay[2].se] = biggest--;					
				}
				
			} 
		}

        // cout << gay[0].fi << ' ' << (int)gay[0].se << ' ' << (int)sus[0] << el;

	};
	
    auto SWAP = [&](my_struct *X, my_struct *Y, int l, int r){

        int block_l = l / S, block_r = r / S, st_l = block_l * S, st_r = block_r * S;

        if(l / S == r / S){
            for(int i=l; r>=i; i++) swap(X[block_l].fi[i - st_l], Y[block_l].fi[i - st_l]);
        }else{
            int lim_l = min(n, (l / S + 1) * S);
            for(int i=l; lim_l > i; i++) swap(X[block_l].fi[i - st_l], Y[block_l].fi[i - st_l]);

            for(int i=l/S + 1; block_r > i; i++) swap(X[i], Y[i]);

            for(int i=block_r*S; r>=i; i++) swap(X[block_r].fi[i - st_r], Y[block_r].fi[i - st_r]);
        }

    };
	
	while(q--){
		int l, r;
        cin >> l >> r;
		l--, r--;
		
		
		int block_l = l / S, lim_l = min(n, (block_l+1) * S), block_r = r / S;
		
		vect<char> ban(3), sus(3, 4);
        smolest = 0, biggest = 2;
		
		if(l / S == r / S){
			check_sus(l, r, sus);		
		}else{
			check_sus(l, lim_l-1, sus);

            // for(int i : sus) cout << i << el;nextl;
 
			
			vect<pair<char, char>> gay;
			for(int i=block_l + 1; block_r > i; i++){
                gay.clear();
                
				if(sus[0] == 4) gay.eb(order[i][A[i].se], 0);
				if(sus[1] == 4) gay.eb(order[i][B[i].se], 1);
				if(sus[2] == 4) gay.eb(order[i][C[i].se], 2);
				
				sort(bend(gay));
				while(gay.size() && gay.size() < 3) gay.eb(gay.back());
                if(gay.empty()) break;
				if(gay[0].fi == gay[2].fi) continue;
				
				if(gay[0].fi < gay[1].fi){
					sus[gay[0].se] = smolest++;
				}
				
				if(gay[1].fi < gay[2].fi){
					sus[gay[2].se] = biggest--;
				}
			}
			
			check_sus(block_r*S, r, sus);
		}

        // for(int i : sus) cout << i << el;


        if(count(bend(sus), 4)){
            vect<int> nigg(3);
            for(int i : sus) if(i < 4) nigg[i] = 1;
            for(int i=0; 3>i; i++) if(!nigg[i]){
                for(auto &f : sus) if(f == 4) f = i;
            }

        }

        // for(int i : sus) cout << i << el;

        if(sus[0] > sus[1]){
            SWAP(A, B, l, r);
            swap(sus[0], sus[1]);
        }
        if(sus[0] > sus[2]){
            SWAP(A, C, l, r);
            swap(sus[0], sus[2]);
        }
        if(sus[1] > sus[2]){
            SWAP(B, C, l, r);
            swap(sus[1], sus[2]);
        }

        build_block(block_l);
        build_block(block_r);
	}

    for(int i=0; MAX_BLOCK>i; i++) cout << A[i].fi;
    nextl;
    for(int i=0; MAX_BLOCK>i; i++) cout << B[i].fi;
    nextl;
    for(int i=0; MAX_BLOCK>i; i++) cout << C[i].fi;
    nextl;
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