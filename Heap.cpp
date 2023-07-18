#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
class Heap{
    vector<T>a;
    int n;
    public:
    Heap(){
        n=0;
    }

    Heap(vector<T>& a){
        this->a=a;
        n=a.size();
        for(int i=n-1;i>=0;i--)alla(i);
    }

    void insert(T v){
        a.push_back(v);
        n++;
        ules(n-1);
    }

    T min(){
        return a[0];
    }

    T delmin(){
        T res=a[0];
        swap(a[0],a[n-1]);
        n--;
        a.pop_back();
        alla(0);
        return res;
    }

    void ules(int i){
        while(i){
            if(a[(i-1)>>1]>a[i]){
                swap(a[i],a[(i-1)>>1]);
                i=(i-1)>>1;
            }else break;
        }
    }
    void alla(int i){
        while(((i<<1)|1)<n){
            int vaiksemi=i;
            if((((i<<1)|1)<n)&&(a[(i<<1)|1]<a[vaiksemi]))vaiksemi=(i<<1)|1;
            if((((i+1)<<1)<n)&&(a[((i+1)<<1)]<a[vaiksemi]))vaiksemi=(i+1)<<1;
            if(vaiksemi!=i){
                swap(a[vaiksemi],a[i]);
                i=vaiksemi;
            }else return;
        }
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*1000*10;
    Heap<int> h;
    for(int i=1;i<=N;i++)h.insert(i);
    for(int i=1;i<=N;i++){
        assert(i==h.delmin());
    }
    return 0;
}
