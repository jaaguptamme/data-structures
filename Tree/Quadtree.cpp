//source:https://sotanishy.github.io/cp-library-cpp/data-structure/quadtree.cpp
template<typename M>
struct QuadTree{
    using T=typename M::T;
    struct Tipp{
        T vaartus;
        Tipp* edasi[4]={nullptr,nullptr,nullptr,nullptr};
        Tipp():vaartus(M::id()){}
    };
    Tipp* juur;
    int suurus;
    QuadTree(int n){
        juur=new Tipp();
        suurus=1;
        while(suurus<n)suurus*=2;
    }
    void uuenda(int x,int y,const T& val,Tipp* t,int p,int q,int ln)const{
        if(ln==1){
            t->vaartus+=val;
            return;
        }
        ln>>=1;
        for(int i=3;i>=0;i--){
            if(x>=p+ln*(i>>1)&&y>=q+ln*(i&1)){
                if(!t->edasi[i])t->edasi[i]=new Tipp();
                uuenda(x,y,val,t->edasi[i],p+ln*(i>>1),q+ln*(i&1),ln);
                break;
            }
        }
        t->vaartus=M::id();
        for(int i=0;i<4;i++){
            if(t->edasi[i])t->vaartus=M::op(t->vaartus,t->edasi[i]->vaartus);
        }
    }

    T saa(int l,int r,int b,int t,Tipp* tp,int p,int q,int ln)const{
        //cout<<l<<' '<<r<<' '<<b<<' '<<t<<' '<<p<<' '<<q<<' '<<ln<<endl;
        if(!tp)return M::id();
        if(p+ln<=l || r<=p || q+ln<=b || t<=q)return M::id();
        if(l<=p && p+ln<=r && b<=q && q+ln<=t)return tp->vaartus;
        ln>>=1;
        T vl=M::id();
        for(int i=0;i<4;i++){
            if(tp->edasi[i])vl=M::op(vl,saa(l,r,b,t,tp->edasi[i],p+ln*(i>>1),q+ln*(i&1),ln));
        }
        return vl;
    }
    T saa(int x,int y){
        return saa(x,x+1,y,y+1);
    }
    T saa(int l,int r,int b,int t){
        return saa(l,r,b,t,juur,0,0,suurus);
    }
    void uuenda(int x,int y,const T& vl){
        uuenda(x,y,vl,juur,0,0,suurus);
    }
};
template<typename T>
struct Kompressi{
    vector<T>xid;
    Kompressi(const vector<T>&x):xid(x){
        sort(xid.begin(),xid.end());
        xid.erase(unique(xid.begin(),xid.end()),xid.end());
    }
    int kompressi(const T& vaartus){
        return lower_bound(xid.begin(),xid.end(),vaartus)-xid.begin();
    }
    vector<int> kompressi(const vector<T>& x){
        int n=x.size();
        vector<int>vas(n);
        for(int i=0;i<n;i++)vas[i]=kompressi(x[i]);
        return vas;
    }
};
struct Add{
    using T=long long;
    static T id(){return 0;}
    static T op(const T& a,const T& b){
        return a+b;
    }
};
