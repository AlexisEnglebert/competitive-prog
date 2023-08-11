#include<bits/stdc++.h>
 
#define int long long
#define double long double

#define INF LONG_LONG_MAX
#define EPS 1e-9
using namespace std;


void dfs(vector<vector<int>>& adj, vector<int>& in_order, int u){
	in_order.push_back(u);
	for(auto v : adj[u])
		dfs(adj, in_order, v), in_order.push_back(u);
}

void solve(){
	int n, q; cin >> n >> q;
	vector<vector<int>> adj(n); 
	vector<int> c(n); 
	for(auto& i : c) cin >> i; 
	
	for(int i = 0; i < (n-1); i++){
		int p; cin >> p; p--;
		adj[p].push_back(i+1); 
	}
	vector<int> euler_tour;
	dfs(adj, euler_tour, 0);
	for(auto&i : euler_tour) cerr << i << " ";
	cerr << endl;
	
	for(int i = 0; i < q; i++){
		int k, x; cin >> k >> x;
	}
	
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  //~ int t; cin >> t;
  //~ while(t--) solve();
  solve();

 
  return 0;
}
