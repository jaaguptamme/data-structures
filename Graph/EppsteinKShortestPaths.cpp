#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef pair<ll,ll> pii;
struct Eppstein{
    const ll INF=LLONG_MAX/2;
    vector<ll> shortestPahts(vector<vector<pii>>&g,int src,int dst,int k){//k shortest paths from src to dst in directed g,
                                                                        //may contain self loops, double edges ect
        int n=g.size();
        vector<vector<pii>>revg(n);
        for(int i=0;i<n;i++){
            for(auto p:g[i])revg[p.first].push_back({i,p.second});
        }
        auto P=dijkstra(revg,dst);
        auto d=P.first;
        auto p=P.second;
        if(d[src]==INF)return {};
        vector<vector<int>>t(n);
        for(int u=0;u<n;u++){
            if(p[u]!=-1)t[p[u]].push_back(u);
        }
        vector<PersistentLeftistHeap*>juured(n,nullptr);
        vector<int>que;
        que.push_back(dst);
        for(int ps=0;ps<que.size();ps++){
            int u=que[ps];
            bool seenp=false;
            for(auto el:g[u]){
                int v=el.first;
                ll w=el.second;
                if(d[v]==INF)continue;
                ll c=w+d[v]-d[u];
                if(!seenp and v==p[u] and c==0){
                    seenp=true;
                    continue;
                }
                juured[u]=PersistentLeftistHeap::insert(juured[u],c,v);
            }
            for(auto v:t[u]){
                juured[v]=juured[u];
                que.push_back(v);
            }
        }
        vector<ll>res;
        res.push_back(d[src]);
        if(!juured[src])return res;
        typedef pair<ll,PersistentLeftistHeap*> ppi;
        priority_queue<ppi,vector<ppi>,greater<ppi>>pq;
        pq.push({d[src]+juured[src]->key,juured[src]});
        while(!pq.empty() and res.size()<k){
            auto P=pq.top();pq.pop();
            ll kaugus=P.first;
            PersistentLeftistHeap* juur=P.second;
            res.push_back(kaugus);
            if(juured[juur->value])
                pq.push({kaugus+juured[juur->value]->key,
                        juured[juur->value]});
            if(juur->left)pq.push({kaugus+juur->left->key-juur->key,juur->left});
            if(juur->right)pq.push({kaugus+juur->right->key-juur->key,juur->right});
        }
        return res;
    }
    pair<vector<ll>,vector<int>>dijkstra(vector<vector<pii>>&g,int src){//returns dist and parent to each node
        int n=g.size();
        vector<ll>d(n,INF);
        vector<int>p(n,-1);
        d[src]=0;
        priority_queue<pii,vector<pii>,greater<pii>>pq;
        pq.push({0,src});
        while(!pq.empty()){
            auto P=pq.top();pq.pop();
            auto du=P.first,u=P.second;
            if(du!=d[u])continue;
            for(auto &el:g[u]){
                ll v=el.first,w=el.second;
                if(du+w<d[v]){
                    d[v]=d[u]+w;
                    p[v]=u;
                    pq.push({d[v],v});
                }
            }
        }
        return make_pair(d,p);
    }
    struct PersistentLeftistHeap{
        int rank;
        ll key;//*Kaugus
        int value;//Tipu number
        PersistentLeftistHeap *left,*right;
        PersistentLeftistHeap(int rank,ll key,int value,PersistentLeftistHeap* left,PersistentLeftistHeap *right):
        rank(rank),key(key),value(value),left(left),right(right){}
        static PersistentLeftistHeap* insert(PersistentLeftistHeap *a,ll key,int value){
            if(!a or key<a->key)return new PersistentLeftistHeap(1,key,value,a,nullptr);
            PersistentLeftistHeap* l=a->left;
            PersistentLeftistHeap* r=insert(a->right,key,value);
            if(!l or r->rank>l->rank)swap(l,r);
            return new PersistentLeftistHeap(r?r->rank+1:1,a->key,a->value,l,r);
        }
    };
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,s,t,k;
    cin>>n>>m>>s>>t>>k;
    vector<vector<pii>>g(n);
    while(m--){
        int u,v,w;cin>>u>>v>>w;
        g[u].push_back({v,w});
    }
    Eppstein T;
    auto res=T.shortestPahts(g,s,t,k);
    while(res.size()<k)res.push_back(-1);
    for(auto el:res)cout<<el<<' ';
    return 0;
}
