//source: https://neterukun1993.github.io/Library/DataStructure/Heap/IntervalHeap.py
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
struct IntervalHeap{
    vector<T>hp;
    T min(){
        return hp[0];
    }
    T max(){
        if(size()==1)return hp[0];
        return hp[1];
    }
    void push(const T& val){
        hp.push_back(val);
        heapUp(size()-1);
    }
    T popMin(){
        if(size()<2){
            auto val=hp.back();
            hp.pop_back();
            return val;
        }
        swap(hp[0],hp[size()-1]);
        auto val=hp.back();hp.pop_back();
        int k=heapDown(0);
        heapUp(k);
        return val;
    }
    T popMax(){
        if(size()<3){
            auto val=hp.back();
            hp.pop_back();
            return val;
        }
        swap(hp[1],hp[size()-1]);
        auto val=hp.back();hp.pop_back();
        int k=heapDown(1);
        heapUp(k);
        return val;
    }
    int size(){
        return hp.size();
    }
    int heapDown(int k){
        if(k&1){
            while(2*k+1<size()){
                int ch=2*k+3;
                if(size()<=ch||hp[ch-2]>hp[ch])ch-=2;
                if(ch<size()&&hp[k]<hp[ch]){
                    swap(hp[k],hp[ch]);
                    k=ch;
                }else break;
            }
        }else{
            while(2*k+2<size()){
                int ch=2*k+4;
                if(size()<=ch||hp[ch-2]<hp[ch])ch-=2;
                if(ch<size()&&hp[k]>hp[ch]){
                    swap(hp[k],hp[ch]);
                    k=ch;
                }else break;
            }
        }
        return k;
    }
    int heapUp(int k){
        if((k|1)<size()&&hp[k&~1]>hp[k|1]){
            swap(hp[k&~1],hp[k|1]);
            k^=1;
        }
        while(k!=0){
            int par=((k>>1)-1)&~1;
            if(par<0)par+=size();
            if(hp[par]<=hp[k])break;
            swap(hp[par],hp[k]);
            k=par;
        }
        while(k!=1){
            int par=(((k>>1)-1)&~1)|1;
            if(par<0)par+=size();
            if(hp[par]>=hp[k])break;
            swap(hp[par],hp[k]);
            k=par;
        }
        return k;
    }
};
