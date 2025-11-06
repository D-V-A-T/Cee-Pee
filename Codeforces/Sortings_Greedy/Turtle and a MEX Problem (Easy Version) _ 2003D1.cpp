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
#define dbl long double
#define int long long
#define popcnt __builtin_popcount
#define ctz __builtin_ctz

const int INF=902337203695775807, N=2e5+69, MOD=1e9+7;    

void ffopen(const string& file){
    if(file.empty())return;
    freopen((file + ".inp").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}

int pm(int a,const int b=1e9+7){return ((a%b)+b)%b;}
int sq(int x){return x*x;}
int __lcm(int a,int b){return a*b/__gcd(a,b);}

void sol(){
    int n,m;
    cin >> n >> m;
    vect<vect<int>> a(n);
    int idk=0;
    for(int i=0;n>i;i++){
        int len;cin >> len;
        a[i].rs(len);
        for(int& j : a[i])cin >> j;
        sort(bend(a[i]));
        auto it=unique(bend(a[i]));
        a[i].rs(it-a[i].begin());
        int MEX1=0, MEX2=0, fm=0;
        a[i].eb(INF);
        for(int j : a[i]){
            if(!fm && j == MEX1){
                MEX1++;
            }else if(!fm){
                fm=1;
                MEX2 = MEX1+1;
            }            
            if(fm && j == MEX2)MEX2++;
            else if(fm)break;
        }idk=max({idk, MEX1, MEX2});
    }
    if(m <= idk)
        cout << (m+1)*idk << el; 
    else
        cout << (idk+1+m)*(m-idk)/2 + idk*(idk+1) << el;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ffopen("");
    int t=1;
    cin >> t;
    while(t--)sol();
}