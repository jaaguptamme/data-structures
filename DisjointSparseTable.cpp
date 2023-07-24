#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,T op(T,T)>
struct DST{
    vector<vector<T>>table;
    DST(vector<T>& a){
        int n=a.size();
        int hei=0;
        while((1<<hei)<n)hei++;
        hei++;
        table.resize(hei,vector<T>(n));
        for(int i=0;i<n;i++)table[0][i]=a[i];
        for(int i=1;i<hei;i++){
            int ln=1<<i;
            for(int cen=0;cen+ln/2<n;cen+=ln){
                int m=cen+ln/2;
                table[i][m-1]=a[m-1];
                for(int j=m-2;j>=cen;j--)table[i][j]=op(a[j],table[i][j+1]);
                table[i][m]=a[m];
                for(int j=m+1;j<min(cen+ln,n);j++)table[i][j]=op(table[i][j-1],a[j]);
            }
        }
    }
    T get(int l,int r){//0 based [l,r]
        if(l==r)return table[0][l];
        int i=32-__builtin_clz(l xor r);
        return op(table[i][l],table[i][r]);
    }
};
