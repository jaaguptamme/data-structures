#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
struct Lahtirullitudahelloend{
    struct LahtirullitudahelloendiTipp{
        static const int MAKS_SUURUS=32768;//või 4096 või mõni muu kahe aste
        LahtirullitudahelloendiTipp* jargmine;
        vector<T> andmed;
        LahtirullitudahelloendiTipp():jargmine(nullptr){}
        bool onTais(){
            return andmed.size()==MAKS_SUURUS;
        }
    };
    int suurus;
    LahtirullitudahelloendiTipp* juur;
    Lahtirullitudahelloend():suurus(0){
        juur=new LahtirullitudahelloendiTipp();
    }
    T saa(int i){
        LahtirullitudahelloendiTipp* tp;
        tie(tp,i)=leiaTipp(i);
        return tp->andmed[i];
    }
    void sea(int i,const T& val){
        LahtirullitudahelloendiTipp* tp;
        tie(tp,i)=leiaTipp(i);
        tp->andmed[i]=val;
    }
    int pikkus(){
        return suurus;
    }

    pair<LahtirullitudahelloendiTipp*,int> leiaTipp(int i){
        LahtirullitudahelloendiTipp* tp=juur;
        while(i>=(int)tp->andmed.size()){
            i-=tp->andmed.size();
            tp=tp->jargmine;
        }
        return {tp,i};
    }
    void lisa(int i,const T& val){
        LahtirullitudahelloendiTipp* tp;
        tie(tp,i)=leiaTipp(i-1);
        tp->andmed.insert(tp->andmed.begin()+i+1,val);
        suurus++;
        if(tp->onTais()){
            LahtirullitudahelloendiTipp* uus=new LahtirullitudahelloendiTipp();
            uus->jargmine=tp->jargmine;
            tp->jargmine=uus;
            vector<T> esimene=vector<T>(tp->andmed.begin(),tp->andmed.begin()+tp->andmed.size()/2);
            vector<T> teine=vector<T>(tp->andmed.begin()+tp->andmed.size()/2,tp->andmed.end());
            tp->andmed=esimene;
            uus->andmed=teine;
        }
    }
    void kustuta(int i){
        LahtirullitudahelloendiTipp* tp;
        tie(tp,i)=leiaTipp(i);
        tp->andmed.erase(tp->andmed.begin()+i);
        suurus--;
    }

    vector<T> listiks(){
        vector<T>vas;
        LahtirullitudahelloendiTipp* tp=juur;
        while(tp){
            for(auto val:tp->andmed)vas.push_back(val);
            tp=tp->jargmine;
        }
        return vas;
    }
};
