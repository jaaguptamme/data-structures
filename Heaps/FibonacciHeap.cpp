#include <bits/stdc++.h>
//source: https://keithschwarz.com/interesting/code/?dir=fibonacci-heap
typedef long long ll;
using namespace std;
template<typename K,typename V>
struct FibonacciHeap{
    struct Tipp{
        K key;
        V val;
        int numOfChilds;
        bool isMarked;
        Tipp *next,*prev,*par,*child;
        Tipp(const K &key,const V &val):key(key),val(val),numOfChilds(0),isMarked(false),next(this),prev(this),par(nullptr),child(nullptr){}
    };
    Tipp *min;
    int size;
    FibonacciHeap():min(nullptr),size(0){}
    Tipp* push(const K &key, const V &val){
        Tipp* tipp=new Tipp(key,val);
        min=mergeLists(min,tipp);
        size++;
        return tipp;
    }
    bool empty(){
        return !min;
    }
    Tipp* getMin(){
        assert(!empty());
        return min;
    }
    static FibonacciHeap<K,V> merge(FibonacciHeap<K,V> l,FibonacciHeap<K,V> r){
        FibonacciHeap<K,V>res;
        res.min=mergeLists(l.min,r.min);
        res.size=l.size+r.size;
        l.size=r.size=0;
        l.min=r.min=nullptr;
        return res;
    }
    Tipp* popMin(){
        assert(!empty());
        size--;
        Tipp *res=min;
        if(min->next==min){
            min=nullptr;
        }else{
            min->prev->next=min->next;
            min->next->prev=min->prev;
            min=min->next;
        }
        if(res->child!=nullptr){
            auto c=res->child;
            do{
                c->par=nullptr;
                c=c->next;
            }while(c!=res->child);
        }
        min=mergeLists(min,res->child);
        if(min==nullptr)return res;
        vector<Tipp*>treeTab,toVis;
        for(auto c=min;toVis.empty()||toVis[0]!=c;c=c->next)toVis.push_back(c);
        for(auto c:toVis){
            while(true){
                while(c->numOfChilds>=(int)treeTab.size())treeTab.push_back(nullptr);
                if(treeTab[c->numOfChilds]==nullptr){
                    treeTab[c->numOfChilds]=c;
                    break;
                }
                Tipp* ot=treeTab[c->numOfChilds];
                treeTab[c->numOfChilds]=nullptr;
                Tipp* smaller=(ot->val<c->val)?ot:c;
                Tipp* bigger=(ot->val<c->val)?c:ot;
                bigger->next->prev=bigger->prev;
                bigger->prev->next=bigger->next;
                bigger->next=bigger->prev=bigger;
                smaller->child=mergeLists(smaller->child,bigger);
                bigger->par=smaller;
                bigger->isMarked=false;
                smaller->numOfChilds++;
                c=smaller;
            }
            if(c->val<=min->val)min=c;
        }
        return res;
    }
    void decreaseKey(Tipp* tipp,const V& newPrio){
        assert(newPrio<=tipp->val);
        decreaseKeyUnchecked(tipp,newPrio);
    }
    void remove(Tipp* tipp){
        decreaseKeyUnchecked(tipp,numeric_limits<V>::min());
        popMin();
    }
    static Tipp* mergeLists(Tipp* l,Tipp *r){
        if(!l&&!r)return nullptr;
        if(!l)return r;
        if(!r)return l;
        auto lNext=l->next;
        l->next=r->next;
        l->next->prev=l;
        r->next=lNext;
        r->next->prev=r;
        return l->val<r->val?l:r;
    }
    void decreaseKeyUnchecked(Tipp* tipp,const V& newPrio){
        tipp->val=newPrio;
        if(tipp->par!=nullptr && tipp->val<=tipp->par->val)cutNode(tipp);
        if(tipp->val<=min->val)min=tipp;
    }
    void cutNode(Tipp* tipp){
        tipp->isMarked=false;
        if(tipp->par==nullptr)return;
        if(tipp->next!=tipp){
            tipp->next->prev=tipp->prev;
            tipp->prev->next=tipp->next;
        }
        if(tipp->par->child==tipp){
            if(tipp->next!=tipp)tipp->par->child=tipp->next;
            else tipp->par->child=nullptr;
        }
        tipp->par->numOfChilds--;
        tipp->prev=tipp->next=tipp;
        min=mergeLists(min,tipp);
        if(tipp->par->isMarked){
            cutNode(tipp->par);
        }else tipp->par->isMarked=true;
        tipp->par=nullptr;
    }
};
typedef pair<ll,ll> pii;
const int N=500005;
vector<pii>g[N];
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll n,m,a,b;
    cin>>n>>m>>a>>b;
    using Fibo=FibonacciHeap<int,ll>;
    Fibo pq;
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        g[a].push_back({b,c});
    }
    vector<ll>dist(n,LLONG_MAX/2);
    vector<int>prev(n,0);
    dist[a]=0;
    pq.push(a,0);
    vector<Fibo::Tipp*>tipud(n);
    while(!pq.empty()){
        Fibo::Tipp* p=pq.popMin();
        int u=p->key;
        //if(p->val!=dist[u])continue;
        for(pii& e:g[u]){
            auto v=e.first,w=e.second;
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                prev[v]=u;
                if(tipud[v]==nullptr)tipud[v]=pq.push(v,dist[v]);
                else pq.decreaseKey(tipud[v],dist[v]);
            }
        }
    }
    if(dist[b]>=LLONG_MAX/2){
        cout<<-1<<endl;
    }else{
        cout<<dist[b]<<' ';
        vector<int>nums;
        int u=b;
        while(u!=a){
            nums.push_back(u);
            u=prev[u];
        }
        nums.push_back(a);
        reverse(nums.begin(),nums.end());
        cout<<nums.size()-1<<'\n';
        for(int i=1;i<nums.size();i++)cout<<nums[i-1]<<' '<<nums[i]<<'\n';
    }
    return 0;
}
