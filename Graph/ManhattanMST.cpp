#include <bits/stdc++.h>
//source https://ei1333.github.io/library/graph/mst/manhattan-mst.hpp
typedef long long ll;
using namespace std;
struct Edge{
    int u,v;
    ll c;
    Edge(int u,int v,ll c):u(u),v(v),c(c){}
};
vector<Edge> calcNeighs(vector<int>&x,vector<int>&y){
    int n=x.size();
    vector<Edge>edges;
    vector<int>ord(n);
    iota(begin(ord),end(ord),0);
    for(int t1=0;t1<2;t1++){
        for(int t2=0;t2<2;t2++){
            sort(begin(ord),end(ord),[&](int i,int j){return x[i]+y[i]<x[j]+y[j];});
            map<int,int>mp;
            for(int i:ord){
                for(auto it=mp.lower_bound(-y[i]);it!=mp.end();it=mp.erase(it)){
                    auto j=it->second;
                    if(x[i]-x[j]<y[i]-y[j])break;
                    edges.push_back({i,j,abs(x[i]-x[j])+abs(y[i]-y[j])});
                }
                mp[-y[i]]=i;
            }
            for(int i=0;i<n;i++)x[i]*=-1;
        }
        swap(x,y);
    }
    return edges;
}
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

    bool unite(int u,int v){
        u=F(u);
        v=F(v);
        if(u==v)return false;
        if(sz[u]>sz[v])swap(u,v);
        if(sz[u]==sz[v])sz[v]++;
        p[u]=v;
        return true;
    }
    bool same_comp(int u,int v){
        return F(u)==F(v);
    }
};
pair<ll,vector<pair<int,int>>> kruskal(int n,vector<Edge>&edges){
    sort(begin(edges),end(edges),[&](Edge& a,Edge& b){return a.c<b.c;});
    DSU t(n);
    ll sum=0;
    vector<pair<int,int>>paarid;
    for(Edge& a:edges){
        if(t.unite(a.u,a.v)){
            sum+=a.c;
            paarid.push_back({a.u,a.v});
        }
    }
    return {sum,paarid};
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    vector<int>x(n),y(n);
    for(int i=0;i<n;i++)cin>>x[i]>>y[i];
    vector<Edge>neighs=calcNeighs(x,y);
    auto res=kruskal(n,neighs);
    cout<<res.first<<'\n';
    for(auto el:res.second)cout<<el.first<<' '<<el.second<<'\n';
    return 0;
}
