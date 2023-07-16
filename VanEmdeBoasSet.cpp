#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int INF=INT_MAX,NON=-INF,SMALL=63;
class genericvEB{
    public:
    int min,max;
    virtual void _insert(int x)=0;
    virtual void _erase(int x)=0;
    virtual bool _lookup(int x)=0;
    virtual int _succ(int x)=0;
    virtual int _pred(int x)=0;
};
class smallvEB: public genericvEB{
    public:
    ll bits;
    smallvEB(){
        bits=0;
        min=max=NON;
    }
    int _next_low(int x){
        ll b=bits&~(((1LL)<<(x+1))-1);
        if(b==0)return NON;
        return 63 - __builtin_clzll(b & -b);
    }

    int _next_high(int x){
        ll b=bits&(((1LL)<<(x))-1);
        if(b==0)return NON;
        return 63 - __builtin_clzll(b);
    }
    int calc_min(){
        if(bits==0)return NON;
        return 63 - __builtin_clzll(bits & -bits);
    }

    int calc_max(){
        if(bits==0)return NON;
        return 63 - __builtin_clzll(bits);
    }

     void _insert(int x){
        bits|=(1LL)<<x;
        min=calc_min();
        max=calc_max();
        return;
     }

     bool _lookup(int x){
        return bits&((1LL)<<x);
     }

     int _succ(int x){
        return _next_low(x);
     }

     int _pred(int x){
        return _next_high(x);
     }

     void _erase(int x){
        bits&=~((1LL)<<x);
        min=calc_min();
        max=calc_max();
     }
};
class vEB: public genericvEB{
    private:
    int indexed_elements;
    int SQRT;
    genericvEB* summary;
    genericvEB** childs;
    int low(int x){
        return x%SQRT;
    }
    int high(int x){
        return x/SQRT;
    }
    int ind(int i,int j){
        return (i*SQRT)+j;
    }

    void _insert(int x){
        if(is_empty()){
            min=max=x;
            return;
        }
        if(x<min)swap(x,min);
        if(x>max)max=x;
        int i=high(x),j=low(x);
        if(childs[i]->min==NON)summary->_insert(i);
        childs[i]->_insert(j);
    }
    bool _lookup(int x){
        if(min==x or max==x)return true;
        return childs[high(x)]->_lookup(low(x));
    }

    int _succ(int x){
        if(is_empty())return NON;
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
        SQRT=sqrt(number_elements);
        if(SQRT*SQRT<number_elements)SQRT++;
        indexed_elements=number_elements;
        min=max=NON;
        /*if(indexed_elements<=SMALL){
            bits=0;
            return;
        }*/
        if(indexed_elements<SMALL*SMALL){
            int mitu=(indexed_elements+SMALL-1)/SMALL;
            summary=new smallvEB();
            childs=new genericvEB*[mitu];
            SQRT=SMALL;
            for(int i=0;i<mitu;i++)childs[i]=new smallvEB();
        }
        else{
            summary=new vEB(SQRT);
            childs=new genericvEB*[SQRT];
            for(int i=0;i<SQRT;i++)childs[i]=new vEB(SQRT);
        }
    }
};

void prindi(vEB &see){
    int u=see.max_element();
    while(u!=NON){
        cout<<u<<' ';
        u=see.pred(u);
    }
    cout<<'\n';
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=100*1000*1000;
    vEB v(N);
    /*for(int i=0;i<N;i+=N/19){
        v.insert(i);
        prindi(v);
    }*/
    for(int i=0;i<N;i++){
        assert(!v.lookup(i));
        v.insert(i);
        assert(v.lookup(i));
        //prindi(v);
    }
    for(int i=0;i<N;i++){
        assert(v.lookup(i));
        v.erase(i);
        assert(!v.lookup(i));
        //prindi(v);
    }
    prindi(v);
    return 0;
}
