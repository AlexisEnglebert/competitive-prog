#include<bits/stdc++.h>
 
#define int long long
#define double long double
//#define P(x) {if (debug) cout << x << endl;}
#define H(x) P(#x << ": " << (x))
#define FR(i,a,b) for (int i=(a); i<(b); i++)
#define F(i,n) FR(i,0,n)
#define DR(i,a,b) for (int i=(b); i-->(a);)
#define D(i,n) DR(i,0,n)
#define S(s) (int)(s).size()
#define ALL(v) v.begin(), v.end()
#define MI(a,v) a = min(a,v)
#define MA(a,v) a = max(a,v)
#define V vector
#define pb push_back
#define mt make_tuple
using namespace std;
template<class T> ostream &operator<<(ostream &os, V<T> v) {
    F(i,S(v)) os<<(i?" ":"")<<v[i];
    return os;
}
const bool debug = 1;
const int INF = numeric_limits<int>::max()/2;

using namespace std;



const double EPS = 1e-12; // -> const int EPS = 0
int solveLinear(V<V<double>> A, V<double> b, V<double>& x) {
    int n = S(A), m = S(A[0]), rank = 0, br, bc;
    V<double> col(m); iota(ALL(col), 0);
    F(i,n) {
        double v, bv = 0;
        FR(r,i,n) FR(c,i,m) if ((v = abs(A[r][c])) > bv)
            br = r, bc = c, bv = v;
        if (bv <= EPS) {
            FR(j,i,n) if (fabs(b[j]) > EPS) return -1;
            break;}
        swap(A[i], A[br]), swap(b[i], b[br]), swap(col[i], col[bc]);
        F(j,n) swap(A[j][i], A[j][bc]);
        bv = 1/A[i][i]; // -> bv = inv(A[i][i], mod)
        FR(j,i+1,n) {
            double fac = A[j][i] * bv; // reduce fac in [0, mod[
            b[j] -= fac * b[i]; // reduce b[j] in [0, mod[
            FR(k,i+1,m) A[j][k] -= fac*A[i][k]; // Same here
        }
        rank++;
    }
    x.assign(m, 0);
    for (int i = rank; i--;) {
        b[i] /= A[i][i], x[col[i]] = b[i]; // mult. by inv. and reduce
        F(j,i) b[j] -= A[j][i] * b[i]; // reduce b[j] in [0, mod[
    }
    return rank; // (multiple solutions if rank < m)
}


void solve(){
	int row; cin >> row; 
	int n = (row * (row+1)) / 2;
	cerr << n << endl;
	vector<int> pay(n); for(auto&i : pay) cin >> i;
	
	
	vector<vector<double>> eq(n, vector<double>(n, 0));
	vector<double> left(n);
	
		int current_row = 1;
	for(int i = 0; i < n; i++){
		if((i+1) > ((current_row*(current_row+1))/2)) current_row ++;
		
		int first_of_row = ((current_row*(current_row-1)) /2); //0's based indices
		int offset = (i - first_of_row);

		double b1, b2, b3, b4, hole; cin >> b1 >> b2 >> b3 >> b4 >> hole;
		
		int id_tleft, id_tright, id_bleft, id_bright;
		
		if(b1 == 0.0) id_tleft = -1;
		else id_tleft = ((((current_row-1) * (current_row-2))/2) + (offset-1));
		
		if(b2 == 0.0) id_tright = -1;
		else id_tright = (((current_row-1) * (current_row-2))/2) + (offset); //no +1 cause previous row has -1 holes
		
		if(b3 == 0.0) id_bleft = -1;
		else id_bleft = (((current_row+1)*(current_row)) /2) + offset; //no -1 cause next row has +1 holes
		
		if(b4 == 0.0) id_bright = -1;
		else id_bright = (((current_row+1)*(current_row)) /2) + offset+1;
		
		
		vector<pair<int,double>> idxs = {{id_tleft,b1}, {id_tright,b2}, {id_bleft,b3}, {id_bright,b4}};
		for(auto& v : idxs){
			if(v.first == -1) continue;
			eq[i][v.first] = -v.second;
		}
		eq[i][i] = 1;
		left[i] = (hole*pay[i]);		
	
	}
	

	
	vector<double> xr(n, 0);
	int ressolve = solveLinear(eq, left, xr);

	
	cout << fixed << setprecision(10) <<  xr[0] << "\n";

	
	
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  //~ int t; cin >> t;
  //~ while(t--) solve();
  solve();

 
  return 0;
}
