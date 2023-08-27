//source: https://kodu.ut.ee/~bleurgh/mo_eio_2019/mo.pdf
//MO algoritm uuendustega, ajaline keerukus O(QN**2/3+N**5/3)
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
class Mo{//indeksid alates nullist
    struct Query{int l,r,t;};
    int n;//massiivi pikkus
    vector<T>ar,dp,cur,nx;//massiiv, massiivi koopia, algne element, uus element
    vector<Query>qs;//Küsimuse päringud
    vector<int>ind;//uuenduse indeks
    public:
    Mo(vector<T>&ar):ar(ar),dp(ar),n(ar.size()){}
    void add_upt(int i,const T& newVal){//Lisab uuenduse kohal i, uus väärtus newVal
        ind.push_back(i);
        cur.push_back(dp[i]);
        nx.push_back(newVal);
        dp[i]=newVal;
    }
    void add_get(int l,int r){//lisab küsimuse päringu piiridega [l,r]
        qs.push_back({l,r,ind.size()});
    }
    template<typename A,typename E,typename O>
    void build(const A &a,const E &e,const O &out){
        int q=qs.size();
        int bs=n/min<int>(n,pow(n,0.333333));
        vector<int>num(q);
        iota(begin(num),end(num),0);
        sort(begin(num),end(num),[&](int a,int b){
            int ab=qs[a].l/bs,bb=qs[b].l/bs;
            if(ab!=bb)return ab<bb;
            int ac=qs[a].r/bs,bc=qs[b].r/bs;
            if(ac!=bc)return ac<bc;
            return qs[a].t<qs[b].t;
             });
        int l=0,r=-1,t=0;
        auto lisaUuendus=[&](int aeg){
            if(l<=ind[aeg]&&ind[aeg]<=r){
                e(cur[aeg]);
                a(nx[aeg]);
            }
            ar[ind[aeg]]=nx[aeg];
        };
        auto eemaldaUuendus=[&](int aeg){
            if(l<=ind[aeg]&&ind[aeg]<=r){
                e(nx[aeg]);
                a(cur[aeg]);
            }
            ar[ind[aeg]]=cur[aeg];
        };
        for(auto ind:num){
            while(r<qs[ind].r)a(ar[++r]);
            while(r>qs[ind].r)e(ar[r--]);
            while(l<qs[ind].l)e(ar[l++]);
            while(l>qs[ind].l)a(ar[--l]);
            while(t<qs[ind].t)lisaUuendus(t++);
            while(t>qs[ind].t)eemaldaUuendus(--t);
            out(ind);
        }
    }
};
