#include <bits/stdc++.h>
//source https://cp-algorithms.com/graph/bridge-searching-online.html
typedef long long ll;
using namespace std;
struct DSU{
    vector<int>p,sz;
    DSU(int n):p(n),sz(n,1){iota(begin(p),end(p),0);}
    int F(int u){
        if(u==-1)return -1;
        if(u==p[u])return u;
        return p[u]=F(p[u]);
    }
};
class Bridges{
    int n,bridges,lca_it;
    DSU twoEdge,simpleConn;
    vector<int>par,last_vis;
    public:
    Bridges(int n):n(n),bridges(0),lca_it(0),twoEdge(n),simpleConn(n),par(n,-1),last_vis(n){}
    void makeRoot(int u){
        u=twoEdge.F(u);
        int root=u;
        int ch=-1;
        while(u!=-1){
            int p=twoEdge.F(par[u]);
            par[u]=ch;
            simpleConn.p[u]=root;
            ch=u;
            u=p;
        }
        simpleConn.sz[root]=simpleConn.sz[ch];
    }
    void mergePath(int u,int v){
        lca_it++;
        vector<int>pu,pv;
        int lca=-1;
        while(true){
            if(u!=-1){
                u=twoEdge.F(u);
                pu.push_back(u);
                if(last_vis[u]==lca_it){
                    lca=u;
                    break;
                }
                last_vis[u]=lca_it;
                u=par[u];
            }
            if(v!=-1){
                v=twoEdge.F(v);
                pv.push_back(v);
                if(last_vis[v]==lca_it){
                    lca=v;
                    break;
                }
                last_vis[v]=lca_it;
                v=par[v];
            }
        }
        for(auto a:pu){
            twoEdge.p[a]=lca;
            if(a==lca)break;
            bridges--;
        }
        for(auto a:pv){
            twoEdge.p[a]=lca;
            if(a==lca)break;
            bridges--;
        }
    }
    void addEdge(int u,int v){
        u=twoEdge.F(u);
        v=twoEdge.F(v);
        if(u==v)return;
        int cu=simpleConn.F(u),cv=simpleConn.F(v);
        if(cu!=cv){
            bridges++;
            if(simpleConn.sz[cu]>simpleConn.sz[cv]){
                swap(u,v);
                swap(cu,cv);
            }
            makeRoot(u);
            par[u]=simpleConn.p[u]=v;
            simpleConn.sz[cv]+=simpleConn.sz[u];
        }else mergePath(u,v);
    }
    int numOfBridges(){
        return bridges;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        Bridges t(n);
        while(m--){
            int u,v;cin>>u>>v;
            t.addEdge(u,v);
            cout<<t.numOfBridges()<<'\n';
        }
    }
    return 0;
}
