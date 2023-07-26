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
    void insert(T& v){
        a.push_back(v);
        n++;
        pushUp(n-1);
    }
};
