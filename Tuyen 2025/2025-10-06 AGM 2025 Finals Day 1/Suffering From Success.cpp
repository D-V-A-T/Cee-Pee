#include<bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define int unsigned
using namespace std;

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<pii> h(n);
    int idx = 0;
    string s;
    for(int i=0;n>i;i++){
        cin >> s;
        int hash1 = 0, pw = 1;
        pii p;
        for(char c : s){
            hash1 = (hash1 + (c-'.'+1) * pw) % (int)(1e9+7);
            pw = (pw * 97) % (int)(1e9+7);
        }
        p.fi = hash1;

        hash1 = 0;
        pw = 1;
        for(char c : s){
            hash1 = (hash1 + (c-'.'+1) * pw) % (int)(1e9+9);
            pw = (pw * 97) % (int)(1e9+9);
        }
        p.se = hash1;
        h[i] = p;
    }

    sort(h.begin(), h.end());
    h.resize(unique(h.begin(), h.end()) - h.begin());
    cout << (h.size() >= k + (n/100000) ? "YES" : "NO");
}