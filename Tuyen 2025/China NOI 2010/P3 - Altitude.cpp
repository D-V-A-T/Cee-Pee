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
#define FILE "skibiditoilet"
 
const ll INF=902337203695775807, N=505*505, MOD=1e9+7;    
 
void IO(){
    if(fopen("in.txt", "r")){
        freopen("in.txt", "r", stdin);
    }else if(fopen(FILE".inp", "r")){
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

int n, C[4][505][505];
// [0] : E, [1] : S, [2] : W, E[3] : N

struct cbd{
    int x, y, d;
    bool operator < (const cbd& o) const{
        return d > o.d;
    }
};

int dickcha(){
    prq<cbd> pq;
    int dist[505][505];
    memset(dist, 5, sizeof dist);
    for(int i=1;n>=i;i++){
        pq.push({1, i, C[0][1][i]}), dist[1][i] = C[0][1][i];
        pq.push({i, n, C[1][i][n+1]}), dist[i][n] = C[1][i][n+1];
    }

    int fumo = INF;
    while(pq.size()){
        auto [x, y, d] = pq.top();
        pq.pop();

        if(dist[x][y] < d) continue;
        
        if(x == n){ // node o hang cuoi
            fumo = min(fumo, d + C[0][x+1][y]);
        }
        if(y == 1){ // node o hang ben trai
            fumo = min(fumo, d + C[1][x][y]);
        }

        int nx, ny;

        // di xuong
        nx = x+1, ny = y;
        if(nx <= n){
            if(dist[nx][ny] > d + C[0][x+1][y]) {
                dist[nx][ny] = d + C[0][x+1][y];
                pq.push({nx, ny, dist[nx][ny]});
            }
        }

        // sang phai
        nx = x, ny = y+1;
        if(ny <= n){ 
            if(dist[nx][ny] > d + C[3][x+1][y+1]){
                dist[nx][ny] = d + C[3][x+1][y+1];
                pq.push({nx, ny, dist[nx][ny]});
            }
        }

        // sang trai
        nx = x, ny = y-1;
        if(ny >= 1){
            if(dist[nx][ny] > d + C[1][x][y]){
                dist[nx][ny] = d + C[1][x][y];
                pq.push({nx, ny, dist[nx][ny]});
            }
        }

        // di len
        nx = x-1, ny = y;
        if(nx >= 1){
            if(dist[nx][ny] > d + C[2][x][y+1]){
                dist[nx][ny] = d + C[2][x][y+1];
                pq.push({nx, ny, dist[nx][ny]});
            }
        }        

    }
    return fumo;
}

void sol(){
    cin >> n;

    for(int i=1;n+1>=i;i++){
        for(int j=1;n>=j;j++){
            int w;cin >> w;
            C[0][i][j] = w;
        }
    }

    for(int i=1;n>=i;i++){
        for(int j=1;n+1>=j;j++){
            int w;cin >> w;
            C[1][i][j] = w;
        }
    }

    for(int i=1;n+1>=i;i++){
        for(int j=2;n+1>=j;j++){
            int w;
            cin >> w;
            C[2][i][j] = w;
        }
    }

    for(int i=2;n+1>=i;i++){
        for(int j=1;n+1>=j;j++){
            int w;cin >> w;
            C[3][i][j] = w;
        }
    }

    cout << dickcha();
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    IO();
    int t=1;
    //cin >> t;
    while(t--)sol();
}