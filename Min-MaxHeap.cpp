#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
class MinMaxHeap{
    vector<T>a;
    int n;
    void pushDown(int  m){
        while(hasChildren(m)){
            int i=m;
            if(onMinLevel(i)){
                m=extemumIndexOfChildGrandchild(i,true);
                if(a[m]<a[i]){
                    swap(a[m],a[i]);
                    if(mGrandChildOfi(m,i)){
                        if(a[m]>a[parent(m)])swap(a[m],a[parent(m)]);
                    }
                    else break;
                }else break;
            }else{
                m=extemumIndexOfChildGrandchild(i,false);
                if(a[m]>a[i]){
                    swap(a[m],a[i]);
                    if(mGrandChildOfi(m,i)){
                        if(a[m]<a[parent(m)])swap(a[m],a[parent(m)]);
                    }else break;
                }else break;
            }
        }
    }
    int parent(int i){
        return (i-1)/2;
    }
    int grandParent(int i){
        return parent(parent(i));
    }

    bool mGrandChildOfi(int m,int i){
        return parent(m)!=i;
    }

    bool hasChildren(int i){
        return (2*i+1)<n;
    }
    bool hasGrandParent(int i){
        return parent(i)!=0;
    }

    int extemumIndexOfChildGrandchild(int i,bool minimise){
        int res=2*i+1;
        if(minimise){
            if(2*i+2<n&&a[res]>a[2*i+2])res=2*i+2;
            if(4*i+3<n&&a[res]>a[4*i+3])res=4*i+3;
            if(4*i+4<n&&a[res]>a[4*i+4])res=4*i+4;
            if(4*i+5<n&&a[res]>a[4*i+5])res=4*i+5;
            if(4*i+6<n&&a[res]>a[4*i+6])res=4*i+6;
        }else{
            if(2*i+2<n&&a[res]<a[2*i+2])res=2*i+2;
            if(4*i+3<n&&a[res]<a[4*i+3])res=4*i+3;
            if(4*i+4<n&&a[res]<a[4*i+4])res=4*i+4;
            if(4*i+5<n&&a[res]<a[4*i+5])res=4*i+5;
            if(4*i+6<n&&a[res]<a[4*i+6])res=4*i+6;
        }
        return res;
    }

    bool onMinLevel(int i){
        if(i==0)return true;
        return (__builtin_clz(i+1)&1)!=0;
    }

    void pushUp(int i){
        if(i==0)return;
        int p=parent(i);
        if(onMinLevel(i)){
            if(a[i]>a[p]){
                swap(a[i],a[p]);
                pushUpMax(p);
            }else pushUpMin(i);
        }else{
            if(a[i]<a[p]){
                swap(a[i],a[p]);
                pushUpMin(p);
            }else pushUpMax(i);
        }
    }


    void pushUpMin(int i){
        while(hasGrandParent(i)&&a[i]<a[grandParent(i)]){
            swap(a[i],a[grandParent(i)]);
            i=grandParent(i);
        }
    }
    void pushUpMax(int i){
        while(hasGrandParent(i)&&a[i]>a[grandParent(i)]){
            swap(a[i],a[grandParent(i)]);
            i=grandParent(i);
        }
    }
public:
     MinMaxHeap(){
        n=0;
    }
    MinMaxHeap(vector<T> &a):a(a){
        n=a.size();
        for(int i=n-1;i>=0;i--)pushDown(i);
    }
    void insert(T val){
        a.push_back(val);
        n++;
        pushUp(n-1);
    }

    T getMin(){
        return a[0];
    }

    T getMax(){
        if(n==1)return a[0];
        if(n==2)return a[1];
        return max(a[1],a[2]);
    }

    T removeMin(){
        T res=a[0];
        swap(a[0],a[n-1]);
        n--;
        a.pop_back();
        pushDown(0);
        return res;
    }

     T removeMax(){
        int ps=0;
        if(n>=2&&a[ps]<a[1])ps=1;
        if(n>=3&&a[ps]<a[2])ps=2;
        T res=a[ps];
        swap(a[ps],a[n-1]);
        n--;
        a.pop_back();
        pushDown(ps);
        return res;
    }

    bool empty(){
        return n;
    }
    void print(){
        for(auto el:a)cout<<el<<' ';
        cout<<endl;
    }
};
