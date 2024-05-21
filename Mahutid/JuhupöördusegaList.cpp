#include <bits/stdc++.h>
//allikas: https://keithschwarz.com/interesting/code/?dir=random-access-list
/*probleem: listis on ette elemendi lisamine ja eemaldamine konstantse keerukusega,
            kuid indeksi järgi arvu otsimine on lineaarse keerukusega

 lahendus: hoiame arve listina täielikest kahendpuudest, kusjuures kasutatavad suurused määrab skew binary numbrisüsteem
           indeksi leidmine on nüüd logaritmilise keerukusega ning lisamine kustutamine endiselt konstantsed
Mälulekke vaba

*/
typedef long long ll;
using namespace std;
template<typename T>
class JLL{
    struct Tipp{
        T vaartus;
        int suurus;
        shared_ptr<Tipp> vasak,parem;
        Tipp(const T& vaartus):vaartus(vaartus),suurus(1),vasak(nullptr),parem(nullptr){}
        Tipp(const T& vaartus,int suurus,shared_ptr<Tipp> vasak,shared_ptr<Tipp> parem):vaartus(vaartus),suurus(suurus),vasak(vasak),parem(parem){}
        void prindi(){
            cout<<vaartus<<' ';
            if(vasak!=nullptr)vasak->prindi();
            if(parem!=nullptr)parem->prindi();
        }
        T puusKsUusim(int k){//k vahemikus [0,suurus)
            if(k==0)return vaartus;
            int alampuu=(suurus-1)/2;
            if(k<=alampuu)return vasak->puusKsUusim(k-1);
            return parem->puusKsUusim(k-1-alampuu);
        }
    };
    using TP=shared_ptr<Tipp>;
    struct List{
        TP tipp;
        shared_ptr<List> edasi;
        List(TP tipp,shared_ptr<List> edasi):tipp(tipp),edasi(edasi){}
    };

    using LP=shared_ptr<List>;
    static TP uhenda(TP vasak,TP parem,const T& vaartus){
        return make_shared<Tipp>(vaartus,1+vasak->suurus+parem->suurus,vasak,parem);
    }
    LP juured=nullptr;
public:
    JLL(){}
    JLL(LP juured):juured(juured){}
    static JLL lisaLoppu(JLL jll,const T& vaartus){
        if(jll.juured==nullptr||jll.juured->edasi==nullptr){
            return JLL(make_shared<List>(make_shared<Tipp>(vaartus),jll.juured));
        }
        else{
            if(jll.juured->tipp->suurus==jll.juured->edasi->tipp->suurus){
                TP a=jll.juured->tipp,b=jll.juured->edasi->tipp;
                return JLL(make_shared<List>(uhenda(a,b,vaartus),jll.juured->edasi->edasi));
            }else{
                return JLL(make_shared<List>(make_shared<Tipp>(vaartus),jll.juured));
            }
        }
    }
    static T viimane(JLL jll){
        if(onTuhi(jll))throw "TÜHI";
        return jll.juured->tipp->vaartus;
    }
    static bool onTuhi(JLL jll){
        return jll.juured==nullptr;
    }
    static int suurus(JLL jll){
        int vastus=0;
        shared_ptr<List>koht=jll.juured;
        while(koht!=nullptr){
            vastus+=koht->tipp->suurus;
            koht=koht->edasi;
        }
        return vastus;
    }
    static JLL eemaldaViimane(JLL jll){
        if(jll.juured->tipp->suurus==1){
            return JLL(jll.juured->edasi);
        }else{
            return JLL(make_shared<List>(jll.juured->tipp->vasak,make_shared<List>(jll.juured->tipp->parem,jll.juured->edasi)));
        }
    }
    static void prindi(JLL jll){
        shared_ptr<List>koht=jll.juured;
        while(koht!=nullptr){
            koht->tipp->prindi();
            koht=koht->edasi;
        }
        cout<<endl;
    }
    static T indeks(JLL jll,int k){//varaseim element indeksil 0
        k=suurus(jll)-k-1;
        shared_ptr<List>koht=jll.juured;
        while(k>=koht->tipp->suurus){
            k-=koht->tipp->suurus;
            koht=koht->edasi;
        }
        return koht->tipp->puusKsUusim(k);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    using TUUP=JLL<int>;
    const int N=1000*1000;
    vector<TUUP>TS(N);
    for(int t=0;t<1;t++){
        for(int i=1;i<N;i++){
            TS[i]=TUUP::lisaLoppu(TS[(rand()*rand())%(i)],i);
            //if(rand()%2)TS[i]=TUUP::eemaldaViimane(TS[i]);
        }
        TUUP::prindi(TS.back());
        for(int i=0;i<TUUP::suurus(TS.back());i++){
            cout<<TUUP::indeks(TS.back(),i)<<' ';
        }
        cout<<endl;
        cout<<t<<endl;
    }
    return 0;
}
