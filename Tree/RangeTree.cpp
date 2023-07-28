#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int M=3;
typedef array<int,M> vi;
template<int D>
struct RangeTree{
    vector<array<int,D+1>>vls;
    int n;
    vector<RangeTree<D-1>*>alampuud;
    RangeTree(vector<array<int,D+1>>& v){
        vls=v;
        n=vls.size();
        sort(vls.begin(),vls.end(),[] (const array<int,D+1>& a, const array<int,D+1>& b){return (a[D] < b[D]);});
        alampuud.resize(2*n);
        build(0,0,n-1);
    }
    void build(int i,int l,int r){
        if(l==r)return;
        int m=(l+r)/2;
        build(i*2+1,l,m);
        build(i*2+2,m+1,r);
        vector<array<int,D>> uusVec(r-l+1);
        for(int k=l;k<=r;k++){
            for(int j=0;j<D;j++)uusVec[k-l][j]=vls[k][j];
        }
        alampuud[i]=new RangeTree<D-1>(uusVec);
    }
    ll check_el(int i,vi& lef,vi& rig){
        for(int p=1;p<D;p++){
            if(vls[i][p]<lef[p]||vls[i][p]>rig[p])return 0;
        }
        return vls[i][0];
    }
    ll rangeSum(vi& lef,vi& rig){
        return rangeSum(0,0,n-1,lef,rig);
    }
    ll rangeSum(int i,int l,int r,vi& lef,vi& rig){
        if(vls[l][D]>=lef[D]&&vls[r][D]<=rig[D]){
            if(l==r)return check_el(l,lef,rig);
            return alampuud[i]->rangeSum(lef,rig);
        }
        if(vls[l][D]>rig[D]||vls[r][D]<lef[D])return 0;
        int m=(l+r)/2;
        return rangeSum(i*2+1,l,m,lef,rig)+rangeSum(i*2+2,m+1,r,lef,rig);
    }
};
template<> struct RangeTree<1>{
    typedef array<ll,2> pii;
    vector<ll>sum;
    vector<int>vls;
    RangeTree(vector<array<int,2>>& v){
        int n=v.size();
        vls.resize(n);
        sum.resize(n+1);
        sort(v.begin(),v.end(),[] (const array<int,2>& a, const array<int,2>& b){return (a[1] < b[1]);});
        for(int i=1;i<=n;i++)sum[i]=v[i-1][0]+sum[i-1];
        for(int i=0;i<n;i++)vls[i]=v[i][1];
    }
    ll rangeSum(vi& lef,vi & rig){
        ll l=lef[1],r=rig[1];
        ll parem=upper_bound(vls.begin(),vls.end(),r)-vls.begin();
        ll vasak=lower_bound(vls.begin(),vls.end(),l)-vls.begin();
        return sum[parem]-sum[vasak];
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<vi>vls(n);
    for(int i=0;i<n;i++){
        cin>>vls[i][2]>>vls[i][1]>>vls[i][0];
    }
    RangeTree<M-1>qs(vls);
    while(q--){
        int l,d,r,u;
        cin>>l>>d>>r>>u;
        vi lef,rig;
        lef[2]=l;
        lef[1]=d;
        rig[2]=r-1;
        rig[1]=u-1;
        cout<<qs.rangeSum(lef,rig)<<'\n';
    }
    return 0;
}
