//source: https://neterukun1993.github.io/Library/DataStructure/BinaryIndexedTree/PersistentBinaryIndexedTree.py
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
struct AjaloogaFenwick{
    struct Tipp{
        Tipp *esimene,*teine;
        T vaartus=0;
        Tipp(Tipp* esimene,Tipp* teine,T vaartus):esimene(esimene),teine(teine),vaartus(vaartus){}
    };
    Tipp* juur;
    int n,suurus;
    AjaloogaFenwick(int n,Tipp* juur=nullptr):juur(juur),n(n){
        suurus=1<<bitLen(n);
    }
    int bitLen(int n){return 32-__builtin_clz(n);}
    void ehita(const vector<T>& ar){
        int n=ar.size();
        vector<Tipp*>bit(this->suurus);
        for(int i=0;i<this->suurus;i++){
            bit[i]=new Tipp(nullptr,nullptr,(0<=(i-1)&&(i-1)<n)?ar[i-1]:0);
        }
        for(int i=1;i<this->suurus;i++){
            if(i+(i&-i)<this->suurus)(*bit[i+(i&-i)]).vaartus+=(*bit[i]).vaartus;
        }
        for(int k=0;k<bitLen(this->suurus)-1;k++){
            for(int i=1<<k;i<this->suurus;i+=1<<(k+1)){
                if(k!=0){
                    int l=i-(1<<(k-1)),r=i+(1<<(k-1));
                    bit[i]->esimene=bit[l];
                    bit[i]->teine=bit[r];
                }
            }
        }
        this->juur=bit[this->suurus>>1];
    }
    T summa(int i){//summa [0,i)
         T s=0;
         Tipp* tipp=this->juur;
         int indeks=this->suurus>>1;
         for(int h=bitLen(this->suurus)-3;h>=0;h--){
            if(i<indeks){
                tipp=tipp->esimene;
                indeks-=1<<h;
            }else{
                s+=tipp->vaartus;
                tipp=tipp->teine;
                indeks+=1<<h;
            }
         }
         if(i>=indeks)s+=tipp->vaartus;
         return s;
    }
    Tipp* lisa_rek(int i,int indeks,int diff,T vaartus,Tipp* tipp){
        if(i==indeks){
            return new Tipp(tipp->esimene,tipp->teine,tipp->vaartus+vaartus);
        }else if(i<indeks){
            auto vasakTipp=lisa_rek(i,indeks-diff,diff>>1,vaartus,tipp->esimene);
            if(indeks-(indeks&(-indeks))<i){
                return new Tipp(vasakTipp,tipp->teine,tipp->vaartus+vaartus);
            }
            return new Tipp(vasakTipp,tipp->teine,tipp->vaartus);
        }else{
            auto paremTipp=lisa_rek(i,indeks+diff,diff>>1,vaartus,tipp->teine);
            return new Tipp(tipp->esimene,paremTipp,tipp->vaartus);
        }
    }
    T summa(int l,int r){
        return summa(r)-summa(l);
    }
    AjaloogaFenwick<T> lisa(int i,T vaartus){//lisa kohale i vaartus
        i+=1;
        int indeks=this->suurus>>1;
        Tipp* juur=lisa_rek(i,indeks,indeks>>1,vaartus,this->juur);
        return AjaloogaFenwick<T>(this->n,juur);
    }
};
