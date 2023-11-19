#include <bits/stdc++.h>
//https://cp-algorithms.com/linear_algebra/determinant-gauss.html
typedef long long ll;
using namespace std;
const ll MOD=998244353;
ll pow(ll a,ll b){
    ll res=1;
    while(b){
        if(b%2)res=(res*a)%MOD;
        a=(a*a)%MOD;
        b/=2;
    }
    return res;
}
ll det(vector<vector<ll>>&a){
    int n=a.size(),j;
    int rev=0;
    ll res=1;
    for(int i=0;i<n;i++){
        for(j=i;j<n;j++){
            if(a[j][i])break;
        }
        if(j>=n)return 0;
        if(i!=j){
            swap(a[j],a[i]);
            rev^=1;
        }
        res=(res*a[i][i])%MOD;
        ll k=pow(a[i][i],MOD-2);
        //cout<<"EL"<<a[i][i]<<' '<<k<<endl;
        for(j=i;j<n;j++)a[i][j]=(a[i][j]*k)%MOD;
        for(j=i+1;j<n;j++){
            a[j][i]=MOD-a[j][i];
            for(int k=i+1;k<n;k++)a[j][k]=(a[j][k]+a[j][i]*a[i][k])%MOD;
            a[j][i]=0;
        }
    }
    if(rev)return (MOD-res)%MOD;
    return res;
}
