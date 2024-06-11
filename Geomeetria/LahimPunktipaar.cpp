#include <bits/stdc++.h>
//ALLIKAS:https://codeforces.com/blog/entry/58747
//KONTROLLITUD: https://judge.yosupo.jp/problem/closest_pair
//KEERUKUS: O(N log N)
typedef long long ll;
using namespace std;
template<typename T>
pair<int,int> lahimPunktiPaar(vector<pair<T,T>>punktid){
    int n=punktid.size();
    map<pair<T,T>,int>mp;
    for(int i=0;i<n;i++){
        if(mp.count(punktid[i])){
            return {mp[punktid[i]],i};
        }
        mp[punktid[i]]=i;
    }
    sort(punktid.begin(),punktid.end());
    set<pair<T,T>>s;
    ll pikkus=4e18;
    pair<int,int>vastus={0,1};
    int j=0;
    for(int i=0;i<n;i++){
        long d=ceil(sqrt(pikkus));
        while(punktid[i].first-punktid[j].first>=d){
            s.erase({punktid[j].second,punktid[j].first});
            j++;
        }
        auto i1=s.lower_bound({punktid[i].second-d,punktid[i].first});
        auto i2=s.upper_bound({punktid[i].second+d,punktid[i].first});
        for(auto it=i1;it!=i2;it++){
            ll dx=punktid[i].first-it->second;
            ll dy=punktid[i].second-it->first;
            ll see=dx*dx+dy*dy;
            if(see<pikkus){
                vastus={mp[punktid[i]],mp[{it->second,it->first}]};
                pikkus=see;
            }
        }
        s.insert({punktid[i].second,punktid[i].first});
    }
    return vastus;
}
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        int N;cin>>N;
        vector<pair<long,long>>A(N);
        for(int i=0;i<N;i++)cin>>A[i].first>>A[i].second;
        auto R=lahimPunktiPaar(A);
        cout<<R.first<<' '<<R.second<<'\n';
    }
    return 0;
}
