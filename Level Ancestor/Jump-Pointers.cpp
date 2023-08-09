#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Tree{
    vector<vector<int>>g;
    int n,m;
    vector<int>dfs_num,dep,dfs_ord;
    int pos=0;
    vector<vector<int>>jump_pointers;
    Tree(){}
    Tree(const vector<vector<int>>&g):g(g){
        n=g.size();
        dfs_num.resize(n);
        dep.resize(n);
        m=log2(n)+1;
        jump_pointers.resize(m,vector<int>(n,0));
        dfs(0);
        for(int j=1;j<m;j++){
            for(int i=0;i<n;i++)jump_pointers[j][i]=jump_pointers[j-1][jump_pointers[j-1][i]];
        }
    }
    void dfs(int u,int pr=-1,int d=0){
        dfs_ord.push_back(u);
        dfs_num[u]=pos++;
        dep[u]=d;
        if(pr!=-1)jump_pointers[0][dfs_num[u]]=dfs_num[pr];
        for(auto v:g[u]){
            if(v==pr)continue;
            dfs(v,u,d+1);
        }
    }
    int get_kth(int node,int k){
        if(dep[node]<k)return -1;
        node=dfs_num[node];
        for(int i=m-1;i>=0;i--){
            if(k&(1<<i)){
                node=jump_pointers[i][node];
            }
        }
        return dfs_ord[node];
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
    for(auto el:t.dfs_num)cout<<el<<' ';
    while(true){
        int a,b;
        cin>>a>>b;
        cout<<t.get_kth(a,b)<<endl;
    }
    return 0;
}
