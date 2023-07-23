#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,T low,T high>
struct LiChao{
    struct Joon{
        T m,b;
        Joon(T m,T b):m(m),b(b){}
        ll operator()(T x)const{return m*x+b;}
    };
    static constexpr T inf=numeric_limits<T>::max();
    struct Tipp{
        Joon j;
        Tipp *l,*r;
        Tipp(const Joon &j):j{j},l{nullptr},r{nullptr}{}
    };
    Tipp* juur;
    LiChao():juur{nullptr}{}
    Tipp* lisa_joon(Tipp* t,Joon j,T l,T r){
        if(!t)return new Tipp(j);
        T jl=j(l),jr=j(r);
        T tl=t->j(l),tr=t->j(r);
        if(tl<=jl&&tr<=jr){
            return t;
        }else if(tl>=jl&&tr>=jr){
            t->j=j;
            return t;
        }else{
            T m=(l+r)/2;
            if(m==r)--m;
            T tm=t->j(m),jm=j(m);
            if(tm>jm){
                swap(t->j,j);
                if(jl>=tl)t->l=lisa_joon(t->l,j,l,m);
                else t->r=lisa_joon(t->r,j,m+1,r);
            }else{
                if(tl>=jl)t->l=lisa_joon(t->l,j,l,m);
                else t->r=lisa_joon(t->r,j,m+1,r);
            }
            return t;
        }
    }
    void lisa_joon(T a,T b){
        Joon j(a,b);
        juur=lisa_joon(juur,j,low,high);
    }

    Tipp* lisa_segment(Tipp *t, Joon j,T se, T en, T l, T r){
        if(r<se||en<l)return t;
        if(se<=l&&r<=en){
            return lisa_joon(t,j,l,r);
        }
        if(t){
            T jl=j(l),jr=j(r);
            T tl=t->j(l),tr=t->j(r);
            if(tl<=jl&&tr<=jr)return t;
        }else{
            t=new Tipp(Joon(0,inf));
        }
        T m=(l+r)/2;
        if(m==r)m--;
        t->l=lisa_segment(t->l,j,se,en,l,m);
        t->r=lisa_segment(t->r,j,se,en,m+1,r);
        return t;
    }
    void lisa_segment(T l,T r,T a,T b){//[l,r] y=a*x+b
        Joon j(a,b);
        juur=lisa_segment(juur,j,l,r,low,high);
    }

    T saa(const Tipp *t,T l,T r,T x) const {
        if(!t)return inf;
        if(l==r)return t->j(x);
        T m=(l+r)/2;
        if(m==r)m--;
        if(x<=m)return min(t->j(x),saa(t->l,l,m,x));
        else return min(t->j(x),saa(t->r,m+1,r,x));
    }
    T saa(const T &x) const {
        return saa(juur,low,high,x);
    }
};
