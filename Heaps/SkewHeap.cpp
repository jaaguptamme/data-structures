template<typename T,typename L>//Edge, lazy type
struct SkewHeap{
    struct Tipp{
        Tipp* ch[2]={nullptr,nullptr};
        T voti;
        L lazy;
        Tipp(T voti, L lazy):voti(voti),lazy(lazy){}
    }*juur;
    SkewHeap():juur(nullptr){}
    void lukka(Tipp *t){
        t->voti.c+=t->lazy;
        if(t->ch[0])t->ch[0]->lazy+=t->lazy;
        if(t->ch[1])t->ch[1]->lazy+=t->lazy;
        t->lazy=0;
    }
    Tipp* uhenda(Tipp *a,Tipp *b){
        if(!a)return b;
        if(!b)return a;
        lukka(a);lukka(b);
        if(a->voti.c>b->voti.c)swap(a,b);
        a->ch[1]=uhenda(b,a->ch[1]);
        swap(a->ch[0],a->ch[1]);
        return a;
    }
    void lisa(T voti){
        Tipp *t=new Tipp(voti,0);
        juur=uhenda(juur,t);
    }
    void pop(){
        lukka(juur);
        juur=uhenda(juur->ch[0],juur->ch[1]);
    }
    T top(){
        lukka(juur);
        return juur->voti;
    }
    bool empty(){
        return !juur;
    }
    void lisa(L lazy){
        if(empty())return;
        juur->lazy+=lazy;
    }
    void uhenda(SkewHeap t){
        juur=uhenda(juur,t.juur);
    }
};
