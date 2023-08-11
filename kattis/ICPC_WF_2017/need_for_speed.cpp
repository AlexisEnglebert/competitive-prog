#include<bits/stdc++.h>
 
#define int long long
#define double long double

#define INF LONG_LONG_MAX
#define EPS 1e-9
using namespace std;


void solve(){
	double n, t; cin >> n >> t; 
	vector<pair<double, double>> a(n); 
	int mini = INF;
	for (auto&i  : a){
		cin >> i.first >> i.second;
		mini = min((int)mini, (int)(i.second));
	}
	
	double left = (mini == INF ? -10000000000 : -1*mini); 
	double right = 10000000000;
	int cnt = 0;
	while(left < right){
		if(cnt > 10000) break;
		double m = (left + right)/2;
		double total = 0; 
		for(auto& i : a){
			total += i.first/(double)(i.second + m);
		}
		 if(total < t){
			right = m;
		}else if(total > t){
			left = m;
		}
		cnt++;
	}
	cout << fixed << setprecision(10) << (left+right)/2 << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  //~ int t; cin >> t;
  //~ while(t--) solve();
  solve();

 
  return 0;
}
