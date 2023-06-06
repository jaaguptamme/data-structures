#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
struct SA{
    vector<int> sa_is(const vector<int>& s, int upper) {
        int n = s.size();
        if (n == 0) return {};
        if (n == 1) return {0};
        if (n == 2) return {s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0}};

        vector<int> sa(n), lms, lms_map(n, -1), sum_l(upper + 1, 0), sum_s(upper + 1, 0);
        vector<bool> is_s(n, false);
        int m = 0;
        for (int i = n - 2; i >= 0; i--) is_s[i] = (s[i] == s[i + 1] ? is_s[i + 1] : (s[i] < s[i + 1]));
        for (int i = 0; i < n; i++) {
            if (!is_s[i])
                sum_s[s[i]]++;
            else {
                sum_l[s[i] + 1]++;
                if (!i || !is_s[i - 1]) {
                    lms_map[i] = m++;
                    lms.emplace_back(i);
                }
            }
        }
        for (int i = 0; i <= upper; i++) {
            sum_s[i] += sum_l[i];
            if (i < upper) sum_l[i + 1] += sum_s[i];
        }

        auto induced_sort = [&](const vector<int>& lms) {
            fill(sa.begin(), sa.end(), -1);
            vector<int> buf(upper + 1);
            copy(sum_s.begin(), sum_s.end(), buf.begin());
            for (int idx : lms) sa[buf[s[idx]]++] = idx;

            copy(sum_l.begin(), sum_l.end(), buf.begin());
            sa[buf[s[n - 1]]++] = n - 1;
            for (int i = 0; i < n; i++) {
                if (sa[i] < 1 || is_s[sa[i] - 1]) continue;
                int c = s[sa[i] - 1];
                sa[buf[c]++] = sa[i] - 1;
            }

            copy(sum_l.begin(), sum_l.end(), buf.begin());
            for (int i = n - 1; i >= 0; i--) {
                if (sa[i] < 1 || !is_s[sa[i] - 1]) continue;
                int c = s[sa[i] - 1];
                sa[--buf[c + 1]] = sa[i] - 1;
            }
        };

        induced_sort(lms);
        if (m) {
            vector<int> sorted_lms;
            for (int& idx : sa) {
                if (~lms_map[idx]) {
                    sorted_lms.emplace_back(idx);
                }
            }
            vector<int> rec_s(m);
            int rec_upper = 0;
            rec_s[lms_map[sorted_lms[0]]] = rec_upper;

            for (int i = 1; i < m; i++) {
                int l = sorted_lms[i - 1], r = sorted_lms[i];
                int end_l = (lms_map[l] + 1 < m ? lms[lms_map[l] + 1] : n);
                int end_r = (lms_map[r] + 1 < m ? lms[lms_map[r] + 1] : n);
                bool same = true;
                if (end_l - l != end_r - r)
                    same = false;
                else {
                    for (; l < end_l; l++, r++) {
                        if (s[l] != s[r]) {
                            break;
                        }
                    }
                    if (l == n || s[l] != s[r]) same = false;
                }
                rec_s[lms_map[sorted_lms[i]]] = (same ? rec_upper : ++rec_upper);
            }

            if (rec_upper + 1 != m) {
                auto rec_sa = sa_is(rec_s, rec_upper);
                for (int i = 0; i < m; i++) sorted_lms[i] = lms[rec_sa[i]];
            }
            induced_sort(sorted_lms);
        }

        return sa;
    }

    vector<int> suffix_array(const vector<int>& s, int upper) {
        for (int x : s) assert(0 <= x && x <= upper);
        return sa_is(s, upper);
    }
    template <class T> vector<int> suffix_array(const vector<T>& s) {
        int n = s.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int x, int y) { return s[x] < s[y]; });
        vector<int> ns(n);
        int cur = 0;
        for (int i = 0; i < n; i++) {
            if (i && s[idx[i - 1]] != s[idx[i]]) cur++;
            ns[idx[i]] = cur;
        }
        return sa_is(s, cur);
    }
    vector<int> suffix_array(const string& s) {
        vector<int> ns;
        for (char c : s) ns.emplace_back(c);
        return sa_is(ns, 255);
    }

    template <class T> vector<int> lcp_array(const vector<T>& s, const vector<int>& sa) {
        int n = s.size();
        vector<int> rank(n);
        for (int i = 0; i < n; i++) rank[sa[i]] = i;
        vector<int> lcp(n - 1);
        for (int i = 0, h = 0; i < n; i++) {
            if (h > 0) h--;
            if (rank[i] == 0) continue;
            int j = sa[rank[i] - 1];
            for (; j + h < n && i + h < n; h++) {
                if (s[j + h] != s[i + h]) {
                    break;
                }
            }
            lcp[rank[i] - 1] = h;
        }
        return lcp;
    }

    vector<int> lcp_array(const string& s, const vector<int>& sa) {
        vector<int> ns;
        for (char c : s) ns.emplace_back(c);
        return lcp_array(ns, sa);
    }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    SA t;
    auto v=t.suffix_array(s);
    for(auto el:v)cout<<el<<' ';
    return 0;
}
