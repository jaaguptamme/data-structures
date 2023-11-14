#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll MOD=998244353,N=205;
typedef array<array<ll,N>,N> mat;
struct MatrixPower{
    static mat mul(mat &a,mat &b){
        mat c;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++)c[i][j]=0;
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                for(int k=0;k<N;k++)c[i][j]=(c[i][j]+a[i][k]*b[k][j])%MOD;
            }
        }
        return c;
    }
    static mat pow(mat& a,ll n){
        mat res;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++)res[i][j]=(i==j);
        }
        while(n){
            if(n%2)res=mul(res,a);
            a=mul(a,a);
            n/=2;
        }
        return res;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    mat base;
    int n;ll k;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)cin>>base[i][j];
    }
    mat res=MatrixPower::pow(base,k);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)cout<<res[i][j]<<' ';
        cout<<'\n';
    }
    return 0;
}
