vector<int>z(string &s){
    int n=s.size();
    vector<int>z(n);
    z[0]=n;
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(r>=i)z[i]=min(z[i-l],r+1-i);
        while(i+z[i]<n && s[i+z[i]]==s[z[i]])z[i]++;
        if(i+z[i]-1>r){
            r=i+z[i]-1;
            l=i;
        }
    }
    return z;
}
