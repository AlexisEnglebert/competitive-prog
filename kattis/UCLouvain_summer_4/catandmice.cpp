#include<bits/stdc++.h>
 
#define int long long
#define double long double

#define INF 1e18
#define EPS 1e-6
using namespace std;

struct mouse{
	double x; 
	double y; 
	double s;
};


double dist(pair<double, double>a , pair<double, double> b){
	return sqrtl(powl(a.first - b.first, 2)  + powl(a.second - b.second,2));
}

int n;
double factor;
vector<mouse> a;

void print_mask(int mask){
	for(int i = n; i >= 0; i--){
		if((mask & (1LL << i))){
			cerr << "1";
		}else{
			cerr << "0";
		}
	}
	cerr << "\n";
}

double dp[1LL<<15][15];
vector<double> fastpow;

bool can(double vel){
	/* 
	 * dp[mask][n]
	 * MASK = le maque
	 * n = l'id de la souris d'avant (previous mouse)
	 */
	
	
	for(int i = 0; i < 1LL<<n; i++){
		for(int j = 0; j < n; j++){
			dp[i][j] = INF;
		}
	} 
	
	//On remplis la base
	for(int i = 0; i < n; i++){	
		int mask = (1LL << i);
		double to_travel = dist(make_pair(0, 0), make_pair(a[i].x, a[i].y));
		
		double time = (to_travel / vel);
			
		if( time - a[i].s > EPS) continue;
		
		dp[mask][i] = time;
	}
	
	for(int mask = 0; mask < (1LL << n); mask++){
		
		int m = __builtin_popcount(mask); // nombre de souris mangées
		if(m == 0) continue;
	
		for(int j = 0; j < n; j++){
			if(((mask>>j) & 1) == 0){ // la souris n'a pas encore été mangée
				int newmask = (mask | (1LL <<j)); //on crée le nouveaux mask
				double to_travel;
			
				for(int k = 0; k < n; k++){ //on regarde si on part de la souris k 
					
					if(((mask >> k) & 1) == 1){
						
						if(dp[mask][k] == INF) continue; //on est pas encore arrivé là
						
						to_travel = dist(make_pair(a[k].x, a[k].y), make_pair(a[j].x, a[j].y));
						double total_speed = (fastpow[m]*vel);
						
						double time = (to_travel / total_speed);
						time += dp[mask][k];

						
						if( time - a[j].s > EPS) continue;
						dp[newmask][j] = min((double)dp[newmask][j], (double)time);
						
					}
				}
			}
		}
	}
	
	for(int i = 0; i < n; i++){
		if(dp[((1LL)<<n)-1][i] < INF) return true;
	}
	return false;
}

void solve(){

	cin >> n;
	a.resize(n);
	for(int i = 0; i < n; i++){
		cin >> a[i].x >> a[i].y >> a[i].s;
	}
	cin >> factor;
	
	fastpow.resize(n+1); 
	fastpow[1] = factor;
	for(int i = 2; i < fastpow.size(); i++){
		fastpow[i] = fastpow[i-1] * factor;
	}
		
	

	double l = 0;
	double r = 100000000;
	int cnt = 0;
	double ans = INF;
	double prev = 0;
	while(l <= r){
		if(cnt > 300)break;
		double m = ((l+r)/2.0);
		
		
		bool c = can(m);
		if(c){
			
			if(fabsl(prev-m) < 1e-5) break;
			
			ans = min(ans, m);
			r = m;
			prev = m;
		}else{
			l = m;
		}
		cnt++;
	}
	cout << fixed << setprecision(15) << ans << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  solve();
 
  return 0;
}
