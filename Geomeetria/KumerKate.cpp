#include <bits/stdc++.h>
//kontrollitud: https://judge.yosupo.jp/problem/static_convex_hull
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pii;
ll orie(const pii&a,const pii&b,const pii&c){
    return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y);
}
vector<pii> hull(vector<pii>&ps){
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
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n;cin>>n;
        vector<pii>vals;
        while(n--){
            pii cur;cin>>cur.x>>cur.y;vals.push_back(cur);
        }
        auto res=hull(vals);
        cout<<res.size()<<'\n';
        for(auto el:res)cout<<el.x<<' '<<el.y<<'\n';
    }
    return 0;
}
