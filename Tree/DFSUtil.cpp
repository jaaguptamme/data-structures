struct DFS{//assume graph G
    vector<int>st,en,ind;//start, end and indexes of all nodes
    int pos;
    DFS(int sz,int root):st(sz),en(sz),ind(sz){
        pos=0;
        dfs(root);
    }
    void dfs(int u){
        st[u]=pos;
        ind[pos]=u;
        pos++;
        for(auto v:g[u])dfs(v);
        en[u]=pos-1;
    }
};
