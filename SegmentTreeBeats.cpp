#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Beats{
    static constexpr ll INF=LLONG_MAX/2.1;
    struct Tipp{
        ll sum=0,mn1=0,mx1=0,mx2=-INF,mn2=INF,add=0;
        int mnc=1,mxc=1;
    };
    vector<Tipp>dp;
    int n;
    Beats(){}
    Beats(int n):Beats(vector<ll>(n)){}
    Beats(const vector<ll>&vec){
        n=vec.size();
        int sz=1;
        while(sz<(int)vec.size())sz*=2;
        dp.resize(2*sz);
        build(1,0,n-1,vec);
    }
    void build(int i,int l,int r,const vector<ll>&vec){
        if(l==r){
            dp[i].sum=dp[i].mn1=dp[i].mx1=vec[l];
            return;
        }
        int m=(l+r)/2;
        build(i*2,l,m,vec);build(i*2+1,m+1,r,vec);
        up(i);
    }
    void range_chmin(int l,int r,ll x){update<1>(l,r,x);}
    void range_chmax(int l,int r,ll x){update<2>(l,r,x);}
    void range_add(int l,int r,ll x){update<3>(l,r,x);}
    void range_update(int l,int r,ll x){update<4>(l,r,x);}
    ll range_min(int l,int r){return query<1>(l,r);}
    ll range_max(int l,int r){return query<2>(l,r);}
    ll range_sum(int l,int r){return query<3>(l,r);}
    private:
    void up(int i){
        Tipp& p=dp[i];
        Tipp& l=dp[i*2];
        Tipp& r=dp[i*2+1];
        p.sum=l.sum+r.sum;
        if(l.mx1==r.mx1){
            p.mx1=l.mx1;
            p.mx2=max(l.mx2,r.mx2);
            p.mxc=l.mxc+r.mxc;
        }else{
            bool f=l.mx1>r.mx1;
            p.mx1=f?l.mx1:r.mx1;
            p.mxc=f?l.mxc:r.mxc;
            p.mx2=max(f?r.mx1:l.mx1,f?l.mx2:r.mx2);
        }
        if(l.mn1==r.mn1){
            p.mn1=l.mn1;
            p.mn2=min(l.mn2,r.mn2);
            p.mnc=l.mnc+r.mnc;
        }else{
            bool f=l.mn1<r.mn1;
            p.mn1=f?l.mn1:r.mn1;
            p.mnc=f?l.mnc:r.mnc;
            p.mn2=min(f?r.mn1:l.mn1,f?l.mn2:r.mn2);
        }
    }
    void push_add(int i,int l,int r,ll x){
        Tipp& p=dp[i];
        p.sum+=x*(r-l+1);
        p.mn1+=x;
        p.mx1+=x;
        if(p.mx2!=-INF)p.mx2+=x;
        if(p.mn2!=INF)p.mn2+=x;
        p.add+=x;
    }
    void push_min(int i,int l,int r,ll x){
        Tipp& p=dp[i];
        p.sum+=(x-p.mx1)*p.mxc;
        if(p.mn1==p.mx1)p.mn1=x;
        if(p.mn2==p.mx1)p.mn2=x;
        p.mx1=x;
    }
    void push_max(int i,int l,int r,ll x){
        Tipp& p=dp[i];
        p.sum+=(x-p.mn1)*p.mnc;
        if(p.mx1==p.mn1)p.mx1=x;
        if(p.mx2==p.mn1)p.mx2=x;
        p.mn1=x;
    }
    void push(int i,int l,int r){
        Tipp& p=dp[i];
        int m=(l+r)/2;
        if(p.add!=0){
            push_add(i*2,l,m,p.add);
            push_add(i*2+1,m+1,r,p.add);
            p.add=0;
        }
        if(p.mx1<dp[i*2].mx1)push_min(i*2,l,m,p.mx1);
        if(p.mn1>dp[i*2].mn1)push_max(i*2,l,m,p.mn1);
        if(p.mx1<dp[i*2+1].mx1)push_min(i*2+1,m+1,r,p.mx1);
        if(p.mn1>dp[i*2+1].mn1)push_max(i*2+1,m+1,r,p.mn1);
    }
    void subtree_chmin(int i,int l,int r,ll x){
        if(dp[i].mx1<=x)return;
        if(dp[i].mx2<x){
            push_min(i,l,r,x);
            return;
        }
        int m=(l+r)/2;
        push(i,l,r);
        subtree_chmin(i*2,l,m,x);
        subtree_chmin(i*2+1,m+1,r,x);
        up(i);
    }
    void subtree_chmax(int i,int l,int r,ll x){
        if(x<=dp[i].mn1)return;
        if(x<dp[i].mn2){
            push_max(i,l,r,x);
            return;
        }
        int m=(l+r)/2;
        push(i,l,r);
        subtree_chmax(i*2,l,m,x);
        subtree_chmax(i*2+1,m+1,r,x);
        up(i);
    }
    template<int CMD>
    void _apply(int i,int l,int r,ll x){
        if (CMD==1)subtree_chmin(i,l,r,x);
        if (CMD==2)subtree_chmax(i,l,r,x);
        if (CMD==3)push_add(i,l,r,x);
        if (CMD==4)subtree_chmin(i,l,r,x),subtree_chmax(i,l,r,x);
    }
    template<int CMD>
    void update(int l,int r,ll x){
        update<CMD>(1,0,n-1,l,r,x);
    }
    template<int CMD>
    void update(int i,int l,int r,int se,int en,ll x){
        if(se<=l&&r<=en){
            _apply<CMD>(i,l,r,x);
            return;
        }
        if(l>en||r<se)return;
        int m=(l+r)/2;
        push(i,l,r);
        update<CMD>(i*2,l,m,se,en,x);
        update<CMD>(i*2+1,m+1,r,se,en,x);
        up(i);
    }

    template<int CMD>
    ll query(int l,int r){
        return query<CMD>(1,0,n-1,l,r);
    }

    template<int CMD>
    ll e(){
        if (CMD==1)return INF;
        if (CMD==2)return -INF;
        if (CMD==3)return 0;
    }

    template<int CMD>
    void op(ll& a,Tipp& b){
        if (CMD==1)a=min(a,b.mn1);
        if (CMD==2)a=max(a,b.mx1);
        if (CMD==3)a+=b.sum;
    }

    template<int CMD>
    ll query(int i,int l,int r,int se,int en){
        ll res=e<CMD>();
        if(se<=l&&r<=en){
            op<CMD>(res,dp[i]);
            return res;
        }
        if(l>en||r<se)return res;
        int m=(l+r)/2;
        push(i,l,r);
        ll nw=query<CMD>(i*2,l,m,se,en);
        if (CMD==1)res=min(res,nw);
        if (CMD==2)res=max(res,nw);
        if (CMD==3)res+=nw;
        nw=query<CMD>(i*2+1,m+1,r,se,en);
        if (CMD==1)res=min(res,nw);
        if (CMD==2)res=max(res,nw);
        if (CMD==3)res+=nw;
        return res;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<ll>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    Beats t(a);
    while(q--){
        int op,l,r;
        ll b;
        cin>>op>>l>>r;
        r--;
        if(op==3){
            cout<<t.range_sum(l,r)<<'\n';
            continue;
        }
        cin>>b;
        if(op==0){
            t.range_chmin(l,r,b);
        }else if(op==1){
            t.range_chmax(l,r,b);
        }else{
            t.range_add(l,r,b);
        }
    }
    return 0;
}
