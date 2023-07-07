#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=500005,LG2=(int)log2(N)+1;
vector<int>g[N];
class LCA{public:
    vector<int>dep;
    vector<vector<int>>P;
    LCA(int root){
        dep=vector<int>(N,0);
        P=vector<vector<int>>(LG2,vector<int>(N,0));
        dfs(root,-1);
        for(int i=1;i<LG2;i++){
            for(int u=0;u<N;u++)P[i][u]=P[i-1][P[i-1][u]];
        }
    }
    void dfs(int u,int pr){
        for(auto v:g[u]){
            if(v==pr)continue;
            P[0][v]=u;
            dep[v]=dep[u]+1;
            dfs(v,u);
        }
    }
    int lca(int u,int v){
        if(dep[u]<dep[v])swap(u,v);
        for(int i=LG2-1;i>=0;i--){
            if(dep[u]-(1<<i)>=dep[v]){
                u=P[i][u];
            }
        }
        if(u==v)return u;
        for(int i=LG2-1;i>=0;i--){
            if(P[i][u]!=P[i][v]){
                u=P[i][u];
                v=P[i][v];
            }
        }
        return P[0][u];
    }
};
