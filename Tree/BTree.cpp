#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
class Btree{
    class Bnode{public:
        vector<T>votmed;
        vector<Bnode*>lapsed;
        bool onLeht;
        Bnode(bool onLeht){
            this->onLeht=onLeht;
        }
        Bnode(){
            onLeht=false;
        }
    };
    Bnode* juur;
    int M;
    public:
    Btree(int m){
        juur=new Bnode(true);
        M=m;
    }
    void insert(T voti){
        auto u=juur;
        if(juur->votmed.size()==(2*M-1)){
            auto temp=new Bnode();
            juur=temp;
            temp->lapsed.push_back(u);
            jaga_lapsed(temp,0);
            insert_mahub_veel(temp,voti);
        }else{
            insert_mahub_veel(u,voti);
        }
    }

    void insert_mahub_veel(Bnode* x,T& voti){
        int i=x->votmed.size()-1;
        if(x->onLeht){
            x->votmed.push_back(voti);
            sort(x->votmed.begin(),x->votmed.end());
        }else{
            while(i>=0 && voti<x->votmed[i])i--;
            i++;
            if(x->lapsed[i]->votmed.size()==(2*M-1)){
                jaga_lapsed(x,i);
                if(voti>x->votmed[i])i++;
            }
            insert_mahub_veel(x->lapsed[i],voti);
        }
    }
    void jaga_lapsed(Bnode* x, int i){
        auto y=x->lapsed[i];
        auto z=new Bnode(y->onLeht);
        x->lapsed.insert(x->lapsed.begin()+i+1,z);
        x->votmed.insert(x->votmed.begin()+i,y->votmed[M-1]);
        /*cout<<"Ya";
        for(auto el:y->votmed)cout<<el<<' ';
        cout<<endl;*/
        z->votmed=vector<T>(y->votmed.begin()+M,y->votmed.begin()+2*M-1);
        y->votmed=vector<T>(y->votmed.begin(),y->votmed.begin()+M-1);
       /* cout<<"Z";
        for(auto el:z->votmed)cout<<el<<' ';
        cout<<endl;
        cout<<"Yl";
        for(auto el:y->votmed)cout<<el<<' ';
        cout<<endl;*/
        if(!y->onLeht){
            z->lapsed=vector<Bnode*>(y->lapsed.begin()+M,y->lapsed.begin()+2*M);
            y->lapsed=vector<Bnode*>(y->lapsed.begin(),y->lapsed.begin()+M-1);
        }
    }
    void kustuta(T voti){
        kustuta(juur,voti);
    }
    void kustuta(Bnode* x,T& voti){
        cout<<"KUSTUTA"<<x->votmed[0]<<endl;
        int i=0;
        while(i<x->votmed.size()&&voti>x->votmed[i])i++;
        if(x->onLeht){
            if(i<x->votmed.size()&&voti==x->votmed[i]){
                x->votmed.erase(x->votmed.begin()+i);
            }
            return;
        }
        if(i<x->votmed.size()&& voti==x->votmed[i]){
            kustuta_sisemine(x,voti,i);
            return;
        }else if(x->lapsed[i]->votmed.size()>=M){
            kustuta(x->lapsed[i],voti);
        }else{
            if(i!=0 && i+2<x->lapsed.size()){
                if(x->lapsed[i-1]->votmed.size()>=M){
                    kustuta_naaber(x,i,i-1);
                }else if(x->lapsed[i+1]->votmed.size()>=M){
                    kustuta_naaber(x,i,i+1);
                }else{
                    kustuta_uhenda(x,i,i+1);
                }
            }else if(i==0){
                if(x->lapsed[i+1]->votmed.size()>=M){
                    kustuta_naaber(x,i,i+1);
                }else{
                    kustuta_uhenda(x,i,i+1);
                }
            }
            else if(i+1==x->lapsed.size()){
                if(x->lapsed[i-1]->votmed.size()>=M){
                    kustuta_naaber(x,i,i-1);
                }else{
                    kustuta_uhenda(x,i,i-1);
                }
            }
            kustuta(x->lapsed[i],voti);
        }
    }

    void kustuta_sisemine(Bnode* x,T& voti,int i){
        cout<<"SISEMINE"<<x->votmed[0]<<endl;
        if(x->onLeht){
            if(x->votmed[i]==voti){
                 x->votmed.erase(x->votmed.begin()+i);
            }
            return;
        }
        if(x->lapsed[i]->votmed.size()>=M){
            x->votmed[i]=kustuta_eelmine(x->lapsed[i]);
        }else if(x->lapsed[i+1]->votmed.size()>=M){
            x->votmed[i]=kustuta_jargmine(x->lapsed[i+1]);
        }else{
            kustuta_uhenda(x,i,i+1);
            kustuta_sisemine(x->lapsed[i],voti,M-1);
        }
    }

