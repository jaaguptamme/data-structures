#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct LoigatudSoel{
    static pair<vector<ll>,vector<char>> soelu(ll l,ll r){//[l,r)
        ll sq=sqrt(r);
        vector<char>isPrimeSqrt(sq+1,true),isPrimeTbl(r-l,true);
        isPrimeSqrt[0]=isPrimeSqrt[1]=false;
        if(l==0)isPrimeTbl[0]=isPrimeTbl[1]=false;
        if(l==1)isPrimeTbl[1]=false;
        for(int i=2;i<=sq;i++){
            if(!isPrimeSqrt[i])continue;
            for(int j=2*i;j<=sq;j+=i)isPrimeSqrt[j]=false;
            for(ll j=max((l+i-1)/i,2LL)*i;j<r;j+=i)isPrimeTbl[j-l]=false;
        }
        vector<ll>primes;
        for(ll i=0;i<(r-l);i++){
            if(isPrimeTbl[i])
                primes.push_back(i+l);
        }
        return {primes,isPrimeTbl};
    }
};
