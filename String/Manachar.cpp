#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
class Manacher{
    string t,orig;
    string convert(string &s){
        stringstream res;
        res<<"@";
        for(auto el:s){
            res<<"#";
            res<<el;
        }
        res<<"#";
        res<<"$";
        return res.str();
    }
public:
    vector<int>p;
    Manacher(string &s):orig(s){
        t=convert(orig);
        int n=t.size();
        p.resize(n);
        int cen=0,rig=0;//center, right limit
        for(int i=0;i<n-1;i++){
            int iMir=cen-(i-cen);
            if(rig>i)p[i]=min(rig-i,p[iMir]);
            while(t[i+1+p[i]]==t[i-1-p[i]])p[i]++;
            if(i+p[i]>rig){
                cen=i;
                rig=i+p[i];
            }
        }
    }

};
