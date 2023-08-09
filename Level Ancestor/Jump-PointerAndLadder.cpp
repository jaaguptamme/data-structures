#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Tree{
    vector<vector<int>>g;
    int n,m;
    vector<int>dfs_num,dep,dfs_ord;
    vector<int>height,mx_child,par,ladder_num;
    int pos=0;
    vector<vector<int>>jump_pointers,ladders;
    Tree(){}
    Tree(const vector<vector<int>>&g):g(g){
        n=g.size();
        dfs_num.resize(n);
        dep.resize(n);
        height.resize(n);
        mx_child.resize(n,-1);
        par.resize(n,-1);
        m=log2(n)+1;
        jump_pointers.resize(m,vector<int>(n,0));
        ladders.resize(n);
        ladder_num.resize(n);
        dfs(0);
        for(int j=1;j<m;j++){
            for(int i=0;i<n;i++)jump_pointers[j][i]=jump_pointers[j-1][jump_pointers[j-1][i]];
        }
        dfs_ladders(0,-1,0);
        extend_ladders();
    }
    void dfs(int u,int pr=-1,int d=0){
        dfs_ord.push_back(u);
        dfs_num[u]=pos++;
        dep[u]=d;
        height[u]=0;
        if(pr!=-1){
            par[u]=pr;
            jump_pointers[0][dfs_num[u]]=dfs_num[pr];
        }
        for(auto v:g[u]){
            if(v==pr)continue;
            dfs(v,u,d+1);
            height[u]=max(height[u],height[v]+1);
            if(mx_child[u]==-1||height[mx_child[u]]<height[v]){
                mx_child[u]=v;
            }
        }
    }
    void dfs_ladders(int u,int pr,int lad){
        ladders[lad].push_back(u);
        ladder_num[u]=lad;
        if(mx_child[u]!=-1)dfs_ladders(mx_child[u],u,lad);
        for(auto v:g[u]){
            if(v==pr)continue;
            if(v==mx_child[u])continue;
            dfs_ladders(v,u,v);
        }
    }
    void extend_ladders(){
        for(int i=0;i<n;i++){
            if(ladders[i].empty())continue;
            int kuni=ladders[i].size();
            int tipp=par[ladders[i][0]];
            reverse(ladders[i].begin(),ladders[i].end());
            while(kuni>0&&tipp!=-1){
                ladders[i].push_back(tipp);
                tipp=par[tipp];
                kuni--;
            }
            reverse(ladders[i].begin(),ladders[i].end());
        }
    }

    int get_kth(int node,int k){
        if(k==0)return node;
        if(dep[node]<k)return -1;
        int msb=31-__builtin_clz(k);
        node=dfs_ord[jump_pointers[msb][dfs_num[node]]];
        k-=1<<msb;
        int lad=ladder_num[node];
        int pos=dep[node]-dep[ladders[lad][0]]-k;
        node=ladders[lad][pos];
        return node;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<vector<int>>g(n);
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    Tree t(g);
    for(auto el:t.height)cout<<el<<' ';
    cout<<endl;
    for(int i=0;i<n;i++){
        if(t.ladders[i].size()){
            for(auto el:t.ladders[i])cout<<el<<' ';
            cout<<endl;
        }
    }
    while(true){
        int a,b;
        cin>>a>>b;
        cout<<t.get_kth(a,b)<<endl;
    }
    return 0;
}
