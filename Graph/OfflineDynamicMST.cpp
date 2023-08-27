//source: https://codeforces.com/blog/entry/105192
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct DSU{
    vector<int>sz,pr;
    int cmps;
    void reset(int n){
        fill(sz.begin(),sz.begin()+n,1);
        iota(pr.begin(),pr.begin()+n,0);
        cmps=n;
    }
    DSU(int n):sz(n),pr(n){reset(n);}
    bool unite(int u,int v){
        u=F(u),v=F(v);
        if(u==v)return false;
        cmps--;
        if(sz[u]<sz[v])swap(u,v);
        sz[u]+=sz[v];
        pr[v]=u;
        return true;
    }
    int F(int u){
        return u==pr[u]?u:pr[u]=F(pr[u]);
    }
};
template<typename EW>//Edge weight type
struct OfflineDynamicMST{
    struct Edge{
        int l,r;//Times active,[l,r)
        int u,v;//Edge points, undirected
        EW w;//Edge weight
        bool operator<(const Edge& e){return w<e.w;}
    };
    vector<Edge>changes;
    vector<tuple<int,int,EW>>activeEdges;
    vector<int>lastChanged,id;
    vector<EW> ans;
    int totalN,queryNum;
    DSU dsu,dsu2;
    OfflineDynamicMST(vector<tuple<int,int,EW>> startEdges,int n):activeEdges(startEdges),lastChanged(startEdges.size()),
    totalN(n),dsu(n),dsu2(n),id(n),queryNum(0){}
    void update(int i,EW x){
        queryNum++;
        auto& [u,v,w]=activeEdges[i];
        changes.push_back({lastChanged[i],queryNum,u,v,w});
        lastChanged[i]=queryNum;
        w=x;
    }
    void solve(int l,int r,vector<Edge>es,int n,EW cost=0){
        es.erase(stable_partition(begin(es),end(es),[&](const Edge& e) {return !(e.r<=l or r<=e.l);}),es.end());
        dsu.reset(n);dsu2.reset(n);
        for(auto& e:es){//partially overlaping
            if(l<e.l or e.r<r)dsu.unite(e.u,e.v);
        }
        for(auto& e:es){
            if(e.l<=l and r<=e.r){//fully overlapping
                if(dsu.unite(e.u,e.v)){
                    cost+=e.w;
                    dsu2.unite(e.u,e.v);
                }
            }
        }
        if(l+1==r){
            ans[l]=cost;
            return;
        }
        int cnt=0;
        for(int i=0;i<n;i++){
            if(dsu2.F(i)==i)id[i]=cnt++;
        }
        dsu.reset(cnt);
        for(auto& e:es){
            e.u=id[dsu2.F(e.u)],e.v=id[dsu2.F(e.v)];
            if(e.l<=l and r<=e.r){
                if(!dsu.unite(e.u,e.v))e.l=INT_MAX,e.r=INT_MIN;//useless edge
            }
        }
        int m=(l+r)/2;
        solve(l,m,es,cnt,cost);
        solve(m,r,es,cnt,cost);
    }
    vector<EW> run(){
        int m=activeEdges.size();
        queryNum++;
        for(int i=0;i<m;i++){
            auto& [u,v,w]=activeEdges[i];
            changes.push_back({lastChanged[i],queryNum,u,v,w});
        }
        sort(begin(changes),end(changes));
        ans.resize(queryNum);
        solve(0,queryNum,changes,totalN);
        return ans;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,q;
    cin>>n>>m>>q;
    vector<tuple<int,int,ll>>es(m);
    for(auto& [u,v,w]:es){
        cin>>u>>v>>w;u--;v--;
    }
    OfflineDynamicMST<ll>mst(es,n);
    for(int i=0;i<q;i++){
        int k;
        ll d;
        cin>>k>>d;k--;
        mst.update(k,d);
    }
    auto res=mst.run();
    for(int i=1;i<=q;i++)cout<<res[i]<<'\n';
    return 0;
}
