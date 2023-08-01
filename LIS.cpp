#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
vector<int> LIS(vector<T>&a){
    int n=a.size();
    vector<int>p(n),m(n+1);
    m[0]=-1;//undefined so any value
    int L=0;//|LIS| found so far
    for(int i=0;i<n;i++){
        int lo=1;
        int hi=L+1;
        while(lo<hi){//bsearsh for smallest l<=L : a[m[l]]>x[i]
            int mid=lo+(hi-lo)/2;//lo<=mid<hi
            if(a[m[mid]]>=a[i])hi=mid;
            else lo=mid+1;
        }
        int newL=lo;
        p[i]=m[newL-1];//pred of X[i] is new last index of subseq of lenth new-1
        m[newL]=i;
        L=max(L,newL);
    }
    vector<int>res(L);
    int k=m[L];
    for(int j=L-1;j>=0;j--){
        res[j]=k;
        k=p[k];
    }
    return res;
}
