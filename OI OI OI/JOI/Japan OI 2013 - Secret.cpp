#include "secret.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 2000;
int n;

int dt[N][1000], mask[N];

int op(int a, int b) { 
    return Secret(a,b); 
}

void dnc(int l, int r, int dep, int *a){
    if(l == r){
        dt[l][999] = a[l];
        return;
    }

    int mid = (l+r)/2;

    dt[mid][dep] = a[mid];
    for(int i = mid-1; i >= l; i--)
        dt[i][dep] = op(a[i], dt[i+1][dep]);

    dt[mid+1][dep] = a[mid+1];
    for(int i = mid+2; i <= r; i++)
        dt[i][dep] = op(dt[i-1][dep], a[i]);

    for(int i = mid+1; i <= r; i++)
        mask[i] ^= (1 << dep);

    dnc(l, mid, dep+1, a);
    dnc(mid+1, r, dep+1, a);
}

int Query(int l, int r){
    if(l == r) return dt[l][999];
    int d = __builtin_ctz(mask[l] ^ mask[r]);
    return op(dt[l][d], dt[r][d]);
}

void Init(int sz, int a[]){
    n = sz;
    dnc(0, n-1, 0, a);
}