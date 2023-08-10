#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Tree{
    int n,JUMPCONST;
    vector<int>dep,par;
    vector<int>dfs_num,dfs_ord;
    vector<int>jump_desc;
    vector<int>ladder_num;
    vector<int>mx_child,subtree_sz;
    int pos=0,micro_sum=0;
    vector<vector<int>>ladders;
    unordered_map<int,vector<int>>jump_pointers;
    unordered_map<int,vector<vector<int>>>micro_nodes;
    vector<int>micro_comp,micro_head;
    Tree(){}
    Tree(vector<vector<int>>&g){
        n=g.size();
        JUMPCONST=max(1,(int)(log2(n)/4));
        dfs_num.resize(n);
        dep.resize(n);
        subtree_sz.resize(n);
        mx_child.resize(n,-1);
        par.resize(n,-1);
        ladders.resize(n);
        ladder_num.resize(n);
        jump_desc.resize(n,-1);
        dfs(0,-1,0,g);
        dfs_ladders(0,-1,0,g);
        extend_ladders();
        find_jump_nodes(0,g);
        compute_jump_ancestors();
        micro_comp.resize(n);
        micro_head.resize(n,-1);
        for(int i=0;i<n;i++){
            if(jump_desc[i]==-1&&micro_head[i]==-1){
                pos=0;
                micro_sum=0;
                process_micro(i,i,g);
                micro_comp[i]=micro_sum;
                if(!micro_nodes.count(micro_sum)){
                    micro_nodes[micro_sum].resize(JUMPCONST);
                    process_micro_subtree(i,i,micro_sum,g);
                }
            }
        }
    }
    void process_micro(int u,int mic_head,vector<vector<int>>&g){
        micro_head[u]=mic_head;
        for(auto v:g[u]){
            if(v==par[u])continue;
            pos++;
            micro_sum+=1<<pos;
            process_micro(v,mic_head,g);
        }
        pos++;
    }
    void process_micro_subtree(int u,int mic_head,int micro_sum,vector<vector<int>>&g){
        int nw=u;
        micro_nodes[micro_sum][dfs_num[u]-dfs_num[mic_head]].push_back(dfs_num[nw]-dfs_num[mic_head]);
        while(nw!=mic_head){
            nw=par[nw];
            micro_nodes[micro_sum][dfs_num[u]-dfs_num[mic_head]].push_back(dfs_num[nw]-dfs_num[mic_head]);
        }
        for(auto v:g[u]){
            if(v==par[u])continue;
            process_micro_subtree(v,mic_head,micro_sum,g);
        }
    }

    int dfs(int u,int pr,int d,vector<vector<int>>&g){
        dfs_ord.push_back(u);
        dfs_num[u]=pos++;
        dep[u]=d;
        int height=0;
        int height_mx_child=-1;
        if(pr!=-1)par[u]=pr;
        for(auto v:g[u]){
            if(v==pr)continue;
            int heightv=dfs(v,u,d+1,g);
            height=max(height,heightv+1);
            if(mx_child[u]==-1||height_mx_child<heightv){
                mx_child[u]=v;
                height_mx_child=heightv;
            }
        }
        return height;
    }
    void dfs_ladders(int u,int pr,int lad,vector<vector<int>>&g){
        ladders[lad].push_back(u);
        ladder_num[u]=lad;
        if(mx_child[u]!=-1)dfs_ladders(mx_child[u],u,lad,g);
        for(auto v:g[u]){
            if(v==pr||v==mx_child[u])continue;
            dfs_ladders(v,u,v,g);
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

    int find_jump_nodes(int u,vector<vector<int>>&g){
        int mxsz=0;
        for(auto v:g[u]){
            if(v==par[u])continue;
            jump_desc[u]=max(jump_desc[u],find_jump_nodes(v,g));
            subtree_sz[u]+=subtree_sz[v]+1;
            mxsz=max(mxsz,subtree_sz[v]);
        }
        if(mxsz<JUMPCONST && subtree_sz[u]>=JUMPCONST){
            jump_desc[u]=u;
            return u;
        }
        return jump_desc[u];
    }
    void compute_jump_ancestors(){
        for(int u=0;u<n;u++){
            if(jump_desc[u]==u)compute_jump_ancestors(u);
        }
    }
    void compute_jump_ancestors(int u){
        int st=u;
        for(int i=0;;i++){
            int uus=ladder_get_kth(u,i==0?1:(1<<(i-1)));
            if(uus==-1)return;
            jump_pointers[st].push_back(uus);
            u=uus;
        }
    }
    int ladder_get_kth(int node,int k){
        if(dep[node]<k)return -1;
        int lad=ladder_num[node];
        int to_lad_start=dep[node]-dep[ladders[lad][0]];
        if(to_lad_start>=k)return ladders[lad][to_lad_start-k];
        return ladder_get_kth(par[ladders[lad][0]],k-to_lad_start-1);
    }
    int get_kth(int node,int k){
        if(dep[node]<k)return -1;
        if(k==0)return node;
        if(jump_desc[node]!=-1){
            int new_node=jump_desc[node];
            int new_k=k-dep[node]+dep[new_node];
            return process_jump(new_node,new_k);
        }
        int parent=micro_head[node];
        int comp=micro_comp[parent];
        int vl=dfs_num[node]-dfs_num[parent];
        if((int)micro_nodes[comp][vl].size()>k){
            return dfs_ord[dfs_num[parent]+micro_nodes[comp][vl][k]];
        }
        return get_kth(par[parent],k-micro_nodes[comp][vl].size());
    }
    int process_jump(int node,int k){
        if(k==0)return node;
        int msb=31-__builtin_clz(k);
        node=jump_pointers[node][msb];
        k-=1<<msb;
        return ladder_get_kth(node,k);
    }
};
