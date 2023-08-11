#include<bits/stdc++.h>
 
#define int long long
#define double long double

#define INF LONG_LONG_MAX
#define EPS 1e-9
using namespace std;

vector<int> ps, lp;
void sieve(int m ){
	lp.assign(m, 0);
	for(int i = 2; i < m; i++){
		if(!lp[i]) {lp[i] = i; ps.push_back(i);}
		for(int p : ps){
			if(p > lp[i] || i*p >= m) break;
			lp[i*p] = p;
		}
	}
}
void solve(){
	int n, m; cin >> n >> m;
	int mod = ((long)1 << n);
	sieve(100000);
	for(int i = 0; i < m; i++){
		int val; cin >> val;
		cout << val << " " << val%mod << endl;
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
