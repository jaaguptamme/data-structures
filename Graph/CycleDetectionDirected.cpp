#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef pair<int,int> pii;
const int N=500005;
vector<pii>g[N];
int vis[N],evis[N];
vector<pii>st;
void dfs(int u){
    /*cout<<u<<endl;
    for(auto el:st)cout<<el.first<<' '<<el.second<<endl;
    cout<<endl;*/
    vis[u]=1;
    for(auto el:g[u]){
        int v=el.first,ind=el.second;
        if(vis[v]==2||evis[ind])continue;
        if(vis[v]==1 && evis[ind]==0){
            vector<int>res;
            res.push_back(ind);
            while(st.back().first!=v){
                res.push_back(st.back().second);
                st.pop_back();
            }
            res.push_back(st.back().second);
            reverse(res.begin(),res.end());
            cout<<res.size()<<endl;
            for(auto el:res)cout<<el<<'\n';
            exit(0);
        }
        evis[ind]=1;
        st.push_back({u,ind});
        dfs(v);
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
        g[a].push_back({b,i});
    }
    for(int i=0;i<n;i++){
        if(vis[i]!=2)dfs(i);
    }
    cout<<-1<<endl;
    return 0;
}
