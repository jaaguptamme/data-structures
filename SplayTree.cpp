#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename K,typename V>
class SplayTree{
    class SplayNode{public:
        K voti;
        V vaartus;
        SplayNode* l;
        SplayNode* r;
        SplayNode* p;
        SplayNode(){
            this->l=this->r=this->p=NULL;
        }
        bool onLeht(){
            return (l==NULL)&&(r==NULL);
        }
    };
    SplayNode* juur;
    V otsi(SplayNode* tipp,K& voti){
        if(tipp==NULL){
            V vaartus;
            return vaartus;
        }
        if(tipp->voti==voti){
            splay(tipp);
            return tipp->vaartus;
        }
        if(tipp->l==NULL && voti<tipp->voti){
            splay(tipp);
            V vaartus;
            return vaartus;
        }
        if(tipp->r==NULL && voti>tipp->voti){
            splay(tipp);
            V vaartus;
            return vaartus;
        }
        if(voti<tipp->voti)return otsi(tipp->l,voti);
        return otsi(tipp->r,voti);
    }
    void kustuta(SplayNode* tipp, K& voti){
        if((tipp==NULL)||(tipp->l==NULL && voti<tipp->voti)||(tipp->r==NULL && voti>tipp->voti))splay(tipp);
        else if(voti>tipp->voti)kustuta(tipp->r,voti);
        else if(voti<tipp->voti)kustuta(tipp->l,voti);
        else if(tipp->onLeht()){
            auto ulem=tipp->p;
            delete tipp;
            tipp=nullptr;
            splay(ulem);
        }else if(tipp->l==NULL || tipp->r==NULL){
            if(tipp->l==NULL){
                auto kustutada=tipp;
                auto ulem=tipp->p;
                tipp=tipp->r;
                tipp->p=ulem;
                splay(tipp->p);
                delete kustutada;
            }else{
                auto kustutada=tipp;
                auto ulem=tipp->p;
                tipp=tipp->l;
                tipp->p=ulem;
                splay(tipp->p);
                delete kustutada;
            }
        }else{
            auto kustutada=tipp->r;
            while(kustutada->l!=NULL)kustutada=kustutada->l;
            tipp->voti=kustutada->voti;
            tipp->vaartus=kustutada->vaartus;
            kustuta(tipp->r,tipp->voti);
        }
    }
    void insert(SplayNode* tipp,K& voti,V& vaartus){
        if(tipp==NULL){
            juur=new SplayNode();
            juur->voti=voti;
            juur->vaartus=vaartus;
        }else if(tipp->l==NULL && tipp->voti>voti){
            tipp->l=new SplayNode();
            tipp->l->voti=voti;
            tipp->l->vaartus=vaartus;
            tipp->l->p=tipp;
            splay(tipp->l);
        }else if(tipp->r==NULL && tipp->voti<voti){
            tipp->r=new SplayNode();
            tipp->r->voti=voti;
            tipp->r->vaartus=vaartus;
            tipp->r->p=tipp;
            splay(tipp->r);
        }else if(tipp->voti>voti)insert(tipp->l,voti,vaartus);
        else if(tipp->voti<voti)insert(tipp->r,voti,vaartus);
        else{
            tipp->vaartus=vaartus;
            splay(tipp);
        }
    }
    SplayNode* parempoore(SplayNode* tipp){
        auto y=tipp;
        auto yp=tipp->p;
        auto x=y->l;
        auto T2=x->r;
        x->r=y;
        y->p=x;
        y->l=T2;
        if(T2!=NULL)
            T2->p=y;
        x->p=yp;
        if(x->p!=NULL){
            if(x->p->l==y)x->p->l=x;
            else x->p->r=x;
        }
        return x;
    }
     SplayNode* vasakpoore(SplayNode* tipp){
        auto x=tipp;
        auto xp=tipp->p;
        auto y=x->r;
        auto T2=y->l;
        y->l=x;
        x->p=y;
        x->r=T2;
        if(T2!=NULL)
            T2->p=x;
        y->p=xp;
        if(y->p!=NULL){
            if(y->p->l==x)y->p->l=y;
            else y->p->r=y;
        }
        return y;
    }
    void splay(SplayNode* tipp){
        if(tipp==juur||tipp==NULL)return;
        else if(tipp->p==juur){
            if(tipp->p->l==tipp)juur=parempoore(juur);
            else juur=vasakpoore(juur);
        }else if(tipp->p->l==tipp && tipp->p->p->l==tipp->p){
            if(tipp->p->p==juur){
                juur=parempoore(juur);
                juur=parempoore(juur);
            }else{
                tipp->p=parempoore(tipp->p->p);
                tipp=parempoore(tipp->p);
                splay(tipp);
            }
        }else if(tipp->p->r==tipp && tipp->p->p->r==tipp->p){
            if(tipp->p->p==juur){
                juur=vasakpoore(juur);
                juur=vasakpoore(juur);
            }else{
                tipp->p=vasakpoore(tipp->p->p);
                tipp=vasakpoore(tipp->p);
                splay(tipp);
            }
        }else if(tipp->p->r==tipp&&tipp->p->p->l==tipp->p){
            tipp=vasakpoore(tipp->p);
            if(tipp->p==juur)juur=parempoore(juur);
            else{
                tipp=parempoore(tipp->p);
                splay(tipp);
            }
        }else if(tipp->p->l==tipp && tipp->p->p->r==tipp->p){
            tipp=parempoore(tipp->p);
            if(tipp->p==juur)juur=vasakpoore(juur);
            else{
                tipp=vasakpoore(tipp->p);
                splay(tipp);
            }
        }
    }
    void prindi(SplayNode* tipp){
        if(tipp==NULL)return;
        cout<<tipp->voti<<' '<<tipp->vaartus<<endl;
        prindi(tipp->l);
        prindi(tipp->r);
    }
public:
    SplayTree(){
        juur=NULL;
    }
    void prindi(){
        prindi(juur);
    }
    void insert(K voti,V vaartus){
        insert(juur,voti,vaartus);
    }
    void kustuta(K voti){
        kustuta(juur,voti);
    }
    V otsi(K voti){
        return otsi(juur,voti);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*100;
    SplayTree<int,int>t;
    for(int i=1;i<=N;i++){
        t.insert(rand(),i);
    }
    /*for(int i=1;i<=N;i++){
        t.kustuta(rand());
    }*/
    t.prindi();
    return 0;
}
