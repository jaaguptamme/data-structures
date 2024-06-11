#include <bits/stdc++.h>
//kontrollitud: https://judge.yosupo.jp/problem/static_convex_hull
//idee: https://en.wikipedia.org/wiki/Rotating_calipers
//ALUS: kumer kate
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pii;
ll dist(const pii&a,const pii&b){
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}
ll orie(const pii&a,const pii&b,const pii&c){
    return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y);
}
vector<pii> hull(vector<pii>ps){
    sort(ps.begin(),ps.end());
    vector<pii>up;
    for(int i=0;i<ps.size();i++){
        while(up.size()>1&&orie(up[up.size()-2],up[up.size()-1],ps[i])<=0)up.pop_back();
        up.push_back(ps[i]);
    }
    vector<pii>dn;
    for(int i=ps.size()-1;i>=0;i--){
        while(dn.size()>1&&orie(dn[dn.size()-2],dn[dn.size()-1],ps[i])<=0)dn.pop_back();
        dn.push_back(ps[i]);
    }
    for(auto el:dn)up.push_back(el);
    set<pii>vals;
    vector<pii>res;
    for(auto el:up){
        if(vals.count(el))continue;
        vals.insert(el);
        res.push_back(el);
    }
    //for(auto el:res)cout<<el.x<<' '<<el.y<<'\n';
    return res;
}
pair<int,int>kaugeimad(vector<pii>kate,vector<pii>algsed){
    map<pii,int>mp;
    for(int i=0;i<algsed.size();i++)mp[algsed[i]]=i;//tagurpidi, et saaks pärast puntkid tagasi
    if(kate.size()==1)return {0,1};
    ll suurim=-1;
    pair<int,int>vas={0,1};
    //for(auto el:kate)cout<<el.first<<'*'<<el.second<<endl;
    int j=0;
    int m=kate.size();
    for(int i=0;i<m;i++){
        j=max(j,i+1);
        //EI saa kasutada puhast kaugust, vaja determinanti, sest kaugus pole monotoonne
        //https://codeforces.com/blog/entry/11179#comment-162768
        while((kate[(i+1)%m].first-kate[i].first)*(kate[(j+1)%m].second-kate[j%m].second)-
              (kate[(i+1)%m].second-kate[i].second)*(kate[(j+1)%m].first-kate[j%m].first)>0)j++;
        ll kaug=dist(kate[i],kate[j%m]);
        //cout<<kate[i].first<<' '<<kate[i].second<<' '<<kaug<<endl;
        if(kaug>suurim){
            suurim=kaug;
            vas={mp[kate[i]],mp[kate[j%m]]};
        }
    }
    //cout<<suurim<<endl;
    return vas;
}
