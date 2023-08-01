#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
T POW(T a,T b,T mod){
    T res=1;
    while(b){
        if(b%2)res=(res*a)%mod;
        a=(a*a)%mod;
        b/=2;
    }
    return res%mod;
}
template<typename T>
T PHI(T n){
    T res=n;
    for(T i=2;i*i<=n;i++){
        if(n%i==0){
            res-=res/i;
            while(n%i==0)n/=i;
        }
    }
    if(n>1)res-=res/n;
    return res;
}
template<typename T>
T tetration(T a,T b,T mod){
    if(mod==1)return 0;
    if(a==0)return 1-b%2;
    if(b==0)return 1;
    if(b==1)return a%mod;
    if(b==2)return POW(a,a,mod);
    T phi=PHI(mod);
    T pw=tetration(a,b-1,phi);
    if(pw==0)pw+=phi;
    return POW(a,pw,mod);
}
