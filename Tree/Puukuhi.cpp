//source:https://ebi-fly13.github.io/Library/data_structure/ImplicitTreap.hpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename S,S (*op)(S,S), S(*e)(),typename F,S(*mapping)(F,S),
F(*composition)(F,F),F(*id)()>
class Puukuhi{
    struct Tipp{
        S vaartus,summa;
        F laisk;
        int taht,mitu;
        bool keeruta;
        Tipp *vasak,*parem;
        Tipp(S vaartus,int taht):vaartus(vaartus),summa(e()),laisk(id()),taht(taht),mitu(0),keeruta(0),vasak(0),parem(){}
    };
    using tipp=Tipp*;
    tipp juur;
    /*random_device rnd;
    mt19937 mt;
    uniform_int_distribution<> pri_rnd;*/
    int mitu(tipp t){
        return t?t->mitu:0;
    }
    void uuendaMitu(tipp t){
        if(t)t->mitu=1+mitu(t->vasak)+mitu(t->parem);
    }
    S summa(tipp t){
        return t?t->summa:e();
    }
    void uuendaSumma(tipp t){
        if(!t)return;
        t->summa=op(summa(t->vasak),t->vaartus);
        t->summa=op(t->summa,summa(t->parem));
    }
    void vaartusta(tipp t){
        if(!t)return;
        if(t->vasak){
            t->vasak->laisk=composition(t->laisk,t->vasak->laisk);
            t->vasak->summa=mapping(t->laisk,t->vasak->summa);
        }
        if(t->parem){
            t->parem->laisk=composition(t->laisk,t->parem->laisk);
            t->parem->summa=mapping(t->laisk,t->parem->summa);
        }
        t->vaartus=mapping(t->laisk,t->vaartus);
        t->laisk=id();
    }
    void alla(tipp t){
        if(t&&t->keeruta){
            t->keeruta=false;
            swap(t->vasak,t->parem);
            if(t->vasak)t->vasak->keeruta^=1;
            if(t->parem)t->parem->keeruta^=1;
        }
        vaartusta(t);
        uuenda(t);
    }
    void uuenda(tipp t){
        uuendaMitu(t);
        uuendaSumma(t);
    }
    tipp mesti(tipp l,tipp r){
        alla(l);
        alla(r);
        if(!l||!r)return !l?r:l;
        if(l->taht>r->taht){
            l->parem=mesti(l->parem,r);
            uuenda(l);
            return l;
        }else{
            r->vasak=mesti(l,r->vasak);
            uuenda(r);
            return r;
        }
    }
    pair<tipp,tipp> loika(tipp t,int arv){
        if(!t)return {nullptr,nullptr};
        alla(t);
        if(arv<mitu(t->vasak)+1){
            auto [l,r]=loika(t->vasak,arv);
            t->vasak=r;
            uuenda(t);
            return {l,t};
        }else{
            auto [l,r]=loika(t->parem,arv-mitu(t->vasak)-1);
            t->parem=l;
            uuenda(t);
            return {t,r};
        }
    }
public:
    Puukuhi():juur(nullptr){
        //mt=mt19937(rnd());
        //pri_rnd=uniform_int_distribution<>(0,1e9);
    }
    void lisa(int k,S v){
        auto [l,r]=loika(juur,k);
        auto t=mesti(l,new Tipp(v,rand()));
        juur=mesti(t,r);
    }
    void eemalda(int k){
        auto [l,r]=loika(juur,k+1);
        auto [nl,_]=loika(l,k);
        juur=mesti(nl,r);
    }
    void poora(int l,int r){
        auto [t1,t2]=loika(juur,l);
        auto [t3,t4]=loika(t2,r-l);
        t3->keeruta^=1;
        t1=mesti(t1,t3);
        juur=mesti(t1,t4);
    }
    void rakenda(int l,int r,F x){
        auto [t1,t2]=loika(juur,l);
        auto [t3,t4]=loika(t2,r-l);
        t3->laisk=composition(x,t3->laisk);
        t3->summa=mapping(x,t3->summa);
        t1=mesti(t1,t3);
        juur=mesti(t1,t4);
    }
    S summa(int l,int r){
        auto [t1,t2]=loika(juur,l);
        auto [t3,t4]=loika(t2,r-l);
        S vas=summa(t3);
        t1=mesti(t1,t3);
        juur=mesti(t1,t4);
        return vas;
    }
};
const ll MOD=998244353;
struct S{
    ll a;
    int mitu;
};
struct F{
    ll a,b;
};
S summa(S a, S b){
    return {(a.a+b.a)%MOD,a.mitu+b.mitu};
}
constexpr S tuhi(){
    return {0,0};
}
S mapi(F l,S r){
    return {(r.a*l.a+r.mitu*l.b)%MOD,r.mitu};
}
F kombi(F l, F r){
    return {(r.a*l.a)%MOD,(r.b*l.a+l.b)%MOD};
}
constexpr F vaike(){
    return {1,0};
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,Q;
    cin>>N>>Q;
    Puukuhi<S,summa,tuhi,F,mapi,kombi,vaike>T;
    for(int i=0;i<N;i++){
        ll a;cin>>a;T.lisa(i,{a,1});
    }
    while(Q--){
        int o;cin>>o;
        if(o==0){
            int i;ll x;
            cin>>i>>x;
            T.lisa(i,{x,1});
        }else if(o==1){
            int i;cin>>i;T.eemalda(i);
        }else if(o==2){
            int l,r;cin>>l>>r;T.poora(l,r);
        }else if(o==3){
            int l,r,b,c;cin>>l>>r>>b>>c;
            T.rakenda(l,r,{b,c});
        }else if(o==4){
            int l,r;cin>>l>>r;
            cout<<T.summa(l,r).a<<'\n';
        }
    }
    return 0;
}
