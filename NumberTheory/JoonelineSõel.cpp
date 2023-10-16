#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct JoonelineSoel{
    static pair<vector<int>,vector<int>> soel(int n){//[0,n]
        vector<int>algarvud,vahimJagaja(n+1);
        iota(begin(vahimJagaja),end(vahimJagaja),0);
        for(int i=2;i<=n;i++){
            if(vahimJagaja[i]==i)algarvud.push_back(i);
            for(int p:algarvud){
                if(p*i>n or p>vahimJagaja[i])break;
                vahimJagaja[p*i]=p;
            }
        }
        return {algarvud,vahimJagaja};
    }
};
