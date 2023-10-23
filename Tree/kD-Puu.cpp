#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
struct KD{
    vector<pair<T,T>>punktid;
    int n;
    vector<int>L,R;
    int juur;
    KD(vector<pair<T,T>>& punktid):punktid(punktid),n(punktid.size()){
        L.resize(n,-1);
        R.resize(n,-1);
        juur=ehita(0,n,0);
    }
    int ehita(int l,int r,int sugavus){
        if(l>=r)return -1;
        int m=(l+r)/2;
        if(sugavus%2==0){
            sort(punktid.begin()+l,punktid.begin()+r,[](const pair<T,T>& a,const pair<T,T> &b){return a.first<b.first;});
        }else  sort(punktid.begin()+l,punktid.begin()+r,[](const pair<T,T>& a,const pair<T,T> &b){return a.second<b.second;});
        L[m]=ehita(l,m,sugavus+1);
        R[m]=ehita(m+1,r,sugavus+1);
        return m;
    }
    void leia(int xl,int xr,int yl,int yr,int sugavus,int ind,vector<pair<T,T>>& sobivad){
        T x,y;
        tie(x,y)=punktid[ind];
        if(xl<=x&&x<xr&&yl<=y&&y<yr)sobivad.push_back(punktid[ind]);
        if(sugavus%2==0){
            if(L[ind]!=-1 && xl<=x)leia(xl,xr,yl,yr,sugavus+1,L[ind],sobivad);
            if(R[ind]!=-1 && x<xr)leia(xl,xr,yl,yr,sugavus+1,R[ind],sobivad);
        }else{
            if(L[ind]!=-1 && yl<=y)leia(xl,xr,yl,yr,sugavus+1,L[ind],sobivad);
            if(R[ind]!=-1 && y<yr)leia(xl,xr,yl,yr,sugavus+1,R[ind],sobivad);
        }
    }
    vector<pair<T,T>> leia(int xl,int xr,int yl,int yr){
        vector<pair<T,T>> vastus;
        leia(xl,xr,yl,yr,0,juur,vastus);
        return vastus;
    }
};
