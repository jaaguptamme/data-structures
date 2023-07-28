#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
class BinomialHeap{
    class BinomialNode{public:
        T vaartus;
        vector<BinomialNode*>lapsed;
        BinomialNode(T& t){
            vaartus=t;
        }
        void lisaSama(BinomialNode* &teine){
            lapsed.push_back(teine);
        }
        int tase(){
            return lapsed.size();
        }
    };
    vector<BinomialNode*> puud;

    void kombineeri(vector<BinomialNode*>&a){
        BinomialHeap uus;
        uus.puud=a;
        kombineeri(uus);
    }

    public:
    void lisa(T val){
        auto uus=new BinomialNode(val);
        BinomialHeap<T> a;
        a.puud={uus};
        kombineeri(a);
    }

    T leia_miinimum(){
        T a=puud[0]->vaartus;
        for(auto el:puud)a=min(a,el->vaartus);
        return a;
    }

    T eemalda_miinimum(){
        int j=0;
        for(int i=1;i<puud.size();i++){
            if(puud[i]->vaartus<puud[j]->vaartus){
                j=i;
            }
        }
        T vas=puud[j]->vaartus;
        auto ulejaanud=vector<BinomialNode*>(puud[j]->lapsed);
        puud.erase(puud.begin()+j);
        kombineeri(ulejaanud);
        return vas;
    }

    void kombineeri(BinomialHeap<T>& a){
        vector<BinomialNode*> uusPuud;
        int i=0,j=0;
        while((i<puud.size())||(j<a.puud.size())){
            if((i<puud.size())&&(j<a.puud.size())){
                 if(puud[i]->tase()<a.puud[j]->tase())kombineeri(uusPuud,puud[i++]);
                 else if(puud[i]->tase()==a.puud[j]->tase()){
                    uusPuud.push_back(puud[i++]);
                    kombineeri(uusPuud,a.puud[j++]);
                 }
                 else kombineeri(uusPuud,a.puud[j++]);
            }else if(i<puud.size()) kombineeri(uusPuud,puud[i++]);
            else kombineeri(uusPuud,a.puud[j++]);
        }
        puud=uusPuud;
    }

    void kombineeri(vector<BinomialNode*>& uusPuud,BinomialNode* tipp){
        if(uusPuud.size()&&uusPuud.back()->tase()==tipp->tase()){
            auto teine=uusPuud.back();uusPuud.pop_back();
            if(teine->vaartus<tipp->vaartus){
                teine->lisaSama(tipp);
                uusPuud.push_back(teine);
            }else{
                tipp->lisaSama(teine);
                uusPuud.push_back(tipp);
            }
        }
        else uusPuud.push_back(tipp);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*1000;
    BinomialHeap<int>b;
    for(int i=1;i<=N;i++)b.lisa(i);
    BinomialHeap<int>c;
    for(int i=1;i<=31;i++)c.lisa(i);
    b.kombineeri(c);
    for(int i=0;i<31;i++){
        cout<<b.eemalda_miinimum()<<endl;
    }
    return 0;
}
