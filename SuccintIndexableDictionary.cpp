#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct SuccintIndexableDictionary{
    int len,blocks;
    typedef unsigned u;
    vector<u>bit,sum;
    SuccintIndexableDictionary(int len){
        this->len=len;
        blocks=(len+31)>>5;
        bit.assign(blocks,0U);
        sum.assign(blocks,0U);
    }
    void set(int k){
        bit[k>>5]|=1U << (k&31);
    }
    void build(){
        sum[0]=0U;
        for(int i=1;i<blocks;i++)sum[i]=sum[i-1]+__builtin_popcount(bit[i-1]);
    }
    bool operator[](int k){
        return (bool((bit[k>>5]>>(k&31))&1));
    }
    int rank(int k){
        return (sum[k>>5]+ __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));
    }
    int rank(bool val,int k){
        return (val?rank(k):k-rank(k));
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*1000*100;
    SuccintIndexableDictionary t(N);
    for(int i=0;i<N;i+=2){
        t.set(i);
    }
    t.build();
    for(int i=0;i<N;i++){
        assert(t[i]==!(i%2));
        assert(t.rank(i)==(i+1)/2);
    }
    return 0;
}
