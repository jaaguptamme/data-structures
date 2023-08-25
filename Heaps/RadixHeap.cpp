#include <bits/stdc++.h>
//source: https://blog.naver.com/jinhan814/222507238041
//push in O(1)
//pop in O(log2(w))
//only push gte lastDeleted like in prim and dijkstra
typedef long long ll;
using namespace std;
template<typename K=int,typename V=int>//Key type value type
class RadixHeap{
    array<vector<pair<K,V>>,sizeof(V)*8+1>v;
    V lastDeleted=0;
    int sz=0,pos=0;
    int lg2(const V &v)const {
        return v?__lg(v):-1;
    }
    void pull(){
        if(pos<v[0].size())return;
        v[0]={};pos=0;
        int p=1;
        while(v[p].empty())p++;
        lastDeleted=min_element(v[p].begin(),v[p].end(),[](const auto& a,const auto &b){return a.second<b.second;})->second;
        for(const auto &i:v[p])v[lg2(i.second xor lastDeleted)+1].push_back(i);
        v[p]={};
    }
public:
    void push(const K &key,const V &value){
        v[lg2(value xor lastDeleted)+1].push_back({key,value});
        sz++;
    }
    void pop(){
        pull();
        sz--;
        pos++;
    }
    pair<K,V> top(){
        pull();
        return v[0][pos];
    }
    bool empty(){
        return sz==0;
    }
    int size(){
        return sz;
    }
};
