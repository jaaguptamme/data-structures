#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T=char,T minChar='a',int diffChars=26>
class Eertree{
    vector<T>s;
    vector<int>len,link;
    vector<vector<int>>to;
    int n,last,sz;
    public:
    Eertree(){
        s.push_back(-1);n=1;
        link.push_back(1);
        link.push_back(0);
        len.push_back(0);
        len.push_back(-1);
        to.push_back(vector<int>(diffChars));
        to.push_back(vector<int>(diffChars));
        sz=2;
        last=0;
    }
    int getLink(int u){
        while(s[n-len[u]-2]!=s[n-1])u=link[u];
        return u;
    }
    void addLetter(const T& ch){
        s.push_back(ch);n++;
        last=getLink(last);
        int c=ch-minChar;
        if(!to[last][c]){
            len.push_back(len[last]+2);
            link.push_back(to[getLink(link[last])][c]);
            to[last][c]=sz++;
            to.push_back(vector<int>(diffChars));
        }
        last=to[last][c];
    }
    int longestPalindrome(){
        int res=0;
        for(int i=0;i<sz;i++)res=max(res,len[i]);
        return res;
    }
};
