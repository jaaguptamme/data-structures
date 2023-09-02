//source: https://mzhang2021.github.io/cp-blog/kruskal/
struct DSU{
    vector<int>p;
    int n;
    DSU(int SZ,int n):p(SZ),n(n+1){
        iota(begin(p),end(p),0);
    }
    int F(int u){
        if(u==p[u])return u;
        return p[u]=F(p[u]);
    }
    void addEdge(int u,int v){
        u=F(u),v=F(v);
        p[u]=p[v]=n;
        g[n].push_back(u);
        if(u!=v)g[n].push_back(v);
        n++;
    }
};
