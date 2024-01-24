//source: https://codeforces.com/blog/entry/78564
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,T sum(T,T),T neg(T)>
struct BIT{
    vector<T>v;
    BIT(){}
    BIT(int n):v(n+1,0){}
    T get(int i){
        T res=0;
        for(;i>0;i-=i&-i)res=sum(res,v[i]);
        //cout<<i<<'='<<res<<endl;
        return res;
    }
    void add(int i,T vl){
        for(;i<(int)v.size();i+=i&-i)v[i]=sum(v[i],vl);
    }
};
template<typename T,T sum(T,T),T neg(T)>
class FenwickiPuuPuul{
    int N,M,koht=1;
    vector<vector<int>>hypped;
    vector<int>sugavus,alg,lopp;
    BIT<T,sum,neg> Puu;
    void dfs(int u,int p,const vector<vector<int>>&g){
        hypped[0][u]=p;
        sugavus[u]=sugavus[p]+1;
        alg[u]=koht++;
        for(auto v:g[u]){
            if(v==p)continue;
            dfs(v,u,g);
        }
        lopp[u]=koht++;
    }
public:
    //0-indekseerimine
    FenwickiPuuPuul(const vector<vector<int>>&g):N(g.size()),sugavus(N,-1),alg(N,-1),lopp(N,-1),Puu(2*N){
        M=__lg(N)+1;
        hypped.resize(M,vector<int>(N,0));
        dfs(0,0,g);
        for(int j=1;j<M;j++){
            for(int i=0;i<N;i++)hypped[j][i]=hypped[j-1][hypped[j-1][i]];
        }
    }
    void lisaServale(int u,int v,int vaartus){
        if(hypped[0][u]==v)swap(u,v);
        //u on v vanem
        Puu.add(alg[v],vaartus);
        Puu.add(lopp[v]+1,neg(vaartus));
    }

    int lca(int u,int v){
        if(sugavus[u]<sugavus[v])swap(u,v);
        for(int i=M-1;i>=0;i--){
            if(sugavus[u]-(1<<i)>=sugavus[v])u=hypped[i][u];
        }
        if(u==v)return u;
        for(int i=M-1;i>=0;i--){
            if(hypped[i][u]!=hypped[i][v]){
                u=hypped[i][u];
                v=hypped[i][v];
            }
        }
        return hypped[0][u];
    }
    T teekond(int u,int v){
        int L=lca(u,v);
        T vas=sum(Puu.get(alg[u]),Puu.get(alg[v]));
        vas=sum(vas,neg(Puu.get(alg[L])));
        vas=sum(vas,neg(Puu.get(alg[L])));
        return vas;
    }
};
int summa(int a,int b){
    return a+b;
}
int miinus(int a){
    return -a;
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ifstream cin("disconnect.in");
    ofstream cout("disconnect.out");
    int N,Q;
    cin>>N>>Q;
    vector<vector<int>>g(N);
    for(int i=1;i<N;i++){
        int u,v;cin>>u>>v;u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    FenwickiPuuPuul<int,summa,miinus> T(g);
    int v=0;
    while(Q--){
        int t, x, y;
        cin >> t >> x >> y;
        int a = x ^ v, b = y ^ v;
        if (t == 1) {
            T.lisaServale(a-1,b-1,1);
        } else {
            if (T.teekond(a-1,b-1)==0) {
                cout << "YES\n";
                v = a;
            } else {
                cout << "NO\n";
                v = b;
            }
        }
    }
    return 0;
}
