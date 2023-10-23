#include <bits/stdc++.h>
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
