#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef pair<int,int> pii;
const int N=500005;
vector<pii>g[N];
int vis[N],evis[N];
vector<pii>st;
void dfs(int u,int pr){
    /*cout<<u<<endl;
    for(auto el:st)cout<<el.first<<' '<<el.second<<endl;
    cout<<endl;*/
    vis[u]=1;
    for(auto el:g[u]){
        int v=el.first,ind=el.second;
        if(v==pr)continue;
        if(vis[v]==2||evis[ind])continue;
        if(vis[v]==1 && evis[ind]==0){
            vector<int>res;
            vector<int>nodes;
            res.push_back(ind);
            nodes.push_back(u);
            while(st.back().first!=v){
                res.push_back(st.back().second);
                nodes.push_back(st.back().first);
                st.pop_back();
            }
            res.push_back(st.back().second);
            nodes.push_back(st.back().first);
            cout<<res.size()<<endl;
            for(auto el:nodes)cout<<el<<' ';
            cout<<endl;
            for(int i=0;i<res.size();i++)
                cout<<res[(i+1)%res.size()]<<' ';
            cout<<endl;
            exit(0);
        }
        evis[ind]=1;
        st.push_back({u,ind});
        dfs(v,u);
        st.pop_back();
    }
    vis[u]=2;
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        if(a==b){
            cout<<1<<endl;
            cout<<a<<endl;
            cout<<i<<endl;
            exit(0);
        }
        g[a].push_back({b,i});
        g[b].push_back({a,i});
    }
    for(int i=0;i<n;i++){
        sort(g[i].begin(),g[i].end());
        for(int j=1;j<g[i].size();j++){
            if(g[i][j].first==g[i][j-1].first){
                cout<<2<<endl;
                cout<<i<<' '<<g[i][j].first<<'\n';
                cout<<g[i][j].second<<' '<<g[i][j-1].second<<endl;
                exit(0);
            }
        }
    }
    for(int i=0;i<n;i++){
        if(vis[i]!=2)dfs(i,-1);
    }
    cout<<-1<<endl;
    return 0;
}
