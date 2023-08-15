#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef pair<ll,ll> pii;
const int N=200005;
struct Edge{
    int u,v;
    ll c;
    Edge():u(0),v(0),c(0){}
    Edge(int u,int v,ll c):u(u),v(v),c(c){}
};
struct DSU{
    vector<int>p,sz;
    DSU(int n){
        p.resize(n);
        sz.resize(n);
        for(int i=0;i<n;i++)p[i]=i;
    }
    int F(int u){
        if(u==p[u])return u;
        return p[u]=F(p[u]);
    }
    bool unite(int u,int v){
        u=F(u);
        v=F(v);
        if(u==v)return false;
        if(sz[u]>sz[v])swap(u,v);
        if(sz[u]==sz[v])sz[v]++;
        p[u]=v;
        return true;
    }
    void setPar(int u,int v){
        p[u]=v;
    }
    bool same_comp(int u,int v){
        return F(u)==F(v);
    }
};
template<typename T,typename L>//Edge, lazy type
struct SkewHeap{
    struct Tipp{
        Tipp* ch[2]={nullptr,nullptr};
        T voti;
        L lazy;
        Tipp(T voti, L lazy):voti(voti),lazy(lazy){}
    }*juur;
    SkewHeap():juur(nullptr){}
    void lukka(Tipp *t){
        t->voti.c+=t->lazy;
        if(t->ch[0])t->ch[0]->lazy+=t->lazy;
        if(t->ch[1])t->ch[1]->lazy+=t->lazy;
        t->lazy=0;
    }
    Tipp* uhenda(Tipp *a,Tipp *b){
        if(!a)return b;
        if(!b)return a;
        lukka(a);lukka(b);
        if(a->voti.c>b->voti.c)swap(a,b);
        a->ch[1]=uhenda(b,a->ch[1]);
        swap(a->ch[0],a->ch[1]);
        return a;
    }
    void lisa(T voti){
        Tipp *t=new Tipp(voti,0);
        juur=uhenda(juur,t);
    }
    void pop(){
        lukka(juur);
        juur=uhenda(juur->ch[0],juur->ch[1]);
    }
    T top(){
        lukka(juur);
        return juur->voti;
    }
    bool empty(){
        return !juur;
    }
    void lisa(L lazy){
        if(empty())return;
        juur->lazy+=lazy;
    }
    void uhenda(SkewHeap t){
        juur=uhenda(juur,t.juur);
    }
};
//0 indekseeritud
//kahe tipupaari vahel olgu max 1 serv
struct DirectedMST{
    int n;
    DirectedMST(int n):n(n){}
    vector<Edge>servad;
    void lisaServ(int s,int t,int c){
        servad.push_back({s,t,c});
    }
    pair<ll,vector<int>> lahenda(int juur){
        int N=2*n-1;
        DSU dsu(N);
        vector<int>u(N,-1),par(N,-1);
        Edge parEdge[N];
        vector<int>child[N];
        vector<SkewHeap<Edge,ll>>kuhjad(N);
        for(Edge& e:servad)kuhjad[e.v].lisa(e);
        for(int i=0;i<n;i++)kuhjad[(i+1)%n].lisa({i,(i+1)%n,LLONG_MAX/2});
        int pea=0;
        int esimeneVaba=n;
        while(!kuhjad[pea].empty()){
            auto e=kuhjad[pea].top();kuhjad[pea].pop();
            int nxHead=dsu.F(e.u);
            if(nxHead==pea)continue;
            u[pea]=nxHead;
            parEdge[pea]=e;
            if(u[nxHead]==-1)pea=nxHead;
            else{
                int j=nxHead;
                do{
                    kuhjad[j].lisa(-parEdge[j].c);
                    kuhjad[esimeneVaba].uhenda(kuhjad[j]);
                    child[esimeneVaba].push_back(j);
                    j=dsu.F(u[j]);
                }while(j!=nxHead);
                for(auto u:child[esimeneVaba])par[u]=esimeneVaba,dsu.setPar(u,esimeneVaba);
                pea=esimeneVaba++;
            }
        }
        vector<int>ulemus(N,-1);
        deque<int>q;q.push_back(juur);
        ll koguKaal=0;
        while(!q.empty()){
            int u=q.front();q.pop_front();
            while(par[u]!=-1){
                for(auto v:child[par[u]]){
                    if(v!=u){
                        ulemus[parEdge[v].v]=parEdge[v].u;
                        q.push_back(parEdge[v].v);
                        par[v]=-1;
                    }
                }
                u=par[u];
            }
        }
        for(auto &e:servad){
            if(ulemus[e.v]==e.u)koguKaal+=e.c;
        }
        ulemus[juur]=juur;ulemus.resize(n);
        return {koguKaal,ulemus};
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,s;
    cin>>n>>m>>s;
    DirectedMST t(n);
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        t.lisaServ(a,b,c);
    }
    auto P=t.lahenda(s);
    cout<<P.first<<'\n';
    for(auto &el:P.second)cout<<el<<' ';
    return 0;
}
