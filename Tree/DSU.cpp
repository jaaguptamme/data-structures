#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct DSU{
    vector<int>p,sz;
    DSU(int n){
        p.resize(n);
        sz.resize(n);
        for(int i=0;i<n;i++)p[i]=i;
    }

    int F(int u){
        if(u==p[u])return u;
        return p[u]=F(p[u]);
    }

    void unite(int u,int v){
        u=F(u);
        v=F(v);
        if(u==v)return;
        if(sz[u]>sz[v])swap(u,v);
        if(sz[u]==sz[v])sz[v]++;
        p[u]=v;
    }
    bool same_comp(int u,int v){
        return F(u)==F(v);
    }
};
