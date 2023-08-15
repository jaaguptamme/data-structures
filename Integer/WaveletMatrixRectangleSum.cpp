#include <bits/stdc++.h>
//source:https://ei1333.github.io/library/structure/wavelet/wavelet-matrix-rectangle-sum.hpp
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
    //set kth bit
    void set(int k){
        bit[k>>5]|=1U << (k&31);
    }
    void build(){
        sum[0]=0U;
        for(int i=1;i<blocks;i++)sum[i]=sum[i-1]+__builtin_popcount(bit[i-1]);
    }
    //get val of kth bit
    bool operator[](int k){
        return (bool((bit[k>>5]>>(k&31))&1));
    }
    //number of 1 bits set <k
    int rank(int k){
        return (sum[k>>5]+ __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));
    }
    int rank(bool val,int k){
        return (val?rank(k):k-rank(k));
    }
};
template<typename T,int MXLOG,typename D>//normal type, log of maxvalue, sum type
struct WaveletMatrixRectangleSum{
    int len;
    SuccintIndexableDictionary mat[MXLOG];
    vector<D>ds[MXLOG];
    int mid[MXLOG];
    WaveletMatrixRectangleSum()=default;
    WaveletMatrixRectangleSum(vector<T>&v,vector<D>&d):len(v.size()){
        vector<int>l(len),r(len),ord(len);
        iota(begin(ord),end(ord),0);
        for(int lev=MXLOG-1;lev>=0;lev--){
            mat[lev]=SuccintIndexableDictionary(len+1);
            int lef=0,rig=0;
            for(int i=0;i<len;i++){
                if((v[ord[i]]>>lev)&1){
                    mat[lev].set(i);
                    r[rig++]=ord[i];
                }else l[lef++]=ord[i];
            }
            mid[lev]=lef;
            mat[lev].build();
            ord.swap(l);
            for(int i=0;i<rig;i++)ord[lef+i]=r[i];
            ds[lev].resize(len+1);
            ds[lev][0]=D();
            for(int i=0;i<len;i++)ds[lev][i+1]=ds[lev][i]+d[ord[i]];
        }
    }
    pair<int,int> succ(bool f,int l,int r,int lev){
        return {mat[lev].rank(f,l)+mid[lev]*f,mat[lev].rank(f,r)+mid[lev]*f};
    }
    //sum d[i] (l<=i<i) v[i]<up
    D rect_sum(int l,int r,T up){
        D res=0;
        for(int lev=MXLOG-1;lev>=0;lev--){
            bool f=((up>>lev)&1);
            if(f)res+=ds[lev][mat[lev].rank(false,r)]-ds[lev][mat[lev].rank(false,l)];
            tie(l,r)=succ(f,l,r,lev);
        }
        return res;
    }
    D rect_sum(int l,int r,T low,T up){
        return rect_sum(l,r,up)-rect_sum(l,r,low);
    }
};
template<typename T,int MXLOG,typename D>
struct CompressedWaveletMatrixRectangleSum{
    WaveletMatrixRectangleSum<int,MXLOG,D>mat;
    vector<T>sortedys;
    CompressedWaveletMatrixRectangleSum()=default;
    CompressedWaveletMatrixRectangleSum(vector<T>&y,vector<D>&w):sortedys(y){
        sort(sortedys.begin(),sortedys.end());
        sortedys.erase(unique(sortedys.begin(),sortedys.end()),sortedys.end());
        vector<int>nwys(y.size());
        for(int i=0;i<(int)y.size();i++){
            nwys[i]=get(y[i]);
        }
        mat=WaveletMatrixRectangleSum<int,MXLOG,D>(nwys,w);
    }
    int get(T& y){
        return lower_bound(sortedys.begin(),sortedys.end(),y)-sortedys.begin();
    }

    //sum d[i] (l<=i<i) v[i]<up
    D rect_sum(int l,int r,T up){
        return mat.rect_sum(l,r,get(up));
    }
    D rect_sum(int l,int r,T low,T up){
        return mat.rect_sum(l,r,get(low),get(up));
    }
};
template<typename T,typename D>
class StaticRectangleSum{
    CompressedWaveletMatrixRectangleSum<T,18,D> wmrs;
    vector<pair<T,int>>xs;
    public:
    StaticRectangleSum(vector<T>&x,vector<T>&y,vector<D>&w){
        int n=x.size();
        xs.resize(n);
        for(int i=0;i<n;i++)xs[i]={x[i],i};
        sort(xs.begin(),xs.end());
        vector<T>ys(n);
        vector<D>ws(n);
        for(int i=0;i<n;i++){
            x[i]=lower_bound(begin(xs),end(xs),make_pair(x[i],i))-begin(xs);
            ys[x[i]]=y[i];
            ws[x[i]]=w[i];
        }
        wmrs=CompressedWaveletMatrixRectangleSum<T,18,D>(ys,ws);
    }
    D query(T l,T r,T d,T u){
        int L=lower_bound(begin(xs),end(xs),make_pair(l,-1))-begin(xs);
        int R=lower_bound(begin(xs),end(xs),make_pair(r,-1))-begin(xs);
        return wmrs.rect_sum(L,R,d,u);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<int>x(n),y(n);
    vector<ll>w(n);
    for(int i=0;i<n;i++)cin>>x[i]>>y[i]>>w[i];
    StaticRectangleSum<int,ll>srs(x,y,w);
    while(q--){
        ll l,r,d,u;
        cin>>l>>d>>r>>u;
        cout<<srs.query(l,r,d,u)<<'\n';
    }
    return 0;
}
