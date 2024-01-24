//source: https://codeforces.com/blog/entry/125018
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Arb{
    vector<vector<int>>alluvad;
    int juur;
};
Arb SDT(vector<vector<int>>&g,int juur=0){
    int n=g.size();
    vector<vector<int>>vas(n),pinud(__lg(n)+1);
    auto saa_ahel=[&](int sildid,int u){
        while(sildid){
            int silt=__lg(sildid);
            sildid^=1<<silt;
            int v=pinud[silt].back();pinud[silt].pop_back();
            vas[u].push_back(v);
            u=v;
        }
    };
    vector<int>keelatud(n,-1);
    auto dfs=[&](int u,int p,auto&& self) -> void {
        int keelatud1=0,keelatud2=0;
        for(auto v:g[u]){
            if(v==p)continue;
            self(v,u,self);
            keelatud2|=keelatud1&(keelatud[v]+1);
            keelatud1|=keelatud[v]+1;
        }
        keelatud[u]=keelatud1|((1<<__lg(2*keelatud2+1))-1);
        int uSilt=__builtin_ctz(keelatud[u]+1);
        pinud[uSilt].push_back(u);
        for(int i=g[u].size()-1;i>=0;i--){
            int v=g[u][i];
            saa_ahel((keelatud[v]+1)&((1<<uSilt)-1),u);
        }
    };
    dfs(juur,-1,dfs);
    int suurimSilt=__lg(keelatud[juur]+1);
    int vastuseJuur=pinud[suurimSilt].back();
    pinud[suurimSilt].pop_back();
    saa_ahel((keelatud[juur]+1)&((1<<suurimSilt)-1),vastuseJuur);
    return {move(vas),vastuseJuur};
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
    Arb vas=SDT(g);
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
