#include<bits/stdc++.h>
 
#define int long long
#define double long double

#define INF LONG_LONG_MAX
#define EPS 1e-9
using namespace std;
#define A 911382323
#define MOD 972663749

vector<int> Ak(10000);




int hash_string(string s){
    int result = 0;
    for(int i = 0; i < s.size(); i++){
        result += s[0] * Ak[i];
        result %= MOD;
    }
    return result;
}

struct elem{
    string s;
    int hash;
        
    vector<elem> inside; //cardinality is the size.
    unordered_map<int, bool> mapper;
    
    elem() = default;
    elem(string s) : s(s){
        hash = hash_string(s);
    }
    
    void add(elem a){
        if(mapper.find(a.hash) != mapper.end()) return;
        inside.push_back(a);
        mapper[a.hash] = true;
        //TODO UPDATE the string ? with better hash handling ?????
        string left = s.substr(0,s.size()-1);
        left += a.s;
        left += "}";
        hash = hash_string(left);
        s = left;
    }
};

vector<elem> all;

void solve(){
    int n; cin >> n;
    
    stack<elem> st;
    
    for(int i = 0; i < n; i++){
        string op; cin >> op;
        if(op =="DUP"){
            vector<elem> temp;
            while(!st.empty()) temp.push_back(st.top()), st.pop();
            for(int i = 0; i < 2; i++) for(auto& i : temp) st.push(i);
            
        }else if(op == "ADD"){
            elem a = st.top(); st.pop(); 
            elem b = st.top(); st.pop();
            b.add(a);
            st.push(b);
            
        }else if(op == "PUSH"){
            st.push(elem("{}"));
        }else if(op == "UNION"){
            elem a = st.top(); st.pop(); 
            elem b = st.top(); st.pop();
            elem res = elem("{}");
            unordered_map<int, elem> un;
            for(auto&i : a.inside){
                if(un.find(i.hash) == un.end()) un[i.hash] = i;
            }
            for(auto&i : b.inside){
                if(un.find(i.hash) == un.end()) un[i.hash] = i;
            }
            for(auto& i : un) res.add(i.second);
            st.push(res);
        }else if(op == "INTERSECT"){
            elem a = st.top(); st.pop();
            elem b = st.top(); st.pop();
                        
            elem res = elem("{}");
            unordered_map<int, elem> un;
            unordered_map<int, int> freq;
            vector<int> intersection;
            for(auto&i : a.inside){
                if(un.find(i.hash) == un.end()) un[i.hash] = i;
                freq[i.hash] = true;
            }
            
            for(auto&i : b.inside){
                if(un.find(i.hash) == un.end()) un[i.hash] = i;
                if(freq.find(i.hash) != freq.end()){
                    intersection.push_back(i.hash);
                }
            }
            
            for(auto& i : intersection){
                res.add(un[i]);
            }
            
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
