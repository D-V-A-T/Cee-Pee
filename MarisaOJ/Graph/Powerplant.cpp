#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
#include<bits/stdc++.h>
#define dbl long double
#define int long long
using namespace std; 

const int INF=2e14, N=1e5+69;
int MOD=1e9+7;    

void ffopen(const string& file){
    if(file.empty())return;
    freopen((file + ".inp").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}

int posmod(int a,int b){
    return ((a%b)+b)%b;
}

int __lcm(int a,int b){
    return a*b/__gcd(a,b);
}

int n,m,k,p;

struct reimu {
    int u, rad;
};

struct Graph {
    vect<vect<int>> graph;
    vect<int> dist;
    umap<int, bool> gay;
    queue<reimu> pq;
    Graph(){
        dist.rs(n+1,INF);
        graph.rs(n+1);
        for(int i=0;m>i;i++){
            int u,v;
            cin >> u >> v;
            graph[u].eb(v);
            graph[v].eb(u);
        }for(int i=0;k>i;i++){
            int v,r;
            cin >> v >> r;
            pq.push({v, r});
            dist[v]=r;
            gay[v]=1;
        }BFS();
        cout << gay.size();
    }void BFS(){
        while(pq.size()){
            int start=pq.front().u, r=pq.front().rad;
            pq.pop();
            if(r < dist[start] || !r)continue;
            for(int v : graph[start]){
                if(!gay[v] || r-1 > dist[v]){
                    gay[v]=1;
                    dist[v]=r-1;
                    pq.push({v, r-1});
                }
            }
        }
    }
};

void sol() {
    cin >> n >> m >> k;
    Graph g;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//  freopen("","r",stdin);
//  freopen("","w",stdout);
    int t=1;
    //cin >> t;
    while(t--)sol();
}