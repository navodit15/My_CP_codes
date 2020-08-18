// ref : https://codeforces.com/blog/entry/63903
// Verification :CSES

#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops") 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
//#define int long long
#define fr(i,a,b) for(int i = a ; i <= b ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define fst first
#define snd second
using namespace __gnu_pbds;
using ordered_set =
 tree<int, null_type,less<int>,
 rb_tree_tag,tree_order_statistics_node_update>;
//find_by_order(k):returns iterator to kth element starting from 0
//order_of_key(k):returns count of elements strictly smaller than k
typedef long long ll;typedef pair<int, int> pii;
typedef vector<int> vi;typedef long double ld;
template<class T>
using min_heap = priority_queue<T,vector<T>,greater<T>>; 
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
template<typename T> 
void remdup(vector<T>& v) {
	sort(all(v)); v.erase(unique(all(v)), v.end());
}
template<typename T> void re(vector<T> &v) {trav(i,v) cin >> i;}
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }
#ifdef np
#include "C:\Users\navodit\Desktop\mycodes\pr.h"
#else
#define trace(...)
#endif

#define MOD 1000000007  


template<unsigned P> struct ModInt {
  using M = ModInt;
  unsigned v;
  constexpr ModInt() : v(0) {}
  constexpr ModInt(unsigned _v, int) : v(_v) {}
  template<class Z> ModInt(const Z& a) : v((a < 0 ? P - -a % P : a) % P) {}
  static constexpr unsigned p() { return P; }
  M operator+() const { return *this; }
  M operator-() const { return {v ? P - v : 0, 0}; }
  explicit operator bool() const noexcept { return v; }
  bool operator!() const noexcept { return !(bool)*this; }
  M& operator*=(M r) { v = (uint64_t)v * r.v % P; return *this; }
  M& operator/=(M r) { return *this *= r.inv(); }
  M& operator+=(M r) { if ((v += r.v) >= P) v -= P; return *this; }
  M& operator-=(M r) { if ((v += P - r.v) >= P) v -= P; return *this; }
  friend M operator*(M l, M r) { return M(l) *= r; }
  friend M operator/(M l, M r) { return M(l) /= r; }
  friend M operator+(M l, M r) { return M(l) += r; }
  friend M operator-(M l, M r) { return M(l) -= r; }
  friend ostream& operator<<(ostream& os, M r) { return os << r.v; }
  friend bool operator==(M l, M r) { return l.v == r.v; }
  friend bool operator!=(M l, M r) { return !(l == r); }
  M inv() const {
    int a = v, b = P, x = 1, u = 0;
    while (b) {
      int q = a / b;
      swap(a -= q * b, b);
      swap(x -= q * u, u);
    }
    assert(a == 1);
    return x;
  }
  template<class Z> M pow(Z n) const {
    if (n < 0) return pow(-n).inv();
    M res = 1;
    for (M a = *this; n; a *= a, n >>= 1) if (n & 1) res *= a;
    return res;
  }
};
using Mint = ModInt<998244353>; // 
constexpr int N = 1 << 21; // set accordingly
struct Fact {
  vector<Mint> v;
  Fact(int n) : v(n + 1, 1) {
    for (int i = 1; i <= n; ++i) v[i] = i * v[i - 1];
  }
  Mint operator[](int i) const { return v[i]; }
} fact(N);
struct Finv {
  vector<Mint> v;
  Finv(int n) : v(n + 1, 1 / fact[n]) {
    for (int i = n; i; --i) v[i - 1] = i * v[i];
  }
  Mint operator[](int i) const { return v[i]; }
} finv(N);
struct Minv {
  vector<Mint> v;
  Minv(int n) : v(n) {
    for (int i = 1; i <= n; ++i) v[i - 1] = fact[i - 1] * finv[i];
  }
  Mint operator[](int i) const { return v[i - 1]; }
} minv(N);
Mint ncr(int n, int r) {
  if (r < 0 or r > n) return 0;
  return fact[n] * finv[r] * finv[n - r];
}


void solve(){
	int n  ,r ; 
	cin >> n >> r ;
	cout << ncr (n,r) << endl;
}

signed main() {
	unsyncIO();
	int tt =1 ;
	//cin >> tt;
	rep(i,0,tt) solve();













#ifdef np
	cout <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}

