#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=500005;
struct DSU{
    vector<int>p,sz;
    vector<int>color;
    DSU(int n){
        p.resize(n);
        sz.resize(n);
        color.resize(n);
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
    void set_ancestsor(int u){//SET u to be ancestor of set u is in
        int par=F(u);
        if(par==u)return;
        sz[u]=sz[par];
        p[par]=u;
        p[u]=u;
    }
};
vector<int>g[N];//Initial graph
vector<int>res(N);//ith place is result of ith query
vector<pair<int,int>>qs[N];//query[u] contains pairs (v,pos)
struct LCA{
    DSU d;
    LCA(int root,int n):d(n){
        dfs(root,-1);
    }
    void dfs(int u,int pr){
        d.set_ancestsor(u);
        for(auto v:g[u]){
            if(v==pr)continue;
            dfs(v,u);
            d.unite(u,v);
            d.set_ancestsor(u);
        }
        d.color[u]=1;
        for(auto el:qs[u]){
            int v=el.first,pos=el.second;
            if(d.color[v]==1)res[pos]=d.F(v);
        }
    }
};

int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int p;cin>>p;
        g[p].push_back(i);
    }
    for(int i=0;i<q;i++){
        int u,v;cin>>u>>v;
        qs[u].emplace_back(v,i);
        qs[v].emplace_back(u,i);
    }
    LCA t(0,n);
    for(int i=0;i<q;i++)cout<<res[i]<<'\n';
    return 0;
}
