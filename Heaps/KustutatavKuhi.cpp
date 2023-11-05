#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,int D>
class dHeap{
int n;
vector<T>a;
    void pushUp(int i){
        if(i==0)return;
        int p=parent(i);
        if(a[p]>a[i]){
            swap(a[p],a[i]);
            pushUp(p);
        }
    }
    void pushDown(int i){
        int vl=i;
        int mx=min(D*i+D,n-1);
        for(int j=D*i+1;j<=mx;j++){
            if(a[j]<a[vl])vl=j;
        }
        if(a[vl]<a[i]){
            swap(a[i],a[vl]);
            pushDown(vl);
        }
    }
    int parent(int i){
        return (i-1)/D;
    }
public:
    dHeap(){
      n=0;
    }
    dHeap(vector<T>& a):a(a){
        n=a.size();
        for(int i=n-1;i>=0;i--)pushDown(i);
    }
    T getMin(){
        return a[0];
    }

    T removeMin(){
        T res=a[0];
        swap(a[0],a[n-1]);
        n--;
        a.pop_back();
        pushDown(0);
        return res;
    }
    void insert(const T& v){
        a.push_back(v);
        n++;
        pushUp(n-1);
    }
    bool empty(){
        return n==0;
    }
};
//source: https://rsk0315.github.io/library-rs/nekolib/ds/removable_heap/index.html
template<typename T,int D>
class KustutatavKuhi{
    dHeap<T,D> olemas,maha;
    int pikkus;
    public:
    KustutatavKuhi():pikkus(0){}
    void lisa(const T& v){
        olemas.insert(v);
        pikkus++;
    }
    void eemalda(const T&  v){
        pikkus--;
        maha.insert(v);
        suru();
    }
    T getMin(){
        return olemas.getMin();
    }
    T removeMin(){
        T vaartus=olemas.removeMin();
        pikkus--;
        suru();
        return vaartus;
    }
    void suru(){
        while(!maha.empty()&&!olemas.empty()&&maha.getMin()==olemas.getMin()){
            maha.removeMin();
            olemas.removeMin();
        }
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    KustutatavKuhi<int,4> K;
    const int N=1000*1000;
    for(int i=0;i<N;i++)K.lisa(i);
    for(int i=1;i<N;i+=2)K.eemalda(i);
    for(int i=0;i<N;i+=2){
        assert(K.removeMin()==i);
    }
    return 0;
}
