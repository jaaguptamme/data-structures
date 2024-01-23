#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll MOD=998244353;
typedef pair<ll,ll> pii;
pii comb(pii a,pii b){
    return {a.first*b.first%MOD,(a.second*b.first+b.second)%MOD};
}
pii pow(pii a,int mitu){
    pii vas={1,0};
    while(mitu){
        if(mitu%2)vas=comb(vas,a);
        a=comb(a,a);
        mitu/=2;
    }
    return vas;
}
ll eval(pii &a,ll x){
    return (a.first*x+a.second)%MOD;
}
template<typename T,T comb(T,T), T aste(T,int)>
class ST{
    int n;
    vector<pii>dp,lazy;
    vector<bool>blazy;
public:
    ST(vector<pii>&A):n(A.size()){
        dp.resize(4*n);
        lazy.resize(8*n);
        blazy.resize(8*n,false);
        ehita(1,0,n-1,A);
    }
    void ehita(int i,int l,int r,vector<pii>&A){
        if(l==r){
            dp[i]=A[l];
            return;
        }
        int m=(l+r)/2;
        ehita(i*2,l,m,A);ehita(i*2+1,m+1,r,A);
        dp[i]=comb(dp[i*2],dp[i*2+1]);
    }
    void alla(int i,int l,int r){
        if(blazy[i]){
            blazy[i*2]=true;
            blazy[i*2+1]=true;
            lazy[i*2]=lazy[i*2+1]=lazy[i];
            dp[i]=aste(lazy[i],(r-l+1));
            blazy[i]=false;
        }
    }
    void uuenda(int i,int l,int r,int st,int en,pii& F){
        alla(i,l,r);
        if(st<=l&&r<=en){
            blazy[i]=true;
            lazy[i]=F;
            alla(i,l,r);
            return;
        }
        if(st>r||l>en)return;
        int m=(l+r)/2;
        uuenda(i*2,l,m,st,en,F);
        uuenda(i*2+1,m+1,r,st,en,F);
        dp[i]=comb(dp[i*2],dp[i*2+1]);
    }
    pii kombineeri(int i,int l,int r,int st,int en){
        alla(i,l,r);
        if(st<=l&&r<=en)return dp[i];
        int m=(l+r)/2;
        if(en<=m)return kombineeri(i*2,l,m,st,en);
        else if(st>m)return kombineeri(i*2+1,m+1,r,st,en);
        return comb(kombineeri(i*2,l,m,st,en),kombineeri(i*2+1,m+1,r,st,en));
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,Q;
    cin>>N>>Q;
    vector<pii>A(N);
    for(auto &[x,y]:A)cin>>x>>y;
    ST<pii,comb,pow> T(A);
    while(Q--){
        int op;cin>>op;
        if(op==0){
            int l,r,b,c;
            cin>>l>>r>>b>>c;
            pii P={b,c};
            T.uuenda(1,0,N-1,l,r-1,P);

        }else{
            int l,r,x;cin>>l>>r>>x;
            auto res=T.kombineeri(1,0,N-1,l,r-1);
            cout<<eval(res,x)<<'\n';
        }
    }
    return 0;
}
