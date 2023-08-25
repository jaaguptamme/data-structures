#include <bits/stdc++.h>
//source: https://blog.naver.com/jinhan814/222627110424
//works for any associative operation with an identity element?
//init in O(n) or O(n log n)
//query in O(n)
typedef long long ll;
using namespace std;
template<typename T,T f(T,T)>//andmetüüp, arvutatav funktsioon
class Fenwick{
    int n;
    T id;
    vector<T> vec,F1,F2;
    public:
    Fenwick(int n,T id):n(n),id(id),vec(n+1,id),F1(n+1,id),F2(n+1,id){}
     Fenwick(int n,T id,vector<T> &a):n(n),id(id),vec(n+1,id),F1(n+1,id),F2(n+1,id){//O(n) init works for operations like min,max,sum
        for(int i=0;i<n;i++){
            vec[i+1]=F1[i+1]=F2[i+1]=a[i];
        }
        for(int i=1;i<=n;i++){
            if(i+(i&-i)<=n)F1[i+(i&-i)]=f(F1[i],F1[i+(i&-i)]);
        }
        for(int i=n;i;i--)F2[i-(i&-i)]=f(F2[i-(i&-i)],F2[i]);
    }
    void update(int i,const T &vl){
        T t=vec[i]=vl;
        for(int j=i,l=i-1,r=i+1;j<=n;j+=j&-j){
            while(l>j-(j&-j))t=f(F1[l],t),l-=l&-l;
            while(r<j)t=f(t,F2[r]),r+=r&-r;
            F1[j]=i xor j ? f(t,vec[j]):t;
        }
        t=vl;
        for(int j=i,l=i-1,r=i+1;j>0;j-=j&-j){
            while(l>j)t=f(F1[l],t),l-=l&-l;
            while(r<=n&&r<j+(j&-j))t=f(t,F2[r]),r+=r&-r;
            F2[j]=i xor j?f(vec[j],t):t;
        }
    }
    T get(int l,int r){
        T L=id,R=id;
        int i;
        for(i=l;i+(i&-i)<=r;i+=i&-i)L=f(L,F2[i]);
        for(i=r;i-(i&-i)>=l;i-=i&-i)R=f(F1[i],R);
        return f(f(L,vec[i]),R);
    }
};
ll MIN(ll a,ll b){
    return a+b;
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<ll>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    Fenwick<ll,MIN>fen(n,0,a);
    while(q--){
        int l,r;cin>>l>>r;
        l++;
        cout<<fen.get(l,r)<<'\n';
    }
    return 0;
}
