#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef pair<int,int> pii;
class TwoEdgeConnectedComponents{
    vector<vector<pii>>g;
    int n;
    int ind=0;
    set<int>bridges;
public:
    TwoEdgeConnectedComponents(int n):n(n){
        g.resize(n);
    }
    void add_edge(int a,int b,int i){
        g[a].push_back({b,i});
        g[b].push_back({a,i});
    }
    vector<vector<int>>build(){
        vector<int>vis(n),pos(n),low(n);
        for(int i=0;i<n;i++){
            dfs(i,-1,vis,pos,low);
        }
        vector<int>vis2(n);
        vector<vector<int>>res;
        for(int i=0;i<n;i++){
            if(!vis2[i]){
                vector<int>ns;
                dfs2(i,ns,vis2);
                res.push_back(ns);
            }
        }
        return res;
    }

    void dfs(int u,int pr,vector<int>&vis,vector<int>&pos,vector<int>&low){
        if(vis[u])return;
        vis[u]=1;
        pos[u]=low[u]=ind++;
        bool dup=false;
        for(auto el:g[u]){
            int v=el.first;
            if(v==pr&&!dup){
                dup=true;
                continue;
            }
            if(vis[v]){
                low[u]=min(low[u],pos[v]);
            }
            else{
                dfs(v,u,vis,pos,low);
                low[u]=min(low[u],low[v]);
                if(low[v]>pos[u]){
                    bridges.insert(el.second);
                }
            }
        }
    }
    void dfs2(int u,vector<int>&ns,vector<int>&vis){//add all nodes to this array ns reachable from this node
        if(vis[u])return;
        ns.push_back(u);
        vis[u]=1;
        for(auto el:g[u]){
            if(bridges.count(el.second))continue;
            dfs2(el.first,ns,vis);
        }
    }
};
