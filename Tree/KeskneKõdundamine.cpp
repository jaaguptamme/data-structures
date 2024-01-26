//source: https://codeforces.com/blog/entry/125018
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Arb{
    vector<vector<int>>alluvad;
    int juur;
};
template<typename T>
void eemalda(vector<T>& V,T& el){
    V.erase(find(V.begin(),V.end(),el));
}
Arb CD(vector<vector<int>> g, int juur=0){
    int n=g.size();
    vector<int>alampuuSuurus(n);
    auto dfs=[&](int u,auto&& self)->int{
        for(auto v:g[u]){
            eemalda(g[v],u);
            alampuuSuurus[u]+=self(v,self);
        }
        return ++alampuuSuurus[u];
    };
    dfs(juur,dfs);
    vector<vector<int>>vas(n);
    auto komposti=[&](int u,auto&& self)->int{
        int SZ=alampuuSuurus[u];
        for(bool leitud=0;!leitud;){
            leitud=1;
            for(auto v:g[u]){
                if(alampuuSuurus[v]>SZ/2){
                    leitud=0;
                    alampuuSuurus[u]=SZ-alampuuSuurus[v];
                    eemalda(g[u],v);
                    g[v].push_back(u);
                    u=v;
                    break;
                }
            }
        }
        for(auto v:g[u])vas[u].push_back(self(v,self));
        return u;
    };
    int uusJuur=komposti(juur,komposti);
    return {move(vas),uusJuur};
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    Arb vas=CD(g);
    auto G=vas.alluvad;
    vector<int>tase(n);
    auto dfs=[&](int u,int lab,auto&& self) -> void{
        tase[u]=lab;
        for(auto v:G[u])self(v,lab+1,self);
    };
    dfs(vas.juur,0,dfs);
    for(auto el:tase)cout<<char(el+'A')<<' ';
    return 0;
}
