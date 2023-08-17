#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct DSU{
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
typedef pair<int,int>pii;
struct OP{
    int u,v,ind;
    bool numCmps;
    OP(int u,int v):u(u),v(v),numCmps(false){}
    OP(int ind)://p real pos, ind=num of query
        ind(ind),numCmps(true){}
};
vector<int>res;
struct QueryTree{
    vector<vector<OP>>t;
    DSU dsu;
    int n,m;
    QueryTree(int n,int m):dsu(n),n(n),m(m),t(4*m+4){}
    void addQuery(int i,int l,int r,int se,int en, OP& o){
        if(se<=l&&r<=en){
            t[i].push_back(o);
            return;
        }
        int m=(l+r)/2;
        if(en<=m)addQuery(i*2,l,m,se,en,o);
        else if(m<se)addQuery(i*2+1,m+1,r,se,en,o);
        else{
            addQuery(i*2,l,m,se,en,o);
            addQuery(i*2+1,m+1,r,se,en,o);
        }
    }
    void addQuery(OP o,int l,int r){
        addQuery(1,0,m-1,l,r,o);
    }
    void dfs(int i,int l,int r){
        dsu.persist();
        for(OP &o:t[i]){
            if(!o.numCmps){dsu.uhenda(o.u,o.v);}
        }
        if(l==r){
            for(OP &o:t[i]){
                if(o.numCmps)res[o.ind]=dsu.getCnt();
            }
        }else{
            int m=(l+r)/2;
            dfs(i*2,l,m);
            dfs(i*2+1,m+1,r);
        }
        dsu.rollback();
    }
    void solve(){
        dfs(1,0,m-1);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m;
    map<pii,int>latest;
    int qcnt=0;
    QueryTree T(n,m+2);
    for(int i=0;i<m;i++){
        char op;
        int u,v;
        cin>>op;
        if(op=='?'){
            T.addQuery(OP(qcnt++),i,i);
        }else if(op=='+'){
            cin>>u>>v;
            if(u>v)swap(u,v);
             u--;v--;
            latest[{u,v}]=i;
        }else{
            cin>>u>>v;
            if(u>v)swap(u,v);
            u--;v--;
            int r=i;
            int l=latest[{u,v}];
            T.addQuery(OP(u,v),l,r);
            latest.erase({u,v});
        }
    }
    res.resize(qcnt);
    for(auto el:latest)T.addQuery(OP(el.first.first,el.first.second),el.second,m);
    T.solve();
    for(int i=0;i<qcnt;i++)cout<<res[i]<<'\n';
    return 0;
}
