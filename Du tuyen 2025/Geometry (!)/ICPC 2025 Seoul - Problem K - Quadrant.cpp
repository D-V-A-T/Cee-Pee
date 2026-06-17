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
#define dbl double
#define int long long

#define FILE "raydist"
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
ll pm(ll a,const int b=MOD){return (a%=b) < 0 ? a + b : a;}
ll sq(ll x){return x*x;}
ll __lcm(ll a, ll b, const ll lim=LLONG_MAX){
    if(a == -1 || b == -1)return -1;
    ll g = __gcd(a,b);
    if(b/g > lim/a)return -1;
    return (a/g)*b;
}

#define GT template<class T>
#define dbl long double
const dbl PI = acosl(-1), epsilon = 1e-15;
GT struct Ln;
GT struct Pt;
GT T cross(const Pt<T> &a, const Pt<T> &b){return a.x * b.y - b.x * a.y;}
GT T angle(const Pt<T> &a, const Pt<T> &b){return acosl((a*b) / (a.len() * b.len()));}
GT T triA(const Pt<T> &a, const Pt<T> &b, const Pt<T> &c){return abs(cross(b-a, c-a))*.5l;}
GT Pt<T> intersex(const Ln<T> &a, const Ln<T> &b){
    T nux = a.b*b.c - a.c*b.b, nuy = b.a*a.c - b.c*a.a;
    T de = a.a*b.b - a.b*b.a;
    return abs(de) <= epsilon ? Pt<T>(NAN, NAN) : Pt<T>(nux/de, nuy/de);
}
GT bool on_segment(const Pt<T> &p, const Pt<T> &a, const Pt<T> &b){
    if(abs(cross(a - p, b - p)) > epsilon) return false;
    return ((a-p)*(b-p))<=epsilon;
}
GT struct Pt{
    T x, y;

    Pt(T x=0, T y=0){
        this -> x = x;
        this -> y = y;
    }

    T sq(T x)const{return x*x;}
    long double len()const{return sqrtl(x*x + y*y);}
    long double dist_to(const Pt &o)const{return sqrtl(1.0l*sq(x - o.x) + 1.0l*sq(y - o.y));}
    long double dist_to(const Ln<T> &o)const{return triA(*this, o.s, o.r)*2.0l / o.s.dist_to(o.r);}
    Pt operator + (const Pt &o) const {return Pt(x+o.x, y+o.y);}
    Pt operator - (const Pt &o) const {return Pt(x-o.x, y-o.y);}
    Pt operator * (T k) const {return Pt(x*k, y*k);}
    T operator * (const Pt &o) const {return x*o.x + y*o.y;}
    Pt height(const Ln<T> &o) const{
        Ln<T> tmp = o;
        tmp.a = -o.b;
        tmp.b = o.a;
        tmp.c = - (tmp.a * x + tmp.b * y);
        return intersex(tmp, o);
    }
    void print(){cout<<x<<' '<<y;}
    void get(){cin>>x>>y;}
};
GT struct Ln{
    T a, b, c;
    Pt<T> s, r, dir;

    Ln(T a=0, T b=1, T c=0){
        this -> a = a;
        this -> b = b;
        this -> c = c;
        getpoints();
    }

    void getpoints(){
        if(b != 0){
            s = Pt<T>(1, (-c-a)/b);
            r = Pt<T>(0, -c/b);
            dir.x = 1;
            dir.y = a / b;
        }else{
            s = Pt<T>((-c-b)/a, 1);
            r = Pt<T>(-c/a, 0);
            dir.y = 1;
            dir.x = b / a;
        }
    }

    void print(){cout << a << ' ' << b << ' ' << c;}
    void get(){cin>>a>>b>>c;getpoints();}

    Ln<T> perp(){return Ln<T>(-b, a, c);}

    Ln(const Pt<T> &q, const Pt<T> &t){
        a = q.y - t.y;
        b = t.x - q.x;
        c = -(a*q.x + b*q.y);
        s = q;
        r = t;
    }
};

inline int cnt(dbl &l, dbl &r, vect<dbl> &v){
    if(l > r){

        return (v.size() - (lwb(bend(v), l)-v.begin()))
            + (upb(bend(v), r) - v.begin());
    }
    return upb(bend(v), r) - v.begin() - (lwb(bend(v), l) - v.begin()); 
}

void sol(){

    int n;
    cin >> n;

    Pt<dbl> a[n];
    for(auto &i : a) i.get();

    vect<int> dih(n+5);
    
    auto add = [&](int l, int r){
        if(min(l, r) < 0) return;
        if(l > r) return;
        // cerr << "+ " << l << ' ' << r << el;
        dih[l]++;
        dih[r+1]--;
    };

    auto deg = [&](dbl x){
        return x/PI*180;
    };

    for(int i=0; n>i; i++){
        vect<dbl> ang(n), sus;
        for(int j=0; n>j; j++){
                // cerr << (a[j]-a[i]).x << ' ' << (a[j]-a[i]).y << el;
            
            if(i == j) continue;
            dbl alpha = atan2l((a[j] - a[i]).y, (a[j] - a[i]).x);
            if(alpha < 0) alpha += 2*PI;    

            // if(i==3 && j==1)cout << i << ' ' << j << ' ' << deg(alpha) << el;

            ang[j] = alpha;
            sus.eb(ang[j]);
        }

        sort(bend(sus));

        // fill(bend(dih), 0);

        for(int j=0; n>j; j++){
            if(i == j) continue;


            dbl alpha = ang[j];
            dbl beta = alpha - PI;

            if(beta < 0) beta += 2*PI; 

            if(alpha > beta) swap(alpha, beta);


            int left = cnt(alpha, beta, sus)-1;

            dbl theta = beta - PI/2;
            if(theta < 0) theta += 2*PI;

            if(ang[j] == beta){
                // a[j] is under Ox
                int t = cnt(alpha, theta, sus);
                add(left-t, left-1);
            }else{
                // a[j] is above Ox
                int t = cnt(theta, beta, sus);
                add(left-t, left-1);
            }




            int right = n-2-left;
            theta = theta - PI; 
            if(theta < 0) theta += 2*PI;


            if(ang[j] == beta){
                int t = cnt(theta, alpha, sus);
                add(right-t, right-1);
            }else{


                int t = cnt(beta, theta, sus);
                add(right-t, right-1);
            }

        }
    }

    for(int i=0; n-2>i; i++){
        if(i) dih[i] += dih[i-1];
        cout << dih[i] << el;
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