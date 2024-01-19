//source: https://judge.yosupo.jp/submission/183651
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
pair<bool,vector<int>> suunatudEuleriAhel(int N,const vector<pii>& es){
    int M=es.size();
    vector<vector<pii>>g(N);
    vector<int>sisse(N),valja(N);
    for(int i=0;i<M;i++){
        auto [u,v]=es[i];
        valja[u]++;
        sisse[v]++;
        g[u].push_back({v,i});
    }
    int erinev=0;
    for(int i=0;i<N;i++){
        if(abs(sisse[i]-valja[i])>=2)return {false,{}};
        if(sisse[i]!=valja[i])erinev++;
    }
    if(erinev>2)return {false,{}};
    vector<int>servad;
    function<void(int)> dfs=[&](int u){
        while(g[u].size()){
            auto [v,i]=g[u].back();
            g[u].pop_back();
            dfs(v);
            servad.push_back(i);
        }
    };
    bool tehtud=false;
    for(int i=0;i<N;i++){
        if(valja[i]>sisse[i]){
            dfs(i);
            tehtud=true;
            break;
        }
    }
    if(!tehtud){
        for(int i=0;i<N;i++){
            if(valja[i]){
                dfs(i);
                break;
            }
        }
    }
    if(servad.size()!=M)return {false,{}};
    reverse(servad.begin(),servad.end());
    return {true,servad};
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        int N,M;cin>>N>>M;
        vector<pii>es(M);
        for(auto &[u,v]:es)cin>>u>>v;
        auto [b,servad]=suunatudEuleriAhel(N,es);
        if(!b){
            cout<<"No"<<'\n';
            continue;
        }
        cout<<"Yes"<<'\n';
        vector<int>tipud;
        if(servad.size()==0)tipud.push_back(0);
        else{
            for(auto el:servad)tipud.push_back(es[el].first);
            tipud.push_back(es[servad.back()].second);
        }
        for(auto el:tipud)cout<<el<<' ';
        cout<<'\n';
        for(auto el:servad)cout<<el<<' ';
        cout<<'\n';
    }
    return 0;
}
