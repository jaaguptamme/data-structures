vector<int>g[N];
class HLD{
    int n,ind;
    vector<int>sz,biggestN,pos,dep,par,head,en;
    F fen;
    void build(int u,int pr){
        sz[u]++;
        int biggestSz=0;
        for(auto v:g[u]){
            if(v==pr)continue;
            dep[v]=dep[u]+1;
            par[v]=u;
            build(v,u);
            sz[u]+=sz[v];
            if(sz[v]>biggestSz){
                biggestSz=sz[v];
                biggestN[u]=v;
            }
        }
    }
    void dfs(int u,int clss){
        pos[u]=ind++;
        head[u]=clss;
        if(biggestN[u]!=-1)dfs(biggestN[u],clss);
        for(auto v:g[u]){
            if(v==par[u]||v==biggestN[u])continue;
            dfs(v,v);
        }
        en[u]=ind-1;
    }

    public:
    HLD(int n_arg):fen(n_arg){
        n=n_arg;
        ind=1;
        sz.resize(n);
        biggestN=vector<int>(n,-1);
        pos.resize(n);
        dep.resize(n);
        par.resize(n);
        head.resize(n);
        en.resize(n);
        build(0,-1);
        dfs(0,0);
    }

    ll query(int a,int b){
        ll ans=0;
        while(head[a]!=head[b]){
            if(dep[head[a]]<dep[head[b]])swap(a,b);
            ll val=fen.get(pos[head[a]],pos[a]);
            ans+=val;
            a=par[head[a]];
        }
        if(pos[a]>pos[b])swap(a,b);
        ll val=fen.get(pos[a],pos[b]);
        ans+=val;
        return ans;
    }

    ll getSubTreeSum(int a){
        return fen.get(pos[a],en[a]);
    }

    void add(int a,int x){
        fen.add(pos[a],x);
    }
};
