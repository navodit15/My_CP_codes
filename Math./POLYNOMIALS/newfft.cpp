#include <bits/stdc++.h>
using namespace std;
using lint = long long;
template<class T = int> using V = vector<T>;
template<class T = int> using VV = V< V<T> >;
#define fr(i,a,b) for(int i = a ; i <= b ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define pb push_back

//https://codeforces.com/contest/958/submission/90193880


struct Mint {
  using M = Mint;
  static unsigned P;
  unsigned v;
  constexpr Mint() : v(0) {}
  constexpr Mint(unsigned _v, int) : v(_v) {}
  template<class Z> Mint(const Z& a) : v((a < 0 ? P - -a % P : a) % P) {}
  static unsigned p() { return P; }
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
unsigned Mint::P;

namespace FFT {
  constexpr double pi = acos(-1);
  struct C {
    double x, y;
    C(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    C operator~() const { return {x, -y}; }
    C operator*(const C& r) const { return {x * r.x - y * r.y, x * r.y + y * r.x}; }
    C operator+(const C& r) const { return {x + r.x, y + r.y}; }
    C operator-(const C& r) const { return {x - r.x, y - r.y}; }
  };
  VV<C> w(1, V<C>(1, 1));
  void init(int lg) {
    for (int k = 1; k <= lg; ++k) if (k >= (int)w.size()) {
      w.emplace_back(1 << (k - 1));
      double th = 2 * pi / (1 << k);
      for (int i = 0; i < 1 << (k - 1); ++i) {
        w[k][i] = i & 1 ? C(cos(i * th), sin(i * th)) : w[k - 1][i >> 1];
      }
    }
  }
  void fft(V<C>& a) {
    int n = a.size(), lg = __lg(n);
    assert(n == 1 << lg);
    init(lg);
    for (int k = lg; k; --k) {
      int d = 1 << (k - 1);
      for (int s = 0; s < n; s += 2 * d) {
        for (int i = s; i < s + d; ++i) {
          C x = a[i], y = a[i + d];
          a[i] = x + y;
          a[i + d] = w[k][i - s] * (x - y);
        }
      }
    }
  }
  void ifft(V<C>& a) {
    int n = a.size(), lg = __lg(n);
    assert(n == 1 << lg);
    init(lg);
    for (int k = 1; k <= lg; ++k) {
      int d = 1 << (k - 1);
      for (int s = 0; s < n; s += 2 * d) {
        for (int i = s; i < s + d; ++i) {
          C x = a[i], y = ~w[k][i - s] * a[i + d];
          a[i] = x + y;
          a[i + d] = x - y;
        }
      }
    }
    for (auto&& e : a) e.x /= n, e.y /= n;
  }
  template<int m = 3, int k = 10>
  V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {
    int na = a.size(), nb = b.size();
    if (!na or !nb) return {};
    int nc = na + nb - 1, n = 1 << __lg(2 * nc - 1);
    if (min(na, nb) < 16) {
      V<Mint> c(nc);
      for (int i = 0; i < na; ++i) for (int j = 0; j < nb; ++j) {
        c[i + j] += a[i] * b[j];
      }
      return c;
    }
    VV<C> f(m, V<C>(n));
    for (int p = 0; p < m; ++p) {
      for (int i = 0; i < n; ++i) {
        if (i < na) f[p][i].x = a[i].v >> (p * k) & ~(~0U << k);
        if (i < nb) f[p][i].y = b[i].v >> (p * k) & ~(~0U << k);
      }
      fft(f[p]);
    }
    C ta[m], tb[m], tc[2 * m];
    for (int i = 0, z = 0; i < n; ++i) {
      if (2 * z + 1 < i) z = 2 * z + 1;
      int j = i ^ z;
      if (i > j) continue;
      for (int p = 0; p < m; ++p) {
        ta[p] = (f[p][i] + ~f[p][j]) * C(0.5, 0);
        tb[p] = (f[p][i] - ~f[p][j]) * C(0, -0.5);
      }
      fill(tc, tc + 2 * m, 0);
      for (int p = 0; p < m; ++p) for (int q = 0; q < m; ++q) {
        tc[p + q] = tc[p + q] + ta[p] * tb[q];
      }
      for (int p = 0; p < m; ++p) {
        f[p][i] = tc[p] + C(0, 1) * tc[m + p];
        f[p][j] = ~tc[p] + C(0, 1) * ~tc[m + p];
      }
    }
    for (int p = 0; p < m; ++p) ifft(f[p]);
    V<Mint> c(nc);
    for (int i = 0; i < nc; ++i) {
      for (int p = 2 * m - 2; p >= 0; --p) {
        lint s = (p < m ? f[p][i].x : f[p - m][i].y) + 0.5;
        c[i].v = (((uint64_t)c[i].v << k) + s) % Mint::p();
      }
    }
    return c;
  }
}

template<class T, V<T> Mul(const V<T>&, const V<T>&)>
struct FormalPowerSeries : public V<T> {
  using F = FormalPowerSeries;
  using V<T>::V;
  FormalPowerSeries() {}
  FormalPowerSeries(const V<T>& v) : V<T>(v) {}
  T get(int i) const { return i < (int)this->size() ? (*this)[i] : 0; }
  F cut(int n) const { return F(begin(*this), begin(*this) + min<int>(n, this->size())); }
  F trim() {
    while (not this->empty() and !this->back()) this->pop_back();
    return *this;
  }
  F operator+() const { return *this; }
  F operator-() const { F res = *this; for (auto&& e : res) e = -e; return res; }
  explicit operator bool() const noexcept { return not F(*this).trim().empty(); }
  bool operator!() const noexcept { return !(bool)*this; }
  F& operator*=(const F& r) { return *this = Mul(*this, r); }
  F& operator*=(const T& r) { for (auto&& e : *this) e *= r; return *this; }
  F& operator/=(const F& r) {
    int n = max(this->size(), r.size());
    *this *= r.inv(n);
    this->resize(n);
    return *this;
  }
  F& operator/=(const T& r) { return *this *= 1 / r; }
  F& operator+=(const F& r) {
    this->resize(max(this->size(), r.size()));
    for (int i = 0; i < (int)r.size(); ++i) (*this)[i] += r[i];
    return *this;
  }
  F& operator+=(const T& r) { return *this += F(1, r); }
  F& operator-=(const F& r) {
    this->resize(max(this->size(), r.size()));
    for (int i = 0; i < (int)r.size(); ++i) (*this)[i] -= r[i];
    return *this;
  }
  F& operator-=(const T& r) { return *this -= F(1, r); }
  F& operator<<=(int n) {
    if (n < 0) return *this >>= -n;
    this->insert(begin(*this), n, 0);
    return *this;
  }
  F& operator>>=(int n) {
    if (n < 0) return *this <<= -n;
    this->erase(begin(*this), begin(*this) + n);
    return *this;
  }
  friend F operator*(const F& l, const F& r) { return F(l) *= r; }
  friend F operator*(const F& l, const T& r) { return F(l) *= r; }
  friend F operator*(const T& l, const F& r) { return r * l; }
  friend F operator/(const F& l, const F& r) { return F(l) /= r; }
  friend F operator/(const F& l, const T& r) { return F(l) /= r; }
  friend F operator/(const T& l, const F& r) { return r.inv() * l; }
  friend F operator+(const F& l, const F& r) { return F(l) += r; }
  friend F operator+(const F& l, const T& r) { return F(l) += r; }
  friend F operator+(const T& l, const F& r) { return r + l; }
  friend F operator-(const F& l, const F& r) { return F(l) -= r; }
  friend F operator-(const F& l, const T& r) { return F(l) -= r; }
  friend F operator-(const T& l, const F& r) { return -r + l; }
  friend ostream& operator<<(ostream& os, const F& r) {
    int n = F(r).trim().size();
    if (!n) return os << '0';
    for (int i = 0; i < n; ++i) if (r[i]) {
      if (!i or r[i] != 1) os << r[i];
      if (i) cout << 'X';
      if (i >= 2) cout << '^' << i;
      if (i < n - 1) cout << " + ";
    }
    return os;
  }
  friend F operator<<(const F& l, int n) { return F(l) <<= n; }
  friend F operator>>(const F& l, int n) { return F(l) >>= n; }
  friend bool operator==(const F& l, const F& r) { return (l - r).trim().empty(); }
  friend bool operator==(const F& l, const T& r) { return l == F(1, r); }
  friend bool operator==(const T& l, const F& r) { return F(1, l) == r; }
  friend bool operator!=(const F& l, const F& r) { return !(l == r); }
  friend bool operator!=(const F& l, const T& r) { return !(l == r); }
  friend bool operator!=(const T& l, const F& r) { return !(l == r); }
  F inv(int n = -1) const {
    assert(get(0));
    if (n == -1) n = this->size();
    F g{1 / (*this)[0]};
    for (int m = 1; m < n; m *= 2) {
      g = (2 * g - cut(2 * m) * g * g).cut(2 * m);
    }
    return g.cut(n);
  }
  F diff() const {
    int n = this->size();
    F res(n - 1);
    for (int i = 1; i < n; ++i) res[i - 1] = i * (*this)[i];
    return res;
  }
  F integ() const {
    int n = this->size();
    F res(n + 1);
    for (int i = 1; i <= n; ++i) res[i] = (*this)[i - 1] / i;
    return res;
  }
  F log(int n = -1) const {
    assert(get(0) == 1);
    if (n == -1) n = this->size();
    return (diff() * inv(n - 1)).cut(n - 1).integ();
  }
  F exp(int n = -1) const {
    assert(!get(0));
    if (n == -1) n = this->size();
    F g{1};
    for (int m = 1; m < n; m *= 2) {
      g = (g * (1 + cut(2 * m) - g.log(2 * m))).cut(2 * m);
    }
    return g.cut(n);
  }
  F sqrt(int n = -1) const {
    assert(get(0) == 1);
    if (n == -1) n = this->size();
    F g{1};
    for (int m = 1; m < n; m *= 2) {
      g = ((g + cut(2 * m) * g.inv(2 * m)) / 2).cut(2 * m);
    }
    return g.cut(n);
  }
};
template<class T> V<T> naive_multiply(const V<T>& a, const V<T>& b) {
  int n = a.size(), m = b.size();
  V<T> c(n + m - 1);
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    c[i + j] += a[i] * b[j];
  }
  return c;
}
// using FPS = FormalPowerSeries<double, naive_multiply>; // for debug

using FPS = FormalPowerSeries< Mint, FFT::multiply<1, 12> >;

pair<FPS, FPS> polynomial_divmod(FPS a, FPS b) {
  a.trim(), b.trim();
  assert(b);
  if (a.size() < b.size()) return {{}, a};
  reverse(begin(a), end(a));
  reverse(begin(b), end(b));
  int m = a.size() - b.size() + 1;
  auto q = (a.cut(m) * b.inv(m)).cut(m);
  reverse(begin(a), end(a));
  reverse(begin(b), end(b));
  reverse(begin(q), end(q));
  return {q, a - q * b};
}
template<class T> T eval(const FPS& f, const T& a) {
  T res = 0, x = 1;
  for (const auto& e : f) {
    res += e * x;
    x *= a;
  }
  return res;
}
template<class T> V<T> multipoint_evaluation(const FPS& f, const V<T>& p) {
  int n = p.size();
  if (n < 256) {
    V<T> res(n);
    for (int i = 0; i < n; ++i) res[i] = eval(f, p[i]);
    return res;
  }
  V<FPS> t(2 * n);
  for (int i = 0; i < n; ++i) {
    t[n + i] = FPS{-p[i], 1};
  }
  for (int i = n - 1; i; --i) {
    t[i] = t[2 * i] * t[2 * i + 1];
  }
  t[1] = polynomial_divmod(f, t[1]).second;
  for (int i = 1; i < n; ++i) {
    t[2 * i] = polynomial_divmod(t[i], t[2 * i]).second;
    t[2 * i + 1] = polynomial_divmod(t[i], t[2 * i + 1]).second;
  }
  V<T> res(n);
  for (int i = 0; i < n; ++i) {
    res[i] = t[n + i].get(0);
  }
  return res;
}
bool operator<(Mint l, Mint r) { return l.v < r.v; }
template<class T> FPS polynomial_interpolation(const V<T>& x, V<T> y) {
  int n = x.size();
  assert((int)set<T>(begin(x), end(x)).size() == n);
  assert((int)y.size() == n);
  V<FPS> t(1 << (__lg(2 * n - 1) + 1));
  auto pre = [&](auto& F, int l, int r, int k) {
    if (r - l == 1) {
      t[k] = {-x[l], 1};
      return;
    }
    int m = (l + r + 1) / 2;
    F(F, l, m, 2 * k + 1);
    F(F, m, r, 2 * k + 2);
    t[k] = t[2 * k + 1] * t[2 * k + 2];
  };
  pre(pre, 0, n, 0);
  V<T> v = multipoint_evaluation(t[0].diff(), x);
  for (int i = 0; i < n; ++i) y[i] /= v[i];
  auto rec = [&](auto& F, int l, int r, int k) -> FPS {
    if (r - l == 1) return {y[l]};
    int m = (l + r + 1) / 2;
    FPS fl = F(F, l, m, 2 * k + 1);
    FPS fr = F(F, m, r, 2 * k + 2);
    return t[2 * k + 2] * fl + t[2 * k + 1] * fr;
  };
  return rec(rec, 0, n, 0);
}
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }

const int N = 2e5+5;
int cnt[N+1];
// Divide and Conquer on n polynomials and multiply using fft 
V<Mint> get (int l , int r){
	V<Mint> ret ;
	if(l==r){
		ret.pb(1);
		while(cnt[l]--){
			ret.pb(1);
		}
		return ret ;
	}
	else{
		int mid = l + r ;
		mid/=2;
		V<Mint> rt , lf ; 
		rt = get(l,mid);
		lf = get(mid+1 ,r);
		ret = FFT::multiply(rt,lf);
		return ret ;
	}
}
void solve(){
	int n , m , k ; 
	cin >> n >> m >> k ;
	Mint::P = 1009;
	fr(i,1,n){
		int a ;
		cin >> a ;
		cnt[a]++;
	} 
	V<int> acnt ; 
	for(auto &it : cnt) acnt.pb(it);
	cout << get(1,m)[k] << endl;
}



signed main(){
	unsyncIO();
	int tt =1 ;
	//cin >> tt; 
	rep(i,0,tt){
		solve();
	}
	return 0;
}
