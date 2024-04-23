#include <bits/stdc++.h>
typedef long long ll;
//source: https://ningenme.github.io/comulo-library/non-verified/Union_Find_Tree_Persistence.cpp
using namespace std;
class DSUPysivus{//O(log n) uuendused ja püsivad päringud
    vector<map<int,int>>ul;
    vector<int>tase,viimane;
    int cnt=0;
    public:
    DSUPysivus(int N):ul(N),tase(N,1),viimane(N,0){
        for(int i=0;i<N;i++)ul[i][0]=i;
    }
    int juur(int n,int t){
        return t>=viimane[n]&&ul[n][viimane[n]]!=n?juur(ul[n][viimane[n]],t):n;
    }
    void uhenda(int n,int m){
        n=juur(n,cnt);
        m=juur(m,cnt);
        cnt++;
        if(n==m)return;
        if(tase[n]<tase[m]){
            ul[n][cnt]=m;
            viimane[n]=cnt;
        }else{
            ul[m][cnt]=n;
            viimane[m]=cnt;
            if(tase[n]==tase[m])tase[n]++;
        }
    }
    bool samas(int n,int m,int t){
        return juur(n,t)==juur(m,t);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,M;
    cin>>N>>M;
    DSUPysivus T(N);
    for(int i=1;i<N;i++){
        int u,v;cin>>u>>v;
        T.uhenda(u,v);
    }
    while(M--){
        int u,v,t;
        cin>>u>>v>>t;
        cout<<T.samas(u,v,t)<<'\n';
    }
    return 0;
}
