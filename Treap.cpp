#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct T{
     T *l=0,*r=0;
     int key=0,prior=0,sz=1;
     bool rev=0;
     T(){};
     T(ll K,ll P){key=K;prior=P;}
};
int SUM(T* RT){
    if(RT)return RT->sz;
    return 0;
}
void UPD(T* RT){
    if(RT->rev){
        swap(RT->l,RT->r);
        if(RT->l)RT->l->rev=1-RT->l->rev;
        if(RT->r)RT->r->rev=1-RT->r->rev;
        RT->rev=0;
    }
    RT->sz=SUM(RT->l)+SUM(RT->r)+1;
}
T* MERGE(T* L,T* R){
    if(!L&&!R)return 0;
    if(!L)return R;
    if(!R)return L;
    UPD(L);UPD(R);
    if(L->prior>R->prior){
        L->r=MERGE(L->r,R);
        UPD(L);
        return L;
    }else{
        R->l=MERGE(L,R->l);
        UPD(R);
        return R;
    }
}
typedef pair<T*,T*>PTT;
PTT SPLIT_BY_CNT(T* RT,int x){
    if(!RT)return {0,0};
    UPD(RT);
    if(SUM(RT->l)+1<=x){
        PTT Q=SPLIT_BY_CNT(RT->r,x-SUM(RT->l)-1);
        RT->r=Q.first;
        UPD(RT);
        return {RT,Q.second};
    }else{
       PTT Q=SPLIT_BY_CNT(RT->l,x);
        RT->l=Q.second;
        UPD(RT);
        return {Q.first,RT};
    }
}
PTT SPLIT_BY_KEY(T* RT,int key){
    if(!RT)return {0,0};
    UPD(RT);
    if(RT->key<=key){
        PTT Q=SPLIT_BY_KEY(RT->r,key);
        RT->r=Q.first;
        UPD(RT);
       return {RT,Q.second};
    }else{
       PTT Q=SPLIT_BY_KEY(RT->l,key);
        RT->l=Q.second;
        UPD(RT);
        return {Q.first,RT};
    }
}
T* RT=0;
void INS_LAST(int x){
    //PTT Q=SPLIT(RT,);
    T* N=new T(x,rand());
    RT=MERGE(RT,N);
}
void U2(int l,int r){
    PTT Q1=SPLIT_BY_CNT(RT,r);
    PTT Q2=SPLIT_BY_CNT(Q1.first,l);
    Q2.second->rev=1;
    RT=MERGE(Q2.first,MERGE(Q2.second,Q1.second));
}
void U1(int l,int r){
    PTT Q1=SPLIT_BY_CNT(RT,r);
    PTT Q2=SPLIT_BY_CNT(Q1.first,l);
    PTT Q3=SPLIT_BY_CNT(Q2.second,(r-l-1));
    RT=MERGE(Q2.first,MERGE(Q3.second,MERGE(Q3.first,Q1.second)));
}
int get(int pos){
    PTT Q1=SPLIT_BY_CNT(RT,pos);
    PTT Q2=SPLIT_BY_CNT(Q1.first,pos-1);
    int ans=Q2.second->key;
    RT=MERGE(Q2.first,MERGE(Q2.second,Q1.second));
    return ans;
}
void print(T* RT){
    if(!RT)return;
    print(RT->l);
    cout<<RT->key<<' ';
    print(RT->r);
}
