#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
vector<int> compress(vector<T>&a){
    int n=a.size();
    set<T>vls;
    for(auto el:a)vls.insert(el);
    map<T,int>mp;
    int ps=0;
    for(auto el:vls)mp[el]=ps++;
    vector<int>b(n);
    for(int i=0;i<n;i++)b[i]=mp[a[i]];
    return b;
}
class Mo{
    int n;
    vector<pair<int,int>>qs;
    public:
    Mo(int n):n(n){}
    void add_q(int l,int r){//[l,r]
        qs.push_back({l,r});
    }
    template<typename AL,typename AR,typename EL,typename ER,typename O>
    void build(const AL& al,const AR& ar, const EL &el, const ER &er, const O &out){
        int q=qs.size();
        int bs=n/min<int>(n,sqrt(q));
        vector<int>num(q);
        iota(begin(num),end(num),0);
        sort(begin(num),end(num),[&](int a,int b){
            int ab=qs[a].first/bs,bb=qs[b].first/bs;
            if(ab!=bb)return ab<bb;
            return qs[a].second<qs[b].second;
             });
        int l=0,r=-1;
        for(auto ind:num){
            while(r<qs[ind].second)ar(++r);
            while(r>qs[ind].second)er(r--);
            while(l<qs[ind].first)el(l++);
            while(l>qs[ind].first)al(--l);
            out(ind);
        }
    }
    template<typename A,typename E,typename O>
    void build(const A &a,const E &e,const O &out){
        build(a,a,e,e,out);
    }
};
