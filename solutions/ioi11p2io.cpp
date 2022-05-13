// author: Shane Chen (MarsFlat)
// concepts: centroid decomposition

#include <bits/stdc++.h>

#define pii pair<int, int>
#define boost() ios_base::sync_with_stdio(0); cin.tie(0);

using namespace std;

int n, k, mn = 1e9;
vector<pii> g[200005];
int sts[200005];
int used[200005], uc;
int dd[1000005];
vector<pii> tmp;
vector<int> mod;

int sz_dfs(int cur, int pre) {
    int ret = 1;
    for (pii const &e : g[cur]) if (e.first != pre && !used[e.first]) {
        ret += sz_dfs(e.first, cur);
    }
    return sts[cur] = ret;
}

vector<pii>& dist_dfs(int cent, int cur, int pre, int cdist, int cdep, vector<pii>& stn) {
    stn.push_back({cdist, cdep});
    for (pii const &e : g[cur]) if (e.first != pre && !used[e.first]) {
        assert(sts[e.first]);
        dist_dfs(cent, e.first, cur, cdist + e.second, cdep+1, stn);
        if (cur == cent) {
            for (pii const &p : stn) {
                int tt = k - p.first;
                if (!(0 <= tt && tt <= 1000000)) continue;
                if (dd[tt]) mn = min(mn, p.second + dd[tt]);
            }
            for (pii const &p : stn) {
                if (p.first > 1000000) continue;
                if (!dd[p.first]) dd[p.first] = p.second;
                else dd[p.first] = min(dd[p.first], p.second);
                mod.push_back(p.first);
            }
            stn.clear();
            stn.push_back({cdist, cdep});
        }
    }
    return stn;
}

int centroid(int cur, int pre, int xx) {
    for (pii const &e : g[cur]) if (e.first != pre && !used[e.first]) {
        if (sts[e.first] * 2 > xx) {
            return centroid(e.first, cur, xx);
        }
    }
    return cur;
}

int main() {
    boost();
    cin >> n >> k;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        u++; v++;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    while (uc < n) {
        memset(sts,0,sizeof sts);
        for (int i = 1; i <= n; ++i) if (!sts[i] && !used[i]) {
            int xx = sz_dfs(i, -1);
            int cent = centroid(i, -1, xx);
            used[cent] = 1; ++uc;
            for (int const &e : mod) dd[e] = 0;
            mod.clear();
            tmp.clear();
            dist_dfs(cent, cent, -1, 0, 0, tmp);
        }
    }
    cout << (mn == 1e9 ? -1 : mn) << '\n';
}
