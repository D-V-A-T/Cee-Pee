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
#define int long long
#define dbl long double
#define popcnt __builtin_popcount
#define ctz __builtin_ctz

const ll INF=1e18+7, N=2e5+69, MOD=1e9+7;    

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

string div2(const string& s, bool print = 0){
    string res;
    int n =s.size(), rem=0;
    for(int i=0;n>i;i++){
        res += (s[i] - '0' + rem*10)/2 + '0';
        rem = (s[i] - '0')%2;
    }
    if(print){
        while(res[0] == '0')res.erase(res.begin());
        if(res.empty())res = "0";
        cout << res << ' ' << res << el;
        return "";
    }else return res;
}

pair<string, string> quickans[1000], onediff[1000];

void brute(int n){
    auto dsum = [&](int n){
        int res=0;
        while(n){
            res += n%10;
            n/=10;
        }return res;
    };
    for(int i = 1; n/2 >= i; i++){
        if(dsum(i) == dsum(n-i)){
            string a = to_string(i), b=to_string(n-i), c;
            while(a.size() + c.size() < b.size())c+='0';
            quickans[n] = {c+a, b};
            break;
        }
    }for(int i = n/2; i>=1; i--){
        if(abs(dsum(i) - dsum(n-i)) == 1){
            string a = to_string(i), b=to_string(n-i), c;
            while(a.size() + c.size() < b.size())c+='0';
            onediff[n] = {c+a, b};
            return;
        }
    }
}

pair<string, string> funky(string s){
    auto dsum = [](const string& s){
        int res =0;
        for(char c : s)res += c - '0';
        return res;
    };
    int oc = 0, n=s.size();
    for(int i=s.size()-1;s[i]&1 && i>=0;i--)oc++;
    string a(n, '0'), b(n, '0');
    if(oc == 1){
        if(s[0]&1){
            a[0] = (s[0] - '0')/2 + '0';
            b[0] = a[0] + 1;
            b[n-1] = (s[n-1] - '0')/2 + '0';
            a[n-1] = b[n-1] + 1;
            string t = div2(s.substr(1, n-2));
            for(int i=1;n-1>i;i++)a[i]=b[i]=t[i-1];
        }else{
            bool check = 0;
            int p=0;
            b[n-1] = (s[n-1] - '0')/2 + '0';
            a[n-1] = b[n-1] + 1;
            for(int i=0;n-1>i;i++){
                if(s[i]&1){
                    a[i] = (s[i] - '0')/2 + '0';
                    b[i] = a[i] + 1;
                    check = 1;
                    p=i;break;
                }
            }if(check){
                string r1 = div2(s.substr(0, p)), r2=div2(s.substr(p+1, (n-2 - (p+1) + 1)));
                for(int i=0;p>i;i++)a[i]=b[i]=r1[i];
                for(int i=p+1;n-1>i;i++)a[i]=b[i]=r2[i - (p+1)];
            }
        }
    }
    if(dsum(a) != dsum(b)){
        //cout << "okay!";
        int len = min(3ll, n-1);
        pair<string, string> pa = onediff[stoi(s.substr(0, len))];
        
        if(pa.fi.empty()){
			        if(s.size()<=3)return quickans[stoi(s)];
        string t = div2(s.substr(0, s.size()-3));
        
        for(int i=0;s.size()-3>i;i++)a[i]=b[i]=t[i];
        int x=(s[n-3]-'0')*100 + (s[n-2]-'0')*10 + (s[n-1]-'0');
        string A = quickans[x].fi, B = quickans[x].se;
        while(A.size()<3)A = "0" + A;
        while(B.size()<3)B = "0" + B;
        for(int i=0;3>i;i++){
            a[n-3+i]=A[i];
            b[n-3+i]=B[i];
        }return {a,b};
		}
        while(pa.fi.size() < len)pa.fi = "0" + pa.fi;
        while(pa.se.size() < len)pa.se = "0" + pa.se;
        a = pa.fi, b = pa.se;
        if(n-1 > 3){
            a += div2(s.substr(len, n-1 - len));
            b += div2(s.substr(len, n-1 - len));
        }if(dsum(a) > dsum(b)){
            a += (s.back()-'0')/2 + '0';
            b += a.back() + 1;
        }else{
            b += (s.back()-'0')/2 + '0';
            a += b.back() + 1;
        }
    }
    return {a,b};
};

void print(string s){
    while(s[0] == '0')s.erase(s.begin());
    if(s.empty())s = "0";
    cout << s << ' ';
}

