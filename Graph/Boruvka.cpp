#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Edge{
    int u,v;
    ll c;
    Edge(int u,int v,ll c):u(u),v(v),c(c){}
};
struct DSU{
    vector<int>p,sz;
    int compCnt;
    DSU(int n):compCnt(n){
        p.resize(n);
        sz.resize(n);
        for(int i=0;i<n;i++)p[i]=i;
    }

    int F(int u){
        if(u==p[u])return u;
        return p[u]=F(p[u]);
    }

    bool unite(int u,int v){
        u=F(u);
        v=F(v);
        if(u==v)return false;
        if(sz[u]>sz[v])swap(u,v);
        if(sz[u]==sz[v])sz[v]++;
        p[u]=v;
        compCnt--;
        return true;
    }
    bool same_comp(int u,int v){
        return F(u)==F(v);
    }
};
pair<ll,vector<pair<int,int>>> boruvka(int n,vector<Edge>&edges){
    ll INF=LLONG_MAX/2;
    DSU t(n);
    ll res=0;
    vector<pair<int,int>>paarid;
    while(t.compCnt!=1){
        bool upd=false;
        vector<Edge>minHind(n,{-1,-1,INF});
        for(auto edge:edges){
            if(!t.same_comp(edge.u,edge.v)){
                int ru=t.F(edge.u);
                int rv=t.F(edge.v);
                if(edge.c<minHind[ru].c)minHind[ru]=edge;
                if(edge.c<minHind[rv].c)minHind[rv]=edge;
            }
        }
        for(auto edge:minHind){
            if(edge.c!=INF && !t.same_comp(edge.u,edge.v)){
                upd=true;
                t.unite(edge.u,edge.v);
                paarid.push_back({edge.u,edge.v});
                res+=edge.c;
            }
        }
        if(!upd)return {-1,{}};
    }
    return {res,paarid};
}
