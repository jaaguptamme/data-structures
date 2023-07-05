#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

class AC{
    public:
    static const int K = 26;
    struct Vertex {
        int next[K];
        vector<int>vls;
        //bool output = false;
        int p = -1;
        char pch;
        int link = -1;
        int go[K];

        Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
            fill(begin(next), end(next), -1);
            fill(begin(go), end(go), -1);
        }
    };
    vector<Vertex>t;
    AC(){
        t.resize(1);
    }

    void add_string(string const& s,int vl) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) {
                t[v].next[c] = t.size();
                t.emplace_back(v, ch);
            }
            v = t[v].next[c];
        }
        t[v].vls.push_back(vl);
    }

    int go(int v, char ch);

    int get_link(int v) {
        if (t[v].link == -1) {
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        }
        return t[v].link;
    }


};
int AC::go(int v, char ch) {
        int c = ch - 'a';
        if (t[v].go[c] == -1) {
            if (t[v].next[c] != -1)
                t[v].go[c] = t[v].next[c];
            else
                t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return t[v].go[c];
    }