void sol(){
    auto dsum = [](const string& s){
        int res =0;
        for(char c : s)res += c - '0';
        return res;
    };
    string s;
    cin >> s;
    int n = s.size();
    if(s.size() <= 3){
        int x= stoi(s);
        if(quickans[x].fi.empty())cout << "-1\n";
        else {
            print(quickans[x].fi);
            print(quickans[x].se);
            cout << el;
        }
    }
    else if(s.back()%2 == 0)div2(s, 1);
    else{
        int oc = 0, nonnine=0;
        for(int i=s.size()-1;s[i]&1 && i>=0;i--){
            oc++;
            nonnine += s[i] != '9';
        }
        vect<int> a(n), b(n);
        
        auto func = [&](){
            if(oc&1){
                bool bl = 0;
        
                for(int i=n-1;i>=0;i--){
                    if((s[i] != '9' || i==2) && !bl && i-2>=0){
                        int x=(s[i-2]-'0')*100 + (s[i-1]-'0')*10 + (s[i]-'0');
                        string A = quickans[x].fi, B = quickans[x].se;
                        if(A.empty())continue;
                        while(A.size()<3)A = "0" + A;
                        while(B.size()<3)B = "0" + B;
                        for(int j=0;3>j;j++){
                            a[i-2+j]=A[j]-'0';
                            b[i-2+j]=B[j]-'0';
                        }bl=1;
                        i-=2;
                    }
                    else if((i+bl)&1){
                        a[i] = (s[i] - '0')/2;
                        b[i] = a[i] + 1;
                    }else {
                        b[i] = (s[i] - '0')/2;
                        a[i] = b[i] + 1;
                    }
                }if(!bl){cout << "-1\n";return;}
                else{
                    pair<string, string> ans;
                    for(int i=0;n>i;i++){
                        ans.fi += a[i]+'0';
                        ans.se += b[i]+'0';
                    }
                    if(dsum(ans.fi) != dsum(ans.se)){
                    cout << "-1\n";return;
                    }
                    print(ans.fi);print(ans.se);cout << el;
                }
            }else{
                int pp = n-oc-1;
                for(int i=s.size()-1;i>pp;i--){
                    if(i&1){
                        a[i] = (s[i] - '0')/2;
                        b[i] = a[i] + 1;
                    }else {
                        b[i] = (s[i] - '0')/2;
                        a[i] = b[i] + 1;
                    }
                }
                string t = div2(s.substr(0, pp+1));
                for(int i=0;pp>=i;i++)a[i]=b[i]=t[i] - '0';
                pair<string, string> ans;
                for(int i=0;n>i;i++){
                    ans.fi += a[i]+'0';
                    ans.se += b[i]+'0';
                }if(dsum(ans.fi) != dsum(ans.se)){
                    cout << "-1\n";return;
                }
                print(ans.fi);print(ans.se);cout << el;
            }
    };
    
    if(oc == 1){
        pair<string, string> ans = funky(s);
        if(dsum(ans.fi) != dsum(ans.se)){
            cout << "-1\n";return;
        }
        print(ans.fi);print(ans.se);cout << el;
    }else{
        if(oc == n){
            func();
        }
        else if(oc&1){
            bool bl = 0;
            int pp = n-oc-1;
            for(int i=n-1;i>pp;i--){
                if((s[i] != '9' || i-2==pp+1) && !bl && i-2>pp){
                    int x=(s[i-2]-'0')*100 + (s[i-1]-'0')*10 + (s[i]-'0');
                    string A = quickans[x].fi, B = quickans[x].se;
                    if(A.empty())continue;
                    while(A.size()<3)A = "0" + A;
                    while(B.size()<3)B = "0" + B;
                    for(int j=0;3>j;j++){
                        a[i-2+j]=A[j]-'0';
                        b[i-2+j]=B[j]-'0';
                    }bl=1;
                    i-=2;
                }
                else if((i+bl)&1){
                    a[i] = (s[i] - '0')/2;
                    b[i] = a[i] + 1;
                }else {
                    b[i] = (s[i] - '0')/2;
                    a[i] = b[i] + 1;
                }
            }
            if(!bl){
                string t=s;
                int pp = n-oc-1;
                for(int i=s.size()-1;i>pp+1;i--){
                    if(i&1){
                            a[i] = (s[i] - '0')/2;
                            b[i] = a[i] + 1;
                        }else {
                            b[i] = (s[i] - '0')/2;
                            a[i] = b[i] + 1;
                        }t.pob();
                    } pair<string, string> ans = funky(t);
                    if(ans.fi.empty()){
                        cout << "-1\n";return;
                    }
                    for(int i=pp+2;n>i;i++){
                        ans.fi += a[i]+'0';
                        ans.se += b[i]+'0';
                    }if(dsum(ans.fi) != dsum(ans.se)){
                        cout << "-1\n";return;
                    }
                    print(ans.fi);print(ans.se);cout << el;
                    return;}
                else{
                    pair<string, string> ans ;
                    ans.fi = ans.se = div2(s.substr(0, n-oc)), div2(s.substr(0, n-oc));
                    for(int i=pp+1;n>i;i++){
                        ans.fi += a[i]+'0';
                        ans.se += b[i]+'0';
                    }
                    if(dsum(ans.fi) != dsum(ans.se)){
                        string t=s;
                        int pp = n-oc-1;
                        for(int i=s.size()-1;i>pp+1;i--){
                            if(i&1){
                                a[i] = (s[i] - '0')/2;
                                b[i] = a[i] + 1;
                            }else {
                                b[i] = (s[i] - '0')/2;
                                a[i] = b[i] + 1;
                            }t.pob();
                        } pair<string, string> ans = funky(t);
                        if(ans.fi.empty()){
                            cout << "-1\n";return;
                        }
                        for(int i=pp+2;n>i;i++){
                            ans.fi += a[i]+'0';
                            ans.se += b[i]+'0';
                        }if(dsum(ans.fi) != dsum(ans.se)){
                            cout << "-1\n";return;
                        }
                        print(ans.fi);print(ans.se);
                        cout << el;return;
                    }
                    print(ans.fi);print(ans.se);cout << el;
                }            
            }else{
                int pp = n-oc-1;
                for(int i=s.size()-1;i>pp;i--){
                    if(i&1){
                        a[i] = (s[i] - '0')/2;
                        b[i] = a[i] + 1;
                    }else {
                        b[i] = (s[i] - '0')/2;
                        a[i] = b[i] + 1;
                    }
                }
                string t = div2(s.substr(0, pp+1));
                for(int i=0;pp>=i;i++)a[i]=b[i]=t[i] - '0';
                pair<string, string> ans;
                for(int i=0;n>i;i++){
                    ans.fi += a[i]+'0';
                    ans.se += b[i]+'0';
                }if(dsum(ans.fi) != dsum(ans.se)){
                    cout << "-1\n";return;
                }
                print(ans.fi);print(ans.se);cout << el;
            }
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen("");
    for(int i=1;1000>i;i++)brute(i);
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