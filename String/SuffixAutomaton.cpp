#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct SAM{
    struct Olek{
        int pikkus, link;
        int sonesid;//Mitu sone loppeb selles kohas, pole vaja kui ei taha esinemiste arvu
        map<char,int>jargmine;
        Olek(int pikkus=0,int link=-1):pikkus(pikkus),link(link),sonesid(0){}
    };
    vector<Olek>olekud;
    int esimeneVaba,eelmine;
    SAM(){
        esimeneVaba=eelmine=0;
        olekud.push_back(Olek());
        esimeneVaba++;
    }
    SAM(string &s):SAM(){
        for(auto taht:s)lisa_taht(taht);
    }

    void arvutaEsinemisteArv(){
        vector<pair<int,int>>pikkuseJargi;//Sorteerime kahanevalt pikkuse järgi
        for(int i=1;i<olekud.size();i++)pikkuseJargi.push_back(make_pair(olekud[i].pikkus,i));
        sort(pikkuseJargi.begin(),pikkuseJargi.end());
        reverse(pikkuseJargi.begin(),pikkuseJargi.end());
        for(auto& paar:pikkuseJargi){
            int i=paar.second;
            olekud[olekud[i].link].sonesid+=olekud[i].sonesid;
        }
    }

    int mituKordaEsineb(string &s){
        int koht=0;
        for(auto &taht:s){
            if(!olekud[koht].jargmine.count(taht))return 0;
            koht=olekud[koht].jargmine[taht];
        }
        return olekud[koht].sonesid;
    }

    void lisa_taht(char c){
        int koht=esimeneVaba++;
        olekud.push_back(Olek(olekud[eelmine].pikkus+1));
        olekud[koht].sonesid=1;//1 sõne lõppeb
        int p=eelmine;
        while(p!=-1 && !olekud[p].jargmine.count(c)){
            olekud[p].jargmine[c]=koht;
            p=olekud[p].link;
        }
        if(p==-1)olekud[koht].link=0;
        else{
            int q=olekud[p].jargmine[c];
            if(olekud[p].pikkus+1==olekud[q].pikkus){
                olekud[koht].link=q;
            }else{
                int kloon=esimeneVaba++;
                olekud.push_back(Olek(olekud[p].pikkus+1,olekud[q].link));
                olekud[kloon].jargmine=olekud[q].jargmine;
                while(p!=-1 && olekud[p].jargmine[c]==q){
                    olekud[p].jargmine[c]=kloon;
                    p=olekud[p].link;
                }
                olekud[q].link=olekud[koht].link=kloon;
            }
        }
        eelmine=koht;
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    SAM T(s);
    T.arvutaEsinemisteArv();
    while(q--){
        string t;
        cin>>t;
        cout<<T.mituKordaEsineb(t)<<'\n';
    }
    return 0;
}
