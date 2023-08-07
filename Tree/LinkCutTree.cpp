#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,typename F,typename S>//F on assotsiatiinve operatsioon, S on ümberpööramise funktsioon
struct LinkCutTree{
    F f;
    S s;
    struct Tipp{
        Tipp *l,*r,*p;
        T voti,summa;
        bool rev;
        int suurus;
        Tipp(const T &v):voti(v),summa(v),suurus(1),rev(false),l(nullptr),r(nullptr),p(nullptr){}
        bool on_juur(){
            return  !p or (p->l!=this && p->r!=this);
        }
    };
    using TP=Tipp*;
    TP uuenda(TP t){
        t->suurus=1;
        t->summa=t->voti;
        if(t->l)t->suurus+=t->l->suurus,t->summa=f(t->l->summa,t->summa);
        if(t->r)t->suurus+=t->r->suurus,t->summa=f(t->summa,t->r->summa);
        return t;
    }
    void parempoore(TP t){
        TP x=t->p,y=x->p;
        if((x->l=t->r))t->r->p=x;
        t->r=x,x->p=t;
        uuenda(x),uuenda(t);
        if((t->p=y)){
            if(y->l==x)y->l=t;
            if(y->r==x)y->r=t;
            uuenda(y);
        }
    }
    void vasakpoore(TP t){
        TP x=t->p,y=x->p;
        if((x->r=t->l))t->l->p=x;
        t->l=x,x->p=t;
        uuenda(x),uuenda(t);
        if((t->p=y)){
            if(y->l==x)y->l=t;
            if(y->r==x)y->r=t;
            uuenda(y);
        }
    }
    void toggle(TP t){
        swap(t->l,t->r);
        t->summa=s(t->summa);
        t->rev ^= true;
    }
    void alla(TP t){
        if(t->rev){
            if(t->l)toggle(t->l);
            if(t->r)toggle(t->r);
            t->rev=false;
        }
    }
    void splay(TP t){
        alla(t);
        while(!t->on_juur()){
            TP q=t->p;
            if(q->on_juur()){
                alla(q),alla(t);
                if(q->l==t)parempoore(t);
                else vasakpoore(t);
            }else{
                TP r=q->p;
                alla(r),alla(q),alla(t);
                if(r->l==q){
                    if(q->l==t)parempoore(q),parempoore(t);
                    else vasakpoore(t),parempoore(t);
                }else{
                    if(q->r==t)vasakpoore(q),vasakpoore(t);
                    else parempoore(t),vasakpoore(t);
                }
            }
        }
    }
    LinkCutTree(const F &f,const S &s):f(f),s(s){}
    TP alloc(const T&v=T()){
        return new Tipp(v);
    }
    vector<TP> build(vector<T>&vec){
        vector<TP>tipud(vec.size());
        for(int i=0;i<vec.size();i++)tipud[i]=alloc(vec[i]);
        return tipud;
    }
    TP expose(TP t){
        TP rp=nullptr;
        for(TP cur=t;cur;cur=cur->p){
            splay(cur);
            cur->r=rp;
            uuenda(cur);
            rp=cur;
        }
        splay(t);
        return rp;
    }
    void evert(TP t){
        expose(t);
        toggle(t);
        alla(t);
    }
    void link(TP child,TP parent){
        if(is_connected(child,parent)){
            throw runtime_error("child and par must be from diff componenets");
        }
        if(child->l){
            throw runtime_error("child must be root");
        }
        child->p=parent;
        parent->r=child;
        uuenda(parent);
    }
    void cut(TP child){
        expose(child);
        TP parent=child->l;
        if(!parent)throw runtime_error("child must not be root");
        child->l=nullptr;
        parent->p=nullptr;
        uuenda(child);
    }
    bool is_connected(TP u,TP v){
        expose(u),expose(v);
        return u==v or u->p;
    }
    TP lca(TP u,TP v){
        if(!is_connected(u,v))return nullptr;
        expose(u);
        return expose(v);
    }
    TP get_kth(TP x,int k){
        expose(x);
        while(x){
            alla(x);
            if(x->r&&x->r->suurus>k){
                x=x->r;
            }else{
                if(x->r)k-=x->r->suurus;
                if(k==0){
                    splay(x);
                    return x;
                }
                k-=1;
                x=x->l;
            }
        }
        return nullptr;
    }
    const T &query(TP u){
        expose(u);
        return u->summa;
    }
    const T &query(TP u,TP v){
        evert(u);
        return query(v);
    }
    void set_key(TP t,T v){
        expose(t);
        t->voti=v;
        uuenda(t);
    }
};
template< typename T, typename F, typename S >
LinkCutTree< T, F, S > get_link_cut_tree(const F &f, const S &s) {
  return {f, s};
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    auto liida=[](ll a,ll b){return a+b;};
    auto poora=[](ll a){return a;};
    auto lct=get_link_cut_tree<ll>(liida,poora);
    vector<ll>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    auto vs=lct.build(a);
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        lct.evert(vs[a]);
        lct.link(vs[a],vs[b]);
    }
    while(q--){
        int t;cin>>t;
        if(t==0){
            int u,v,w,x;
            cin>>u>>v>>w>>x;
            lct.evert(vs[u]);
            lct.cut(vs[v]);
            lct.evert(vs[w]);
            lct.link(vs[w],vs[x]);
        }else if(t==1){
            int p,x;
            cin>>p>>x;
            lct.set_key(vs[p],vs[p]->voti+x);
        }else{
            int u,v;
            cin>>u>>v;
            cout<<lct.query(vs[u],vs[v])<<'\n';
        }
    }
    return 0;
}
