#include <bits/stdc++.h>
//source https://blog.naver.com/jinhan814/222511581119
//single source shortest path, works well for small integer edge weights
//complexity O(V*maxw+E)
typedef long long ll;
using namespace std;
template<typename Graph>
vector<int>Dial(Graph& g,int s,int maxw){//edges in range [0,maxw)
    vector<vector<int>>qs(maxw);
    vector<int>dist(g.size(),-1);
    dist[s]=0;
    qs[0].push_back(s);
    for(int d=0,maxd=0;d<=maxd;d++){
        for(auto& q=qs[d%maxw];q.size();){
            auto u=q.back();q.pop_back();
            if(dist[u]!=d)continue;
            for(auto el:g[u]){
                auto v=el.first,w=el.second;
                if(dist[v]!=-1 && dist[v]<=d+w)continue;
                dist[v]=d+w;
                qs[(d+w)%maxw].push_back(v);
                maxd=max(maxd,d+w);
            }
        }
    }
    return dist;
}
