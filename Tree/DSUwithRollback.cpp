#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
class DSU{
    struct Kirje{
        int u,v,szu;
        bool check;
        Kirje(int u,int v,int szu):u(u),v(v),szu(szu),check(false){}
        Kirje():check(true){}
    };
    vector<int>fa,sz;
    vector<Kirje>kirjed;
    int n,setCnt;
      public:
    DSU(int n):n(n),setCnt(n){
        n++;
        fa.resize(n);
        sz.resize(n,0);
        for(int i=0;i<n;i++)fa[i]=i;
    }
    int F(int u){//Esindaja leidmine
        if(u==fa[u])return u;
        return F(fa[u]);
    }

    void uhenda(int u,int v){
        int fu=F(u);
        int fv=F(v);
        if(fu==fv)return;
        if(sz[fu]<sz[fv])swap(fu,fv);
        kirjed.push_back(Kirje(fu,fv,sz[fu]));
        setCnt--;
        fa[fv]=fu;
        sz[fu]=sz[fu]+(sz[fu]==sz[fv]);
    }
    void persist(){//Tee kontrollpunkt, alati enne rollbacki
        kirjed.push_back(Kirje());
    }
    void rollback(){//Seis tagasi viimase kontrollpunktini
        while(!kirjed.back().check){
            auto e=kirjed.back();
            int u=e.u,v=e.v,szu=e.szu;
            fa[v]=v;
            sz[u]=szu;
            kirjed.pop_back();
            setCnt++;
        }
        kirjed.pop_back();
    }
    int getCnt(){//Komponentide arv
        return setCnt;
    }
};
