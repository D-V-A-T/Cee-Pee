// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#define int long long
#define vect vector
#define bend(v) v.begin(),v.end()
#define eb emplace_back
using namespace std;

int32_t main() {
 ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, M;
    cin >> n >> M;
    vect<int> a(n+1), b(n+1), h(n+1), dp;
    int ans=0, fumo=n;
    a[0]=b[0]=0;
    for(int i=1;n>=i;i++){
        cin >> a[i];
        if(a[i] > M && i==1){
            ans++;
            a[i]=M;
        }
        h[i] = a[i] - a[i-1] - M ;
        b[i] = -1*b[i-1] + h[i];
        b[i] *= -1; 
    }

    auto LNDS = [&](){
        dp.clear();
        for(int i=1;n>=i;i++){
            if(dp.empty()|| dp.back() <= b[i])dp.eb(b[i]);
            else if (b[i] >= b[1]){
                int p = upper_bound(bend(dp), b[i])-dp.begin();
                dp[p]=b[i];
            }
        }
        fumo = min(fumo, ans+n-(int)dp.size());
    };

    LNDS();
    ans = 1;
    a[1] = M;
    for(int i=1;n>=i;i++){
        h[i] = a[i] - a[i-1] - M ;
        b[i] = -1*b[i-1] + h[i];
        b[i] *= -1;
    }
    LNDS();
    cout << fumo;
}