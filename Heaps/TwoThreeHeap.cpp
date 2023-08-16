#include <bits/stdc++.h>
//source https://keithschwarz.com/interesting/code/?dir=two-three-heap
//works for 1e6 elements in about second, not very fast
typedef long long ll;
using namespace std;
template<typename T>
class TwoThreeHeap{
    vector<T> elems;
    int leafLev;
    vector<int>rowIndices;
    int brancingFactorForLevel(int lev){
        return lev%4==0?2:3;
    }
    int parent(int ind,int lev){
        int rowInd=ind-rowIndices[lev];
        int parentRowInd=rowInd/brancingFactorForLevel(lev-1);
        return rowIndices[lev-1]+parentRowInd;
    }
    pair<int,int> childs(int ind,int lev){
        int rowInd=ind-rowIndices[lev];
        int branching=brancingFactorForLevel(lev);
        int firstCh=rowIndices[lev+1]+rowInd*branching;
        return {firstCh,firstCh+branching};
    }
    public:
    TwoThreeHeap():leafLev(-1){
        rowIndices = {0, 1, 3, 9, 27, 81, 189, 513, 1485, 4401, 10233, 27729,
    80217, 237681, 552609, 1497393, 4331745, 12834801, 29840913,
    80859249, 233914257,693079281};
    }
    const T& top(){
        return elems.front();
    }
    int size(){
        return elems.size();
    }
    void push(const T& val){
        elems.push_back(val);
        if(size()-1==rowIndices[leafLev+1])leafLev++;
        int row=leafLev;
        for(int ind=elems.size()-1;ind;--row){
            int par=parent(ind,row);
            if(elems[par]>elems[ind])break;
            swap(elems[par],elems[ind]);
            ind=par;
        }
    }
    void pop(){
        swap(elems.front(),elems.back());
        elems.pop_back();
        if(size()==0){
            leafLev=-1;
            return;
        }
        if(rowIndices[leafLev]==size())leafLev--;
        int row=0;
        for(int ind=0;ind<size();row++){
            auto children=childs(ind,row);
            if(children.first>=size())return;
            children.second=min(children.second,size());
            int maxChild=max_element(elems.begin()+children.first,elems.begin()+children.second)-elems.begin();
            if(elems[ind]>elems[maxChild])break;
            swap(elems[ind],elems[maxChild]);
            ind=maxChild;
        }
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*1000;
    TwoThreeHeap<int>t;
    for(int i=N-1;i>=0;i--)t.push(rand()*rand());
    for(int i=0;i<N;i++){
        t.pop();
    }
    return 0;
}
