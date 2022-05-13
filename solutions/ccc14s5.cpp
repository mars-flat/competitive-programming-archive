// author: Shane Chen (MarsFlat)
// concepts: dfs, dp, ds optimization

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>

#define MN 2001
#define boost() ios_base::sync_with_stdio(false); cin.tie(NULL);
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

using namespace std;

struct dist {
    int to, weight;
    bool operator <(const dist &x) const {
        return weight < x.weight;
    }
};

vector<dist> adj[MN];

int pEnum[MN][2], dp[MN][MN], pma[MN][MN], previous[MN]; //dp[i][j] = ans to the dfs call to the neighbor from cur
//pma[i][j] stores the maximums of the dp answers so i dont have to iterate again

int dfs(int cur, int dist) { 
	int mx = 1;
	
	int lo = 0, hi = (int)(adj[cur].size());
	int idx = -1;
	while (lo < hi) {
		int mid = lo+(hi-lo)/2;
		if (adj[cur][mid].weight < dist && ((mid >= hi-1) || adj[cur][mid+1].weight >= dist)) {
			idx = mid;
			break;
		} else if (adj[cur][mid].weight >= dist) {
			hi = mid;
		} else {
			lo = mid+1;
		}
	}
	if (idx != -1) {
	    if (pma[cur][idx] != -1) {
	        return max(mx, pma[cur][idx]+1);
	    }
	}
	
	for (int i = previous[cur]; i <= idx; ++i) {
        //dp calculated?
		if (pma[cur][i] == -1) {
		    if (dp[cur][i] == -1) {
			dp[cur][i] = dfs(adj[cur][i].to, adj[cur][i].weight);
    		}
    		if (i > 0) {
    			pma[cur][i] = max(dp[cur][i], pma[cur][i-1]);
    		} else {
    			pma[cur][0] = dp[cur][0];
    		}
		}
		mx = max(mx, pma[cur][i]+1);
	 
	}
	previous[cur] = idx+1;
	return mx;
}

int main() {
	boost();

	memset(dp, -1, sizeof(dp));
	memset(pma, -1, sizeof(pma));

	int n; cin >> n;
	pEnum[0][0] = 0; pEnum[0][1] = 0;

    for (int i = 1; i <= n; ++i) {
		cin >> pEnum[i][0]; cin >> pEnum[i][1];
	}
    for (int i = 0; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i != j) {
				adj[i].push_back({
					j, (pEnum[i][0] - pEnum[j][0]) * (pEnum[i][0] - pEnum[j][0]) + 
					(pEnum[i][1] - pEnum[j][1]) * (pEnum[i][1] - pEnum[j][1])}
				);
			}
		}
	}
	for (auto &cons : adj) {
		sort(cons.begin(), cons.end());
	}

	printf("%d\n", dfs(0, 1 << 28)-1); //really just infinity but i dont want int overflow
}
