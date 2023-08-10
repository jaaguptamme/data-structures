#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
class CHT{
     struct Joon{
        ll m,b;
        Joon(){}
        Joon(ll m,ll b):m(m),b(b){}
        ll operator()(ll x)const{return m*x+b;}
        long double IN(Joon& a){
            return  -((long double) (1.0)*(b-a.b))/(m-a.m);
        }
    };
    int pos;
    vector<Joon>ar;
    public:
    CHT(int n){//n kokku jooni maksimaalselt
        pos=0;
        ar.resize(n);
    }
    ll get(ll x){
        if(pos==1)return ar[pos-1](x);
        if(ar[0](x)>=ar[1](x))return ar[0](x);
        if(ar[pos-1](x)>=ar[pos-2](x))return ar[pos-1](x);
        int l=0,r=pos-2,ans=-1;
        while(l<=r){
            int m=(l+r)/2;
            //cout<<ar[m].eval(x)<<' '<<ar[m+1].eval(x)<<'\n';
            if(ar[m](x)>=ar[m+1](x)){
                r=m-1;
                ans=m;
            }else l=m+1;
        }
        return ar[ans](x);
    }
    void lisaViimane(ll m,ll b){//m kasvavas järjekorras
        Joon cur(m,b);
        while(pos>1&&ar[pos-2].IN(cur)>=ar[pos-1].IN(cur))pos--;
        ar[pos++]=cur;
    }
};
