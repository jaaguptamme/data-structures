#include <bits/stdc++.h>
//source: https://blog.naver.com/PostView.naver?blogId=jinhan814&logNo=222616180470&parentCategoryNo=&categoryNo=&viewDate=&isShowPopularPosts=false&from=postView
typedef long long ll;
using namespace std;
template<typename T>
class SMMH{
    vector<T> v;
    public:
    SMMH():v(2){}
    int size(){
        return v.size()-2;
    }
    bool empty(){
        return v.size()==2;
    }
    T min(){
        assert(!empty());
        return v[2];
    }
    T max(){
        assert(!empty());
        return v.size()>3?v[3]:v[2];
    }
    void push(const T& vl){
        int ps=v.size();v.push_back(vl);
        while(ps>3){
            if(ps%2&&v[ps-1]>v[ps])swap(v[ps-1],v[ps]),ps--;
            if(v[ps]<v[ps/4*2])swap(v[ps],v[ps/4*2]),ps=ps/4*2;
            else if(v[ps]>v[ps/4*2+1])swap(v[ps],v[ps/4*2+1]),ps=ps/4*2+1;
            else break;

        }
        if(ps==3&&v[2]>v[3])swap(v[2],v[3]);
    }
    void popMin(){
        assert(!empty());
        int ps=2,nx;
        swap(v[ps],v.back());v.pop_back();
        while(ps<v.size()){
            if(ps+1<v.size()&&v[ps]>v[ps+1])swap(v[ps],v[ps+1]);
            nx=ps*2;
            if(nx>=v.size())break;
            if(2*(ps+1)<v.size()&&v[nx]>v[2*(ps+1)])nx=2*(ps+1);
            if(v[ps]>v[nx])swap(v[ps],v[nx]),ps=nx;
            else break;
        }
    }
    void popMax(){
        assert(!empty());
        if(size()==1){
            v.pop_back();
            return;
        }
        int ps=3,nx;
        swap(v[ps],v.back());v.pop_back();
        while(ps<v.size()){
            if(v[ps-1]>v[ps])swap(v[ps-1],v[ps]);
            nx=2*(ps-1)+1;
            if(nx>=v.size())break;
            if(2*ps+1<v.size()&&v[nx]<v[2*ps+1])nx=2*ps+1;
            if(v[ps]<v[nx])swap(v[ps],v[nx]),ps=nx;
            else break;
        }
    }
};
