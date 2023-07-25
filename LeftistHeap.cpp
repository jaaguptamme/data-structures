#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename K,typename V>
class LeftistHeap{
    struct Tipp{
        Tipp *l,*r;
        int s;//minimum distance to leaf
        K key;
        V val;
        Tipp(K key, V val):key(key),val(val),l(nullptr),r(nullptr),s(0){}
    };
    Tipp *juur;
    LeftistHeap(Tipp* juur):juur(juur){}
    static Tipp* uhenda(Tipp *v,Tipp *p){
        if(!v)return p;
        if(!p)return v;
        if(v->key>p->key)swap(v,p);//maintain heap property
        v->r=uhenda(v->r,p);
        if(!v->l||v->l->s<v->r->s)swap(v->l,v->r);
        v->s=(v->r?v->r->s:0)+1;
        return v;
    }
    public:
    LeftistHeap():juur(nullptr){}
    static LeftistHeap uhenda(LeftistHeap v,LeftistHeap p){
        return LeftistHeap(uhenda(v.juur,p.juur));
    }
    pair<K,V> top(){
        return {juur->key,juur->val};
    }
    void pop(){
        juur=uhenda(juur->l,juur->r);
    }
    bool empty(){
        return juur==NULL;
    }
    void push(K k,V v){
        juur=uhenda(juur,new Tipp(k,v));
    }
};
