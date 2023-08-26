#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
vector<int> compress(vector<T>&a){
    int n=a.size();
    set<T>vls;
    for(auto el:a)vls.insert(el);
    map<T,int>mp;
    int ps=0;
    for(auto el:vls)mp[el]=ps++;
    vector<int>b(n);
    for(int i=0;i<n;i++)b[i]=mp[a[i]];
    return b;
}
class Mo{
    struct Query{
        int l,r,lca;
    };
    int n,m,curDfsPos=0;
    vector<vector<int>>par;
    vector<int>st,en,dfsOrd,dep;
    vector<Query>qs;
    public:
    Mo(vector<vector<int>>&g):n(g.size()){//numbered [0,n)
        m=log2(n)+1;
        par.resize(m,vector<int>(n));
        st.resize(n);
        en.resize(n);
        dep.resize(n);
        dfs(0,-1,g);
        for(int j=1;j<m;j++){
            for(int i=0;i<n;i++)par[j][i]=par[j-1][par[j-1][i]];
        }
        //for(int i=0;i<n;i++)cout<<i<<' '<<st[i]<<' '<<en[i]<<' '<<dep[i]<<endl;
    }
    void dfs(int u,int pr,vector<vector<int>>&g){
        dfsOrd.push_back(u);
        st[u]=curDfsPos++;
        for(auto v:g[u]){
            if(v==pr)continue;
            par[0][v]=u;
            dep[v]=dep[u]+1;
            dfs(v,u,g);
        }
        dfsOrd.push_back(u);
        en[u]=curDfsPos++;
    }
    int lca(int u,int v){
        if(dep[u]<dep[v])swap(u,v);
        for(int i=m-1;i>=0;i--){
            if(dep[u]-(1<<i)>=dep[v]){
                u=par[i][u];
            }
        }
        if(u==v)return u;
        for(int i=m-1;i>=0;i--){
            if(par[i][u]!=par[i][v]){
                u=par[i][u];
                v=par[i][v];
            }
        }
        return par[0][u];
    }
    void add_q(int u,int v){
        int lc=lca(u,v);
        if(st[u]>st[v])swap(u,v);
        Query q;
        if(lc==u)q={st[u],st[v],lc};
        else q={en[u],st[v],lc};
        qs.push_back(q);
    }
    template<typename A,typename O>
    void build(const A &a,const O &out){
        int q=qs.size();
        int bs=n/min<int>(n,sqrt(q));
        vector<int>num(q);
        iota(begin(num),end(num),0);
        sort(begin(num),end(num),[&](int a,int b){
            int ab=qs[a].l/bs,bb=qs[b].l/bs;
            if(ab!=bb)return ab<bb;
            return qs[a].r<qs[b].r;
             });
        int l=0,r=-1;
        for(auto ind:num){
            while(l<qs[ind].l)a(dfsOrd[l++]);
            while(l>qs[ind].l)a(dfsOrd[--l]);
            while(r<qs[ind].r)a(dfsOrd[++r]);
            while(r>qs[ind].r)a(dfsOrd[r--]);
            if(st[qs[ind].lca]!=qs[ind].l)a(qs[ind].lca);
            out(ind);
            if(st[qs[ind].lca]!=qs[ind].l)a(qs[ind].lca);
        }
    }
};
