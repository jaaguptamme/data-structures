#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
class SuffixTree{
    public:
    struct Tipp{
        int algus,lopp;//Sõne sees indeksid [algus,lõpp)
        int ulemus;//eelmine tipp
        int link;//sufiksilink
        map<char,int>jargmised;
        Tipp(int algus=0,int lopp=0,int ulemus=-1):algus(algus),lopp(lopp),ulemus(ulemus),link(-1){}
        int pikkus(){return lopp-algus;}
        int &edasi(char ch){
            if(!jargmised.count(ch))jargmised[ch]=-1;
            return jargmised[ch];
        }
    };
    Tipp* tipud;
    int esimeneVaba,n;
    string s;
    struct Olek{
        int tipp,koht;
        Olek(int tipp,int koht):tipp(tipp),koht(koht){}
    };
    Olek praegune=Olek(0,0);
    Olek edasi(Olek o,int algus,int lopp){
        while(algus<lopp){
            if(o.koht==tipud[o.tipp].pikkus()){
                o=Olek(tipud[o.tipp].edasi(s[algus]),0);
                if(o.tipp==-1)return o;
            }else{
                if(s[tipud[o.tipp].algus+o.koht]!=s[algus])return Olek(-1,-1);
                if(lopp-algus<tipud[o.tipp].pikkus()-o.koht)return Olek(o.tipp,o.koht+lopp-algus);
                algus+=tipud[o.tipp].pikkus()-o.koht;
                o.koht=tipud[o.tipp].pikkus();
            }
        }
        return o;
    }
    int jaga(Olek o){
        if(o.koht==tipud[o.tipp].pikkus())return o.tipp;
        if(o.koht==0)return tipud[o.tipp].ulemus;
        Tipp v=tipud[o.tipp];
        int koht=esimeneVaba++;
        tipud[koht]=Tipp(v.algus,v.algus+o.koht,v.ulemus);
        tipud[v.ulemus].edasi(s[v.algus])=koht;
        tipud[koht].edasi(s[v.algus+o.koht])=o.tipp;
        tipud[o.tipp].ulemus=koht;
        tipud[o.tipp].algus+=o.koht;
        return koht;
    }
    int saa_link(int t){
        if(tipud[t].link!=-1)return tipud[t].link;
        if(tipud[t].ulemus==-1)return 0;
        int e=saa_link(tipud[t].ulemus);
        return tipud[t].link=jaga(edasi(Olek(e,tipud[e].pikkus()),tipud[t].algus+(tipud[t].ulemus==0),tipud[t].lopp));
    }
    void laienda(int koht){
        while(true){
            Olek o=edasi(praegune,koht,koht+1);
            if(o.tipp!=-1){
                praegune=o;
                return;
            }
            int keskmine=jaga(praegune);
            int leht=esimeneVaba++;
            tipud[leht]=Tipp(koht,n,keskmine);
            tipud[keskmine].edasi(s[koht])=leht;
            praegune.tipp=saa_link(keskmine);
            praegune.koht=tipud[praegune.tipp].pikkus();
            if(!keskmine)break;
        }
    }
    SuffixTree(string &s):s(s){
        s+='$';
        n=s.size();
        tipud=new Tipp[3*n];
        esimeneVaba=1;
        for(int i=0;i<n;i++)laienda(i);
        prindi(0);
    }
    void prindi(int p,int pikkus=0){
        for(auto el:tipud[p].jargmised){
            prindi(el.second,pikkus+tipud[p].pikkus());
        }
        if(tipud[p].jargmised.size()==0){
            //cout<<s.substr(tipud[p].algus-pikkus,tipud[p].pikkus()+pikkus)<<endl;
            int a=tipud[p].algus-pikkus;
            if(a!=n-1)cout<<a<<' ';
        }
    }
};
