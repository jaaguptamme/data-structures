//source:https://ei1333.github.io/library/structure/segment-tree/lazy-segment-tree.hpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,typename E,typename F,typename G,typename H>
struct LoikudePuu{
private:
    int n{},suurus{},korgus{};
    vector<T>sisu;
    vector<E>laisk;
    const F f;
    const G g;
    const H h;
    const T ti;
    const E ei;
    void uuenda(int i){
        sisu[i]=f(sisu[i*2],sisu[i*2+1]);
    }
    void KoikRakenda(int i,const E& x){
        sisu[i]=g(sisu[i],x);
        if(i<suurus)laisk[i]=h(laisk[i],x);
    }
    void lukka(int i){
        if(laisk[i]!=ei){
            KoikRakenda(i*2,laisk[i]);
            KoikRakenda(i*2+1,laisk[i]);
            laisk[i]=ei;
        }
    }
public:
    LoikudePuu()=default;
     explicit LoikudePuu(int n,const F f,const G g,const H h,const T& ti,const E &ei):n(n),f(f),g(g),h(h),ti(ti),ei(ei){
        suurus=1;
        korgus=0;
        while(suurus<n){
            suurus*=2;
            korgus++;
        }
        sisu.assign(2*suurus,ti);
        laisk.assign(2*suurus,ei);
    }
    explicit LoikudePuu(const vector< T > &v, const F f, const G g, const H h,
        const T &ti, const E &ei): LoikudePuu(v.size(),f,g,h,ti,ei){
        ehita(v);
    }
    void ehita(const vector<T>& v){
        for(int k=0;k<n;k++)sisu[k+suurus]=v[k];
        for(int k=suurus-1;k>0;k--)uuenda(k);
    }
    void sea(int k,const T& x){
        k+=suurus;
        for(int i=korgus;i>0;i--)lukka(k>>i);
        sisu[k]=x;
        for(int i=1;i<=korgus;i++)uuenda(k>>i);
    }
    T saa(int k){
        k+=suurus;
        for(int i=korgus;i>0;i--)lukka(k>>i);
        return sisu[k];
    }
    T operator[](int k){
        return saa(k);
    }
    T saa(int l,int r){//[l,r)
        if(l>=r)return ti;
        l+=suurus;
        r+=suurus;
        for(int i=korgus;i>0;i--){
            if(((l>>i)<<i)!=l)lukka(l>>i);
            if(((r>>i)<<i)!=r)lukka((r-1)>>i);
        }
        T L=ti,R=ti;
        for(;l<r;l>>=1,r>>=1){
            if(l&1)L=f(L,sisu[l++]);
            if(r&1)R=f(sisu[--r],R);
        }
        return f(L,R);
    }
    T saa(){
        return sisu[1];
    }
    void rakenda(int k,const E& e){
        k+=suurus;
        for(int i=korgus;i>0;i--)lukka(k>>i);
        sisu[k]=g(sisu[k],e);
        for(int i=1;i<=korgus;i++)uuenda(k>>i);
    }
    void rakenda(int l,int r,const E& e){
        if(l>=r)return;
        l+=suurus;
        r+=suurus;
        for(int i=korgus;i>0;i--){
            if(((l>>i)<<i)!=l)lukka(l>>i);
            if(((r>>i)<<i)!=r)lukka((r-1)>>i);
        }
        {
          int l2=l,r2=r;
          for(;l<r;l>>=1,r>>=1){
            if(l&1)KoikRakenda(l++,e);
            if(r&1)KoikRakenda(--r,e);
          }
          l=l2,r=r2;
        }
        for(int i=1;i<=korgus;i++){
            if(((l>>i)<<i)!=l)uuenda(l>>i);
            if(((r>>i)<<i)!=r)uuenda((r-1)>>i);
        }
    }
};
template< typename T, typename E, typename F, typename G, typename H >
LoikudePuu< T, E, F, G, H > saaLoikudePuu
    (int N, const F &f, const G &g, const H &h, const T &ti, const E &ei) {
  return LoikudePuu< T, E, F, G, H >{N, f, g, h, ti, ei};
}

template< typename T, typename E, typename F, typename G, typename H >
LoikudePuu< T, E, F, G, H > saaLoikudePuu
    (const vector< T > &v, const F &f, const G &g, const H &h, const T &ti, const E &ei) {
  return LoikudePuu< T, E, F, G, H>{v, f, g, h, ti, ei};
}
const ll MOD=998244353;
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    using pii=pair<ll,int>;
    using qii=pair<ll,ll>;
    auto f=[](const pii& a,const pii& b) -> pii {
        return {(a.first+b.first)%MOD,a.second+b.second};
    };
    auto g=[](const pii& a,const qii &b) -> pii {
        return {(a.first*b.first+a.second*b.second)%MOD,a.second};
    };
    auto h=[](const qii& a,const qii& b) -> qii {
        return {(a.first * b.first)%MOD,(a.second * b.first + b.second)%MOD};
    };
    int N,Q;
    cin>>N>>Q;
    auto puu=saaLoikudePuu(N,f,g,h,pii(0,0),qii(1,0));
    for(int i=0;i<N;i++){
        ll a;cin>>a;puu.sea(i,pii(a,1));
    }
    while(Q--){
        int t;cin>>t;
        if(t==0){
            int l,r;ll b,c;
            cin>>l>>r>>b>>c;
            puu.rakenda(l,r,qii(b,c));
        }else{
            int l,r;cin>>l>>r;
            cout<<puu.saa(l,r).first<<'\n';
        }
    }
    return 0;
}
