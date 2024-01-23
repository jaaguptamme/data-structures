//source: https://judge.yosupo.jp/submission/183656
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
pair<bool,vector<int>> suunamataEuleriAhel(int N,const vector<pii>& es){
    int M=es.size(),i=0;
    vector<int>mitu(N),servad(M+1),vas;
    vector<vector<pair<int,int>>>g(N);
    for(auto [u,v]:es){
        mitu[u]++;mitu[v]++;
        g[u].push_back({v,++i});
        g[v].push_back({u,-i});
    }
    int paaritu=0;
    for(int i=0;i<N;i++)paaritu+=mitu[i]&1;
    if(paaritu>2)return {false,{}};
    function<void(int)> dfs=[&](int u){
        while(g[u].size()){
            auto [v,w]=g[u].back();
            g[u].pop_back();
            if(servad[abs(w)])continue;
            servad[abs(w)]=1;
            dfs(v);
            vas.push_back(w);
        }
    };
    bool tehtud=false;
    for(int i=0;i<N;i++){
        if(mitu[i]&1){
            dfs(i);
            tehtud=true;
            break;
        }
    }
    if(!tehtud){
        for(int i=0;i<N;i++){
            if(mitu[i]){
                dfs(i);
                break;
            }
        }
    }
    reverse(vas.begin(),vas.end());
    if(vas.size()!=es.size())return {false,{}};
    return {true,vas};
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        int N,M;cin>>N>>M;
        vector<pii>es(M);
        for(auto &[u,v]:es)cin>>u>>v;
        auto [b,servad]=suunamataEuleriAhel(N,es);
        if(!b){
            cout<<"No"<<'\n';
            continue;
        }
        cout<<"Yes"<<'\n';
        if(M==0){
            cout<<"0"<<'\n'<<'\n';continue;
        }
        for(int i=0;i<M;i++){
            if(servad[i]){
                bool tp=0;
                if(servad[i]<0)tp=1;
                servad[i]=abs(servad[i])-1;
                if(tp)swap(es[servad[i]].first,es[servad[i]].second);
                cout<<es[servad[i]].first<<' ';
            }
        }
        cout<<es[servad[M-1]].second<<'\n';
        for(auto el:servad)cout<<el<<' ';
        cout<<'\n';
    }
    return 0;
}
