#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
class PersistentQueue{
    struct Tipp{
        T vaartus;
        vector<Tipp*>ulemused;
        int pikkus;
        Tipp(T vaartus,int pikkus):vaartus(vaartus),pikkus(pikkus){}
        Tipp():pikkus(0){}
        void lisaUlemus(Tipp* ul){
            ulemused.push_back(ul);
        }
    };
    vector<Tipp*>versioonid;
    public:
    PersistentQueue(){
        versioonid.push_back(new Tipp());
    }
    void uus(int ul,T &vaartus){//Lisa järjekorra ul lõppu vaartus, tee sellest uus järjekord
        Tipp *ulemus=versioonid[ul];
        int maht=ulemus->pikkus+1;
        Tipp *uus=new Tipp(vaartus,maht);
        uus->lisaUlemus(ulemus);
        maht-=1;
        int koht=0;
        while(maht>(1<<koht)){
            ulemus=ulemus->ulemused[koht];
            uus->lisaUlemus(ulemus);
            maht-=1<<koht;
            koht++;
        }
        versioonid.push_back(uus);
    }
    T eemalda(int i){//eemalda järjekorrast i esimene element, tagasta sees, tee uus järjekord
        Tipp *t=versioonid[i];
        int maht=t->pikkus-1;
        Tipp *eem=KsUlemus(t,maht);
        T vastus=eem->vaartus;
        Tipp *uus=new Tipp(t->vaartus,maht);
        for(auto el:t->ulemused)uus->lisaUlemus(el);
        versioonid.push_back(uus);
        return vastus;
    }
    Tipp *KsUlemus(Tipp *t,int k){//Leia tipu t,k-s ulemus
        int i=0;
        while(k){
            if(k&(1<<i)){
                t=t->ulemused[i];
                k-=1<<i;
            }
            i++;
        }
        return t;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int q;
    cin>>q;
    PersistentQueue<int>T;
    while(q--){
        int op,t,x;
        cin>>op>>t;
        if(op==0){
            cin>>x;
            T.uus(t+1,x);
        }else{
            cout<<T.eemalda(t+1)<<'\n';
        }
    }
    return 0;
}
