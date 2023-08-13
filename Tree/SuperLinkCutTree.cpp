#include <bits/stdc++.h>
//source:https://ei1333.github.io/library/structure/develop/super-link-cut-tree.hpp
typedef long long ll;
using namespace std;
template<typename LInfo,typename Lazy>
struct SplayTree{
    struct Tipp{
        Tipp *l,*r,*p;
        LInfo info;
        Lazy lazy,lbuf;
        Tipp(LInfo &info):info(info),l(nullptr),r(nullptr),p(nullptr),lazy(Lazy()),lbuf(Lazy()){}
    };
    const LInfo e;
    SplayTree():e(LInfo()){}
    using TP=Tipp*;
    void parempoore(TP t){
        TP x=t->p,y=x->p;
        alla(x),alla(t);
        if((x->l=t->r))t->r->p=x;
        t->r=x,x->p=t;
        uuenda(x),uuenda(t);
        if((t->p=y)){
            if(y->l==x)y->l=t;
            if(y->r==x)y->r=t;
        }
    }
    void vasakpoore(TP t){
        TP x=t->p,y=x->p;
        alla(x),alla(t);
        if((x->r=t->l))t->l->p=x;
        t->l=x,x->p=t;
        uuenda(x),uuenda(t);
        if((t->p=y)){
            if(y->l==x)y->l=t;
            if(y->r==x)y->r=t;
        }
    }
    LInfo saa_info(TP t){
        return t?t->info:e;
    }
    void uuenda(TP t){
        t->info.update(saa_info(t->l),saa_info(t->r));
    }
    TP saa_parem(TP t){
        while(t->r)t=t->r;
        return t;
    }
    TP alloc(LInfo &v){
        auto t=new Tipp(v);
        uuenda(t);
        return t;
    }
    void lukka(TP t,Lazy &lazy){
        t->info.propagate(lazy);
        t->lbuf.propagate(lazy);
        t->lazy.propagate(lazy);
    }
    void alla(TP t){
        if(t->l)lukka(t->l,t->lazy);
        if(t->r)lukka(t->r,t->lazy);
        t->lazy=Lazy();
    }
    void splay(TP t){
        alla(t);
        while(t->p){
            TP q=t->p;
            if(!q->p){
                if(q->l==t)parempoore(t);
                else vasakpoore(t);
            }else{
                TP r=q->p;
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
    TP insert(TP t,LInfo v){
        if(!t){
            t=alloc(v);
            return t;
        }else{
            TP cur=saa_parem(t),z=alloc(v);
            splay(cur);
            z->p=cur;
            cur->r=z;
            uuenda(cur);
            splay(z);
            return z;
        }
    }
    TP erase(TP t){
        splay(t);
        TP x=t->l,y=t->r;
        delete t;
        if(!x){
            t=y;
            if(t)t->p=nullptr;
        }else if(!y){
            t=x;
            t->p=nullptr;
        }else{
            x->p=nullptr;
            t=saa_parem(x);
            splay(t);
            t->r=y;
            y->p=t;
            uuenda(t);
        }
        return t;
    }
};
template<template<typename,typename> typename _Info,template<typename> typename _LInfo,typename Lazy>
struct SuperLinkCutTree{
    using LInfo=_LInfo<Lazy>;
    using Info=_Info<LInfo,Lazy>;
    struct Tipp{
        Tipp *l,*r,*p;
        Info info;
        typename SplayTree<LInfo,Lazy>::Tipp *light,*belong;
        bool rev;
        Lazy hlazy,llazy;
        bool is_root(){
            return !p or (p->l!=this and p->r!=this);
        }
        Tipp(Info &info):info(info),l(nullptr),
        r(nullptr),p(nullptr),rev(false),light(nullptr),
        belong(nullptr),hlazy(Lazy()),llazy(Lazy()){}
    };
    using TP=Tipp*;
    SplayTree<LInfo,Lazy>splay_tree;
    const Info e;
    SuperLinkCutTree():e{Info()},splay_tree{}{}
    void toggle(TP t){
        swap(t->l,t->r);
        t->info.toggle();
        t->rev^= true;
    }
    void parempoore(TP t){
        TP x=t->p,y=x->p;
        alla(x),alla(t);
        if((x->l=t->r))t->r->p=x;
        t->r=x,x->p=t;
        uuenda(x),uuenda(t);
        if((t->p=y)){
            if(y->l==x)y->l=t;
            if(y->r==x)y->r=t;
        }
    }
    void vasakpoore(TP t){
        TP x=t->p,y=x->p;
        alla(x),alla(t);
        if((x->r=t->l))t->l->p=x;
        t->l=x,x->p=t;
        uuenda(x),uuenda(t);
        if((t->p=y)){
            if(y->l==x)y->l=t;
            if(y->r==x)y->r=t;
        }
    }
    void propagate_heavy(TP t,Lazy &hlazy){
        t->hlazy.propagate(hlazy);
        t->info.propagate(hlazy);
    }
    void propagate_light(TP t,Lazy &llazy){
        t->llazy.propagate(llazy);
        t->info.propagate_light(llazy);
    }
    void propagate_all(TP t,Lazy &lazy){
        propagate_heavy(t,lazy);
        propagate_light(t,lazy);
    }
    void alla(TP t){
        if(t->rev){
            if(t->l)toggle(t->l);
            if(t->r)toggle(t->r);
            t->rev=false;
        }
        {
            if(t->l){
                propagate_heavy(t->l,t->hlazy);
                propagate_light(t->l,t->llazy);
            }
            if(t->r){
                propagate_heavy(t->r,t->hlazy);
                propagate_light(t->r,t->llazy);
            }
            if(t->light){
                splay_tree.lukka(t->light,t->llazy);
            }
            t->hlazy=Lazy();
            t->llazy=Lazy();
        }
    }
    void push_rev(TP t){
        if(t->rev){
            if(t->l)toggle(t->l);
            if(t->r)toggle(t->r);
            t->rev=false;
        }
    }
    const Info saa_info(TP t){
        return t?t->info:e;
    }
    void uuenda(TP t){
        t->info.update(saa_info(t->l),saa_info(t->r),splay_tree.saa_info(t->light));
    }
    void splay(TP t){
        alla(t);
        {
            TP rot=t;
            while(!rot->is_root())rot=rot->p;
            t->belong=rot->belong;
            if(t!=rot)rot->belong=nullptr;
        }
        while(!t->is_root()){
             TP q=t->p;
              if(q->is_root()) {
                push_rev(q),push_rev(t);
                if(q->l==t)parempoore(t);
                else vasakpoore(t);
              } else {
                    TP r=q->p;
                    push_rev(r),push_rev(q),push_rev(t);
                    if(r->l==q) {
                      if(q->l==t)parempoore(q),parempoore(t);
                      else vasakpoore(t),parempoore(t);
                    } else {
                      if(q->r==t)vasakpoore(q),vasakpoore(t);
                      else parempoore(t),vasakpoore(t);
                    }
                  }
        }
    }
    TP expose(TP t){
        TP rp=nullptr;
        for(TP cur=t;cur;cur=cur->p){
            splay(cur);
            if(cur->r){
                cur->light=splay_tree.insert(cur->light,cur->r->info.link());
                cur->r->belong=cur->light;
            }
            cur->r=rp;
            if(cur->r){
                splay_tree.splay(cur->r->belong);
                propagate_all(cur->r,cur->r->belong->lbuf);
                alla(cur->r);
                cur->light=splay_tree.erase(cur->r->belong);
            }
            uuenda(cur);
            rp=cur;
        }
        splay(t);
        return rp;
    }
    void link(TP child,TP parent){
        expose(parent);
        expose(child);
        child->p=parent;
        parent->r=child;
        uuenda(parent);
    }
    void cut(TP child){
        expose(child);
        TP parent=child->l;
        child->l=nullptr;
        parent->p=nullptr;
        uuenda(child);
    }
    void evert(TP t){
        expose(t);
        toggle(t);
        alla(t);
    }
    TP alloc(Info &info){
        TP t=new Tipp(info);
        uuenda(t);
        return t;
    }
    bool is_connected(TP u,TP v){
        expose(u),expose(v);
        return u==v or u->p;
    }
    vector<TP>build(vector<Info>&vec){
        vector<TP>tipud(vec.size());
        for(int i=0;i<vec.size();i++)tipud[i]=alloc(vec[i]);
        return tipud;
    }
    TP lca(TP u,TP v){
        if(!is_connected(u,v))return nullptr;
        expose(v);
        return expose(v);
    }
    void set_key(TP t,Info v){
        expose(t);
        t->info=move(v);
        uuenda(t);
    }
    void set_propagate_path(TP t,Lazy &lazy){
        expose(t);
        propagate_heavy(t,lazy);
        alla(t);
        uuenda(t);
    }
    void set_propagate_path(TP u,TP v,Lazy &lazy){
        evert(u);
        set_propagate_path(v,lazy);
    }
    void set_propagate_all(TP t,Lazy& lazy){
        expose(t);
        propagate_all(t,lazy);
        alla(t);
        uuenda(t);
    }
    void set_propagate_subtree(TP t,Lazy &lazy){
        expose(t);
        TP l=t->l;
        t->l=nullptr;
        propagate_all(t,lazy);
        alla(t);
        t->l=l;
        uuenda(t);
    }
    Info query(TP u){
        expose(u);
        return saa_info(u);
    }
    Info query_path(TP u,TP v){
        evert(u);
        expose(v);
        return saa_info(v);
    }
    Info query_subtree(TP u){
        expose(u);
        TP l=u->l;
        u->l=nullptr;
        uuenda(u);
        auto vas=u->info;
        u->l=l;
        uuenda(u);
        return vas;
    }
};
using T=ll;
struct Lazy{
    Lazy(){}//Tühi element
    Lazy(T v){}//Algväärtus
    void propagate(const Lazy &p){}//Alla
};
template<typename Lazy>//Kerge serv
struct LInfo{
    LInfo(){}
    LInfo(T v){}
    void update(const LInfo &l,const LInfo &r){}//l,r on alluvad
    void propagate(const Lazy &p){}//lazy propagate
};
template<typename LInfo,typename Lazy>
struct Info{//Raske serv
    T v;
    T sum;
    Info():sum(0){}
    Info(T v):v{v}{}
    void toggle(){}//tagurpidi keeramine
    void update(const Info &p,const Info &c,const LInfo &l){//p vanem, c on raske laps, l teine laps
        sum=p.sum+v+c.sum;
    }
    LInfo link(){return LInfo();}//ühenda vanem heleda servaga
    void propagate(const Lazy &p){}//lazy propagate
    void propagate_light(const Lazy &p){}//lazy porpagate kerge serva jaoks, vaja kui nii tee kui alampuu päring
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    SuperLinkCutTree<Info,LInfo,Lazy> lct;
    vector<Info<LInfo<Lazy>,Lazy>>a(n);
    for(int i=0;i<n;i++){
        ll x;
        cin>>x;
        a[i].v=x;
    }
    auto vs=lct.build(a);
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        lct.evert(vs[a]);
        lct.link(vs[a],vs[b]);
    }
    while(q--){
        int t;cin>>t;
        if(t==0){
            int u,v,w,x;cin>>u>>v>>w>>x;
            lct.evert(vs[u]);
            lct.cut(vs[v]);
            lct.evert(vs[w]);
            lct.link(vs[w],vs[x]);
        }else if(t==1){
            int p;T x;
            cin>>p>>x;
            lct.set_key(vs[p],lct.saa_info(vs[p]).v+x);
        }else{
            int u,v;
            cin>>u>>v;
            cout<<lct.query_path(vs[u],vs[v]).sum<<'\n';
        }
    }
    return 0;
}
