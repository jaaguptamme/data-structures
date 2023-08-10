#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct F{
    vector<ll>dp;
    int n;
    F(int n){
        this->n=n+1;
        dp.resize(n+1);
    }
    void add(ll pos,ll vl){
        while(pos<n){
            dp[pos]+=vl;
            pos+=pos&(-pos);
        }
    }
    ll get(ll pos){
        ll res=0;
        while(pos>0){
            res+=dp[pos];
            pos-=pos&(-pos);
        }
        return res;
    }
    ll get(ll l,ll r){
        return get(r)-get(l-1);
    }
};
