#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int INF=INT_MAX,NON=-INF;
class vEB{
    private:
    int active_elements,indexed_elements;
    int halfbitcnt,mask;
    int min,max;
    vEB* summary;
    vector<vEB*> childs;
    int low(int x){
        return x&mask;
    }
    int high(int x){
        return x>>halfbitcnt;
    }
    int ind(int i,int j){
        return (i<<halfbitcnt)|j;
    }
     void build(){
        min=max=NON;
        if(indexed_elements==2){
            summary=nullptr;
            childs=vector<vEB*>(0,nullptr);
            return;
        }
        int root=(1<<halfbitcnt);
        summary=new vEB(root);
        childs=vector<vEB*>(root,nullptr);
        for(int i=0;i<root;i++)childs[i]=new vEB(root);
    }
    void _insert(int x){
        if(is_empty()){
            min=max=x;
            return;
        }
        if(x<min)swap(x,min);
        if(x>max)max=x;
        if(indexed_elements==2)return;
        int i=high(x),j=low(x);
        if(childs[i]->min==NON)summary->_insert(i);
        childs[i]->_insert(j);
    }
    bool _lookup(int x){
        if(min==x or max==x)return true;
        if(indexed_elements==2)return false;
        return childs[high(x)]->_lookup(low(x));
    }
    int _succ(int x){
        if(is_empty())return NON;
        if(indexed_elements==2 and x==0 and max==1)return 1;
        if(indexed_elements==2)return NON;
        if(x<min)return min;
        if(x>max)return NON;
        int i=high(x),j=low(x);
        if(j<childs[i]->max){
            j=childs[i]->_succ(j);
        }else{
            i=summary->_succ(i);
            if(i==NON)return NON;
            j=childs[i]->min;
        }
        return ind(i,j);
    }
    int _pred(int x){
        if(is_empty())return NON;
        if(indexed_elements==2 and x==1 and min==0)return 0;
        if(indexed_elements==2)return NON;
        if(max<x)return max;
        if(x<min)return NON;
        int i=high(x),j=low(x);
        if(childs[i]->min!=NON and childs[i]->min<j){
            j=childs[i]->_pred(j);
        }else{
            i=summary->_pred(i);
            if(i==NON and min<x)return min;
            if(i==NON)return NON;
            j=childs[i]->max;
        }
        return ind(i,j);
    }
    void _erase(int x){
        if(min==x and max==x){
            min=max=NON;
            return;
        }
        if(indexed_elements==2){
            if(x==0)min=1;
            if(x==1)min=0;
            max=min;
            return;
        }
        if (x==min) {
            int cur=summary->min;
            if(cur==NON) {
              min=max=NON;
              return;
            }
            x=min=ind(cur,childs[cur]->min);
          }
          int i=high(x),j=low(x);
          childs[i]->_erase(j);
          if (childs[i]->min==NON) {
            summary->_erase(i);
          }
          if(x==max) {
            if(summary->max==NON) {
              max=min;
            } else {
              int cur=summary->max;
              max=ind(cur,childs[cur]->max);
            }
          }
    }
    public:
    int pred(int x){
        if(x>=indexed_elements)return max;
        if(x<0)return NON;
        return _pred(x);
    }
    int succ(int x){
        if(x>=indexed_elements)return NON;
        if(x<0)return min;
        return _succ(x);
    }
    bool lookup(int x){
        if(x<0||x>= indexed_elements)return false;
        return _lookup(x);
    }
    void insert (int x){
        if(lookup(x))return;
        _insert(x);
    }
    int min_element(){return min;}
    int max_element(){return max;}
    int is_empty(){return min==NON;}
    void erase(int x){
        if(!lookup(x))return;
        _erase(x);
    }
    vEB (int number_elements){
        halfbitcnt=log2(2*number_elements-1);
        if(halfbitcnt<1)halfbitcnt=1;
        indexed_elements=1<<halfbitcnt;
        if(halfbitcnt%2){
            halfbitcnt/=2;halfbitcnt++;
        }else{
            halfbitcnt/=2;
        }
        mask=(1<<halfbitcnt)-1;
        build();
    }
};
