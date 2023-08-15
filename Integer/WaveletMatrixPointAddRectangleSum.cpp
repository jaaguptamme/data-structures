#include <bits/stdc++.h>
//source: https://ei1333.github.io/library/structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
typedef long long ll;
using namespace std;
struct F{
    vector<ll>dp;
    int n;
    F()=default;
    F(int n){
        this->n=n+1;
        dp.resize(n+1);
    }
    void add(ll pos,ll vl){
        while(pos<n){
            dp[pos]+=vl;
            pos+=pos&(-pos);
        }
    }
    ll get(ll pos){
        ll res=0;
        while(pos>0){
            res+=dp[pos];
            pos-=pos&(-pos);
        }
        return res;
    }
    ll get(ll l,ll r){
        return get(r)-get(l-1);
    }
};
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
template<typename T,int MXLOG>//normal type, log of maxvalue
struct WaveletMatrixPointAddRectangleSum{
    int len;
    SuccintIndexableDictionary mat[MXLOG];
    F fen[MXLOG];
    vector<T> v;
    int mid[MXLOG];
    WaveletMatrixPointAddRectangleSum()=default;
    WaveletMatrixPointAddRectangleSum(const vector<T>& v,const vector<ll> &d):len(v.size()),v(v){
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
            fen[lev]=F(len);
            for(int i=0;i<len;i++)fen[lev].add(i+1,d[ord[i]]);
        }
    }
    pair<int,int> succ(bool f,int l,int r,int lev){
        return {mat[lev].rank(f,l)+mid[lev]*f,mat[lev].rank(f,r)+mid[lev]*f};
    }
    //sum d[i] (l<=i<r) v[i]<up
    ll rect_sum(int l,int r,T up){
        ll res=0;
        for(int lev=MXLOG-1;lev>=0;lev--){
            if((up>>lev)&1){
                auto nxt=succ(false,l,r,lev);
                res+=fen[lev].get(nxt.first+1,nxt.second);
                l=l-nxt.first+mid[lev];
                r=r-nxt.second+mid[lev];
            }else tie(l,r)=succ(false,l,r,lev);
        }
        return res;
    }
    ll rect_sum(int l,int r,T low,T up){
        return rect_sum(l,r,up)-rect_sum(l,r,low);
    }
    void point_add(int k,const ll &x){
        auto &y=v[k];
        for(int lev=MXLOG-1;lev>=0;lev--){
            bool f=((y>>lev)&1);
            k=mat[lev].rank(f,k)+mid[lev]*f;
            fen[lev].add(k+1,x);
        }
    }
};
template<typename T,int MXLOG>
struct CompressedWaveletMatrixPointAddRectangleSum{
    WaveletMatrixPointAddRectangleSum<int,MXLOG>mat;
    vector<T>ys;
    CompressedWaveletMatrixPointAddRectangleSum(const vector<T>&v,const vector<ll>&d):ys(v){
        sort(begin(ys),end(ys));
        ys.erase(unique(begin(ys),end(ys)),end(ys));
        vector<int>t(v.size());
        for(int i=0;i<v.size();i++)t[i]=get(v[i]);
        mat=WaveletMatrixPointAddRectangleSum<int,MXLOG>(t,d);
    }
    inline int get(const T &x){
        return lower_bound(begin(ys),end(ys),x)-begin(ys);
    }
    ll rect_sum(int l,int r,T up){
        return mat.rect_sum(l,r,get(up));
    }
    ll rect_sum(int l,int r,T low,T up){
        return mat.rect_sum(l,r,get(low),get(up));
    }
    void point_add(int k,const ll &x){
        mat.point_add(k,x);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<int>x(n),y(n),w(n);
    vector<pair<int,int>>xs;
    for(int i=0;i<n;i++){
        cin>>x[i]>>y[i]>>w[i];
        xs.push_back({x[i],y[i]});
    }
    vector<int>t(q),a(q),b(q),c(q),d(q);
    for(int i=0;i<q;i++){
        cin>>t[i]>>a[i]>>b[i]>>c[i];
        if(t[i]==0)xs.push_back({a[i],b[i]});
        else cin>>d[i];
    }
    sort(xs.begin(),xs.end());
    xs.erase(unique(begin(xs),end(xs)),end(xs));
    vector<int>ys(xs.size());
    for(int i=0;i<xs.size();i++)ys[i]=xs[i].second;
    vector<ll>ws(xs.size());
    for(int i=0;i<n;i++){
        x[i]=lower_bound(begin(xs),end(xs),make_pair(x[i],y[i]))-begin(xs);
        ws[x[i]]+=w[i];
    }
    for(int i=0;i<q;i++){
        if(t[i]==0){
            a[i]=lower_bound(begin(xs),end(xs),make_pair(a[i],b[i]))-begin(xs);
        }else{
            a[i]=lower_bound(begin(xs),end(xs),make_pair(a[i],-1))-begin(xs);
            c[i]=lower_bound(begin(xs),end(xs),make_pair(c[i],-1))-begin(xs);
        }
    }
    CompressedWaveletMatrixPointAddRectangleSum<int,18>mat(ys,ws);
    for(int i=0;i<q;i++){
        if(t[i]==0)mat.point_add(a[i],c[i]);
        else cout<<mat.rect_sum(a[i],c[i],b[i],d[i])<<'\n';
    }
    return 0;
}
