#include <bits/stdc++.h>
#define int long long
using namespace std;

struct gate{
    string op;int x;
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    gate a[n];
    for(gate& i : a)cin >> i.op >> i.x;
    
    int fumo = 0;
    for(int b=32;b>=0;b--){
        if(fumo + (1ll<<b) > m) continue;
        int num = 0;
        for(auto [op, x] : a){
            if(op[0] == 'O') num |= x;
            else if(op[0] == 'X') num ^= x;
            else num &= x;
        }
        
        if(num & (1ll<<b)) continue;
        
        num = 1ll<<b;
        for(auto [op, x] : a){
            if(op[0] == 'O') num |= x;
            else if(op[0] == 'X') num ^= x;
            else num &= x;
        }
        
        if(num & (1ll<<b)) fumo += 1ll<<b;
    }
    for(auto [op, x] : a){
        if(op[0] == 'O') fumo |= x;
        else if(op[0] == 'X') fumo ^= x;
        else fumo &= x;
    }
    cout << fumo;

}
