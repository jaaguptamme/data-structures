#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
struct SplayPuuList{
    struct SplayTipp{
        SplayTipp *l,*r,*p;
        int suurus;
        T val;
        SplayTipp(const T& val):l(nullptr),r(nullptr),p(nullptr),suurus(1),val(val){}
        void uuenda(){
            suurus=1;
            if(l)suurus+=l->suurus;
            if(r)suurus+=r->suurus;
        }
        int olek(){
            if(!p)return 0;
            if(p->l==this)return 1;
            return -1;
        }
        SplayTipp* splay(){
            while(p){
                int o=olek(),op=p->olek();
                if(op==0){
                    if(o==1)p->pp();
                    else p->vp();
                }else if(op==1){
                    if(o==1){
                        p->p->pp();
                        p->pp();
                    }else{
                        p->vp();
                        p->pp();
                    }
                }else{
                    if(o==1){
                        p->pp();
                        p->vp();
                    }else{
                        p->p->vp();
                        p->vp();
                    }
                }
            }
            return this;
        }
        void vp(){
            SplayTipp* tp=this->r;
            tp->p=this->p;
            if(tp->p){
                if(tp->p->l==this)tp->p->l=tp;
                else tp->p->r=tp;
            }
            this->r=tp->l;
            if(this->r)this->r->p=this;
            this->p=tp;
            tp->l=this;
            this->uuenda();
            tp->uuenda();
        }
        void pp(){
            SplayTipp* tp=this->l;
            tp->p=this->p;
            if(this->p){
                if(tp->p->r==this)tp->p->r=tp;
                else tp->p->l=tp;
            }
            this->l=tp->r;
            if(this->l)this->l->p=this;
            this->p=tp;
            tp->r=this;
            this->uuenda();
            tp->uuenda();
        }
    };
    SplayTipp* juur;
    SplayPuuList():juur(nullptr){}
    T saa(int indeks){
        splay(indeks);
        return juur->val;
    }
    void sea(int indeks,const T& val){
        splay(indeks);
        juur->val=val;
    }
    void splay(int indeks){
        SplayTipp* tp=this->juur;
        while(true){
            int vsuurus=(tp->l?tp->l->suurus:0);
            if(indeks<vsuurus)tp=tp->l;
            else if(indeks>vsuurus){
                tp=tp->r;
                indeks-=vsuurus+1;
            }else{
                this->juur=tp->splay();
                break;
            }
        }
    }
    SplayTipp* uhenda(SplayTipp* vas,SplayTipp* par){
        if(!vas)return par;
        if(!par)return vas;
        while(vas->r)vas=vas->r;
        vas=vas->splay();
        vas->r=par;
        par->p=vas;
        vas->uuenda();
        return vas;
    }
    pair<SplayTipp*,SplayTipp*> loika(int mitu){
        if(mitu==0)return {nullptr,this->juur};
        if(mitu==this->juur->suurus)return {this->juur,nullptr};
        this->splay(mitu);
        SplayTipp* vas=this->juur->l;
        SplayTipp* par=this->juur;
        vas->p=nullptr;
        par->l=nullptr;
        par->uuenda();
        return {vas,par};
    }
    void lisa(int ind,const T& val){
        SplayTipp *vas,*par;
        tie(vas,par)=loika(ind);
        SplayTipp* juur=new SplayTipp(val);
        this->juur=uhenda(vas,uhenda(juur,par));
    }
    void kustuta(int ind){
        splay(ind);
        SplayTipp* vas=this->juur->l;
        SplayTipp* par=this->juur->r;
        if(vas)vas->p=nullptr;
        if(par)par->p=nullptr;
        this->juur=uhenda(vas,par);
    }
    void prindi(SplayTipp* tipp){
        if(!tipp)return;
        prindi(tipp->l);
        cout<<tipp->val<<' ';
        prindi(tipp->r);
    }
    void prindi(){
        prindi(this->juur);
        cout<<endl;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*1000;
    SplayPuuList<int>T;
    for(int i=1;i<=N;i++){
        T.lisa(rand()%i,i);
    }
    for(int i=1;i<=N-100;i++)T.kustuta(0);
    T.prindi();
    for(int i=0;i<10;i++)T.sea(i,i);
    T.prindi();
    return 0;
}
