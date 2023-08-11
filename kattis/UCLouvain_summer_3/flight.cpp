#include<bits/stdc++.h>
 
#define int long long
#define double long double

#define INF LONG_LONG_MAX
#define EPS 1e-9
using namespace std;

struct cmp {
    bool operator() (pair<int,int>a , pair<int,int>b) const {
         return a.second > b.second;
    }
};

void solve(){
	int n, m, k; cin >> n >> m >> k;
	vector<int> a(n);
	for(auto& i : a){
		cin >> i;
	}

	map<int, int>unpaid;
	map<int, int> paid; 

	int ans = 0;
	int total_paid = 0;
	unordered_map<int, int> real_pay;
	for(int i = 0; i < n+m; i++){
		
		while(paid.size() > 0 && paid.begin()->first <= i-m){
			auto it = paid.begin();
			total_paid -= it->second;;
			paid.erase(it);
		}
		
		while(unpaid.size() > 0 && unpaid.begin()->first <= i-m){
			unpaid.erase(unpaid.begin());
		}
		
		if(i < n){
			unpaid.insert({i,a[i],});
		}

		while(unpaid.size() && total_paid < k ){
			auto it = unpaid.end(); it--;
			
			int nv = min(abs(total_paid -(int)k), it->second);
			it->second -= nv;
			ans += nv;
			
			paid[it->first] += nv;
			total_paid += nv;
			
			if(it->second <= 0)
				unpaid.erase(it);
		}
	}
	
	cout << ans << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  //~ int t; cin >> t;
  //~ while(t--) solve();
  solve();

 
  return 0;
}
