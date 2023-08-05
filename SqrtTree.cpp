#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,T op(T,T)>
class SqrtTree{
    vector<T>vec;
    vector<int>on_layer,layer_lg;
    vector<vector<T>>pref,suf,btwn;
    public:
    SqrtTree(vector<T>& vec):vec(vec){
        int n=vec.size(),lg=0;
        while((1<<lg)<n)lg++;
        on_layer.resize(lg+1);
        int n_layer=0;
        for(int i=lg;i>1;i=(i+1)/2){
            on_layer[i]=n_layer++;
            layer_lg.push_back(i);
        }
        for(int i=lg-1;i>=0;i--)on_layer[i]=max(on_layer[i],on_layer[i+1]);
        pref.resize(n_layer,vector<T>(1<<lg));
        suf.resize(n_layer,vector<T>(1<<lg));
        btwn.resize(n_layer,vector<T>(1<<lg));
        for(int lay=0;lay<n_layer;lay++){
            int prev_b_sz=1<<layer_lg[lay];
            int b_sz=1<<((layer_lg[lay]+1)/2);
            int b_cnt=1<<(layer_lg[lay]/2);
            for(int l=0;l<n;l+=prev_b_sz){
                int r=min(l+prev_b_sz,n);
                for(int a=l;a<r;a+=b_sz){
                    int b=min(a+b_sz,r);
                    pref[lay][a]=vec[a];
                    for(int i=a+1;i<b;i++)pref[lay][i]=op(pref[lay][i-1],vec[i]);
                    suf[lay][b-1]=vec[b-1];
                    for(int i=b-2;i>=a;i--)suf[lay][i]=op(vec[i],suf[lay][i+1]);
                }
                for(int i=0;i<b_cnt;i++){
                    T vl=suf[lay][l+i*b_sz];
                    btwn[lay][l+i*b_cnt+i]=vl;
                    for(int j=i+1;j<b_cnt;j++){
                        vl=op(vl,suf[lay][l+j*b_sz]);
                        btwn[lay][l+i*b_cnt+j]=vl;
                    }
                }
            }
        }
    }
    T get(int l,int r){//0 based [l,r]
        if(l==r)return vec[l];
        if(l+1==r)return op(vec[l],vec[r]);
        int lay=on_layer[32-__builtin_clz(l ^ r)];
        int b_sz=1<<((layer_lg[lay]+1)/2);
        int b_cnt=1<<(layer_lg[lay]/2);
        int a=(l>>layer_lg[lay])<<layer_lg[lay];
        int lb=(l-a)/b_sz+1;
        int rb=(r-a)/b_sz-1;
        T vl=suf[lay][l];
        if(lb<=rb)vl=op(vl,btwn[lay][a+lb*b_cnt+rb]);
        vl=op(vl,pref[lay][r]);
        return vl;
    }
};
