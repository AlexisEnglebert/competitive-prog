#include<bits/stdc++.h>
#pragma GCC optimize ("O2")
 
#define int long long
#define double long double

#define INF LONG_LONG_MAX
#define EPS 1e-9
using namespace std;

struct trajet{
	pair<int, int> start;
	pair<int, int> end;
	int start_time;
	int dist;
};


bitset<1000> vis;        // N = left size
array<int, 1000> match;  // M = right size
bool augment(int u, vector<vector<int>>& adj) {
    if (vis[u]) return false;
    vis[u] = true;
    for (int v : adj[u]) {
        if (match[v] == -1 || augment(match[v], adj)) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int khun(vector<vector<int>>& adj){
	//left size < N 
	//right size >= N
	int mcbm = 0;
	vector<int> no_match;
	match.fill(-1);
	for (int u=0; u<(adj.size()/2); u++) {
		vis.reset();
		if (augment(u, adj)) mcbm++;
		else no_match.push_back(u);
	}
	
	return mcbm;
}


void solve(){
	int n;
	scanf("%ld", &n);
	vector<trajet> all;
	char dumb;
	
	auto dist = [](pair<int, int> a, pair<int, int> b){
		return abs(a.first - b.first) + abs(a.second - b.second);
	};
	
	for(int i = 0; i < n; i++){
		int h, m;
		pair<int, int> start; 
		pair<int, int> end; 
		
		scanf("%ld %c %ld %ld %ld %ld %ld", &h, &dumb, &m, &start.first, &start.second, &end.first, &end.second);

		
		int start_time = (h*60) + m;
		int d = dist(start, end);
		all.push_back({start, end, start_time, d});
	}
	
	//possible de faire un autre trajet si on fait le trajet de base qu'on nous a demandé
	vector<vector<int>> adj(2*n); //2*n car on utilise le tricks avec in_node et out_node
	
	for(int i = 0 ; i < all.size(); i++){
		for(int j = 0; j < all.size(); j++){
			//from dest to the point
			
			int total_time = (all[i].start_time + all[i].dist); // le trajet obligé
			total_time += dist(all[i].end, all[j].start); //le trajet pour arriver jusqu'au pts de départ 
			
			
			if(total_time < all[j].start_time){
				adj[i].push_back(n+j); //to be the other node ( path vertex cover tricks)
			}
		}
	}

	cout << n- khun(adj) << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  scanf("%ld", &t);
  while(t--) solve();
 
  return 0;
}
