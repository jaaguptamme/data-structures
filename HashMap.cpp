#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,typename V>
class HashMap{
    typedef unsigned long long ull;
    static constexpr ull S=21,R=64-S,M=19960909211996090921ull;
    static constexpr int SZ=(1<<S)+205;
    struct Tipp{
        T key;
        V val;
    }tipud[SZ];
    bool e[SZ];
    T hash(T &k){
        return ((ull)k*M>>R);
    }
    public:
    void insert(T &key,V &val){
        int i=hash(key);
        for(;e[i];i++){
            if(tipud[i].key==key){
                tipud[i].val=val;
                return;
            }
        }
        tipud[i].key=key;
        tipud[i].val=val;
        e[i]=true;
    }
    V find(T &key){
        for(int i=hash(key);e[i];i++){
            if(tipud[i].key==key)return tipud[i].val;
        }
        return 0;
    }
};
