#include <bits/stdc++.h>
//ALLIKAS: https://codeforces.com/blog/entry/107849
//KONTROLLITUD:https://judge.yosupo.jp/problem/range_kth_smallest
//2.4s/20Mb - 200*1000 N&Q
typedef long long ll;
using namespace std;
//Sarnane merge sort treega, kuid saab hakkama vaid siis, kui on olemas lahutamise funktsioon
//NB! 0 või 1 indekseerimine
template<typename T>
class SortFenwick{
    vector<vector<T>>r;
    int N;
    public:
    SortFenwick(int N):N(N+1),r(N+1){}
    SortFenwick(vector<T>&a):SortFenwick(a.size()){//Idee: sorteerime arvud enne ja lisame õiges järjestuses
        vector<int>indeksid(N);
        iota(indeksid.begin(),indeksid.end(),0);
        sort(indeksid.begin(),indeksid.end(),[&](int i,int j){
             return a[i]<a[j];});
        for(int& i:indeksid)lisa(i+1,a[i]);
    }
    void ehita(){//Kui miskipärast ei saa alguses sorteerida, siis võib ka hiljem. Seda pole vist kunagi vaja
        for(auto &v:r)sort(v.begin(),v.end());
    }
    void lisa(int i,T vl){//Lisame arvu igasse vajalikku listi
        for(int j=i;j<N;j+=j&(-j))r[j].push_back(vl);
    }
    int mitteSuuremaid(int i,T x){//mitu arvu vahemikus [1,i] on <= x
        int vas=0;
        for(int j=i;j>0;j-=j&(-j)){
            //cout<<i<<'I'<<j<<'J'<<x<<endl;
            vas+=lower_bound(r[j].begin(),r[j].end(),x)-r[j].begin();
        }
        return vas;
    }
    int mitteSuuremaid(int i,int j,T x){//mitu arvu vahemikus [i,j) on <= x
        return mitteSuuremaid(j,x)-mitteSuuremaid(i,x);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,Q;
    cin>>N>>Q;
    vector<int>a(N);
    for(int &x:a)cin>>x;
    SortFenwick<int> T(a);
    while(Q--){
        int L,R,K;
        cin>>L>>R>>K;
        int l=0,r=1e9,ans=-1;
        while(l<=r){
            int m=(l+r)/2;
            //cout<<m<<' '<<T.mitteSuuremaid(L,R,m)<<endl;
            if(T.mitteSuuremaid(L,R,m)>K){
                ans=m;
                r=m-1;
            }else l=m+1;
        }
        cout<<ans-1<<'\n';
    }
    return 0;
}
