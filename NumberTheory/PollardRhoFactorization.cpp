#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct MR{
    using u64 = uint64_t;
    using u128 = __uint128_t;

    static u64 binpower(u64 base, u64 e, u64 mod) {
        u64 result = 1;
        base %= mod;
        while (e) {
            if (e & 1)
                result = (u128)result * base % mod;
            base = (u128)base * base % mod;
            e >>= 1;
        }
        return result;
    }

   static bool check_composite(u64 n, u64 a, u64 d, int s) {
        u64 x = binpower(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        for (int r = 1; r < s; r++) {
            x = (u128)x * x % n;
            if (x == n - 1)
                return false;
        }
        return true;
    };

   static bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
        if (n < 2)
            return false;

        int r = 0;
        u64 d = n - 1;
        while ((d & 1) == 0) {
            d >>= 1;
            r++;
        }

        for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if (n == a)
                return true;
            if (check_composite(n, a, d, r))
                return false;
        }
        return true;
    }
};
struct Floyd{
    ll mult(ll a,ll b,ll MOD){
        return (__int128)a*b%MOD;
    }
    ll f(ll x,ll c,ll MOD){
        return (mult(x,x,MOD)+c)%MOD;
    }
    ll single_rho(ll n){
        if(n%2==0)return 2;
        if(MR::MillerRabin(n))return n;
        ll st=0;
        while(true){
            st++;
            ll x=st,y=f(x,st,n);
            while(true){
                ll g=__gcd(y-x+n,n);
                if(g==0||g==n)break;
                if(g!=1)return g;
                x=f(x,st,n);
                y=f(y,st,n);
                y=f(y,st,n);
            }
        }
    }
    vector<ll>rho(ll n){
        if(n==1)return {};
        ll res=single_rho(n);
        if(res==n)return {n};
        auto l=rho(res);
        auto r=rho(n/res);
        l.insert(l.end(),r.begin(),r.end());
        return l;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    Floyd f;
    int q;
    cin>>q;
    while(q--){
        ll a;
        cin>>a;
        vector<ll>facs=f.rho(a);
        sort(facs.begin(),facs.end()),
        cout<<facs.size()<<' ';
        for(auto el:facs)cout<<el<<' ';
        cout<<'\n';
    }
    return 0;
}
