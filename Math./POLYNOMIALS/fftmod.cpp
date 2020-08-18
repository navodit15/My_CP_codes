//ref : http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
// Verification : https://codeforces.com/contest/958/submission/90277044
 
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
    //assert(a == 1);
    return x;
  }
  template<class Z> M pow(Z n) const {
    if (n < 0) return pow(-n).inv();
    M res = 1;
    for (M a = *this; n; a *= a, n >>= 1) if (n & 1) res *= a;
    return res;
  }
};
using Mint = ModInt<1009>;
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
  vector<vector<C>> w(1, vector<C>(1, 1));
  void init(int lg) {
    for (int k = 1; k <= lg; ++k) if (k >= (int)w.size()) {
      w.emplace_back(1 << (k - 1));
      double th = 2 * pi / (1 << k);
      for (int i = 0; i < 1 << (k - 1); ++i) {
        w[k][i] = i & 1 ? C(cos(i * th), sin(i * th)) : w[k - 1][i >> 1];
      }
    }
  }
  void fft(vector<C>& a) {
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
  void ifft(vector<C>& a) {
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
  vector<Mint> multiply(const vector<Mint>& a, const vector<Mint>& b) {
    int na = a.size(), nb = b.size();
    if (!na or !nb) return {};
    int nc = na + nb - 1, n = 1 << __lg(2 * nc - 1);
    if (min(na, nb) < 16) {
      vector<Mint> c(nc);
      for (int i = 0; i < na; ++i) for (int j = 0; j < nb; ++j) {
        c[i + j] += a[i] * b[j];
      }
      return c;
    }
    vector<vector<C>> f(m, vector<C>(n));
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
    vector<Mint> c(nc);
    for (int i = 0; i < nc; ++i) {
      for (int p = 2 * m - 2; p >= 0; --p) {
        ll s = (p < m ? f[p][i].x : f[p - m][i].y) + 0.5;
        c[i].v = (((uint64_t)c[i].v << k) + s) % Mint::p();
      }
    }
    return c;
  }
}
