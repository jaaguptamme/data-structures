#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
class PairingHeap{
    struct Tipp{
        T vaartus;
        Tipp *jargmine;
        Tipp *teine;
        Tipp(T vaartus):vaartus(vaartus),jargmine(nullptr),teine(nullptr){}
    };
    static Tipp* uhenda(Tipp* vasak, Tipp* parem){
        if(!vasak)return parem;
        if(!parem)return vasak;
        if(vasak->vaartus>parem->vaartus)swap(vasak,parem);
        parem->jargmine=vasak->teine;
        vasak->teine=parem;
        return vasak;
    }
    static Tipp* uhendaJarjest(Tipp *t){
        if(!t||!t->jargmine)return t;
        Tipp* jargmine=t->jargmine;
        Tipp* teised=jargmine->jargmine;
        return uhenda(uhenda(t,jargmine),uhendaJarjest(teised));
    }

    Tipp *juur;
    PairingHeap(Tipp *juur):juur(juur){}
public:
    PairingHeap():juur(nullptr){}
    void insert(T vaartus){
        juur=uhenda(juur,new Tipp(vaartus));
    }
    T min(){
        return juur->vaartus;
    }

    T removeMin(){
        T vastus=juur->vaartus;
        juur=uhendaJarjest(juur->teine);
        return vastus;
    }
    static PairingHeap uhenda(PairingHeap &a, PairingHeap &b){
        return PairingHeap(uhenda(a.juur,b.juur));
    }
};
