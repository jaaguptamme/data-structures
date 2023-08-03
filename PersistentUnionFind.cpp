#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,int LG>//Blocksize
struct PersistentArray{
    static constexpr int BTMSK=(1<<LG)-1;
    struct Tipp{
        T vaartus;
        Tipp* jargmised[1<<LG]={};
        Tipp(){}
        Tipp(T &vaartus):vaartus(vaartus){}
    };
    Tipp* juur;
    PersistentArray():juur(nullptr){}
    T saa(Tipp *t,int koht){
        if(koht==0)return t->vaartus;
        return saa(t->jargmised[koht&BTMSK],koht>>LG);
    }
    T saa(int k){
        return saa(juur,k);
    }
    pair<Tipp*,T*> muteeritav_saa(Tipp *t,int koht){
        t=t?new Tipp(*t):new Tipp();
        if(koht==0)return {t,&t->vaartus};
        auto alumine=muteeritav_saa(t->jargmised[koht&BTMSK],koht>>LG);
        t->jargmised[koht&BTMSK]=alumine.first;
        return {t,alumine.second};
    }
    T* muteeritav_saa(int k){
        auto uus=muteeritav_saa(juur,k);
        juur=uus.first;
        return uus.second;
    }
    Tipp* ehita(Tipp* t,T &vaartus,int koht){
        if(!t)t=new Tipp();
        if(koht==0){
            t->vaartus=vaartus;
            return t;
        }
        auto alumine=ehita(t->jargmised[koht&BTMSK],vaartus,koht>>LG);
        t->jargmised[koht&BTMSK]=alumine;
        return t;
    }
    void ehita(vector<T> vec){
        juur=nullptr;
        for(int i=0;i<vec.size();i++)
            juur=ehita(juur,vec[i],i);
    }
};
struct PersistentUnionFind{
    PersistentArray<int,3>massiiv;
    PersistentUnionFind(){}
    PersistentUnionFind(int suurus){
        massiiv.ehita(vector<int>(suurus,-1));//kõik komponendid suurusega 1
    }
    int leia(int k){
        int p=massiiv.saa(k);
        if(p>=0)return leia(p);
        return k;
    }
    int suurus(int k){
        return -massiiv.saa(leia(k));
    }
    bool uhenda(int u,int v){
        u=leia(u);
        v=leia(v);
        if(u==v)return false;
        auto i=massiiv.saa(u);
        auto j=massiiv.saa(v);
        if(i>=j){
            swap(u,v);
            swap(i,j);
        }
        auto a=massiiv.muteeritav_saa(u);
        *a+=j;
        auto b=massiiv.muteeritav_saa(v);
        *b=u;
        return true;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<PersistentUnionFind>hulgad(q+1);
    hulgad[0]=PersistentUnionFind(n);
    for(int i=1;i<=q;i++){
        int t,k,u,v;
        cin>>t>>k>>u>>v;
        k++;
        if(t==0){
            hulgad[i]=hulgad[k];
            hulgad[i].uhenda(u,v);
        }else{
            cout<<(hulgad[k].leia(u)==hulgad[k].leia(v))<<'\n';
        }
    }
    return 0;
}
