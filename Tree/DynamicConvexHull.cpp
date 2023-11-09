//source: https://codeforces.com/blog/entry/75929
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct Punkt{
    ll x,y;
    Punkt operator-(Punkt p){
        return {x-p.x,y-p.y};
    }
    ll cross(Punkt p){
        return x*p.y-y*p.x;
    }
    ll dot(Punkt p){
        return x*p.x+y*p.y;
    }
    bool operator<(Punkt p)const{
        if(y!=p.y)return y<p.y;
        return x<p.x;
    }
    bool operator==(Punkt p){
        return x==p.x&&y==p.y;
    }
    Punkt operator-(){
        return {-x,-y};
    }
};
ll cross(Punkt a,Punkt b,Punkt c){
    return (b-a).cross(c-a);
}
class Hull{
    vector<Punkt> punktid;
    struct Tipp{
        int all,alr;
        int lsild,rsild;
        int ljarg,rjarg;
    };
    vector<Tipp> tipud;
    int juur;
    bool onLeht(int i){
        return tipud[i].ljarg==-1&&tipud[i].rjarg==-1;
    }
    void ules(int i){
        assert(!onLeht(i));
        int l=tipud[i].ljarg,r=tipud[i].rjarg;
        ll jagaY=punktid[tipud[r].lsild].y;
        while(!onLeht(l)||!onLeht(r)){
            int a=tipud[l].all,b=tipud[l].alr,c=tipud[r].all,d=tipud[r].alr;
            if(a!=b&&cross(punktid[a],punktid[b],punktid[c])>0)l=tipud[l].ljarg;
            else if(c!=d&&cross(punktid[b],punktid[c],punktid[d])>0)r=tipud[r].rjarg;
            else if(a==b)r=tipud[r].ljarg;
            else if(c==d)l=tipud[l].rjarg;
            else{
                ll s1=cross(punktid[a],punktid[b],punktid[c]);
                ll s2=cross(punktid[b],punktid[a],punktid[d]);
                assert(s1+s2>=0);
                if(s1+s2==0||s1*punktid[d].y+s2*punktid[c].y<jagaY*(s1+s2))l=tipud[l].rjarg;
                else r=tipud[r].ljarg;
            }
        }
        tipud[i].all=tipud[l].lsild;
        tipud[i].alr=tipud[r].lsild;
    }
    void ehita(int i,int L,int R){
        tipud[i].lsild=L;
        tipud[i].rsild=R;
        if(R-L==1){
            tipud[i].ljarg=tipud[i].rjarg=-1;
            tipud[i].all=tipud[i].alr=L;
        }else{
            int M=(L+R)/2;
            tipud[i].ljarg=i+1;
            tipud[i].rjarg=i+2*(M-L);
            ehita(tipud[i].ljarg,L,M);
            ehita(tipud[i].rjarg,M,R);
            ules(i);
        }
    }
    int eemalda(int i,int L,int R){
        if(R<=tipud[i].lsild||L>=tipud[i].rsild)return i;
        if(L<=tipud[i].lsild&&R>=tipud[i].rsild)return -1;
        tipud[i].ljarg=eemalda(tipud[i].ljarg,L,R);
        tipud[i].rjarg=eemalda(tipud[i].rjarg,L,R);
        if(tipud[i].ljarg==-1)return tipud[i].rjarg;
        if(tipud[i].rjarg==-1)return tipud[i].ljarg;
        ules(i);
        return i;
    }
    void saaKate(int i,int l,int r,vector<int>&vas){
        if(onLeht(i))vas.push_back(tipud[i].lsild);
        else if(r<=tipud[i].all)saaKate(tipud[i].ljarg,l,r,vas);
        else if(l>=tipud[i].alr)saaKate(tipud[i].rjarg,l,r,vas);
        else{
            assert(l<=tipud[i].all&&tipud[i].alr<=r);
            saaKate(tipud[i].ljarg,l,tipud[i].all,vas);
            saaKate(tipud[i].rjarg,tipud[i].alr,r,vas);
        }
    }
public:
    Hull(vector<Punkt>& punktid):punktid(punktid),tipud(punktid.size()*2),juur(0){
        ehita(0,0,punktid.size());
    }
    vector<int>saaKate(){
        if(juur==-1)return {};
        vector<int>vas;
        saaKate(juur,0,punktid.size()-1,vas);
        return vas;
    }
    void eemalda(int L){
        juur=eemalda(juur,L,L+1);
    }
};
vector<Punkt>punktid;
map<Punkt,int>number;
const int N=1000*1000+5;
vector<int>kiht(N,0),vas(N,0);
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    punktid.resize(n);
    for(int i=0;i<n;i++){
        cin>>punktid[i].x>>punktid[i].y;
        number[punktid[i]]=i;
    }
    sort(punktid.begin(),punktid.end());
    Hull vasak(punktid);
    reverse(punktid.begin(),punktid.end());
    for(auto &el:punktid)el=-el;
    Hull parem(punktid);
    reverse(punktid.begin(),punktid.end());
    for(auto &el:punktid)el=-el;
    for(int l=1,mitu=0;mitu<n;l++){
        set<int>kate;
        for(int i:vasak.saaKate())kate.insert(i);
        for(int i:parem.saaKate())kate.insert(n-1-i);
        for(int i:kate){
            assert(!kiht[i]);
            mitu++;
            kiht[i]=l;
            vasak.eemalda(i);
            parem.eemalda(n-1-i);
        }
    }
    for(int i=0;i<n;i++)vas[number[punktid[i]]]=kiht[i];
    for(int i=0;i<n;i++)cout<<vas[i]<<'\n';
    return 0;
}
