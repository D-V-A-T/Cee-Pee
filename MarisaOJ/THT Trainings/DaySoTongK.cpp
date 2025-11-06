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

const ll INF=902337203695775807, N=4e5+69, MOD=1e9+7;    

void ffopen(const string& file){
    if(file.empty())return;
    freopen((file + ".inp").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}

int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

int n, q;
int a[N], pfs[N];
set<int> zero;

struct node{
    int mr, ml, sum, ms, msi, ri, li;
    node(){mr=ml=sum=ms=0;}
    // mr : max/min from right
    // ml : max/min from left
    // sum: sum
    // ms : max/min subarray sum 
    // msi: end of ms
    // ri : end of mr
    // li : end of ml
};

struct Seggs{
    int tmn[N], tmx[N], lz[N];
    Seggs(){build();}
    void build(int l=0, int r=n-1, int id=1){
        if(l == r){
            tmx[id] = tmn[id] = pfs[l];
            return;
        }int mid = (l+r)/2;
        build(l, mid, id*2);
        build(mid+1, r, id*2+1);
        tmx[id] = max(tmx[id*2], tmx[id*2+1]);
        tmn[id] = min(tmn[id*2], tmn[id*2+1]);
    }
    void push(int l, int r, int id){
        tmx[id] += lz[id];
        tmn[id] += lz[id];
        if(l < r){
            lz[id*2] += lz[id];
            lz[id*2+1] += lz[id];
        }lz[id] = 0;
    }
    void upd(int v, int p, int l=0, int r=n-1, int id=1){
        push(l, r, id);
        if(r < p)return;
        if(l >= p){
            lz[id] += v;
            push(l, r, id);
            return;
        }int mid = (l+r)/2;
        upd(v, p, l, mid, id*2);
        upd(v, p, mid+1, r, id*2+1);
        tmx[id] = max(tmx[id*2], tmx[id*2+1]);
        tmn[id] = min(tmn[id*2], tmn[id*2+1]);
    }int get(int p, int l=0, int r=n-1, int id=1){
        push(l, r, id);
        if(r < p || l > p)return -1e9;
        if(l == r) return tmx[id];
        int mid = (l+r)/2;
        return max(get(p, l, mid, id*2),  get(p, mid+1, r, id*2+1));
    }
    void find(int& res, int x, int i, int j, int l=0, int r=n-1, int id=1){
        push(l, r, id);
        if(l > j || r < i || res != -1)return;
        if(l == r){
            if(tmx[id]==x)res = l+1;
            return;
        }int mid = (l+r)/2;
        push(l, mid, id*2);
        push(mid+1, r, id*2+1);
        if(tmx[id*2] >= x && x >= tmn[id*2]) 
            find(res, x, i, j, l, mid, id*2);
        if(res==-1 && tmx[id*2+1] >= x && x >= tmn[id*2+1])
            find(res, x, i, j, mid+1, r, id*2+1);
    }
};

struct MaxSeggs{
    node t[N];
    MaxSeggs(){build();}
    void merge(int l, int r, int id){
        t[id].sum = t[id*2].sum + t[id*2+1].sum;
        int S = t[id*2].mr + t[id*2+1].ml, M = max({S, t[id*2].ms, t[id*2+1].ms});
        if(S == M) t[id].msi = t[id*2+1].li;
        else if(t[id*2].ms == M)t[id].msi = t[id*2].msi;
        else t[id].msi = t[id*2+1].msi;
        t[id].ms = M;

        if(t[id*2].mr + t[id*2+1].sum > t[id*2+1].mr)
            t[id].ri = r;
        else t[id].ri = t[id*2+1].ri;
        t[id].mr = max(t[id*2].mr + t[id*2+1].sum, t[id*2+1].mr);

        if(t[id*2+1].ml + t[id*2].sum > t[id*2].ml)
            t[id].li = t[id*2+1].li;
        else t[id].li = t[id*2].li;
        t[id].ml = max(t[id*2+1].ml + t[id*2].sum, t[id*2].ml);
        
    }
    void build(int l=0, int r=n-1, int id=1){
        if(l == r){
            t[id].mr = t[id].ml = t[id].sum = t[id].ms = a[l];
            t[id].msi = t[id].li = t[id].ri = l;
            return;
        }
        int mid = (l+r)/2;
        build(l, mid, id*2);
        build(mid+1, r, id*2+1);
        merge(l, r, id);
    }

    void upd(int p, int l=0, int r=n-1, int id=1){
        if(l > p || r < p)return;
        if(l == r){
            t[id].mr = t[id].ml = t[id].sum = t[id].ms = a[l];
            return;
        }int mid = (l+r)/2;
        upd(p, l, mid, id*2);
        upd(p, mid+1, r, id*2+1);
        merge(l, r, id);
    }

    void func(vect<int>& ids, int i, int j, int l=0, int r=n-1, int id=1){
        if(l > j || r < i)return ;
        if(i <= l && r <= j){
            //cout << id << ' ' << l << ' ' << r << el;
            ids.eb(id);return;
        }int mid = (l+r)/2;
        func(ids, i, j, l, mid, id*2);
        func(ids, i, j, mid+1, r, id*2+1);
    }

    int get(int l, int r, int k){
        vect<int> ids;
        func(ids, l, r);
        int m = ids.size();
        for(int i=0;m>i;i++){
            int csum = 0, R = t[ids[i]].mr;
            if(t[ids[i]].ms >= k){return t[ids[i]].msi;}
            for(int j=i+1;m>j;j++){
                if(R + csum + t[ids[j]].ml >= k){
                    //cout << t[ids[j]].li << el;
                    return t[ids[j]].li;
                }
                csum += t[ids[j]].sum;
            }
        }return -1;
    }
};

struct MinSeggs{
    node t[N];
    MinSeggs(){build();}
    void merge(int l, int r, int id){
        t[id].sum = t[id*2].sum + t[id*2+1].sum;
        int S = t[id*2].mr + t[id*2+1].ml, M = min({S, t[id*2].ms, t[id*2+1].ms});
        if(S == M) t[id].msi = t[id*2+1].li;
        else if(t[id*2].ms == M)t[id].msi = t[id*2].msi;
        else t[id].msi = t[id*2+1].msi;
        t[id].ms = M;

        if(t[id*2].mr + t[id*2+1].sum < t[id*2+1].mr)
            t[id].ri = r;
        else t[id].ri = t[id*2+1].ri;
        t[id].mr = min(t[id*2].mr + t[id*2+1].sum, t[id*2+1].mr);

        if(t[id*2+1].ml + t[id*2].sum < t[id*2].ml)
            t[id].li = t[id*2+1].li;
        else t[id].li = t[id*2].li;
        t[id].ml = min(t[id*2+1].ml + t[id*2].sum, t[id*2].ml);
        
    }
    void build(int l=0, int r=n-1, int id=1){
        if(l == r){
            t[id].mr = t[id].ml = t[id].sum = t[id].ms = a[l];
            t[id].msi = t[id].li = t[id].ri = l;
            return;
        }
        int mid = (l+r)/2;
        build(l, mid, id*2);
        build(mid+1, r, id*2+1);
        merge(l, r, id);
    }

    void upd(int p, int l=0, int r=n-1, int id=1){
        if(l > p || r < p)return;
        if(l == r){
            t[id].mr = t[id].ml = t[id].sum = t[id].ms = a[l];
            return;
        }int mid = (l+r)/2;
        upd(p, l, mid, id*2);
        upd(p, mid+1, r, id*2+1);
        merge(l, r, id);
    }

    void func(vect<int>& ids, int i, int j, int l=0, int r=n-1, int id=1){
        if(l > j || r < i)return ;
        if(i <= l && r <= j){
            ids.eb(id);return;
        }int mid = (l+r)/2;
        func(ids, i, j, l, mid, id*2);
        func(ids, i, j, mid+1, r, id*2+1);
    }

    int get(int l, int r, int k){
        vect<int> ids;
        func(ids, l, r);
        int m = ids.size();
        for(int i=0;m>i;i++){
            int csum = 0, R = t[ids[i]].mr;
            if(t[ids[i]].ms <= k) return t[ids[i]].msi;
            for(int j=i+1;m>j;j++){
                if(R + csum + t[ids[j]].ml <= k)
                    return t[ids[j]].li;
                csum += t[ids[j]].sum;
            }
        }return -1;
    }
};

void sol(){
    cin >> n >> q;
    for(int i=0;n>i;i++){
        cin >> a[i];
        pfs[i] = (i ? pfs[i-1] : 0) + a[i];
        if(i && a[i]+a[i-1]==0)zero.insert(i-1);
    }
    
    Seggs sgt;
    MaxSeggs mxt;
    MinSeggs mnt;
    auto Answer = [&](int l, int r, int k){
        if(k==0){
            auto it = zero.lwb(l);
            if(it != zero.end()){
                //cout << "ok";
                if(*it +1 <= r){
                    cout << *it + 1 << ' ' << *it + 2 << el;
                    return;
                }
            }cout << "-1\n";
            return;
        }
        
        int y;
        if(k > 0)y = mxt.get(l, r, k);
        else y = mnt.get(l, r, k);

        if(y == -1){
            cout << "-1\n";return;
        }
        int P = sgt.get(y) - k, pf = (l ? sgt.get(l-1) : 0);
        //cout << y << el;
        int x = -1;
        sgt.find(x, P, l, y-1);
        if(P == pf)x=l;
        if(x == -1){
            cout << "-1\n";return;
        }cout << x+1 << ' ' << y+1 << el;
    };

    while(q--){
        int t;cin >> t;
        if(t==1){
            int i, v;cin >> i >> v;
            i--;
            if(a[i] == v)continue;
            sgt.upd(v-a[i], i);
            if(i>0){
                if(a[i-1] + a[i] == 0)zero.erase(i-1);
                else zero.insert(i-1);
            }
            if(i+1<n){
                if(a[i+1] + a[i] == 0)zero.erase(i);
                else zero.insert(i);
            }
            
            a[i] = v;
            mnt.upd(i);
            mxt.upd(i);
        }else{
            int l, r, k;cin >> l >> r >> k;
            Answer(l-1, r-1, k);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen("");
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