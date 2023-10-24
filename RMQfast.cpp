//source: https://codeforces.com/blog/entry/78931
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,int B=30>
class RMQ{
    vector<T>ar;
    int n;
    const int nb;
    vector<int>mask,st;
    int vaiksem(int i,int j){
        return ar[i]<ar[j]?i:j;
    }
    int vahimBit(int i){
        return i&(-i);
    }
    int suurimaBitiIndeks(int i){
        return __builtin_clz(1)-__builtin_clz(i);
    }
    int vaike(int r,int suurus=B){
        return r-suurimaBitiIndeks(mask[r]&((1<<suurus)-1));
    }
    public:
    RMQ(const vector<T>&ar):ar(ar),n(ar.size()),mask(n),st(n),nb(n/B){
        int msk=0;
        for(int i=0;i<n;i++){
            msk=(msk<<1)&((1<<B)-1);
            while(msk>0&&vaiksem(i,i-suurimaBitiIndeks(vahimBit(msk)))==i)msk^=vahimBit(msk);
             msk|=1;
            mask[i]=msk;
        }
        for(int i=0;i<n/B;i++)st[i]=vaike(B*i+B-1);
        for(int j=1;(1<<j)<=n/B;j++){
            for(int i=0;i+(1<<j)<=n/B;i++){
                st[nb*j+i]=vaiksem(st[nb*(j-1)+i],st[nb*(j-1)+i+(1<<(j-1))]);
            }
        }
    }
    T saa(int l,int r){//[l,r]
        if(r-l+1<=B)return ar[vaike(r,r-l+1)];
        int va=vaiksem(vaike(l+B-1),vaike(r));
        int v=l/B+1,p=r/B-1;
        if(v<=p){
            int j=suurimaBitiIndeks(p-v+1);
            va=vaiksem(va,vaiksem(st[nb*j+v],st[nb*j+p-(1<<j)+1]));
        }
        return ar[va];
    }
};
