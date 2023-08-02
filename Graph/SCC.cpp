#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
class SCC{
    vector<vector<int>>g,rg;
    int n;
public:
    SCC(int n):n(n){//0 based
        g.resize(n);
        rg.resize(n);
    }
    void add_edge(int a,int b){
        g[a].push_back(b);
        rg[b].push_back(a);
    }
    vector<vector<int>>build(){
        vector<int>vis(n),nodes;
        for(int i=0;i<n;i++)dfs(i,g,vis,nodes,false);
        vector<vector<int>>res;
        vector<int>vis2(n);
        while(nodes.size()){
            int u=nodes.back();nodes.pop_back();
            if(!vis2[u]){
                vector<int>tipud;
                dfs(u,rg,vis2,tipud,true);
                reverse(tipud.begin(),tipud.end());
                res.push_back(tipud);
            }
        }
        return res;
    }
    void dfs(int u,vector<vector<int>>&g,vector<int>&vis,vector<int>&ns,bool add_first){
        if(vis[u])return;
        vis[u]=1;
        if(add_first)ns.push_back(u);
        for(auto v:g[u])dfs(v,g,vis,ns,add_first);
        if(!add_first)ns.push_back(u);
    }
};
