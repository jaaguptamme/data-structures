#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
struct BPuu{
    struct Tipp{
        int suurus;
        vector<T> votmed;
        vector<Tipp*>alla;
        Tipp(int suurus):suurus(suurus){}
        Tipp* poolita(){
            if(votmed.size()!=suurus*2){
                return nullptr;
            }
            Tipp* uus=new Tipp(suurus);
            vector<T> uusVotmed={votmed.begin(),votmed.begin()+suurus};
            vector<T> vanaVotmed={votmed.begin()+suurus,votmed.end()};
            vector<Tipp*> uusAlla,vanaAlla;
            for(int i=0;i<alla.size();i++){
                if(i<suurus)uusAlla.push_back(alla[i]);
                else vanaAlla.push_back(alla[i]);
            }
            this->votmed=vanaVotmed;
            this->alla=vanaAlla;
            uus->alla=uusAlla;
            uus->votmed=uusVotmed;
            return uus;
        }
        void lukka_lr(int ind){
            Tipp *vas=alla[ind],*par=alla[ind+1];
            par->votmed.insert(par->votmed.begin(),vas->votmed.back());
            vas->votmed.pop_back();
            if(vas->alla.size()){
                par->alla.insert(par->alla.begin(),vas->alla.back());
                vas->alla.pop_back();
            }
            swap(this->votmed[ind],par->votmed[0]);
        }
         void lukka_rl(int ind){
            Tipp *vas=alla[ind],*par=alla[ind+1];
            vas->votmed.push_back(par->votmed[0]);
            par->votmed.erase(par->votmed.begin());
            if(par->alla.size()){
                vas->alla.push_back(par->alla[0]);
                par->alla.erase(par->alla.begin());
            }
            swap(this->votmed[ind],vas->votmed.back());
        }
        void uhenda(int ind){
            alla[ind]->votmed.push_back(votmed[ind]);
            for(auto& el:alla[ind+1]->votmed)alla[ind]->votmed.push_back(el);
            for(auto& el:alla[ind+1]->alla)alla[ind]->alla.push_back(el);
            votmed.erase(votmed.begin()+ind);
            alla.erase(alla.begin()+ind+1);
        }
    };
    int BS,suurus;
    Tipp* juur;
    BPuu(int BS=512):BS(BS),suurus(0){
        juur=new Tipp(BS);
    }
    int bisect_left(vector<T>& votmed,const T& voti){
        if(votmed.empty())return 0;
        if(votmed.back()<voti)return votmed.size();
        int l=0,r=votmed.size()-1,ans=-1;
        while(l<=r){
            int m=(l+r)/2;
            if(votmed[m]>=voti){
                ans=m;
                r=m-1;
            }else l=m+1;
        }
        return ans;
    }
    bool otsi(const T& voti){
        Tipp* tp=juur;
        while(true){
            int ind=bisect_left(tp->votmed,voti);
            //cout<<"VOTI"<<voti<<endl;
            //for(auto el:tp->votmed)cout<<el<<' ';
            //cout<<endl;
            //cout<<"IND"<<ind<<endl;
            //cout<<(ind!=tp->votmed.size())<<' '<<tp->votmed[ind]<<' '<<(tp->votmed[ind]==voti)<<endl;
            if((ind!=tp->votmed.size())&&(tp->votmed[ind]==voti))return true;
            if(tp->alla.empty())return false;
            tp=tp->alla[ind];
        }
    }
    int bisect_rigth(vector<T>& votmed,const T& voti){
        if(votmed.back()<voti)return votmed.size();
        int l=0,r=votmed.size()-1,ans=-1;
        while(l<=r){
            int m=(l+r)/2;
            if(votmed[m]>=voti){
                ans=m;
                l=m+1;
            }else r=m-1;
        }
        return ans;
    }
    Tipp* lisaRek(Tipp* tp,const T& voti){
        if(tp->alla.empty()){
            auto ps=upper_bound(begin(tp->votmed),end(tp->votmed),voti);
            //if(ps==begin(tp->votmed))ps++;
            tp->votmed.insert(ps,voti);
        }else{
            int i=upper_bound(begin(tp->votmed),end(tp->votmed),voti)-tp->votmed.begin();
            Tipp* p=lisaRek(tp->alla[i],voti);
            if(p){
                tp->votmed.insert(tp->votmed.begin()+i,p->votmed.back());p->votmed.pop_back();
                tp->alla.insert(tp->alla.begin()+i,p);
            }
        }
        return tp->poolita();
    }
    bool lisa(const T& voti){
        //if(otsi(voti))return true;
        Tipp* tp=this->juur;
        Tipp* p=lisaRek(tp,voti);
        if(p){
            Tipp* juur=new Tipp(BS);
            juur->votmed.push_back(p->votmed.back());p->votmed.pop_back();
            juur->alla.push_back(p);
            juur->alla.push_back(this->juur);
            this->juur=juur;
        }
        suurus++;
        return true;
    }

    bool eemaldaRek(Tipp* tp,const T& voti){
        int ind=bisect_left(tp->votmed,voti);
        if((ind!=tp->votmed.size())&&(tp->votmed[ind]==voti)){
            if(tp->alla.empty()){
                tp->votmed.erase(tp->votmed.begin()+ind);
            }else{
                tp->votmed[ind]=eemaldaVahim(tp->alla[ind+1]);
                alataitumine(tp,ind+1);
            }
            return true;
        }else if(!tp->alla.empty()&&eemaldaRek(tp->alla[ind],voti)){
            alataitumine(tp,ind);
            return true;
        }
        return false;
    }
    T eemaldaVahim(Tipp* tp){
        if(tp->alla.empty()){
           T res=tp->votmed[0];tp->votmed.erase(tp->votmed.begin());
           return res;
        }
        T res=eemaldaVahim(tp->alla[0]);
        alataitumine(tp,0);
        return res;
    }

    void alataitumine(Tipp* tp,int ind){
        if(tp->alla[ind]->votmed.size()>=BS-1)return;
        else if(ind==0){
            if(tp->alla[ind+1]->votmed.size()>BS)tp->lukka_rl(ind);
            else tp->uhenda(ind);
        }else{
            if(tp->alla[ind-1]->votmed.size()>BS)tp->lukka_lr(ind-1);
            else tp->uhenda(ind-1);

        }
    }

    bool eemalda(const T& voti){
        bool f=eemaldaRek(juur,voti);
        if(juur->alla.size()==1){
            juur=juur->alla[0];
        }
        if(f)suurus--;
        return f;
    }

    void prindi(){
        prindi(juur);
        cout<<endl;
    }
    void prindi(Tipp* tp){
        for(int i=0;i<tp->alla.size();i++){
            prindi(tp->alla[i]);
            //cout<<"E"<<i<<endl;
        }
        for(auto el:tp->votmed)cout<<el<<' ';
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*1000;
    BPuu<int> BP;
    for(int i=0;i<N;i++)BP.lisa(i);
    for(int i=1;i<N;i+=2)BP.eemalda(i);
    //BP.prindi();
    for(int i=0;i<2*N;i++){
        assert(BP.otsi(i)==(i<N&&(i%2==0)));
    }

    return 0;
}
