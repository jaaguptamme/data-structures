#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=1<<12;
vector<bitset<N>>a(N),b(N),c(N);
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,M,K;
    cin>>N>>M>>K;
    for(int i=0;i<N;i++){
        string s;cin>>s;
        for(int j=0;j<M;j++){
            if(s[j]=='1')a[i].set(j);
        }
    }
    for(int i=0;i<M;i++){
        string s;cin>>s;
        for(int j=0;j<K;j++){
            if(s[j]=='1')b[j].set(i);
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<K;j++){
            cout<<(a[i]&b[j]).count()%2;
        }
        cout<<'\n';
    }
    return 0;
}
