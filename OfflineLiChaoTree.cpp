#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
class LiChao{
    struct Joon{
        T m,b;
        Joon(T m,T b):m(m),b(b){}
        T operator()(T x)const{return m*x+b;}
    };
    static constexpr T inf=numeric_limits<T>::max();
    int size;
    vector<T>paringud;
    vector<Joon>tipud;
    void uuenda(int i,int l,int r,Joon joon){
        int m=(l+r)/2;
        bool vasak=joon(paringud[l])<tipud[i](paringud[l]);
        bool kesk=joon(paringud[m])<tipud[i](paringud[m]);
        bool parem=joon(paringud[r])<tipud[i](paringud[r]);
        if(!vasak&&!parem)return;
        if(vasak&&parem){
            tipud[i]=joon;
            return;
        }
        if(kesk)swap(tipud[i],joon);
        if(l==r)return;
        if(vasak!=kesk){
            uuenda(i*2,l,m,joon);
        }else{
            uuenda(i*2+1,m+1,r,joon);
        }
    }
public:
    LiChao()=default;
    LiChao(vector<T>& vec){
        paringud=vec;
        if(paringud.empty())paringud.push_back(inf);
        sort(paringud.begin(),paringud.end());
        paringud.erase(unique(paringud.begin(),paringud.end()),paringud.end());
        size=1;
        while(size<paringud.size())size*=2;
        tipud.resize(2*size,{0,inf});
        while(paringud.size()<size)paringud.push_back(paringud.back()+1);
    }
    void add_line(T a,T b){
        Joon j(a,b);
        uuenda(1,0,size-1,j);
    }
    void add_segment(T a,T b, T xl,T xr){
        int l = lower_bound(paringud.begin(), paringud.end(), xl) - paringud.begin();
        int r = upper_bound(paringud.begin(), paringud.end(), xr) - paringud.begin()-1;
        if(l>r)return;
        if(r<0)return;
        if(l>=size)return;
        Joon joon(a,b);
        add_segment(1,0,size-1,l,r,joon);
    }
    void add_segment(int i,int l,int r,int se,int en,Joon joon){
        if(se<=l&&r<=en){
            uuenda(i,l,r,joon);
            return;
        }
        if(se>r||l>en)return;
        int m=(l+r)/2;
        add_segment(i*2,l,m,se,en,joon);
        add_segment(i*2+1,m+1,r,se,en,joon);
    }

    T saa(T x){
        int k=lower_bound(paringud.begin(),paringud.end(),x)-paringud.begin();
        return saa(1,0,size-1,k,x);
    }
    T saa(int i,int l,int r,int pos,T& x){
        if(l==r){
            return tipud[i](x);
        }
        int m=(l+r)/2;
        if(pos<=m)return min(tipud[i](x),saa(i*2,l,m,pos,x));
        return min(tipud[i](x),saa(i*2+1,m+1,r,pos,x));
    }
};