    T kustuta_eelmine(Bnode* x){
        cout<<"EELMINE"<<x->votmed[0]<<endl;
        if(x->onLeht){
            T v=x->votmed.back();
            x->votmed.pop_back();
            return v;
        }
        int n=x->votmed.size()-1;
        if(x->lapsed[n]->votmed.size()>=M){
            kustuta_naaber(x,n+1,n);
        }else{
            kustuta_uhenda(x,n,n+1);
        }
        return kustuta_eelmine(x->lapsed[n]);
    }

     T kustuta_jargmine(Bnode* x){
         cout<<"JARGMINE"<<x->votmed[0]<<endl;
        if(x->onLeht){
            T v=x->votmed[0];
            x->votmed.erase(x->votmed.begin());
            return v;
        }
        if(x->lapsed[1]->votmed.size()>=M){
            kustuta_naaber(x,0,1);
        }else{
            kustuta_uhenda(x,0,1);
        }
        return kustuta_jargmine(x->lapsed[0]);
    }

    void kustuta_uhenda(Bnode* x,int i,int j){
        cout<<"UHENDA"<<x->votmed[0]<<' '<<i<<'-'<<j<<endl;
        auto c=x->lapsed[i];
        auto uus=c;
        if(j>i){
            auto r=x->lapsed[j];
            c->votmed.push_back(x->votmed[i]);
            cout<<r->votmed.size()<<endl;
            int suurus=r->votmed.size();
            for(int k=0;k<suurus;k++){
                c->votmed.push_back(r->votmed[k]);
                if(r->lapsed.size()>0)c->lapsed.push_back(r->lapsed[k]);
            }
            if(r->lapsed.size()>0){
                c->lapsed.push_back(r->lapsed.back());r->lapsed.pop_back();
            }
            x->votmed.erase(x->votmed.begin()+i);
            x->lapsed.erase(x->lapsed.begin()+j);
            uus=c;
        }else{
            auto l=x->lapsed[j];
            l->votmed.push_back(x->votmed[j]);
            int suurus=c->votmed.size();
            for(int k=0;k<suurus;k++){
                l->votmed.push_back(c->votmed[k]);
                if(c->lapsed.size()>0)l->lapsed.push_back(c->lapsed[k]);
            }
            if(c->lapsed.size()>0){
                l->lapsed.push_back(c->lapsed.back());c->lapsed.pop_back();
            }
            x->votmed.erase(x->votmed.begin()+j);
            x->lapsed.erase(x->lapsed.begin()+i);
            uus=l;
        }
        cout<<"UHENDA2"<<endl;
        if(x==juur && x->votmed.size()==0){
            juur=uus;
        }
    }

    void kustuta_naaber(Bnode* x,int i,int j){
        cout<<"NAABER"<<x->votmed[0]<<endl;
        auto c=x->lapsed[i];
        if(i<j){
            auto r=x->lapsed[j];
            c->votmed.push_back(x->votmed[i]);
            x->votmed[i]=r->votmed[0];
            if(r->lapsed.size()>0){
                c->lapsed.push_back(r->lapsed[0]);
                r->lapsed.erase(r->lapsed.begin());
            }
            r->votmed.erase(r->votmed.begin());
        }
        else{
            auto l=x->lapsed[j];
            c->votmed.insert(c->votmed.begin(),x->votmed[i-1]);
            x->votmed[i-1]=l->votmed.back();l->votmed.pop_back();
            if(l->lapsed.size()>0){
                c->lapsed.insert(c->lapsed.begin(),l->lapsed.back());
                l->lapsed.pop_back();
            }
        }
    }

    void prindi(){
        prindi(juur,0);
    }

    void prindi(Bnode* x,int l){
        cout<<"TASE"<<l<<'-';
        for(auto i:x->votmed){
            cout<<i<<' ';
        }
        cout<<'\n';
        if(x->lapsed.size()!=0){
            for(auto i:x->lapsed)prindi(i,l+1);
        }
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    Btree<int>b(3);
    for(int i=1;i<=100;i++)b.insert(i);
    for(int i=1;i<=90;i++){
        b.kustuta(i);
        b.prindi();
    }
    return 0;
}
