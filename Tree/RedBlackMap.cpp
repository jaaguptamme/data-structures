#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,typename V>
class RBMap{
    struct Tipp{
        bool isBlack;
        T key;
        V val;
        Tipp *l,*r,*p;
        Tipp():isBlack(true){}
        Tipp(T &key,V val):key(key),val(val),l(nullptr),r(nullptr),p(nullptr){}
    };
    Tipp *Nil=new Tipp();
    Tipp* juur;

    void vasakPoore(Tipp *x){
        auto y=x->r;
        x->r=y->l;
        if(y->l!=Nil){
            y->l->p=x;
        }
        y->p=x->p;
        if(x->p==Nil){
            juur=y;
        }else if(x==x->p->l){
            x->p->l=y;
        }else x->p->r=y;
        y->l=x;
        x->p=y;
    }
    void paremPoore(Tipp *y){
        auto x=y->l;
        y->l=x->r;
        if(x->r!=Nil){
            x->r->p=y;
        }
        x->p=y->p;
        if(y->p==Nil){
            juur=x;
        }else if(y==y->p->r){
            y->p->r=x;
        }else y->p->l=x;
        x->r=y;
        y->p=x;
    }
    void insert(Tipp *z){
        auto x=juur;
        auto y=Nil;
        while(x!=Nil){
            y=x;
            if(z->key<x->key){
                x=x->l;
            }else x=x->r;
        }
        z->p=y;
        if(y==Nil)juur=z;
        else if(z->key<y->key)y->l=z;
        else y->r=z;
        z->l=Nil;
        z->r=Nil;
        z->isBlack=false;
        insertFixup(z);
    }
    void insertFixup(Tipp *z){
        while(!z->p->isBlack){
            if(z->p==z->p->p->l){
                auto y=z->p->p->r;
                if(!y->isBlack){
                    z->p->isBlack=true;
                    y->isBlack=true;
                    z->p->p->isBlack=false;
                    z=z->p->p;
                }else{
                    if(z==z->p->r){
                        z=z->p;
                        vasakPoore(z);
                    }
                    z->p->isBlack=true;
                    z->p->p->isBlack=false;
                    paremPoore(z->p->p);
                }
            }else{
                auto y=z->p->p->l;
                if(!y->isBlack){
                    z->p->isBlack=true;
                    y->isBlack=true;
                    z->p->p->isBlack=false;
                    z=z->p->p;
                }else{
                    if(z==z->p->l){
                        z=z->p;
                        paremPoore(z);
                    }
                    z->p->isBlack=true;
                    z->p->p->isBlack=false;
                    vasakPoore(z->p->p);
                }
            }
        }
        juur->isBlack=true;
    }
    void transplant(Tipp *u,Tipp *v){
        if(u->p==Nil)juur=v;
        else if(u==u->p->l)u->p->l=v;
        else u->p->r=v;
        v->p=u->p;
    }
    Tipp* min(Tipp *x){
        while(x->l!=Nil)x=x->l;
        return x;
    }
    void remove(Tipp *z){
        Tipp* y=z;
        auto ycol=y->isBlack;
        Tipp* x;
        if(z->l==Nil){
            x=z->r;
            transplant(z,z->r);
        }else if(z->r==Nil){
            x=z->l;
            transplant(z,z->l);
        }else{
            y=min(z->r);
            ycol=y->isBlack;
            x=y->r;
            if(y!=z->r){
                transplant(y,y->r);
                y->r=z->r;
                y->r->p=y;
            }else x->p=y;
            transplant(z,y);
            y->l=z->l;
            y->l->p=y;
            y->isBlack=z->isBlack;
        }
        if(ycol)deleteFixup(x);
    }
    void deleteFixup(Tipp* x){
        while(x!=juur&&x->isBlack){
            if(x==x->p->l){
                Tipp* w=x->p->r;
                if(!w->isBlack){
                    w->isBlack=true;
                    x->p->isBlack=false;
                    vasakPoore(x->p);
                    w=x->p->r;
                }
                if(w->l->isBlack&&w->r->isBlack){
                    w->isBlack=false;
                    x=x->p;
                }else{
                    if(w->r->isBlack){
                        w->l->isBlack=true;
                        w->isBlack=false;
                        paremPoore(w);
                        w=x->p->r;
                    }
                    w->isBlack=x->p->isBlack;
                    x->p->isBlack=true;
                    w->r->isBlack=true;
                    vasakPoore(x->p);
                    x=juur;
                }
            }else{
                Tipp* w=x->p->l;
                if(!w->isBlack){
                    w->isBlack=true;
                    x->p->isBlack=false;
                    paremPoore(x->p);
                    w=x->p->l;
                }
                if(w->l->isBlack&&w->r->isBlack){
                    w->isBlack=false;
                    x=x->p;
                }else{
                    if(w->l->isBlack){
                        w->l->isBlack=true;
                        w->isBlack=false;
                        vasakPoore(w);
                        w=x->p->l;
                    }
                    w->isBlack=x->p->isBlack;
                    x->p->isBlack=true;
                    w->l->isBlack=true;
                    paremPoore(x->p);
                    x=juur;
                }
            }
        }
        x->isBlack=true;
    }

public:
    void insert(T &key,V &val){
        auto pr=find(juur,key);
        if(pr!=Nil){
            pr->val=val;
            return;
        }
        Tipp* z=new Tipp(key,val);
        insert(z);
    }
    Tipp* find(Tipp *x,T &vl){
        if(x==Nil||vl==x->key)return x;
        if(vl<x->key)return find(x->l,vl);
        return find(x->r,vl);
    }
    V find(T& vl){
        auto e=find(juur,vl);
        if(e==Nil)return 0;
        return e->val;
    }
    void remove(T &vl){
        Tipp* z=find(juur,vl);
        if(z==Nil)return;
        remove(z);
    }
    RBMap(){
        juur=Nil;
    }
    void print(){
        print(juur);
        cout<<endl;
    }
    void print(Tipp *t,int dep=0){
        if(t==Nil)return;
        print(t->l,dep+1);
        cout<<t->key<<' ';
        print(t->r,dep+1);
    }
};
