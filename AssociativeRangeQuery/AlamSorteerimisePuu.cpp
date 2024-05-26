//allikas: https://ningenme.github.io/compro-library/lib/13-static-range-query/StaticRangeSortQuery.cpp
//kontrollitud: https://atcoder.jp/contests/abc237/tasks/abc237_g
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<int BL,class Monoid>
class AlamSorteerimine{
    using Vaartus=typename Monoid::Tuup;
    using Voti=int;
    class SisePuu{
        struct Tipp{
            Tipp *vas,*par;
            int suurus;
            Vaartus vaartus;
            Tipp():suurus(0),vaartus(Monoid::vaike){
                vas=par=nullptr;
            }
            Tipp(Tipp* vas,Tipp* par):
                suurus(0),vaartus(Monoid::vaike),vas(vas),par(par){}
            void tuhjenda(){
                vas=par=nullptr;
                suurus=0;
                vaartus=Monoid::vaike;
            }
            void tekita(Vaartus val){
                suurus=1;
                vaartus=val;
            }
        };
        using TP=Tipp*;
        int umberPoord;
        TP juur;
        int suurus(TP t){
            return t?t->suurus:0;
        }
        Vaartus vaartus(TP t){
            return t?t->vaartus:Monoid::vaike;
        }
        void uuenda(TP t){
            int sv=suurus(t->vas);
            int sp=suurus(t->par);
            if(!sv&&t->vas!=nullptr)t->vas=nullptr;
            if(!sp&&t->par!=nullptr)t->par=nullptr;
            t->suurus=sv+sp;
        }
        void lisa(TP t,int i,const Voti voti,const Vaartus vaartus){
            if(i<0){
                t->tekita(vaartus);
                return;
            }
            const Voti j=((voti>>i)&1);
            if(j){
                if(t->par==nullptr)t->par=new Tipp();
                lisa(t->par,i-1,voti,vaartus);
            }else{
                if(t->vas==nullptr)t->vas=new Tipp();
                lisa(t->vas,i-1,voti,vaartus);
            }
            uuenda(t);
        }
        void eemalda(TP t,int i,const Voti voti){
            if(i<0){
                t->tuhjenda();
                return;
            }
            const Voti j=((voti>>i)&1);
            if(j){
                if(t->par!=nullptr)eemalda(t->par,i-1,voti);
            }else{
                if(t->vas!=nullptr)eemalda(t->vas,i-1,voti);
            }
            uuenda(t);
        }
        pair<Voti,Vaartus> ks(TP t,int i,int k){
            if(i<0){return {0,vaartus(t)};}
            const Voti j=(1ULL<<i);
            int sv=suurus(t->vas);
            if(k<sv)return ks(t->vas,i-1,k);
            else{
                auto p=ks(t->par,i-1,k-sv);
                p.first|=j;
                return p;
            }
        }
        TP mesti(TP v,TP p){
            if(!v)return p;
            if(!p)return v;
            v->vas=mesti(v->vas,p->vas);
            v->par=mesti(v->par,p->par);
            p->tuhjenda();
            uuenda(v);
            return v;
        }
        pair<TP,TP> jaga(TP t,int k){
            if(k==0)return {nullptr,t};
            if(k==suurus(t))return {t,nullptr};
            int vs=suurus(t->vas);
            if(k<vs){
                auto [a,b]=jaga(t->vas,k);
                t->vas=b;
                TP vas=new Tipp(a,nullptr);
                uuenda(vas),uuenda(t);
                return {vas,t};
            }else{
                auto [a,b]=jaga(t->par,k-vs);
                t->par=a;
                TP par=new Tipp(nullptr,b);
                uuenda(t),uuenda(par);
                return {t,par};
            }
        }
        SisePuu(TP t,int umberPoord=0):juur(t),umberPoord(umberPoord){}
    public:
        SisePuu(int umberPoord=0):juur(new Tipp()),umberPoord(umberPoord){}
        void lisa(const Voti voti,const Vaartus vaartus){lisa(juur,BL-1,voti,vaartus);}
        void eemalda(const Voti voti){eemalda(juur,BL-1,voti);}
        int suurus(){return suurus(juur);}
        pair<Voti,Vaartus> ks(int k){return ks(juur,BL-1,(umberPoord?suurus()-1-k:k));}
        Vaartus koik(){return vaartus(juur);}
        void mesti(SisePuu s){
            mesti(juur,s.juur);
            umberPoord=0;
            s.tuhjenda();
        }
        pair<SisePuu,SisePuu> loika(int k){
            if(umberPoord){
                auto [x,y]=jaga(juur,suurus()-k);
                return {SisePuu(y,umberPoord),SisePuu(x,umberPoord)};
            }
            else{
                 auto [x,y]=jaga(juur,k);
                return {SisePuu(x,umberPoord),SisePuu(y,umberPoord)};
            }
        }
        void tuhjenda(){
            juur=new Tipp();
            umberPoord=0;
        }
        void kasvav(){
            umberPoord=0;
        }
        void kahanev(){
            umberPoord=1;
        }
    };
    int pikkus;
    vector<SisePuu> leht;
    set<int>vahemik;
    void poordumiseEeltoo(int i){
        if(pikkus<=i)return;
        auto it=vahemik.lower_bound(i);
        int r=*it;
        if(r==i)return;
        it--;
        int l=*it;
        auto [sl,sr]=leht[l].loika(i-l);
        leht[l]=sl;
        leht[i]=sr;
        vahemik.insert(i);
    }
    void sorteeri(int l,int r,int umberPoord){
        poordumiseEeltoo(l);
        poordumiseEeltoo(r);
        while(true){
            int c=*vahemik.upper_bound(l);
            if(c==r)break;
            leht[l].mesti(leht[c]);
            vahemik.erase(c);
        }
        if(umberPoord)leht[l].kahanev();
        else leht[l].kasvav();
    }
    public:
        AlamSorteerimine(const vector<Voti>&votmed,const vector<Vaartus>&vaartused){
            pikkus=votmed.size();
            leht.resize(pikkus);
            for(int i=0;i<=pikkus;i++)vahemik.insert(i);
            for(int i=0;i<pikkus;i++)leht[i].lisa(votmed[i],vaartused[i]);
        }
        void kasvavaks(int l,int r){
            sorteeri(l,r,0);
        }
        void kahanevaks(int l,int r){
            sorteeri(l,r,1);
        }
        Vaartus saa(int ind){
            if(ind<0||pikkus<=ind)return Monoid::vaike;
            poordumiseEeltoo(ind);
            return leht[ind].ks(0).second;
        }
        void print(){
            cout << "{ ";
            for(int i = 0; i < pikkus; ++i) cout << leht[i].koik() << ", ";
            cout << " }" << endl;
            }
};
template<class T> struct MonoidInt {
    using Tuup = T;
    inline static constexpr Tuup vaike = 0;
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    /*const int N=1000*100;
    vector<int>A(N),B;
    iota(A.begin(),A.end(),0);
    random_shuffle(A.begin(),A.end());
    for(auto el:A)B.push_back(el);
    AlamSorteerimine<20,MonoidInt<int>>T(A,B);
    T.kahanevaks(0,N/2);
    for(int i=0;i<N;i++){
        cout<<T.saa(i)<<endl;
    }*/
    /*
    int N,Q,X;
    cin>>N>>Q>>X;
    vector<int>A,B;
    for(auto &el:P)cin>>el;
    AlamSorteerimine<20,MonoidInt<int>>T(P,P);
    while(Q--){
        int C,L,R;
        cin>>C>>L>>R;
        if(C==1)T.kasvavaks(L-1,R);
        else T.kahanevaks(L-1,R);
    }
    for(int i=0;i<N;i++){
        if(T.saa(i)==X){
            cout<<i+1<<endl;
        }
    }*/
    int N,M;
    cin>>N>>M;
    vector<int>A(N),B(N);
    for(int i=0;i<N;i++)cin>>A[i]>>B[i];
    AlamSorteerimine<20,MonoidInt<int>>T(A,B);
    while(M--){
        int t;
        cin>>t;
        if(t==0){
            int l,r;cin>>l>>r;
            T.kasvavaks(l,r+1);
        }else if(t==1){
            int l,r;cin>>l>>r;
            T.kahanevaks(l,r+1);
        }else{
            int i;cin>>i;
            cout<<T.saa(i)<<'\n';
        }
    }
    return 0;
}
