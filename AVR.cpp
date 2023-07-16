#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,typename V>
class AVL{
    public:
    class AVL_node{
        public:
        AVL_node* l;
        AVL_node* r;
        T info;
        int korgus;
        int suurus;
        V vaartus;
        V summa,maksimum;
        AVL_node(T& info,V& vaartus){
            this->info=info;
            this->korgus=1;
            this->suurus=1;
            this->l=NULL;
            this->r=NULL;
            this->vaartus=this->summa=this->maksimum=vaartus;
        }
    };
    void uuendakorgus(AVL_node* RT){
         RT->korgus=1+max(korgus(RT->l),korgus(RT->r));
         RT->suurus=1+suurus(RT->l)+suurus(RT->r);
         RT->summa=RT->vaartus;
         if(RT->l!=NULL)RT->summa+=RT->l->summa;
         if(RT->r!=NULL)RT->summa+=RT->r->summa;
    }

    int suurus(AVL_node* RT){
        if(RT==NULL)return 0;
        return RT->suurus;
    }

    int korgus(AVL_node* RT){
        if(RT==NULL)return 0;
        return RT->korgus;
    }

    AVL_node* root=0;

    AVL_node* _insert(AVL_node* root,T& info,V& vaartus){
        if(root==NULL)return new AVL_node(info,vaartus);
        if(info<root->info)root->l=_insert(root->l,info,vaartus);
        else root->r=_insert(root->r,info,vaartus);
        return balance(root);
    }

    AVL_node* minimaalneVaartus(AVL_node* RT){
        AVL_node* u=RT;
        while(u->l!=NULL)u=u->l;
        return u;
    }

    AVL_node* _erase(AVL_node* root,T& info){
        if(root==NULL)return NULL;
        if(info<root->info)root->l=_erase(root->l,info);
        else if(info>root->info)root->r=_erase(root->r,info);
        else{
            if((root->l==NULL)||(root->r==NULL)){
                AVL_node* t=root->l?root->l:root->r;
                if(t==NULL){
                    t=root;
                    root=NULL;
                }else *root=*t;
                free(t);
            }else{
                 AVL_node* t=minimaalneVaartus(root->r);
                 root->info=t->info;
                 root->r=_erase(root->r,t->info);
            }
        }
        if(root==NULL)return NULL;
        return balance(root);
    }

    AVL_node* balance(AVL_node* root){
        uuendakorgus(root);
        int vahe=korgustevahe(root);
        if(vahe==-2){
            if(korgustevahe(root->r)<1)root=vasakpoore(root);
            else{
                root->r=parempoore(root->r);
                root=vasakpoore(root);
            }
        }else if(vahe==2){
            if(korgustevahe(root->l)>-1)root=parempoore(root);
            else{
                root->l=vasakpoore(root->l);
                root=parempoore(root);
            }
        }
        return root;
    }

    AVL_node* vasakpoore(AVL_node* x){
        AVL_node *y=x->r;
        AVL_node *T3=y->l;
        y->l=x;
        x->r=T3;
        uuendakorgus(x);
        uuendakorgus(y);
        return y;
    }

    AVL_node* parempoore(AVL_node* y){
        AVL_node* x=y->l;
        AVL_node* T3=x->r;
        x->r=y;
        y->l=T3;
        uuendakorgus(y);
        uuendakorgus(x);
        return x;
    }

    int korgustevahe(AVL_node* RT){
        if(RT==NULL)return 0;
        return korgus(RT->l)-korgus(RT->r);
    }

    void insert(T voti,V vaartus){
        root=_insert(root,voti,vaartus);
    }

    void erase(T voti){
        root=_erase(root,voti);
    }

    void prindi(AVL_node *RT,int dep){
        if(RT==NULL)return;
        prindi(RT->l,dep+1);
        cout<<RT->info<<' '<<dep<<'\n';
        prindi(RT->r,dep+1);
    }

    void prindi(){
        prindi(root,0);
    }

   V getSegmentSum(AVL_node* root, int start, int end) {
        //if (root == NULL || start > end) return 0;
        if (root == NULL)return 0;
        if(start<=1 && end>=root->suurus)return root->summa;
        int vasakuSuurus = suurus(root->l);
        V summa=0;
        if(start<=vasakuSuurus){
            summa+=getSegmentSum(root->l,start,min(end,vasakuSuurus));
        }
        start-=vasakuSuurus;
        end-=vasakuSuurus;
        if(start<=1&&end>0)summa+=root->vaartus;
        if(end>1)summa+=getSegmentSum(root->r,start-1,end-1);
        return summa;
    }

    bool _contains(AVL_node* root, T& key){
        if(root==NULL)return false;
        if(root->info==key)return true;
        if(root->info>key)return _contains(root->l,key);
        return _contains(root->r,key);
    }

    bool contains(T key){
        return _contains(root,key);
    }

    T get_kth(AVL_node* root,int k){
        if(suurus(root->l)+1==k)return root->info;
        if(suurus(root->l)>=k)return get_kth(root->l,k);
        return get_kth(root->r,k-1-suurus(root->l));
    }

    T get_kth(int k){
        return get_kth(root,k);
    }

};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*1000;
    AVL<int,int> t;
    for(int i=1;i<=N;i++)assert(t.contains(i)==false);
    for(int i=1;i<=N;i++){
        t.insert(i,1);
    }
    for(int i=1;i<=N;i++)assert(t.get_kth(i)==i);
    //t.prindi();
    /*for(int i=1;i<=N;i++){
        for(int j=i;j<=N;j++){
            assert(t.getSegmentSum(t.root,i,j)==(j-i+1));
            //cout<<i<<' '<<j<<' '<<t.getSegmentSum(t.root,i,j)<<'\n';
        }
    }*/
    for(int i=0;i<N;i++){
        int l=(rand()*rand())%N+1;
        int r=(rand()*rand())%N+1;
        if(l>r)swap(l,r);
        assert(t.getSegmentSumBetweenVals(t.root,l,r)==(r-l+1));
    }
    //t.prindi();
    return 0;
}
