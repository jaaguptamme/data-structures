#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
struct SA{
    vector<int>p,c,l;
    SA(string s){

        int n=s.size();
        p.resize(n);
        c.resize(n);
        {
            vector<pair<char,int>>a(n);
            for(int i=0;i<n;i++)a[i]={s[i],i};
            sort(a.begin(),a.end());
            for(int i=0;i<n;i++)p[i]=a[i].second;
            c[p[0]]=0;
            for(int i=1;i<n;i++){
                c[p[i]]=c[p[i-1]];
                if(a[i].first!=a[i-1].first)c[p[i]]++;
            }

        }
        vector<pair<pair<int,int>,int>>a(n);
        int k=1;
        while(k<n){
            for(int i=0;i<n;i++)a[i]={{c[i],c[(i+k)%n]},i};

            SORT(a);
            for(int i=0;i<n;i++)p[i]=a[i].second;

            c[p[0]]=0;
            for(int i=1;i<n;i++){
                c[p[i]]=c[p[i-1]];
                if(a[i].first!=a[i-1].first)c[p[i]]++;
            }
            k*=2;
        }
        l.resize(n);
        k=0;
        for(int i=0;i<n-1;i++){
            int pi=c[i];
            int j=p[pi-1];
            while(s[i+k]==s[j+k])k++;
            l[pi]=k;
            k=max(k-1,0);
        }
    }
    void SORT(auto &ar){
        int n=ar.size();
        {
            vector<int>p(n),c(n);
            auto br=ar;
            for(auto el:ar)c[el.first.second]++;
            for(int i=1;i<n;i++)p[i]=p[i-1]+c[i-1];
            for(auto el:ar)br[p[el.first.second]++]=el;
            ar=br;
        }
        {
            vector<int>p(n),c(n);
            auto br=ar;
            for(auto el:ar)c[el.first.first]++;
            for(int i=1;i<n;i++)p[i]=p[i-1]+c[i-1];
            for(auto el:ar)br[p[el.first.first]++]=el;
            ar=br;
        }
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    s+='$';
    SA t(s);
    for(int i=1;i<s.size();i++)cout<<t.p[i]<<' ';
    return 0;
}
