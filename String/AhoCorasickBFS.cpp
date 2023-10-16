#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct AhoCorasick{
    struct Tipp{
        map<char,Tipp*>jargmised;
        Tipp* tagasi;
        int sobivaid;
        Tipp():tagasi(nullptr),sobivaid(0){}
        void sea(char s){
            jargmised[s]=new Tipp();
        }
        Tipp* saa(char s){
            if(!jargmised.count(s))return nullptr;
            return jargmised[s];
        }
    };
    Tipp* juur;
    AhoCorasick(){
        juur=new Tipp();
    }
    void lisa(const string& muster){
        Tipp* tipp=this->juur;
        for(char s:muster){
            if(tipp->saa(s)==nullptr)tipp->sea(s);
            tipp=tipp->saa(s);
        }
        tipp->sobivaid++;
    }
    void ehita(){
        deque<Tipp*> mag;
        for(auto& [s,tp]:juur->jargmised){
            tp->tagasi=this->juur;
            mag.push_back(tp);
        }
        while(!mag.empty()){
            Tipp* tipp=mag.front();mag.pop_front();
            tipp->sobivaid+=tipp->tagasi->sobivaid;
            for(auto& [s,uus]:tipp->jargmised){
                Tipp* f=tipp->tagasi;
                while(f && !f->saa(s))f=f->tagasi;
                uus->tagasi=(f?f->saa(s):this->juur);
                mag.push_back(uus);
            }
        }
    }
    ll loenda(const string &text){
        Tipp* tipp=this->juur;
        ll vas=0;
        for(auto s:text){
            while(tipp&&!tipp->saa(s))tipp=tipp->tagasi;
            tipp=(tipp?tipp->saa(s):this->juur);
            vas+=tipp->sobivaid;
        }
        return vas;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    AhoCorasick AC;
    AC.lisa("C");
    AC.lisa("CC");
    AC.lisa("CCC");
    AC.ehita();
    while(true){
        string s;cin>>s;
        cout<<AC.loenda(s)<<endl;
    }
    return 0;
}
