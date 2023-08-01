#include <bits/stdc++.h>
//based on :https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
typedef long long ll;
using namespace std;
const int N=200005;
vector<int>g[N],revg[N];
class DominatorTree{
    vector<vector<int>>g,rg,buck;
    int n,S;
    int ind;
    vector<int>nodeToInd,indToNode,label,sdom,dom,dsu,par;//dfs orders, label-vert with min sdom on part from i to root
    public:
    DominatorTree(int n,int S):n(n),S(S){
        g.resize(n+1);
        rg.resize(n+1);
        buck.resize(n+1);
        nodeToInd.resize(n+1);
        indToNode.resize(n+1);
        label.resize(n+1);
        sdom.resize(n+1);
        dom.resize(n+1,-1);
        dsu.resize(n+1);
        par.resize(n+1);
        ind=0;
    }
    void addEdge(int u,int v){
        g[u].push_back(v);
    }
    void build(){
        dfs(S);
        for(int i=ind;i>=1;i--){
            for(auto j:rg[i])sdom[i]=min(sdom[i],sdom[leia(j)]);
            if(i>1)buck[sdom[i]].push_back(i);
            for(auto w:buck[i]){
                int v=leia(w);
                if(sdom[v]==sdom[w])dom[w]=sdom[w];
                else dom[w]=v;
            }
            if(i>1)uhenda(par[i],i);
        }
        for(int i=2;i<=ind;i++){
            if(dom[i]!=sdom[i])dom[i]=dom[dom[i]];
        }
    }

    void dfs(int u){
        ind++;
        nodeToInd[u]=ind;indToNode[ind]=u;
        label[ind]=ind;sdom[ind]=ind;dsu[ind]=ind;
        for(auto v:g[u]){
            if(!nodeToInd[v]){
                dfs(v);
                par[nodeToInd[v]]=nodeToInd[u];
            }
            rg[nodeToInd[v]].push_back(nodeToInd[u]);
        }
    }
    int leia(int u,int x=0){
        if(u==dsu[u])return x?-1:u;
        int v=leia(dsu[u],x+1);
        if(v<0)return u;
        if(sdom[label[dsu[u]]]<sdom[label[u]])label[u]=label[dsu[u]];
        dsu[u]=v;
        return x?v:label[u];
    }
    void uhenda(int u,int v){
        dsu[v]=u;
    }
    vector<int> vas(){
        vector<int>res(n,-1);
        for(int i=1;i<=ind;i++)res[indToNode[i]]=indToNode[dom[i]];
        res[S]=S;
        return res;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,S;
    cin>>n>>m>>S;
    DominatorTree t(n,S);
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        t.addEdge(u,v);
    }
    t.build();
    auto vas=t.vas();
    for(auto el:vas)cout<<el<<' ';
    return 0;
}
