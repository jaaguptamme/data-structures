//source: https://codeforces.com/blog/entry/124286
#include "bits/stdc++.h"
using namespace std;
namespace reroot {
    const auto exclusive = [](const auto& a, const auto& base, const auto& merge_into, int vertex) {
        int n = (int)a.size();
        using Aggregate = decay_t<decltype(base)>;
        vector<Aggregate> b(n, base);
        for (int bit = (int)__lg(n); bit >= 0; --bit) {
            for (int i = n - 1; i >= 0; --i) b[i] = b[i >> 1];
            int sz = n - (n & !bit);
            for (int i = 0; i < sz; ++i) {
                int index = (i >> bit) ^ 1;
                b[index] = merge_into(b[index], a[i], vertex, i);
            }
        }
        return b;
    };
    // MergeInto : Aggregate * Value * Vertex(int) * EdgeIndex(int) -> Aggregate
    // Base : Vertex(int) -> Aggregate
    // FinalizeMerge : Aggregate * Vertex(int) * EdgeIndex(int) -> Value
    const auto rerooter = [](const auto& g, const auto& base, const auto& merge_into, const auto& finalize_merge) {
        int n = (int)g.size();
        using Aggregate = decay_t<decltype(base(0))>;
        using Value = decay_t<decltype(finalize_merge(base(0), 0, 0))>;
        vector<Value> root_dp(n), dp(n);
        vector<vector<Value>> edge_dp(n), redge_dp(n);
        vector<int> bfs, parent(n);
        bfs.reserve(n);
        bfs.push_back(0);
        for (int i = 0; i < n; ++i) {
            int u = bfs[i];
            for (auto v : g[u]) {
                if (parent[u] == v) continue;
                parent[v] = u;
                bfs.push_back(v);
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            int u = bfs[i];
            int p_edge_index = -1;
            Aggregate aggregate = base(u);
            for (int edge_index = 0; edge_index < (int)g[u].size(); ++edge_index) {
                int v = g[u][edge_index];
                if (parent[u] == v) {
                    p_edge_index = edge_index;
                    continue;
                }
                aggregate = merge_into(aggregate, dp[v], u, edge_index);
            }
            dp[u] = finalize_merge(aggregate, u, p_edge_index);
        }
        for (auto u : bfs) {
            dp[parent[u]] = dp[u];
            edge_dp[u].reserve(g[u].size());
            for (auto v : g[u]) edge_dp[u].push_back(dp[v]);
            auto dp_exclusive = exclusive(edge_dp[u], base(u), merge_into, u);
            redge_dp[u].reserve(g[u].size());
            for (int i = 0; i < (int)dp_exclusive.size(); ++i) redge_dp[u].push_back(finalize_merge(dp_exclusive[i], u, i));
            root_dp[u] = finalize_merge(n > 1 ? merge_into(dp_exclusive[0], edge_dp[u][0], u, 0) : base(u), u, -1);
            for (int i = 0; i < (int)g[u].size(); ++i) {
                dp[g[u][i]] = redge_dp[u][i];
            }
        }
        return make_tuple(move(root_dp), move(edge_dp), move(redge_dp));
    };
}  // namespace reroot
typedef long long ll;
const ll MOD=998244353;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    vector<vector<int>> g(n);
    vector<vector<pair<ll,ll>>>lisa(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        ll b,c;cin>>b>>c;
        lisa[u].push_back({b,c});
        lisa[v].push_back({b,c});
    }
    using Aggregate = array<ll,2>;
    using Value = array<ll,2>;

    auto base = [](int vertex) -> Aggregate {
        return {0,0};
    };
    auto merge_into = [&](Aggregate vertex_dp, Value neighbor_dp, int vertex, int edge_index) -> Aggregate {
        return {(vertex_dp[0]+neighbor_dp[0])%MOD,vertex_dp[1]+neighbor_dp[1]};
    };
    auto finalize_merge = [&](Aggregate vertex_dp, int vertex, int edge_index) -> Value {
        if(edge_index==-1)return vertex_dp;
        Aggregate res={lisa[vertex][edge_index].second*(vertex_dp[1]+1)+
        lisa[vertex][edge_index].first*(vertex_dp[0]+a[vertex]),
        vertex_dp[1]+1};
        res[0]%=MOD;
        return res;
    };

    auto [reroot_result, edge_dp, redge_dp] = reroot::rerooter(g, base, merge_into, finalize_merge);
    for(int i=0;i<n;i++){
        cout<<(reroot_result[i][0]+a[i])%MOD<<' ';
    }
    cout << '\n';
}
