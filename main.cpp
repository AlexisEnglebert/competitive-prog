#include<bits/stdc++.h>
 
#define int long long
#define double long double

#define INF 1e18
#define EPS 1e-9
using namespace std;

vector<pair<int, int>> ans;
vector<bool> visited;
struct edge{
	edge() = default;
	edge(int u, int v, int idx) : u(u), v(v), idx(idx){}
	int u; int v;
	int idx;
};
void dfs(vector<vector<edge>>& adj, edge current){
	//~ cerr << "current is : " << current.u << " " << current.v << " " << endl;
	visited[current.idx] = true;
	ans.emplace_back(current.u, current.v);
	for(auto& e : adj[current.v]){
		if(visited[e.idx]) continue;
		//~ cerr << "go for : " << e.u << " " << e.v << "\n";
		dfs(adj, e);
		//~ break;
	}
}


void solve(){
	int n, m; cin >> n >> m;
	vector<vector<edge>> adj(n);
	edge first;
	for(int i = 0; i < m; i++){
		int u, v; cin >> u >> v;
		u--, v--;
		if(i == 0){
			first = edge(u, v, i);
		}
		adj[u].emplace_back(u, v, i);
		adj[v].emplace_back(v, u, i);
	}
	visited.resize(m);
	dfs(adj, first);
	
	if(ans.size() != m ){ // check if one connectivity
		cout << "NO\n";
		return;
	 }
	cout << "YES\n";
	for(auto& i : ans) cout << i.first+1 << " " << i.second+1 << "\n";
	
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  //~ int t; cin >> t;
  //~ while(t--) solve();
  solve();
 
  return 0;
}
