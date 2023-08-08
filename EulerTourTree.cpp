#include <bits/stdc++.h>
//source https://sotanishy.github.io/cp-library-cpp/tree/euler_tour_tree.cpp
typedef long long ll;
using namespace std;
template<typename M,typename O,typename M::T (*act)(typename M::T,typename O::T)>
class EulerTourTree{
    public:
    using T=typename M::T;
    using E=typename O::T;
    struct Tipp{
        Tipp* ch[2]={nullptr,nullptr};
        Tipp* p=nullptr;
        int from,to,sz;
        T val=M::id(),sum=M::id();
        E lazy=O::id();
        Tipp(int from,int to):from(from),to(to),sz(from==to){}
    };
    using TP=Tipp*;
    EulerTourTree(int n){
        ptr.resize(n);
        for(int i=0;i<n;i++)ptr[i][i]=new Tipp(i,i);
    }
    vector<unordered_map<int,TP>>ptr;
    void link(int u,int v){
        assert(!same(u,v));
        auto tu=reroot(get_node(u,u));
        auto tv=reroot(get_node(v,v));
        join(join(tu,get_node(u,v)),join(tv,get_node(v,u)));
    }
    void cut(int u,int v){
        assert(ptr[u].find(v)!=ptr[u].end());
        Tipp *a,*b,*c;
        tie(a,b,c)=split(get_node(u,v),get_node(v,u));
        join(a,c);
        ptr[u].erase(v);
        ptr[v].erase(u);
    }
    bool same(int u,int v){
        return same(get_node(u,u),get_node(v,v));
    }
    T get(int v){
        auto t=get_node(v,v);
        splay(t);
        return t->val;
    }
    void update(int v,T x){
        auto t=get_node(v,v);
        splay(t);
        t->val=x;
        recalc(t);
    }
    void update(int v,int p,E& x){
        cut(p,v);
        auto t=get_node(v,v);
        splay(t);
        t->lazy=O::op(t->lazy,x);
        link(p,v);
    }
    T fold(int v,int p=-1){
        if(p!=-1)cut(p,v);
        auto t=get_node(v,v);
        splay(t);
        T ret=t->sum;
        if(p!=-1)link(p,v);
        return ret;
    }
    TP get_node(int u,int v){
        if(ptr[u].find(v)==ptr[u].end())ptr[u][v]=new Tipp(u,v);
        return ptr[u][v];
    }
    static TP root(TP t){
        if(!t)return nullptr;
        while(t->p)t=t->p;
        return t;
    }
    static bool same(TP s,TP t){
        if(s)splay(s);
        if(t)splay(t);
        return root(s)==root(t);
    }
    static TP reroot(TP t){
        auto s=split(t);
        return join(s.second,s.first);
    }
    static int size(TP t){
        return t?t->sz:0;
    }
    static TP recalc(TP t){
        if(!t)return t;
        t->sz=size(t->ch[0])+(t->from==t->to)+size(t->ch[1]);
        t->sum=t->val;
        if(t->ch[0])t->sum=M::op(t->ch[0]->sum,t->sum);
        if(t->ch[1])t->sum=M::op(t->sum,t->ch[1]->sum);
        return t;
    }
    static void push(TP t){
        if(t->lazy!=O::id()){
            t->val=act(t->val,t->lazy);
            if(t->ch[0]){
                t->ch[0]->lazy=O::op(t->ch[0]->lazy,t->lazy);
                t->ch[0]->sum=act(t->ch[0]->sum,t->lazy);
            }
            if(t->ch[1]){
                t->ch[1]->lazy=O::op(t->ch[1]->lazy,t->lazy);
                t->ch[1]->sum=act(t->ch[1]->sum,t->lazy);
            }
            t->lazy=O::id();
        }
        recalc(t);
    }
    static TP join(TP l,TP r){
        if(!l)return r;
        if(!r)return l;
        while(l->ch[1])l=l->ch[1];
        splay(l);
        l->ch[1]=r;
        r->p=l;
        return recalc(l);
    }
    static pair<TP,TP> split(TP t){
        splay(t);
        auto s=t->ch[0];
        t->ch[0]=nullptr;
        if(s)s->p=nullptr;
        return {s,recalc(t)};
    }
    static pair<TP,TP> split2(TP t){
        splay(t);
        auto l=t->ch[0];
        auto r=t->ch[1];
        t->ch[0]=nullptr;
        if(l)l->p=nullptr;
        t->ch[1]=nullptr;
        if(r)r->p=nullptr;
        return {l,r};
    }
    static tuple<TP,TP,TP> split(TP s,TP t){
        TP a,b,c,d;
        tie(a,b)=split2(s);
        if(same(a,t)){
            tie(c,d)=split2(t);
            return {c,d,b};
        }else{
            tie(c,d)=split2(t);
            return {a,c,d};
        }
    }
    static void rotate(TP t,bool b){
        TP p=t->p,g=p->p;
        p->ch[1-b]=t->ch[b];
        if(p->ch[1-b])t->ch[b]->p=p;
        t->ch[b]=p;
        p->p=t;
        recalc(p);
        recalc(t);
        t->p=g;
        if(t->p){
            if(g->ch[0]==p)g->ch[0]=t;
            else g->ch[1]=t;
            recalc(g);
        }
    }
    static void splay(TP t){
        push(t);
        while(t->p){
            auto p=t->p,g=p->p;
            if(!g){
                push(p);
                push(t);
                rotate(t,p->ch[0]==t);
            }else{
                push(g);
                push(p);
                push(t);
                bool b=g->ch[0]==p;
                if(p->ch[1-b]==t){
                    rotate(p,b);
                    rotate(t,b);
                }else{
                    rotate(t,1-b);
                    rotate(t,b);
                }
            }
        }
    }
};
struct Add{
    using T=ll;
    static T id(){return 0;}
    static T op(T a,T b){return a+b;}
};
ll sum(ll a,ll b){return a+b;}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    EulerTourTree<Add,Add,sum>ett(n);
    for(int i=0;i<n;i++){
        int a;cin>>a;
        ett.update(i,a);
    }
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        ett.link(u,v);
    }
    while(q--){
        int t;
        cin>>t;
        if(t==0){
            int u,v,w,x;
            cin>>u>>v>>w>>x;
            ett.cut(u,v);
            ett.link(w,x);
        }else if(t==1){
            int p,x;cin>>p>>x;
            ett.update(p,ett.get(p)+x);
        }else{
            int v,p;
            cin>>v>>p;
            cout<<ett.fold(v,p)<<'\n';
        }
    }
    return 0;
}
