#include <bits/stdc++.h>
//source: https://anz1217.tistory.com/50
typedef long long ll;
using namespace std;
struct BMATCH{
    int left,right,flow=0;
    vector<vector<int>>g;
    vector<int>matchFromLeft,matchFromRight,dist;
    BMATCH(int l,int r):left(l),right(r),g(l),matchFromLeft(l,-1),matchFromRight(r,-1),dist(l){}
    void add(int u,int v){
        g[u].push_back(v);
    }
    void bfs(){
        queue<int>q;
        for(int i=0;i<left;i++){
            if (!~matchFromLeft[i]){
                q.push(i);
                dist[i]=0;
            }else dist[i]=-1;
        }
        while(!q.empty()){
            int u=q.front();q.pop();
            for(auto v:g[u]){
                if(~matchFromRight[v]&&!~dist[matchFromRight[v]]){
                    dist[matchFromRight[v]]=dist[u]+1;
                    q.push(matchFromRight[v]);
                }
            }
        }
    }
    bool dfs(int u){
        for(auto v:g[u]){
            if(!~matchFromRight[v]){
                matchFromLeft[u]=v;matchFromRight[v]=u;
                return true;
            }
        }
        for(auto v:g[u]){
            if(dist[matchFromRight[v]]==dist[u]+1&&dfs(matchFromRight[v])){
                matchFromLeft[u]=v,matchFromRight[v]=u;
                return true;
            }
        }
        return false;
    }
    int getMaxMatching(){
        while(true){
            bfs();
            int cur=0;
            for(int u=0;u<left;u++){
                if(!~matchFromLeft[u])cur+=dfs(u);
            }
            if(!cur)break;
            flow+=cur;
        }
        return flow;
    }
    pair<vector<int>,vector<int>> minVertexCover(){
        vector<int>L,R;
        for(int i=0;i<left;i++){
            if(!~dist[i])L.push_back(i);
            else if(~matchFromLeft[i])R.push_back(matchFromLeft[i]);
        }
        return {L,R};
    }
    vector<pair<int,int>> getEdges(){
        vector<pair<int,int>>res;
        for(int i=0;i<left;i++){
            if(matchFromLeft[i]!=-1)res.push_back({i,matchFromLeft[i]});
        }
        return res;
    }
};
