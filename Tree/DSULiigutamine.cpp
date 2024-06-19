#include <bits/stdc++.h>
//ALLIKAS: https://codeforces.com/blog/entry/130521
//KONTROLLITUD: https://vjudge.net/problem/UVA-11987
typedef long long ll;
using namespace std;
/*Võimaldab lisaks tavalistele DSU operatsioonidele tippu liigutada teise klassipuusee (kuid ainult seda üksikut tippu)
Või ka tippu klassipuust kustutada.
Idee: kasutame N lisatippu, ühte iga tipu jaoks, et õiged tipud oleksid alati lehed ehk neile ei näitaks üksi nool,
siis saame kustutatmist ja nihutamist lihtsalt implementeerida. Ehk kasutame 2x mälu võrreldes tavapärasega.
Keerukus on vist sama nagu tavalise DSU puhul, kuid pole päris kindel.
NB! Kõike funktsioone kasutada ainult argumentidega [0,N), sest need on "päris" tipud
*/
struct DSULiigutamine{
    vector<int>f;
    vector<ll>summa;
    public:
    DSULiigutamine(int N):f(2*N,-1),summa(2*N){
        iota(f.begin(),f.begin()+N,N);
        iota(summa.begin()+N,summa.end(),1);
    }
    int Yl(int u){//ülemuse leidmine
        if(f[u]<0)return u;
        return f[u]=Yl(f[u]);
    }
     bool uhenda(int u,int v){//Ühenda tippude u ja v klassipuud, tagasta kas midagi pidi selle jaoks muutma
        int uyl=Yl(u),vyl=Yl(v);
        if(kustutatud(u)||kustutatud(v)||uyl==vyl)return false;
        if(f[uyl]>f[vyl])swap(uyl,vyl);
        f[uyl]+=f[vyl];
        summa[uyl]+=summa[vyl];
        f[vyl]=uyl;
        return true;
     }
     bool liiguta(int u,int v){//Liiguta tipp u tipu v klassipuusse
        int uyl=Yl(u),vyl=Yl(v);
        if(kustutatud(u)||kustutatud(v)||uyl==vyl)return false;
        f[uyl]++;f[vyl]--;
        summa[uyl]-=u+1;
        summa[vyl]+=u+1;
        f[u]=vyl;
        return true;
     }
     bool kustuta(int u){//Tipu u kustutamine on klassipuust, nüüd on ta eraldi tipp
        auto uyl=Yl(u);
        if(kustutatud(u))return false;
        summa[uyl]-=u+1;
        summa[u]=u+1;
        f[uyl]++;f[u]=-1;
        return true;
     }
     bool kustutatud(int u){//kas tipp on juba kustutatud
        return f[u]==-1;
    }
    int suurus(int u){//Elementide arv tipu u klassipuus
        return -f[Yl(u)];
    }
    ll saaSumma(int u){//Tipunumbrite summa tipu u klassipuus
        return summa[Yl(u)];
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,Q;
    while(cin>>N){
        cin>>Q;
        DSULiigutamine T(N);
        while(Q--){
            int op,p;
            cin>>op>>p;
            if(op==3){
                cout<<T.suurus(p-1)<<' '<<T.saaSumma(p-1)<<'\n';
            }else if(op==1){
                int q;cin>>q;
                T.uhenda(p-1,q-1);
            }else{
                int q;cin>>q;
                T.liiguta(p-1,q-1);
            }
        }
    }
    return 0;
}
