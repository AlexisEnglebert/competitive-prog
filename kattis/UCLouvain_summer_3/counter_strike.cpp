#include<bits/stdc++.h>
 
#define int long long
#define double long double
using namespace std;

#define INF LONG_LONG_MAX
#define EPS 1e-9

typedef complex<double> pt;

#define x real() 
#define y imag() 

double cross(pt a, pt b){
	return (conj(a) * b).y;
}

double orient(pt a, pt b, pt c){
	return cross(b-a, c-a);
}


struct event{
	pair<double, double> p;
	bool start;
};


void polar(vector<event>& p, pt o){
	
	
	
	sort(p.begin(), p.end(), [&](event& a, event& b){

		pt aa = {a.p.first, a.p.second};
		pt bb = {b.p.first, b.p.second};
		
	
		double a1 = (atan2 (aa.y,aa.x)*180/M_PI) ;
		a1+=(a1<0)*360 ;
		
		double a2 = (atan2 (bb.y,bb.x)*180/M_PI) ;
		a2+=(a2<0)*360 ;
		
		return a1 < a2;

	});
	
}

double sign(double a){
	if(a < 0) return -1;
	if(a == 0.0) return 0; 
	return 1;
	//~ return ((double)0 < a) - (a < 0);
}

void solve(){
	int n; cin >> n;
	vector<event> e;
	auto dist = [](pair<double, double> a, pair<double, double> b){
		return sqrt(pow(a.first - b.first,2) + pow(a.second - b.second,2));
	};
	pair<double, double> o = {0, 0};
	pt oo = {0, 0};
	map<pair<double,double>, pair<double, double>> mapper;
		
	for(int i = 0; i < n; i++){
		double xx, yy, r; cin >> xx >> yy >> r;
		double hyp = dist({xx, yy}, o);

		double alpha = asinl((double)(r/hyp));
		double beta = atan2l((yy - o.second), (xx-o.first) );

	
		double t = beta - alpha;
		
		pair<double, double> p1 = {xx+(r * sin(t)), yy+(r* -cos(t))};
		t = beta + alpha;
		pair<double, double> p2 = {xx+(r*-sin(t)), yy+(r*cos(t))};
		mapper[p1] = p2;
		mapper[p2] = p1; 
		
		if(sign(p1.first) > 0 &&  sign(p2.first) > 0){ //ALL POSITIVE X 

			if(p1.second < p2.second){
				e.push_back({p1, true});
				e.push_back({p2, false});
			}else{
				e.push_back({p2, true});
				e.push_back({p1, false});
			}
			
		}else if(sign(p1.first) < 0 &&  sign(p2.first) < 0){ // ALL NEGATIVE X
			if(p1.second > p2.second){
				e.push_back({p1, true});
				e.push_back({p2, false});
			}else{
				e.push_back({p2, true});
				e.push_back({p1, false});
			}

		}
		else{
			
			if(sign(p1.second) == 0 ){
				if(sign(p2.second) > 0){
					
					if(p1.first > p2.first){
						e.push_back({p1, true});
						e.push_back({p2, false});
					}else{
						e.push_back({p2, true});
						e.push_back({p1, false});
					}
					
				}else if(sign(p2.second) < 0){
					if(p1.first < p2.first){
						e.push_back({p1, true});
						e.push_back({p2, false});
					}else{
						e.push_back({p2, true});
						e.push_back({p1, false});
					}
				}else if(sign(p2.second) == 0){
					assert(false);
				}
				
			}else if(sign(p2.second) == 0){
				
					if(sign(p1.second) > 0){
					
					if(p1.first > p2.first){
						e.push_back({p1, true});
						e.push_back({p2, false});
					}else{
						e.push_back({p2, true});
						e.push_back({p1, false});
					}
					
				}else if(sign(p1.second) < 0){
					if(p1.first < p2.first){
						e.push_back({p1, true});
						e.push_back({p2, false});
					}else{
						e.push_back({p2, true});
						e.push_back({p1, false});
					}
				}else if(sign(p1.second) == 0){
					assert(false);
				}
				
			}else if(sign(p1.first) == 0 ){
				if(sign(p2.first) > 0){
					if(p1.second < p2.second){
						e.push_back({p1, true});
						e.push_back({p2, false});
					}else{
						e.push_back({p2, true});
						e.push_back({p1, false});
					}
				}else if(sign(p2.first) < 0){
					if(p1.second > p2.second){
						e.push_back({p1, true});
						e.push_back({p2, false});
					}else{
						e.push_back({p2, true});
						e.push_back({p1, false});
					}
				}else{
					assert(false);
				}
				
			}else if(sign(p2.first) == 0){
				
				if(sign(p1.first) > 0){
					if(p1.second < p2.second){
						e.push_back({p1, true});
						e.push_back({p2, false});
					}else{
						e.push_back({p2, true});
						e.push_back({p1, false});
					}
				}else if(sign(p1.first) < 0){
					if(p1.second > p2.second){
						e.push_back({p1, true});
						e.push_back({p2, false});
					}else{
						e.push_back({p2, true});
						e.push_back({p1, false});
					}
				}else{
					assert(false);
				}
				
			}else if(p1.first > 0 && p2.first < 0){
				if(p1.second < 0 && p2.second < 0){
					e.push_back({p2, true});
					e.push_back({p1, false});
				}else if(p1.second > 0 && p2.second > 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}else if(p1.second > 0 && p2.second < 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}else if(p1.second < 0 && p2.second > 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}
			}else if(p1.first < 0 && p2.first > 0){

				if(p2.second < 0 && p1.second < 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}else if(p2.second > 0 && p1.second > 0){
					e.push_back({p2, true});
					e.push_back({p1, false});
				}else if(p2.second > 0 && p1.second < 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}else if(p2.second < 0 && p1.second > 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}
				
			}else if(p1.second > 0 && p2.second < 0){
				
				if(p1.first > 0 && p2.first > 0){
					e.push_back({p2, true});
					e.push_back({p1, false});
				}else if(p1.first < 0 && p2.first < 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}else if(p1.first > 0 && p2.first < 0){
					assert(false);
				}else if(p1.first < 0 && p2.first > 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}
				
	
			}else if(p1.second < 0 && p2.second > 0){ 
				if(p2.first > 0 && p1.first > 0){
					e.push_back({p1, true});
					e.push_back({p2, false});
				}else if(p2.first < 0 && p1.first < 0){
					e.push_back({p2, true});
					e.push_back({p1, false});
				}else if(p2.first > 0 && p1.first < 0){
					assert(false);
				}else if(p2.first < 0 && p1.first > 0){
					e.push_back({p2, true});
					e.push_back({p1, false});
				}
			
			}else{
				assert(false);
			}
		}
	}
		

	polar(e, oo);
	
	set<pair<double, double>> pts;

	int maxi = 0;
	
	for(int i = 0; i < (e.size()) * 2 ; i++){
		if(e[i%e.size()].start == false){
			if(pts.find(mapper[e[i%e.size()].p]) == pts.end()) continue;
			pts.erase(pts.find(mapper[e[i%e.size()].p]));
		}else{
			pts.insert(e[i%e.size()].p);
		}
		
		maxi = max(maxi, (int)pts.size());

	}
	
	cout << maxi << "\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  //~ int t; cin >> t;
  //~ while(t--) solve();
  solve();

 
  return 0;
}
