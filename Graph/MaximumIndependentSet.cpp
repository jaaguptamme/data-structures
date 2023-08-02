#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=45;
ll G[N];
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,M;
    cin>>N>>M;
    for(int i=0;i<M;i++){
        ll u,v;cin>>u>>v;
        G[u]|=(1LL)<<v;
        G[v]|=(1LL)<<u;
    }
    int half=N/2;
    int smalf=(1<<half);
    vector<int>dp(smalf,0);
    vector<int>prev(smalf,0);
    for(int b=0;b<smalf;b++){
        int in=0;
        bool can=true;
        for(int i=0;i<half;i++){
            if(b&(1<<i)){
                if(G[i]&in)can=false;
                in|=1<<i;
            }
        }
        if(can){
            dp[b]=__builtin_popcount(in);
            prev[b]=b;
        }
    }
    for(int i=0;i<smalf;i++){
        for(int j=0;j<half;j++){
            if(dp[i]==-1)continue;
            if(i&(1<<j))continue;
            int u=i|(1<<j);
            if(dp[i]>dp[u]){
                dp[u]=dp[i];
                prev[u]=i;
            }
        }
    }
    int oth=N-half;
    int bigf=1<<oth;
    int resCnt=0;
    vector<int>vals;
    for(int b=0;b<bigf;b++){
        ll in=0;
        bool can=true;
        //cout<<b<<endl;
        for(int i=0;i<oth;i++){
            if(b&(1<<i)){
                //cout<<i<<' '<<G[i]<<' '<<in<<' '<<(G[i]&in)<<endl;
                if(G[i+half]&in)can=false;
                in|=(1LL)<<(i+half);
            }
        }
        if(!can)continue;
        ll o=smalf-1;
        for(int i=0;i<oth;i++){
            if(b&(1<<i)){
                o&=~G[i+half];
            }
        }
        int cnt=__builtin_popcountll(in);
        cnt+=dp[o];
        //cout<<b<<' '<<in<<endl;
        if(cnt>resCnt){
             resCnt=cnt;
             while(o!=prev[o])o=prev[o];
             vals.clear();
              for(int i=0;i<oth;i++){
                if(b&(1<<i))vals.push_back(i+half);
              }
              for(int i=0;i<half;i++){
                if(o&(1<<i))vals.push_back(i);
              }
        }

    }
    cout<<resCnt<<endl;
    for(auto el:vals)cout<<el<<' ';
    return 0;
}
