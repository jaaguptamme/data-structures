#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template<typename T,typename V>
struct SkipMap{
    private:
    struct Node{
        Node** next;
        T key;
        V val;
        Node(T key,V val,int level){
            next=new Node*[level];
            for(int i=0;i<level;i++)next[i]=nullptr;
            this->key=key;
            this->val=val;
        }
        Node(int level){
            next=new Node*[level];
            for(int i=0;i<level;i++)next[i]=nullptr;
        }
    };
    Node* _head=new Node(33);
    int _levels=1;
    int size=0;

    public:

    void insert(T key,V val){
        if(contains(key))return;
        size++;
        int level=0;
        while(level<32 && rand()%2==1){
            level++;
            if(level==_levels){
                _levels++;
                break;
            }
        }
        Node* newNode=new Node(key,val,level+1);
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->key>key)break;
            }
            if(i<=level){
                newNode->next[i]=cur->next[i];
                cur->next[i]=newNode;
            }
        }
    }
    bool contains(T key){
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->key>key)break;
                if(cur->next[i]->key==key)return true;
            }
        }
        return false;
    }

    V get(T key){
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->key>key)break;
                if(cur->next[i]->key==key)return cur->next[i]->val;
            }
        }
        V a;
        insert(key,a);
        return a;
    }

    T succ(T key){
        if(key>=max_element())return key;
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->key>key)break;
            }
        }
        if(cur->next[0]==nullptr)throw invalid_argument("end reached");
        return cur->next[0]->key;
    }

    T max_element(){
        Node* cur=_head;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){}
        }
        return cur->key;
    }

    T min_element(){
        return _head->next[0]->key;
    }

    int get_size(){
        return size;
    }

    bool remove(T key){
        Node* cur=_head;
        bool found=false;
        for(int i=_levels-1;i>=0;i--){
            for(;cur->next[i]!=nullptr;cur=cur->next[i]){
                if(cur->next[i]->key==key){
                    found=true;
                    cur->next[i]=cur->next[i]->next[i];
                    break;
                }
                if(cur->next[i]->key>key)break;
            }
        }
        if(found)size--;
        return found;
    }

    vector<T> to_vec(){
        vector<T>res;
        Node* cur=_head->next[0];
        while(cur!=nullptr){
            res.push_back(cur->key);
            cur=cur->next[0];
        }
        return res;
    }

};
