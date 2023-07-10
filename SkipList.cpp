#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T>
struct SkipList{
    private:
    struct Node{
        vector<Node*> next;
        T val;
        Node(T val,int level){
            next.resize(level);
            this->val=val;
        }
        Node(int level){
            next.resize(level);
        }
    };
    Node* _head=new Node(33);
    int _levels=1;
    int size=0;

    public:

    void insert(T val){
        if(contains(val))return;
        size++;
        int level=0;
        while(level<32 && rand()%2==1){
            level++;
            if(level==_levels){
                _levels++;
                break;
            }
        }
        Node* newNode=new Node(val,level+1);
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->val>val)break;
            }
            if(i<=level){
                newNode->next[i]=cur->next[i];
                cur->next[i]=newNode;
            }
        }
    }
    bool contains(T val){
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->val>val)break;
                if(cur->next[i]->val==val)return true;
            }
        }
        return false;
    }

    T succ(T val){
        if(val>=max_element())return val;
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->val>val)break;
            }
        }
        if(cur->next[0]==nullptr)throw invalid_argument("end reached");
        return cur->next[0]->val;
    }

    T max_element(){
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){}
        }
        return cur->val;
    }

    T min_element(){
        return _head->next[0]->val;
    }

    int get_size(){
        return size;
    }

    bool remove(T val){
        Node* cur=_head;
        bool found=false;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->val==val){
                    found=true;
                    cur->next[i]=cur->next[i]->next[i];
                    break;
                }
                if(cur->next[i]->val>val)break;
            }
        }
        if(found)size--;
        return found;
    }

    vector<T> to_vec(){
        vector<T>res;
        Node* cur=_head->next[0];
        while(cur!=nullptr){
            res.push_back(cur->val);
            cur=cur->next[0];
        }
        return res;
    }

};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    SkipList<int> vals;
    for(int i=5;i<10;i++){
        vals.insert(i);
        cout<<i<<' '<<vals.max_element()<<' '<<vals.min_element()<<endl;
    }
    vector<int>V=vals.to_vec();
    for(auto el:V)cout<<el<<'+';
    cout<<endl;
    for(int i=0;i<10;i++){
        cout<<vals.succ(i)<<' ';
    }

    for(int i=0;i<10;i++){
        cout<<vals.remove(i)<<' '<<' '<<vals.get_size()<<endl;
    }
    return 0;
}
