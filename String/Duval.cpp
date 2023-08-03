#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
vector<int>duval(string &s){
    int n=s.size();
    int i=0;
    vector<int>res;
    while(i<n){
        int j=i+1,k=i;
        while(j<n&&s[k]<=s[j]){
            if(s[k]<s[j])k=i;
            else k++;
            j++;
        }
        while(i<=k){
            res.push_back(i);
            i+=j-k;
        }
    }
    res.push_back(n);
    return res;
}
