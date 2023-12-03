#include <bits/stdc++.h>
//source: https://codeforces.com/blog/entry/121441
typedef long long ll;
using namespace std;
template<typename T,T comb(T,T)>
struct Fen2{
    T e;
    vector<T>sisu,kokku;
    vector<int>hypped;
    int n;
    Fen2(int n,T id):n(n),e(id){
        hypped.resize(n);
        sisu.resize(n);
        kokku.resize(n);
        hypped[1]=hypped[2]=1;
        for(int i=2;i+1<n;i++){
            if(hypped[i]==hypped[i-hypped[i]])hypped[i+1]=2*hypped[i]+1;
            else hypped[i+1]=1;
        }
    }
    Fen2(const vector<T>& sisu,T id):Fen2(sisu.size()+5,id){
        this->sisu.resize(sisu.size()+1);
        kokku.resize(sisu.size()+1);
        for(int i=0;i<sisu.size();i++)this->sisu[i+1]=sisu[i];
        for(int i=1;i<this->sisu.size();i++){
            auto el=this->sisu[i];
            kokku[i]=hypped[i]==1?el:comb(comb(kokku[i-1-hypped[i-1]],kokku[i-1]),el);
        }
    }
    T saa(int i,int j){//1 based [i,j]
       T vas=e;
       while(j-i+1>0){
            if(j-i+1>=hypped[j])vas=comb(kokku[j],vas),j-=hypped[j];
            else vas=comb(sisu[j],vas),j-=1;
       }
       return vas;
    }
    int cover(int i) {
      return hypped[i] == hypped[i-hypped[i]] ? i + 1 : i + hypped[i] + 1;
    }
    void uuenda(int i,T x){
        sisu[i]=x;
        if(hypped[i]==1)kokku[i]=x,i=cover(i);
        for(;i<this->sisu.size();i=cover(i)){
            kokku[i]=comb(kokku[i-1-hypped[i-1]],comb(kokku[i-1],sisu[i]));
        }
    }
};
typedef long long ll;
typedef pair<ll,ll>pii;
const int MOD=998244353;
pii comb(pii a,pii b){
    return {a.first*b.first%MOD,(a.second*b.first+b.second)%MOD};
}
ll eval(const pii &a,ll x){
    return (a.first*x+a.second)%MOD;
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,Q;
    cin>>N>>Q;
    vector<pii>A(N);
    for(int i=0;i<N;i++)cin>>A[i].first>>A[i].second;
    const pii P={1,0};
    Fen2<pii,comb> T(A,P);
    while(Q--){
        int op;
        cin>>op;
        if(op==1){
            int l,r;
            ll x;
            cin>>l>>r>>x;
            cout<<eval(T.saa(l+1,r),x)<<'\n';
        }else{
            int p,c,d;cin>>p>>c>>d;
            T.uuenda(p+1,{c,d});
        }
    }
    return 0;
}
