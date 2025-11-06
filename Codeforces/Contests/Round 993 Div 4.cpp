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
#include<bits/stdc++.h>
#define dbl long double
#define int long long
#define popcnt __builtin_popcount
#define ctz __builtin_ctz
using namespace std; 

const int INF=902337203695775807, N=2e5+69, MOD=1e9+7;    

void ffopen(const string& file){
    if(file.empty())return;
    freopen((file + ".inp").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}

int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
int __lcm(int a,int b){return a*b/__gcd(a,b);}

void A(){
    int n, ans=0;
    cin >> n;
    for(int i=1;690>=i;i++)
    for(int f=1;690>=f;f++)if(i == n-f)ans++;
    cout << ans << el;
}

void B(){
    string s;
    cin >> s;
    reverse(bend(s));
    for(char& c : s){
        if(c == 'p')c='q';
        else if(c=='q')c='p';
    }cout << s << el;
}

void C(){
    int n, a, b,c;
    cin >> n >> a >> b >> c;
    int r1=min(n, a), r2=min(n, b);
    if(r1 < n){
        int temp=r1;
        r1 = min(r1 + c, n);
        c -= r1 - temp;
    }if(r2 < n){
        int temp=r2;
        r2 = min(r2 + c, n);
        c -= r2 - temp;
    }cout << r1 + r2 << el;
}

void D(){
    int n;
    cin >> n;
    unordered_set<int> us;
    vect<int> a(n), seen(n+5);
    for(int i=1;n>=i;i++)us.insert(i);
    vect<int> fumo;
    for(int& i : a){
        cin >> i;
        if(us.find(i) != us.end())us.erase(i);
    }for(int i : us)fumo.eb(i);
    for(int i=0;n>i;i++){
        if(!seen[a[i]])cout << a[i] << ' ';
        else{
            cout << fumo.back() << ' ';
            fumo.pob();
        }seen[a[i]]=1;
    }nextl;
}
 
void E(){
    int l1, r1, l2, r2, k;
    cin >> k >> l1 >> r1 >> l2 >> r2;
    int sl=max(l1, l2), sr=min(r1, r2), ans=0;
    ans += max(sr - sl + 1, 0ll);
    int fumo=k;
    while(fumo <= r2){
        // count the number of x (l1 <= x <= r1) so that l2 <= x * fumo <= r2
        int lm = ceil((dbl)l2 / (dbl)fumo), rm = r2 / fumo;
        sl=max(lm, l1);
        sr=min(rm, r1);
        ans += max(sr - sl + 1, 0ll);
        fumo *= k;
    }cout << ans << el;
}
 

void funky(const vect<int>& v, vect<int>& vv, int n){
    vect<int> pfs(n+5), sfs(n+5);
    for(int i=1;n>=i;i++)pfs[i]=v[i]+pfs[i-1];
    for(int i=n;i>=1;i--)sfs[i]=v[i]+sfs[i+1];
    for(int i=1;n>=i;i++)vv[i] = pfs[i-1] + sfs[i+1];
}
 
void F(){
    int n,m,q;
    cin >> n >> m >> q;
    vect<int> a(n+5), b(m+5), aa(n+5), bb(m+5);
    umap<int, int> fumo, fimi;
    for(int i=1;n>=i;i++) cin >> a[i];
    for(int i=1;m>=i;i++) cin >> b[i];
    funky(a, aa, n);
    funky(b, bb, m);
    
    for(int i=1;n>=i;i++)fumo[aa[i]]=1;
    for(int i=1;m>=i;i++)fimi[bb[i]]=1;
    while(q--){
        int x, reimu=0;cin >> x;
        for(int i=1;i*i<=abs(x);i++){
            if(x%i == 0){
                if((fumo[i] && fimi[x/i]) || (fumo[x/i] && fimi[i])){
                    cout << "YES\n";
                    reimu=1;break;
                }i *= -1;
                if((fumo[i] && fimi[x/i]) || (fumo[x/i] && fimi[i])){
                    cout << "YES\n";
                    reimu=1;break;
                }i *= -1;
            }
        }if(!reimu)cout << "NO\n";
    }
}

vect<vect<int>> graph, rgraph;  
vect<int> visited, ver, dp;
int fumo=0;
 
void DDFS(int start){
    ver[start]=visited[start]=1;
    for(int i : graph[start]){
        if(!ver[i]){
            DDFS(i);
        }
    }
}
 
void DFS(int start, int time){
    visited[start]=time;
    for(int i : graph[start]){
        if(ver[i])return;
        if(visited[i] == time){
            if(!ver[i])DDFS(i);
            return;
        }else if(!visited[i])DFS(i, time);
    }
}

void DDDFS(int start, int step){
    visited[start]=1;
    fumo=max(fumo, step);
    for(int i : rgraph[start]){
        if(!visited[i] && !ver[i])
            DDDFS(i, step+1);
    }
}
 
void DDDFS2(int start){
    visited[start]=1;
    dp[start]=1;
    for(int i : rgraph[start]){
        if(!visited[i] && !ver[i]){
            DDDFS2(i);
            if(!ver[start]) dp[start] += dp[i];
            else dp[start] = max(dp[start], dp[i]+1);
        }
    }
}


void G1(){
    int n;
    cin >> n;
    graph.clear();
    ver.assign(n+1, 0);
    visited.assign(n+1, 0);
    rgraph.assign(n+1, {});
    graph.assign(n+1, {});
    fumo=0;
    for(int i=1;n>=i;i++){
        int u;cin >> u;
        graph[i].eb(u);
        rgraph[u].eb(i);
    }int time=1;
    for(int i=1;n>=i;i++){
        if(!visited[i] && !ver[i]){
            DFS(i, time);
            time++;
        }
    }visited.assign(n+1, 0);
    for(int i=1;n>=i;i++){
        if(ver[i])DDDFS(i, 1);
    }
    cout << fumo+1 << el;
}

void G2(){
    int n;
    cin >> n;
    graph.clear();
    ver.assign(n+1, 0);
    visited.assign(n+1, 0);
    dp.assign(n+1, 0);
    rgraph.assign(n+1, {});
    graph.assign(n+1, {});
    fumo=0;
    for(int i=1;n>=i;i++){
        int u;cin >> u;
        graph[i].eb(u);
        rgraph[u].eb(i);
    }int time=1;
    for(int i=1;n>=i;i++){
        if(!visited[i] && !ver[i]){
            DFS(i, time);
            time++;
        }
    }visited.assign(n+1, 0);
    for(int i=1;n>=i;i++){
        if(ver[i])DDDFS2(i);
    }
    cout << *max_element(bend(dp))+1 << el;
}

inline int get(int x1, int y1, int x2, int y2, vect<vect<int>>& pfs){
	return pfs[x2][y2] + pfs[x1-1][y1-1] - pfs[x2][y1-1] - pfs[x1-1][y2];
}

void H(){
    int n, q;
    cin >> n >> q;
    vect<vect<int>> mpfs(n+1, vect<int>(n+1)), rpfs(n+1, vect<int>(n+1)), 
                    a(n+1, vect<int>(n+1)), am(n+1, vect<int>(n+1)), ar(n+1, vect<int>(n+1)),
                    pfs(n+1, vect<int>(n+1));
    for(int i=1;n>=i;i++){
        for(int j=1;n>=j;j++){
            cin >> a[i][j];
            am[i][j] = a[i][j] * i;
            ar[i][j] = a[i][j] * j;
            pfs[i][j] = pfs[i-1][j] + pfs[i][j-1] - pfs[i-1][j-1] + a[i][j];
            rpfs[i][j] = rpfs[i-1][j] + rpfs[i][j-1] - rpfs[i-1][j-1] + ar[i][j];
            mpfs[i][j] = mpfs[i-1][j] + mpfs[i][j-1] - mpfs[i-1][j-1] + am[i][j];
        }
    }       
    while(q--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int fumo = get(x1, y1, x2, y2, rpfs) - get(x1, y1, x2, y2, pfs) * (y1-1);
        int fimi = get(x1, y1, x2, y2, mpfs) - get(x1, y1, x2, y2, pfs) * (x1);
        fimi *= y2-y1+1;
        cout <<  fimi+fumo << ' ';
    }nextl; 
}

void sol(){
    
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen("");
    int t=1;
    cin >> t;
    while(t--)sol();
}
/*                                                                              .+*
                                                                          ###.####+
                                                                    =####%%#-#####*.
                                                               -##%%%%%%%%#:-#####*:..
  .:.=####:+                                              +*###%%%%%%%%%%#::#%%%###:::
  ...######:####*                                      *#####%%%%%%%%%%%%#:-##%%###:::.
  ...######::#######=                               ###%%############%%%%%%#::####*...
 .:.+#%####+###############*+=                   ##%%%%%%%%%%%%%##########%%#:.####...
 .::###*.-##%%%%%%%%%%%%%%%%%#####*           +#%%%%%%%%%%%%%%%%%%%%#######:.##%###:.:.
 ..-###:####%%%%%%%%%%%%%%%%%%%%%%%%###-     ##%%%%%%%%%%%%%%%%%%%%%%%%#%##::######...
 :.*##.*#######%%%%%%%%%%####%%##########*-*%%#%%%%%%###%%%%%%%%%%%%%%%%%%#%#*.####..:
 ::#####+::############%%%%%%%%%%%%%%%%%%%%##%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#=::*####.::
...##%%#%#:#%%%#####%%%%%%%%%%%-+#%#:--%%%##=+=:-%%%%%#%%%%%%%%%%%%%%%%%%::##%%%##+:::
 ..-##%##:#%%%%%%%%%%%%%%+-=###%%%#######%#####+=+==-::#%%%%%%%%%%%%%%%%%#:+%%%%%#-...
 .:.##%#*:#%%%%%%%%%%*#%%#%%#%###########%#####*###**-=-##%%%%%%%%%%%%%%%%#-#%%%%#-:::
 . .#%%%##----+%%%%%#+#%%#%#%##############*########**##%:-=%%#+%%%%%%%##*=--%%%##:::
  ..-#%%%%%%%-#%%%%#%%%%################*#####**#########*=+#%%%# %%%%%=#%%%%%%%#=:::
   -:#%%%%%%#-#%#+###%#############*###################*#####-=*%#   %%#-%%%%%##*..:.
   -.=#%%%%%#-+%*#%##########################################*=#%%#+    +*%%%#%#::
   ..:#%%%##  -+###############################################@+-%%#       ##*:
    ::-      #+####################################%#####%#####*-*-%%#
            ###################*################%#%#%#############=#%%#-
           ::=##########################%######%%#%##%%#%%%#######*-+#%#=
           -=+##########################%%#########%#%%###%#######%=-#%%#*
          ##*%#*##################################%#%%#%%#########%+-+##%##
         ---+%###############################%####++*%%%%%%%#######=-:=*####
        .:=+#%#*############*+==#########%%#%#%%#==---=*#%%%%%%##### :--#%%##
       :.=*%%%############%%%#%#%%#######%%#%#%%#*###*####%###%#####  ==::#%##
      .:-=#%%%###########*+=--:--=+##%#%##%#%#%#=-----:--=*%##%#%##*   ==:%###*
      :-+#%%%%*########%*+=----:---=%##%%#%%#%%%=---::::--=*########    :-#%###
      -=#%%%%%*#######@@*+---------==%%%%%%%%#%+------:----=*%%#####     ---####
    :::*%%%%%#*######@@@#+------=---==+%%%%%%%%==--=------==*%%%#####   ----####+
   .:-%%%%%%%*######%@@%#+=%:.%######@+==#%%%%#+@-:-%####%+=#%%@@####-   .--:####
   :-###%%%%#%####%@@@@%*+=%#@%######%----==*%=-%@#%#####%=+*%%%@@%##%     ::+###-
      -=*####% +*#@@@@%%*+=@########%=----------+%#######%=+*%%%%#=#%#     :-:###
            #%  ==+%%%%%*+==%#######@------------%#####%%=+=%#**##-%%        :.
             #  %%%###%%++===%#####@=------------=%###%%====%%%%%#:#
                %%%@%%%%=+===--=#*-----:-----------=+==-===-%%%%%*
                *%%%#%%%=====--------------------------==-=%%%**#+
                +%% -+**=-====-----------###-----------==@@@#%#@#-
                #*  #%%#%%*-===----------------------=+@@@@%#%@@%*
                   #%@@%      -=-------------------:  %@+# -#@@%%#
                  #%%@@%#      -=+==---------==++=+++      #%%%%%%=
                 .%%%%%%#--=- ---===----=#-------===++-----%%%%##%#-:::.
            ..::::#%#####-----=-==-:::::::::::::-#+=%=--::-#######-:::.:
            ..:#::#######::::::=--=%%**#:..:-%%%%%%%=--::::######*#:::::
            :::#:::*#####--::::-=--=%%%-....=%%%%%%%#+-::::#####::%:::::
            :::::::::+##+----:::=*-*%%::::..-%%%%%%%%*=::::##+:::-+:::-:
            ..:#:::::::------:-++##%%:.::.:.:%%%%%%%%*--::::::::::::::-:
            ..:#:::::::---:::=+#%%%%+::.:::::+%%%%%%%%*---::::::=#:::--:
             ..#::::-----====+%%%%%%::.......-%%%%%%%%%%+--:::::#-:::-::
             .:::------=--==#%%%%%%%:::....:::%%%%%%%%%%%%+--::=+:::-::
              .:-=-----==+#%%%%%%%%%%%%%#=--=*%%%%%%%%%%%%%%+--::.:---:
             ..:=--#===+#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#-::==--:
             :::##+=+##%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#=:----
            .::+%%%+:#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%#=##.
            :::#%%%%#:%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#-#%%%%%#%%#=:
           .::::=##%%%%#--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%++#%#%%%##%%%%%#::
           :.::::.::*##%%%%%-#%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%##########+::::
            :  :-::-::.:#%%%%#:#%%%%%%%%%%%%%%%%%%%%-#%%##+......::::::::::
                %%%*:--..:#%%%%%%*##%%%%%%#%%%##::%%%%#-::.....:::.::::::
              %%%%%%%%%-..:=%%%%%%##=+%=:=*#%#%#%%#+::-+-::%%%%-
             %%%%%%%%@%%::::-=#%%%%%%%%%%%%%%%##:::.::@%%%%%%%%%:
            #%%%%%%%%%%%@:::.....+#%%%%%###+:.::: ::+%%%%@%%%@%%%
            %%%%%%%%%%%%%    ....:...:..:.::::..    %%%%@%%%%%%%%=
             %%%%%%%%%%%=     ::...  :.:..  .       %%%%%%%%%%%%%#
              %%%%%%%%%=                            #%%%%%%%%%%%%=
                  +*                                 %%%%%%%%%%%#
                                                      +%%%%%%%%
               
*/