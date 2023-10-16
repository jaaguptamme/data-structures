#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Patricia{
    struct PatriciaTipp{
        string s;
        bool sobib;
        map<char,PatriciaTipp*>jargmised;
        PatriciaTipp(const string& s):s(s),sobib(false){}
        PatriciaTipp* sea(const string& s){
            jargmised[s[0]]=new PatriciaTipp(s);
            return jargmised[s[0]];
        }
        PatriciaTipp* saa(char s){
            if(!jargmised.count(s))return nullptr;
            return jargmised[s];
        }
    };
    PatriciaTipp* juur;
    Patricia(){
        juur=new PatriciaTipp("");
    }
    tuple<PatriciaTipp*,int,int> pikimUhine(const string& s){
        PatriciaTipp* tp=this->juur;
        int i=0;
        while(i<s.size()){
            PatriciaTipp* jarg=tp->saa(s[i]);
            if(!jarg)break;
            int j=1;
            while(j<jarg->s.size()){
                if(i+j==s.size() || s[i+j]!=jarg->s[j]){
                    return {jarg,i+j,j};
                }
                j++;
            }
            i+=j;
            tp=jarg;
        }
        return {tp,i,0};
    }
    bool otsi(const string& s){
        PatriciaTipp* tp;
        int sama,osa;
        tie(tp,sama,osa)=pikimUhine(s);
        if(s.size()==sama && osa==0)return tp->sobib;
        return false;
    }
    bool lisa(const string& s){
        PatriciaTipp* tp;
        int sama,osa;
        tie(tp,sama,osa)=pikimUhine(s);
        if(s.size()==sama && osa==0 && tp->sobib)return false;
        if(osa>0){
            PatriciaTipp* uus=new PatriciaTipp(tp->s.substr(osa));
            uus->jargmised=tp->jargmised;
            uus->sobib=tp->sobib;
            tp->s=tp->s.substr(0,osa);
            tp->jargmised.clear();
            tp->jargmised[uus->s[0]]=uus;
            tp->sobib=false;
        }
        if(sama<s.size()){
            tp=tp->sea(s.substr(sama));
        }
        tp->sobib=true;
        return true;
    }
    bool eemalda(const string& s){
        PatriciaTipp* tp;
        int sama,osa;
        tie(tp,sama,osa)=pikimUhine(s);
        if(s.size()==sama && osa==0 && tp->sobib){
            tp->sobib=false;
            return true;
        }
        return false;
    }
};
