#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
struct ST{
    vector<vector<int>>mn;
    vector<int>lg;
    vector<T> A;
    ST(){}
    ST(vector<T>& A):A(A){
        int n=A.size();
        lg.resize(n+1,0);
        for(int i=1;i<=n;i++)lg[i]=log2(i);
        int m=log2(n);
        mn.resize(m+1,vector<int>(n));
        for(int i=0;i<n;i++)mn[0][i]=i;
        for(int j=1;j<=m;j++){
            for(int i=0;i+(1<<j)<=n;i++)mn[j][i]=MIN(mn[j-1][i],mn[j-1][i+(1<<(j-1))]);
        }
    }
    int MIN(int i,int j){
        if(A[i]<A[j])return i;
        return j;
    }
    int get(int s,int e){
        int ln=lg[e+1-s];
        return MIN(mn[ln][s],mn[ln][e+1-(1<<ln)]);
    }
};
struct RMQPMONE{//RMQ+-1
    ST<int> spartab;
    vector<int>treenum;
    unordered_map<int,vector<vector<int>>>mns;
    vector<int>vals;
    int b;
    RMQPMONE()=default;
    RMQPMONE(vector<int> &a){
        vals=a;
        int n=a.size();
        b=log2(n)/2;
        b=max(1,b);
        vector<int>current;
        vector<int>global;
        for(int i=0;i<n;i++){
            current.push_back(a[i]);
            if((i+1)%b==0 || i==n-1){
                global.push_back(*min_element(current.begin(),current.end()));
                transpose(current);
                int vl=getNum(current);
                treenum.push_back(vl);
                if(!mns.count(vl))build(current,vl);
                current={};
            }
        }
        spartab=ST<int>(global);
    }
    void transpose(vector<int>&a){
        int vl=a[0];
        for(auto &el:a)el-=vl;
    }

    int getNum(vector<int>&a){
        int res=0;
        for(int i=0;i+1<a.size();i++){
            if(a[i]>a[i+1])res+=1<<i;
        }
        return res;
    }

     void build(vector<int>& A,int vl){
        vector<vector<int>>R;
        A.resize(b);
        R.resize(b,vector<int>(b,0));
        for(int i=0;i<b;i++)R[i][i]=i;
        for(int i=0;i<b;i++){
            for(int j=i+1;j<b;j++)R[i][j]=A[R[i][j-1]]<A[j]?R[i][j-1]:j;
        }
        mns[vl]=R;
    }
    int get(int i,int j){//0-based [i,j]
        int bi=i/b,bj=j/b;
        if(i>j)exit(0);
        if(bi==bj)return bi*b+mns[treenum[bi]][i%b][j%b];
        else if(bi+1==bj){
                int lef=bi*b+mns[treenum[bi]][i%b][b-1];
                int rig=bj*b+mns[treenum[bj]][0][j%b];
                if(vals[lef]<vals[rig])return lef;
                return rig;
        }else{
            int lef=bi*b+mns[treenum[bi]][i%b][b-1];
            int rig=bj*b+mns[treenum[bj]][0][j%b];
            int mid=spartab.get(bi+1,bj-1);
            mid=b*mid+mns[treenum[mid]][0][b-1];
            if(vals[mid]<=vals[lef]&&vals[mid]<=vals[rig])return mid;
            if(vals[lef]<=vals[mid]&&vals[lef]<=vals[rig])return lef;
            return rig;
        }
    }
};
class LCATORMQ{//0 based indexing
    int n,ind;
    vector<int>ET;
    vector<int>fir;
    vector<int>level;
    RMQPMONE rmq;

    void dfs(int u,int pr,int dep,vector<vector<int>>&g){
        int pos=ind++;
        ET[pos]=u;
        level[pos]=dep;
        fir[u]=pos;
        for(auto v:g[u]){
            if(v==pr)continue;
            dfs(v,u,dep+1,g);
            pos=ind++;
            ET[pos]=u;
            level[pos]=dep;
        }
    }
    public:
    LCATORMQ()=default;
    LCATORMQ(vector<vector<int>>&g,int root=0){
        n=g.size();
        ET.resize(2*n-1);
        fir.resize(n);
        level.resize(2*n-1);
        ind=0;
        dfs(root,-1,0,g);
        rmq=RMQPMONE(level);
    }
    int get(int u,int v){
        int l=fir[u],r=fir[v];
        return ET[rmq.get(min(l,r),max(l,r))];
    }
};
template<typename T>
class RMQ{
    LCATORMQ lca;
    vector<T>a;
    public:
    RMQ(vector<T>&a):a(a){
        int n=a.size();
        vector<vector<int>>g(n);
        vector<int>res(n,-1);
        deque<int>dq;
        for(int i=0;i<n;i++){
            while(dq.size()&&a[dq.back()]>=a[i])dq.pop_back();
            if(dq.size())res[i]=dq.back();
            dq.push_back(i);
        }
        dq={};
        for(int i=n-1;i>=0;i--){
            while(dq.size()&&a[dq.back()]>a[i])dq.pop_back();
            if(dq.size()){
                if(res[i]==-1)res[i]=dq.back();
                else res[i]=a[res[i]]>a[dq.back()]?res[i]:dq.back();
            }
            dq.push_back(i);
        }
        int rt=-1;
        for(int i=0;i<n;i++){
            if(res[i]!=-1)g[res[i]].push_back(i);
            else rt=i;
        }
        lca=LCATORMQ(g,rt);
    }
    T get(int l,int r){
        return a[lca.get(l,r)];
    }
};
