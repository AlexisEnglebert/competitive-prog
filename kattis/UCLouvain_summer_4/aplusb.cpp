#include <bits/stdc++.h>
#define int long long
#define double long double
#define P(x) {if (debug) cout << x << endl;}
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

typedef valarray<complex<double>> carray;
// WARNING: S(x) must be a power of 2!
void fft(carray &x, carray &roots) {
    int n = S(x); if (n <= 1) return;
    carray even = x[slice(0, n/2, 2)],
        odd = x[slice(1, n/2, 2)],
        rs = roots[slice(0, n/2, 2)];
    fft(even, rs), fft(odd, rs);
    F(k,n/2) {
        auto t = roots[k] * odd[k];
        x[k    ] = even[k] + t;
        x[k+n/2] = even[k] - t;
    }
}
typedef vector<double> vd;
vd conv(vd a, vd b) {
    int s = S(a) + S(b) - 1, n = 1;
    if (s <= 0) return {}; while (n < s) n *= 2;
    carray ab(n), roots(n), cv(n);
    F(i,n) roots[i] = polar((double)1.0, 2 * M_PIl * i / n);
    a.resize(n), b.resize(n);
    for(int i = 0; i < n; i++) ab[i] = {(double)a[i],(double)b[i]}; // "2 in 1" trick
    fft(ab, roots); ab *= ab;
    for(int i = 0 ; i < n; i++) cv[i] = ab[i] - conj(ab[(n-i)%n]);
    roots = roots.apply(conj); fft(cv, roots);
    vd c(s); F(i,s) c[i] = imag(cv[i])/n/4;
    return c;
}


void solve(){
	//IT IS ALL POSSIBLE SUM PROBLEM
	// ai x^i  (ai) = number of occurence and ^i = the number
	int n; cin >> n;
	unordered_map<int, bool> is_in;
	unordered_map<int, int> cnt;
	vector<double> a(n);
	
	int maxn = 0;
	int minn = 0;
	bool has_zero = false;
	for(auto&i : a){
		cin >> i;
		is_in[i] = true;
		cnt[i]++;
		maxn = max((int)maxn, (int)i);
		minn = min((int)minn, (int)i);
	}
	
	minn = abs(minn) + (int)(minn!=0); // avoid 0
	maxn += minn; //total size
	maxn++; //avoid overflow 

	int offset = 0;
	while( (1LL << offset) < maxn){
		offset++;
	}
	
	unordered_map<int, int> to_sub;
	for(int i = 0; i < a.size(); i++){
		to_sub[a[i]*2]++;
	}
	
	int ans = 0;

	vd poly1(1LL << offset,0); //must be power of 2 so 
	vd poly2(1LL << offset,0);
	
	//~ cerr << poly1.size() << endl;
	//~ cerr << "minn : " << minn << endl;
	
	for(int i = 0; i < n; i++){
		if(a[i] == 0) continue;
		poly1[a[i] + minn]++; //on shift pour pas avoir d'exposant négatifs
		poly2[a[i] + minn]++;
	}

	vd res_poly = conv(poly1, poly2);

	
	for(int i = 0; i < res_poly.size(); i++){
		if(res_poly[i] < 1.0) continue;
		
		int real = i - (2*minn);
		
		if(!is_in[real]) continue;
		
		int coef = roundl(res_poly[i]);
		int substract = real == 0 ? 0 : to_sub[real];
		int to_add = coef - substract; 
		
		ans += (to_add * cnt[real]);
	}
	
	//BON MAINTENANT LES 0 DE MERDE LÀ
	for(auto& i : cnt){
		if(i.second > 1 && i.first != 0){
			ans += (2*(i.second * cnt[0]))*(i.second-1);
		}else if(i.first == 0){
			if(i.second <= 2) continue;
			for(int c = i.second; c >= 2; c--){
				ans += ((c-1)*2)*max((int)1,(i.second-2));
			}
			
		}
	}
	
	
	
	cout << ans << "\n";
	
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  solve();
 
  return 0;
}
