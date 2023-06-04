#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
struct ST{
    vector<vector<int>>mn;
    vector<int>lg;
    ST(){}
    ST(vector<int>& A){
        int n=A.size();
        lg.resize(n+1,0);
        for(int i=1;i<=n;i++)lg[i]=log2(i);
        int m=log2(n);
        mn.resize(m+1,vector<int>(n,0));
        for(int i=0;i<n;i++)mn[0][i]=A[i];
        for(int j=1;j<=m;j++){
            for(int i=0;i+(1<<j)<=n;i++)mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<(j-1))]);
        }
    }
    int get(int s,int e){
        int ln=lg[e+1-s];
        return min(mn[ln][s],mn[ln][e+1-(1<<ln)]);
    }
};
struct FH{
    ST sparse_table;
    int b;
    vector<int>W;
    unordered_map<int,vector<vector<int>>>mns;
    vector<int>treenum;
    FH(vector<int>& vals){
        W=vals;
        int n=vals.size();
        b=max(1.0,(log2(n)+3)/4);
        vector<int>current;
        vector<int>global;
        for(int i=0;i<n;i++){
            current.push_back(vals[i]);
            if((i+1)%b==0 || i==n-1){
                global.push_back(*min_element(current.begin(),current.end()));
                int vl=calc(current);
                treenum.push_back(vl);
                if(!mns.count(vl))build(current,vl);
                current={};
            }
        }
        sparse_table=ST(global);
    }
    int calc(vector<int>& A){
        deque<int>dq;
        int res=0;
        int place=2*b-1;
        for(auto el:A){
            while(dq.size()&&dq.back()>el){
                place--;
                dq.pop_back();
            }
            res+=1<<place;
            place--;
            dq.push_back(el);
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
    int get(int i,int j){
        int bi=i/b,bj=j/b;
        if(i>j)exit(0);
        if(bi==bj){
            auto V=mns[treenum[bi]];
            int ii=i%b;
            int ij=j%b;
            return W[bi*b+V[ii][ij]];
        }
        else if(bi+1==bj){
            int left=W[bi*b+mns[treenum[bi]][i%b][b-1]];
            int right=W[bj*b+mns[treenum[bj]][0][j%b]];
            return min(left,right);
        }else{
            int left=W[bi*b+mns[treenum[bi]][i%b][b-1]];
            int right=W[bj*b+mns[treenum[bj]][0][j%b]];
            int mid=sparse_table.get(bi+1,bj-1);
            return min(left,min(mid,right));
        }
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    vector<int>a;//={1};
    cin>>n>>q;
    for(int i=0;i<n;i++){
        int el;cin>>el;a.push_back(el);
    }
    FH t=FH(a);
    /*for(int i=0;i<a.size();i++){
        for(int j=i;j<a.size();j++){
            cout<<i<<' '<<j<<' '<<t.get(i,j)<<'\n';
        }
    }*/
    //vector<int>b={27,18,28,18,28,45,90,45,23,53,60,28,74,71,35};
    //cout<<t.calc(b)<<endl;
    for(int i=0;i<q;i++){
        int l,r;cin>>l>>r;
        cout<<t.get(l,r-1)<<'\n';
    }
    return 0;
}
