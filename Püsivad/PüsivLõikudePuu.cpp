//source: https://neterukun1993.github.io/Library/DataStructure/SegmentTree/PersistentSegmentTree.py
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,T op(T,T)>
struct PusivLoikudePuu{
    struct Tipp{
        Tipp *vasak,*parem;
        T vaartus;
        Tipp(Tipp* vasak,Tipp* parem,const T& vaartus):vasak(vasak),parem(parem),vaartus(vaartus){}
    };
    int n,log,suurus;
    Tipp* juur;
    PusivLoikudePuu(int n,Tipp* juur=nullptr):n(n),juur(juur){
        log=bitLen(n-1);
        suurus=1<<log;
    }
    int bitLen(int n){return 32-__builtin_clz(n);}
    void ehita(const vector<T>& ar){
        vector<Tipp*>massiiv(suurus);
        for(int i=0;i<suurus;i++)massiiv[i]=new Tipp(nullptr,nullptr,(i<n)?ar[i]:T());
        for(int h=0;h<log;h++){
            vector<Tipp*>ajutine;
            for(int i=0;i<(1<<(log-h-1));i++)
                ajutine.push_back(uhenda(massiiv[i*2],massiiv[i*2+1]));
            swap(ajutine,massiiv);
        }
        juur=massiiv[0];
    }
    T saa(int i){
        Tipp* tp=juur;
        for(int h=0;h<log;h++){
            if((i>>(log-h-1))&1)tp=tp->parem;
            else tp=tp->vasak;
        }
        return tp->vaartus;
    }
    PusivLoikudePuu uuenda(int i,const T& vaartus){
        Tipp* tp=juur;
        vector<Tipp*>mag;
        mag.push_back(tp);
         for(int h=0;h<log;h++){
            if((i>>(log-h-1))&1)tp=tp->parem;
            else tp=tp->vasak;
            mag.push_back(tp);
        }
        tp=new Tipp(nullptr,nullptr,vaartus);
        for(int i=mag.size()-1;i>0;i--){
            Tipp *c=mag[i],*p=mag[i-1];
            if(p->vasak==c)tp=uhenda(tp,p->parem);
            else tp=uhenda(p->vasak,tp);
        }
        return PusivLoikudePuu(suurus,tp);
    }
    Tipp* uhenda(Tipp* vas,Tipp* par){
        return new Tipp(vas,par,op(vas->vaartus,par->vaartus));
    }
    T saa(int l,int r){
        return saa(l,r,0,n-1,juur);
    }
    T saa(int a,int b,int l,int r,Tipp* tp){
        if(a<=l&&r<=b)return tp->vaartus;
        int m=(l+r)/2;
        if(m>=b)return saa(a,b,l,m,tp->vasak);
        else if(m<a)return saa(a,b,m+1,r,tp->parem);
        return op(saa(a,b,l,m,tp->vasak),saa(a,b,m+1,r,tp->parem));
    }
    T saa_koik(){
        return juur->vaartus;
    }
};
