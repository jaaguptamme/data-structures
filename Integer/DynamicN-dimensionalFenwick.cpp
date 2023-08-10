#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAXN=1000*1000*1000+5;
template<typename T,typename D,int M>//T is index type, D sum type, and M is dimension
struct DynamicFenwick{
    unordered_map<T,DynamicFenwick<T,D,M-1>>fens;
    void add_point(vector<T>& loc,D &val){//location,value, loc 1-based
        T stpos=loc.back();loc.pop_back();
        T pos=stpos;
        while(pos<MAXN){
            fens[pos].add_point(loc,val);
            pos+=pos&(-pos);
        }
        loc.push_back(stpos);
    }
    D get(vector<T>& l,vector<T>&r){//[l,r]
        T posl=l.back();l.pop_back();
        T posr=r.back();r.pop_back();
        T pos=posl-1;
        D res=0;
        while(pos>0){
            if(fens.count(pos))res-=fens[pos].get(l,r);
            pos-=pos&(-pos);
        }
        pos=posr;
        while(pos>0){
            if(fens.count(pos))res+=fens[pos].get(l,r);
            pos-=pos&(-pos);
        }
        l.push_back(posl);
        r.push_back(posr);
        //cout<<posl<<'Q'<<posr<<endl;
        return res;
    }
};
template<typename T,typename D>
struct DynamicFenwick<T,D,1>{
    unordered_map<T,D>dp;
     void add_point(vector<T>& loc,D &val){//location,value, loc 1-based
        T stpos=loc.back();loc.pop_back();
        T pos=stpos;
        while(pos<MAXN){
            dp[pos]+=val;
            pos+=pos&(-pos);
        }
        loc.push_back(stpos);
    }
    D get(vector<T>& l,vector<T>&r){//[l,r]
        T posl=l.back();l.pop_back();
        T posr=r.back();r.pop_back();
        T pos=posl-1;
        D res=0;
        while(pos>0){
            if(dp.count(pos))res-=dp[pos];
            pos-=pos&(-pos);
        }
        pos=posr;
        while(pos>0){
            if(dp.count(pos))res+=dp[pos];
            pos-=pos&(-pos);
        }
        l.push_back(posl);
        r.push_back(posr);
        //cout<<posl<<'r'<<posr<<'S'<<res<<endl;
        return res;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    DynamicFenwick<int,ll,2>fen;
    int n,q;
    cin>>n>>q;
    while(n--){
        int x,y;
        ll w;
        cin>>x>>y>>w;
        vector<int>loc={y+1,x+1};
        fen.add_point(loc,w);
    }
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int l,d,r,u;
            cin>>l>>d>>r>>u;
            vector<int>v={d+1,l+1};
            vector<int>p={u,r};
            cout<<fen.get(v,p)<<'\n';
        }else{
            int x,y;
            ll w;
            cin>>x>>y>>w;
            vector<int>loc={y+1,x+1};
            fen.add_point(loc,w);
        }
    }
    return 0;
}
