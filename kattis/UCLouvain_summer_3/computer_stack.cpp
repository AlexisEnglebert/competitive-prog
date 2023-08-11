#include<bits/stdc++.h>
#pragma GCC optimize("O2")

#define int long long
#define double long double

#define INF LONG_LONG_MAX
#define EPS 1e-9
using namespace std;
#define A 911382323
#define MOD 972663749

vector<int> Ak(10000);

int safemod(int a, int m){
	return (a%m + m) % m;
}

int hash_string(string s){
	int result = 0;
	for(int i = 0; i < s.size(); i++){
		assert(i < 10000);
		result += s[i] * Ak[i];
		result = safemod(result, MOD);
	}
	return result;
}

struct elem{
	int size;
	int hash;
		
	vector<elem> inside; //cardinality is the size.
	unordered_map<int, bool> mapper;
	
	elem() = default;
	elem(string s){
		hash = 121131865;
		size = 2;
	}
	
	void add(elem& a){
		if(mapper.find(a.hash) != mapper.end()) return;
		inside.push_back(a);
		mapper[a.hash] = true;

		hash -= ('}'*Ak[size-1]);
		hash = safemod(hash, MOD);

		
		int toadd = (a.hash * Ak[size-1]) % MOD;
		hash += toadd;
		hash %= MOD;
		
		size += a.size;
		hash += '}' * Ak[size-1];
		hash %= MOD;
		
	}
};

void solve(){
	int n; cin >> n;
	
	stack<elem> st;
	string op; 
	for(int i = 0; i < n; i++){
		cin >> op;
		if(op =="DUP"){
			st.push(st.top());
			
		}else if(op == "ADD"){
			elem a = st.top(); st.pop(); 
			st.top().add(a);
			
		}else if(op == "PUSH"){
			st.push(elem("{"));
		}else if(op == "UNION"){
			
			elem a = st.top(); st.pop();
			elem b = st.top(); st.pop();
			if(a.inside.size() < b.inside.size()){
				for(auto&i : a.inside){
					b.add(i);
				}
				st.push(b);
			}else{
				for(auto&i : b.inside){
					a.add(i);
				}
				st.push(a);
			}
			
		}else if(op == "INTERSECT"){
			elem res = elem("{");

			elem a = st.top(); st.pop();
			
			vector<int> intersection;
			for(auto& i : st.top().inside){ //if both inside
				if(a.mapper[i.hash]){
					res.add(i);
				}
			}
			st.pop();

			st.push(res);
		}
		cout << st.top().inside.size() << "\n";
	}
	cout << "***\n";
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  Ak[0] = 1;
  for(int i = 1; i < Ak.size(); i++){ //precompute hash
	  Ak[i] = ((Ak[i-1] * A) % MOD);
  }
  
  int t; cin >> t;
  while(t--) solve();
  //~ solve();

 
  return 0;
}
