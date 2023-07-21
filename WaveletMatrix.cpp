#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct SuccintIndexableDictionary{
    int len,blocks;
    typedef unsigned u;
    vector<u>bit,sum;
    SuccintIndexableDictionary()=default;
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
template<typename T,int MXLOG>
struct WaveletMatrix{
    int len;
    SuccintIndexableDictionary mat[MXLOG];
    int mid[MXLOG];
    WaveletMatrix()=default;
    WaveletMatrix(vector<T>& vec){
        len=vec.size();
        vector<T> l(len),r(len);
        for(int lev=MXLOG-1;lev>=0;lev--){
            mat[lev]=SuccintIndexableDictionary(len+1);
            int lef=0,rig=0;
            for(int i=0;i<len;i++){
                if((vec[i]>>lev)&1){
                    mat[lev].set(i);
                    r[rig++]=vec[i];
                }else l[lef++]=vec[i];
            }
            mid[lev]=lef;
            mat[lev].build();
            vec.swap(l);
            for(int i=0;i<rig;i++)vec[lef+i]=r[i];
        }
    }
    typedef pair<int,int> pii;
    pii succ(bool f,int l,int r,int lev){
        return {mat[lev].rank(f,l)+mid[lev]*f,mat[lev].rank(f,r)+mid[lev]*f};
    }
    //v[k]
    T get_position(int k){
        T vas=0;
        for(int lev=MXLOG-1;lev>=0;lev--){
            bool f=mat[lev][k];
            if(f)vas|=T(1)<<lev;
            k=mat[lev].rank(f,k)+mid[lev]*f;
        }
        return vas;
    }
    T operator[](const int &k){
        return get_position(k);
    }
    //number of i<r:v[i]==k
    int rank(T& k,int r){
        int l=0;
        for(int lev=MXLOG-1;lev>=0;lev--)tie(l,r)=succ((k>>lev)&1,l,r,lev);
        return r-l;
    }
    //k,l,r are 0-based
    T kth_smallest(int l,int r,int k){
        assert(0 <= k && k < r - l);
        T vas=0;
        for(int lev=MXLOG-1;lev>=0;lev--){
            int cnt=mat[lev].rank(0,r)-mat[lev].rank(0,l);
            bool f=cnt<=k;
            if(f){
                vas|=T(1)<<lev;
                k-=cnt;
            }
            tie(l,r)=succ(f,l,r,lev);
        }
        return vas;
    }
    T kth_largest(int l,int r,int k){
        return kth_smallest(l,r,r-l-k-1);
    }
    //count i such that l <=i < r and v[i]<up
    int range_freq(int l,int r,T up){
        int vas=0;
        for(int lev=MXLOG-1;lev>=0;lev--){
            bool f=((up>>lev)&1);
            if(f)vas+=mat[lev].rank(0,r)-mat[lev].rank(0,l);
            tie(l,r)=succ(f,l,r,lev);
        }
        return vas;
    }
    //count i that (l<= i < r) and (low <= v[i] < up)
    int range_freq(int l,int r,T low,T up){
        return range_freq(l,r,up)-range_freq(l,r,low);
    }
    //maximal v[i] : v[i]<up
    T prev_val(int l,int r, T up){
        int cnt=range_freq(l,r,up);
        return cnt==0?T(-1):kth_smallest(l,r,cnt-1);
    }
    //minimal v[i] : v[i]>=low
    T next_val(int l,int r,T low){
        int cnt=range_freq(l,r,low);
        return cnt==r-l?T(-1):kth_smallest(l,r,cnt);
    }
};
template<typename T,int MXLOG>
struct CompressedWaveletMatrix{
    WaveletMatrix<int,MXLOG>mat;
    vector<T>vls;
    CompressedWaveletMatrix(vector<T>& vec):vls(vec){
        sort(vls.begin(),vls.end());
        vls.erase(unique(vls.begin(),vls.end()),vls.end());
        vector<int>nw(vec.size());
        for(int i=0;i<vec.size();i++)nw[i]=get(vec[i]);
        mat=WaveletMatrix<int,MXLOG>(nw);
    }
    //x->its compressed int
    int get(T& x){
        return lower_bound(vls.begin(),vls.end(),x)-vls.begin();
    }
    //vec[k]
    T get_position(int k){
        return vls[mat[k]];
    }
    //vec[k]
    T operator[](int &k){
        return get_position(k);
    }
    //number of i<r:v[i]==k
    int rank(T &k,int r){
        auto ind=get(k);
        if(ind==vls.size()||vls[ind]!=k)return 0;
        return mat.rank(ind,r);
    }
    //k,l,r are 0-based
    T kth_smallest(int l,int r,int k){
        return vls[mat.kth_smallest(l,r,k)];
    }
    T kth_largest(int l,int r,int k){
        return vls[mat.kth_largest(l,r,k)];
    }
    //count i such that l <=i < r and v[i]<up
    int range_freq(int l,int r,T up){
        return mat.range_freq(l,r,get(up));
    }
    //count i that (l<= i < r) and (low <= v[i] < up)
    int range_freq(int l,int r,T low,T up){
        return mat.range_freq(l,r,get(low),get(up));
    }
    //maximal v[i] : v[i]<up, or -1
    T prev_val(int l,int r,T up){
        auto vas=mat.prev_val(l,r,get(up));
        return (vas==-1)?T(-1):vls[vas];
    }
    //minimal v[i] : v[i]>=low, or -1
    T next_val(int l,int r,T low){
        auto vas=mat.next_val(l,r,get(low));
        return (vas==-1)?T(-1):vls[vas];
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*1000;
    vector<int>a(N);
    for(int i=0;i<N;i++)a[i]=i;
    CompressedWaveletMatrix<int,20>w(a);
    for(int i=0;i<N;i++){
        assert(w.get_position(i)==i);
    }
    for(int i=0;i<N;i++){
        assert(w.rank(i,i)==0);
        assert(w.rank(i,i+1)==1);
        assert(w.kth_smallest(0,i+1,i)==i);
        assert(w.kth_largest(0,i+1,0)==i);
        assert(w.range_freq(0,i+1,i)==i);
        assert(w.prev_val(0,N,i)==(i-1));
        assert(w.next_val(0,N,i)==i);
    }
    return 0;
}
