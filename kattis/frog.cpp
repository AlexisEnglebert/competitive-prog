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
	//vector<vector<char>> grid(l, vector<char>(w
	vector<vector<car>> voit(l);
	for(int v = 0; v < l; v++){
		int o, i, s; cin >> o >> i >> s;
		//~ cerr << "hmmm" << endl;
		bool lr = !(v%2);
	
		for(int j = o; j < w; j += i){
			voit[l-1-v].push_back({make_pair(j,l-1-v), s, i, lr});
		}
		
		//get the direction
		//~ cerr << "ici" << endl;
	}
	
	//~ for(auto& i : voit){
		//~ for(auto& j : i){
			//~ cout << j.pos.first << " " << j.pos.second << " " << j.speed << " " << j.dir << endl;
		//~ }
	//~ }
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
			//~ cerr << "orig " << orig << endl;
			//~ cerr << v.pos.first << " " << v.pos.second << endl;
			//~ cerr << "dir is : " << dir << " " << v.dir << endl;
			pair<int , int> newpos;
						
			bool is_squished = false;
			if(orig){
				//~ cerr << "cycles" << endl;
				
				newpos = make_pair(v.pos.first + ((-1)*dir*(ts*v.speed)), v.pos.second);
				if(newpos.first < pos.first && pos.first <= v.pos.first) is_squished = true;
				
				//check if current layout is in interval when moving in opposite direction
				
			}else{ //check juste for + inteval
				//~ cerr << "update pos" << endl;
				newpos = make_pair(v.pos.first + (dir* (ts*v.speed)), v.pos.second);
				
				if(v.pos.first < pos.first && pos.first <= newpos.first) is_squished = true; 
			}
			//check if a car colide
			//simply if it is 
			//~ //pair<int, int> 
						
			if(pos == newpos){
				//~ cerr << pos.first << " " << pos.second << " " << newpos.first << " " << newpos.second <<  endl;
				cout << "squish\n";
				//~ cerr << "timetep is : " << i << endl;
				return;
			}
		}		
	}
	//~ cerr << pos.second << endl;
	if(pos.second < l){
		cout << "squish\n";
		return;
	 }
	cout << "safe\n" << endl;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  //~ int t; cin >> t;
  //~ while(t--) solve();
  solve();

 
  return 0;
}
