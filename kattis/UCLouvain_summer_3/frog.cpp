#include<bits/stdc++.h>
 
#define int long long
#define double long double

#define INF LONG_LONG_MAX
#define EPS 1e-9
using namespace std;

struct car{
	pair<int, int> pos;
	int speed;
	int interval;
	int dir; // 1 -> ,   0  <-
	
};

void solve(){
	int l, w; cin >> l >> w;
	vector<vector<car>> voit(l);
	for(int v = 0; v < l; v++){
		int o, i, s; cin >> o >> i >> s;
		bool lr = !(v%2);
	
		for(int j = o; j < w; j += i){
			voit[l-1-v].push_back({make_pair(j,l-1-v), s, i, lr});
		}
	}
	
	int p; cin >> p; 
	string s; cin >> s;
	pair<int, int> pos = make_pair(p, -1);
	for(int i = 0; i < s.size(); i++){
		//update player position
		if(s[i] == 'U'){
			pos.second++;
		}else if(s[i] == 'D'){
			pos.second--;
		}else if(s[i] == 'L'){
			pos.first--;
		}else if(s[i] == 'R'){
			pos.first++;
		}
			
		int level = pos.second; //get the current level :)
			
		if(level >= l) continue;
		
		//check for cycles 
		
		for(auto& v : voit[level]){
			// get new x by timestep
			int ts = i+1;
			int dir = (v.dir == 1) ? 1 : -1;
			bool orig = (((i+1)%v.interval) == 0);
			pair<int , int> newpos;
						
			bool is_squished = false;
			if(orig){
				newpos = make_pair(v.pos.first + ((-1)*dir*(ts*v.speed)), v.pos.second);
				if(newpos.first < pos.first && pos.first <= v.pos.first) is_squished = true;

			}else{ 
				newpos = make_pair(v.pos.first + (dir* (ts*v.speed)), v.pos.second);
				
				if(v.pos.first < pos.first && pos.first <= newpos.first) is_squished = true; 
			}
						
			if(pos == newpos){
				cout << "squish\n";
				return;
			}
		}		
	}
	if(pos.second < l){
		cout << "squish\n";
		return;
	 }
	cout << "safe\n" << endl;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  solve();

 
  return 0;
}
