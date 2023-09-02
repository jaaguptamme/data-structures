void calc(int l,int r,vector<int>&candidates,BIT &b){
    if(l+1==r||candidates.empty()){
        for(auto c:candidates)ans[c]=l;
        return;
    }
    int m=(l+r)/2;
    for(int i=l;i<m;i++){//append updates [l,mid)
        auto [l,r,a]=events[i];
        b.upd(l,r,a);
    }
    //split candidates into 2 parts
    vector<int>ok,nok;
    for(auto c:candidates){
        ll sum=0;
        for(auto land:lands[c])sum+=b.q(land);
        if(sum>=target[c])ok.push_back(c);
        else{
            target[c]-=sum;
            nok.push_back(c);
        }
    }
    //undo bit updates
     for(int i=l;i<m;i++){//append updates [l,mid)
        auto [l,r,a]=events[i];
        b.upd(l,r,-a);
    }
    calc(l,m,ok,b);vector<int>().swap(ok);//clear mem
    calc(m,r,nok,b);vector<int>().swap(nok);
}
