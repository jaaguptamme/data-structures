#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>
struct ST{
    T* mn;
    int* lg;
    int n;
    ST(){}
    ST(vector<T>& A){
        n=A.size();
        lg=new int[n+1];
        for(int i=1;i<=n;i++)lg[i]=log2(i);
        int m=log2(n);
        mn=new T[(m+1)*n];
        for(int i=0;i<n;i++)mn[i]=A[i];
        for(int j=1;j<=m;j++){
            for(int i=0;i+(1<<j)<=n;i++)mn[j*n+i]=min(mn[(j-1)*n+i],mn[(j-1)*n+i+(1<<(j-1))]);
        }
    }
    ST(T A[],int n){
        this->n=n;
        lg=new int[n+1];
        for(int i=1;i<=n;i++)lg[i]=log2(i);
        int m=log2(n);
        mn=new T[(m+1)*n];
        for(int i=0;i<n;i++)mn[i]=A[i];
        for(int j=1;j<=m;j++){
            for(int i=0;i+(1<<j)<=n;i++)mn[j*n+i]=min(mn[(j-1)*n+i],mn[(j-1)*n+i+(1<<(j-1))]);
        }
    }
    T get(int s,int e){
        int ln=lg[e+1-s];
        return min(mn[ln*n+s],mn[ln*n+e+1-(1<<ln)]);
    }
};
template<typename T>
struct FH{
    ST<T> sparse_table;
    int b;
    T* W;
    unordered_map<int,int*>mns;
    int* treenum;
    T* dq;
    FH(vector<T>& vals){
        int n=vals.size();
        W=new T[n];
        for(int i=0;i<n;i++)W[i]=vals[i];
        b=max(1.0,(log2(n)+3)/4);
        dq=new T[b];
        vector<T>current;
        T* global=new T[n/b+(n%b!=0)];
        int global_pos=0;
        treenum=new int[n];
        int treenum_cnt=0;
        for(int i=0;i<n;i++){
            current.push_back(vals[i]);
            if((i+1)%b==0 || i==n-1){
                global[global_pos++]=*min_element(current.begin(),current.end());
                int vl=calc(current);
                treenum[treenum_cnt++]=vl;
                if(!mns.count(vl))build(current,vl);
                current.clear();
            }
        }
        sparse_table=ST<T>(global,global_pos);
    }

    int calc(vector<T>& A){
        int back=0;
        int res=0;
        int place=2*b-1;
        for(auto el:A){
            while(back&&dq[back-1]>el){
                place--;
                back--;
            }
            res+=1<<place;
            place--;
            dq[back++]=el;
        }
        return res;
    }
    void build(vector<T>& A,int vl){
        int* R=new int[b*b];
        //vector<vector<int>>R;
        //A.resize(b);
        //R.resize(b,vector<int>(b,0));
        for(int i=0;i<b;i++)R[i*b+i]=i;
        for(int i=0;i<b;i++){
            for(int j=i+1;j<b;j++)R[i*b+j]=A[R[i*b+j-1]]<A[j]?R[i*b+j-1]:j;
        }
        mns[vl]=R;
    }
    T get(int i,int j){
        int bi=i/b,bj=j/b;
        if(i>j)exit(0);
        if(bi==bj){
            auto V=mns[treenum[bi]];
            int ii=i%b;
            int ij=j%b;
            return W[bi*b+V[ii*b+ij]];
        }
        else if(bi+1==bj){
            T left=W[bi*b+mns[treenum[bi]][(i%b)*b+b-1]];
            T right=W[bj*b+mns[treenum[bj]][j%b]];
            return min(left,right);
            }else{
            T left=W[bi*b+mns[treenum[bi]][(i%b)*b+b-1]];
            T right=W[bj*b+mns[treenum[bj]][j%b]];
            T mid=sparse_table.get(bi+1,bj-1);
            return min(left,min(mid,right));
        }
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    vector<int>a;
    cin>>n>>q;
    for(int i=0;i<n;i++){
        int el;cin>>el;a.push_back(el);
    }
    FH<int> t=FH<int>(a);
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
