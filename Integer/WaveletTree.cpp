//source: https://github.com/TWal/acm-book/blob/371739a66f2550c2566efecf281002e888a720ee/src/datastruct/wavelettree.cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct BIT{
    vector<int>v;
    BIT()=default;
    BIT(int n):v(n+1,0){}
    int get(int i){
        int res=0;
        for(i+=1;i>0;i-=i&-i)res+=v[i];
        return res;
    }
    void add(int i,int vl){
        for(i+=1;i<v.size();i+=i&-i)v[i]+=vl;
    }
};
struct WaveletTree{
    vector<int>a;
    vector<BIT>active;
    vector<vector<int>>t;
    int n;
    void build(auto b,auto e,int L,int R,int i){
        int s=e-b+1;
        active[i]=BIT(s);
        for(int p=1;p<s;p++)active[i].add(p,1);
        if(L==R)return;
        int M=(L+R)/2;
        t[i].reserve(s);t[i].push_back(0);
        auto f=[&](int i){return i<=M;};
        for(auto it=b;it!=e;++it)t[i].push_back(t[i].back()+f(*it));
        auto mv=stable_partition(b,e,f);
        build(b,mv,L,M,2*i);build(mv,e,M+1,R,2*i+1);
    }
    WaveletTree()=default;
    WaveletTree(int n,const vector<int>&a):a(a),t(2*n),active(4*n),n(n){
        vector<int>v=a;
        build(v.begin(),v.end(),0,n-1,1);
    }
    pair<int,int> rank(int v,int r,bool calcSum=true){
        int L=0,R=n-1,i=1,sum=0;
        while(L!=R){
            int M=(L+R)/2;
            if(v<=M){
                r=t[i][r];
                R=M;
                i*=2;
            }else{
                if(calcSum)sum+=active[2*i].get(t[i][r]);
                r-=t[i][r];
                L=M+1;
                i=2*i+1;
            }
        }
        return make_pair(sum,active[i].get(r));
    }
    void wswap(int ps){
        int pssave=ps;
        bool act[2];
        for(int i=0;i<2;i++)act[i]=!isActivated(ps+i);
        for(int i=0;i<2;i++){
            if(act[i])activate(ps+i,true,false);
        }
        int L=0,R=n-1,i=1;
        int v1=a[ps],v2=a[ps+1];
        swap(a[ps],a[ps+1]);
        while(L!=R){
            int M=(L+R)/2;
            if((v1<=M)!=(v2<=M)){
                t[i][ps+1]+=v1<=M?-1:1;
                break;
            }else if(v1<=M){
                ps=t[i][ps];
                R=M;
                i*=2;
            }else{
                ps-=t[i][ps];
                L=M+1;
                i=i*2+1;
            }
        }
        for(int i=0;i<2;i++)if(act[i])activate(pssave+i,false,false);
    }

    bool isActivated(int x) { return active[1].get(x+1) == 1+active[1].get(x); }

    void activate(int ps,bool activation,bool check=true){
        if(check && isActivated(ps)==activation)return;
        int L=0,R=n-1,i=1;
        int v=a[ps];
        while(L!=R){
            int M=(L+R)/2;
            active[i].add(ps+1,activation?1:-1);
            if(v<=M){
                ps=t[i][ps];
                R=M;
                i*=2;
            }else{
                ps-=t[i][ps];
                L=M+1;
                i=i*2+1;
            }
        }
        active[i].add(ps+1,activation?1:-1);
    }
    int rank(int v,int l,int r){//Cnt l<=k<r | a[k]==v
        return rank(v,r,false).second-rank(v,l,false).second;
    }
    int rank(int x,int y,int l,int r){//cnt l<=k<r| x<=a[k]<y
        return rank(y,r).first-rank(x,r).first-rank(y,l).first+rank(x,l).first;
    }
    int kth(int k,int l,int r){//kth smallest in [l,r)
        if(active[1].get(r)-active[1].get(l)<k)assert(false);
        int L=0,R=n-1,i=1;
        while(L!=R){
            int M=(L+R)/2;
            int c=active[2*i].get(t[i][r])-active[2*i].get(t[i][l]);
            if(k<=c){
                l=t[i][l],r=t[i][r];
                R=M;
                i*=2;
            }else{
                k-=c;l-=t[i][l];r-=t[i][r];
                L=M+1;
                i=i*2+1;
            }
        }
        return L;
    }
    void toggle(int ps){
        activate(ps,!isActivated(ps));
    }
};
struct CompressedWaveletTree{
    WaveletTree mat;
    vector<int>vls;
    CompressedWaveletTree(vector<int>& vec):vls(vec){
        sort(vls.begin(),vls.end());
        vls.erase(unique(vls.begin(),vls.end()),vls.end());
        vector<int>nw(vec.size());
        for(int i=0;i<vec.size();i++)nw[i]=get(vec[i]);
        mat=WaveletTree(nw.size(),nw);
    }
    //x->its compressed int
    int get(int& x){
        return lower_bound(vls.begin(),vls.end(),x)-vls.begin();
    }
    int rank(int v,int l,int r){
        if(*lower_bound(vls.begin(),vls.end(),v)!=v)return 0;
        return mat.rank(get(v),l,r);
    }
    void toggle(int ps){
        mat.toggle(ps);
    }
    void wswap(int ps){
        mat.wswap(ps);
    }
    int kth(int k,int l,int r){
        return vls[mat.kth(k,l,r)];
    }
};
