#include <bits/stdc++.h>
//allikas: https://codeforces.com/blog/entry/127472
typedef long long ll;
using namespace std;
template<int N>//Hulga elemendid vahemikus [0,n)
class HULK2{
    private:
    int n;
    array<int,N>s,d;
    public:
        HULK2():n(0){}

        bool get(int i){//Kas arv i on hulgas?
            return s[i]>=0&&s[i]<n&&d[s[i]]==i;
        }
        void set(int i){//Lisa arvu i hulka
            if(get(i))return;
            d[n]=i;
            s[i]=n;
            n++;
        }
        void reset(int i){//Eemalda arv i hulgas
            if(!get(i))return;
            d[s[i]]=d[n-1];
            s[d[n-1]]=s[i];
            n--;
        }

        void clear(){//Hulk tühjaks, aeg O(1)
            n=0;
        }
        void flip(int i){//"pööra ümber arv i
            if(get(i))reset(i);
            else set(i);
        }
        void flip(){//Kogu hulga ümberpöörd
            for(int i=0;i<N;i++)flip(i);
        }
        vector<int> getAll(){//Kõik arvud, mis päriselt on hulgas
            vector<int>res;
            for(int i=0;i<n;i++)res.push_back(d[i]);
            return res;
        }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=10;
    HULK2<N>A;
    for(int i=N-1;i>=0;i-=2)A.set(i);
    A.flip();
    A.flip();
    for(auto el:A.getAll())cout<<el<<' ';
    cout<<endl;
    for(int i=0;i<N;i++){
        if(A.get(i)!=(i%2)){
            cout<<"VIGA"<<endl;
        }
    }
    return 0;
}
