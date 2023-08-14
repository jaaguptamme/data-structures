#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Sack{
    vector<vector<int>>g;
    int n,lef,rig;
     F fenwick;
    ll res;
    vector<int>dep,sz;
    vector<vector<int>*>alampuuTipud;
    Sack(vector<vector<int>>&g,int L,int R,int root=0):g(g),fenwick(g.size()+1),res(0){
        n=g.size();
        dep.resize(n,1);
        sz.resize(n);
        alampuuTipud.resize(n);
        calcSize(root);
        lef=n-1-R;
        rig=n-1-L;
        dfs(root);
        //for(int i=0;i<n;i++)cout<<i<<' '<<dep[i]<<' '<<sz[i]<<endl;
    }
    void calcSize(int u,int pr=-1){
        sz[u]++;
        for(auto v:g[u]){
            if(v==pr)continue;
            dep[v]=dep[u]+1;
            calcSize(v,u);
            sz[u]+=sz[v];
        }
    }

    void dfs(int u,int pr=0,bool keep=false){
        int mx=-1,bigChild=-1;
        for(auto v:g[u]){
            if(v!=pr && sz[v]>mx)
                mx=sz[v],bigChild=v;
        }
        for(auto v:g[u]){
            if(v!=pr && v!=bigChild)dfs(v,u,0);
        }
        if(bigChild!=-1)dfs(bigChild,u,1),alampuuTipud[u]=alampuuTipud[bigChild];
        else alampuuTipud[u]=new vector<int>();
        alampuuTipud[u]->push_back(u);
        res+=fenwick.get(lef+2*dep[u]-dep[u],rig+2*dep[u]-dep[u]);
        fenwick.add(dep[u],1);
        for(auto v:g[u]){
            if(v==pr || v==bigChild)continue;
            for(auto tipp:*alampuuTipud[v]){
                res+=fenwick.get(lef+2*dep[u]-dep[tipp],rig+2*dep[u]-dep[tipp]);
            }
            for(auto tipp:*alampuuTipud[v]){
                fenwick.add(dep[tipp],1);
                alampuuTipud[u]->push_back(tipp); //NB
            }
        }
        if(keep==0){
            for(auto v:*alampuuTipud[u])fenwick.add(dep[v],-1);
        }
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,l,r;
        cin>>n>>l>>r;
        vector<vector<int>>g(n);
        for(int i=1;i<n;i++){
            int x,y;cin>>x>>y;
            x--;y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        Sack S(g,l,r);
        cout<<S.res<<'\n';
    }
    return 0;
}
