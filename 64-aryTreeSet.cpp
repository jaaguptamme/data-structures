#include <bits/stdc++.h>
//Seg fault if N is big and not enough stack
//use linker option "-Wl,--stack,268435456" or any other number in bytes to change stack size
typedef long long ll;
using namespace std;
typedef uint64_t u64;
constexpr int suurim64Aste(int n){
    int res=1;
    while(n>64){
        res*=64;
        n/=64;
    }
    return res;
}
template<int N,class D=void>
class TreeSet{
    static constexpr int C=suurim64Aste(N);
    array<TreeSet<C>,(N+C-1)/C>alumised;
public:
    u64 kokkuvote;
    TreeSet():alumised(),kokkuvote(0){}
    bool insert(const int x){
        const int pos=x/C;
        kokkuvote|=static_cast<u64>(1)<<pos;
        return alumised[pos].insert(x%C);
    }
    bool erase(const int x){
        const int pos=x/C;
        const bool res=alumised[pos].erase(x%C);
        if(alumised[pos].kokkuvote==0){
            kokkuvote&=~(static_cast<u64>(1)<<pos);
        }
        return res;
    }
    bool contains(const int x)const{
        return alumised[x/C].contains(x%C);
    }
    int min()const{
        const int pos=__builtin_ctzll(kokkuvote);
        return pos*C+alumised[pos].min();
    }
    int max()const{
        const int pos=63-__builtin_clzll(kokkuvote);
        return pos*C+alumised[pos].max();
    }
    int pred(const int x)const{//greatest < x, or -1
        const int pos=x/C;
        const int al=alumised[pos].pred(x%C);
        if(al!=-1)return pos*C+al;
        const u64 mask=kokkuvote&~(~static_cast<u64>(0)<<pos);
        if(mask==0)return -1;
        const int pos2=63-__builtin_clzll(mask);
        return pos2*C+alumised[pos2].max();
    }
    int succ(const int x)const{//smallest >= x, or -1
        const int pos=x/C;
        const int al=alumised[pos].succ(x%C);
        if(al!=-1)return pos*C+al;
        const u64 mask=kokkuvote&~(~static_cast<u64>(0)>>(63-pos));
        if(mask==0)return -1;
        const int pos2=__builtin_ctzll(mask);
        return pos2*C+alumised[pos2].min();
    }
};
template<int N>
class TreeSet<N,typename enable_if<N<=64>::type>{
public:
    u64 kokkuvote;
    TreeSet():kokkuvote(0){}
     bool insert(const int x){
        const u64 tase=static_cast<u64>(1)<<x;
        if((kokkuvote&tase)!=0)return false;
        kokkuvote|=tase;
        return true;
    }
    bool erase(const int x){
        const u64 tase=static_cast<u64>(1)<<x;
        if((kokkuvote&tase)!=0){
            kokkuvote&=~tase;
            return true;
        }
        return false;
    }
    bool contains(const int x)const{
        return (kokkuvote&(static_cast<u64>(1)<<x))!=0;
    }

    int min()const{
        return __builtin_ctzll(kokkuvote);
    }
    int max()const{
        return 63-__builtin_clzll(kokkuvote);
    }
    int pred(const int x)const{
       const u64 mask=kokkuvote&~(~static_cast<u64>(0)<<x);
        if(mask==0)return -1;
        return 63-__builtin_clzll(mask);
    }
    int succ(const int x)const{
        const u64 mask=kokkuvote&(~static_cast<u64>(0)<<x);
        if(mask==0)return -1;
        return __builtin_ctzll(mask);
    }
};
