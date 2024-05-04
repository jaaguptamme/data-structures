#include <bits/stdc++.h>
//IDEE: https://codeforces.com/blog/entry/57516?#comment-412071
typedef long long ll;
using namespace std;
class DSUMisTipud{//Saab teada kõik tipud komponendis, lisamine konstantse ajaga
    int n,komponente;
    vector<int>ulemus;//-suurus,+ulemus
    vector<int>jargmine;
    public:
    DSUMisTipud(int n):n(n),komponente(n),ulemus(n,-1),jargmine(n){
        iota(jargmine.begin(),jargmine.end(),0);
    }
    int F(int u){
        if(ulemus[u]<0)return u;
        return ulemus[u]=F(ulemus[u]);
    }
    bool uhenda(int u,int v){
        u=F(u);
        v=F(v);
        if(u==v)return false;
        swap(jargmine[u],jargmine[v]);
        if(ulemus[u]>ulemus[v])swap(u,v);
        ulemus[u]+=ulemus[v];
        ulemus[v]=u;
        komponente--;
        return true;
    }
    vector<int> loeKoik(int u){
        vector<int>vas;
        int alg=u;
        while(true){
            vas.push_back(u);
            u=jargmine[u];
            if(u==alg)break;
        }
        return vas;
    }
    bool samas(int u,int v){
        return F(u)==F(v);
    }
    int komponendiSuurus(int u){
        return -ulemus[F(u)];
    }
    int komponenteKokku(){
        return komponente;
    }
    vector<vector<int>> koikKomponendid(){
        vector<vector<int>>vastus;
        for(int i=0;i<n;i++){
            if(F(i)==i)vastus.push_back(loeKoik(i));
        }
        return vastus;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,M;
    cin>>N>>M;
    vector<vector<int>>sees(N);
    while(M--){
        int a,b;
        cin>>a>>b;
        sees[a].push_back(b);
        sees[b].push_back(a);
    }
    for(int i=0;i<N;i++)sort(sees[i].begin(),sees[i].end());
    DSUMisTipud T(N);
    int eelmine=-1;
    for(int i=0;i<N;i++){
        if(sees[i].size()>=N/2){
            auto& v=sees[i];
            int koht=0;
            for(int j=0;j<N;j++){
                if(koht<v.size()&&v[koht]==j)koht++;
                else T.uhenda(i,j);
            }
        }else{
            if(eelmine!=-1)T.uhenda(eelmine,i);
            eelmine=i;
        }
    }

    cout<<T.komponenteKokku()<<'\n';
    for(int i=0;i<N;i++){
        if(T.F(i)==i){
            auto e=T.loeKoik(i);
            cout<<e.size()<<' ';
            for(auto el:e)cout<<el<<' ';
            cout<<'\n';
        }
    }
    return 0;
}
