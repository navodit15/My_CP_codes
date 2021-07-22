/*
ref : https://codeforces.com/blog/entry/63903
https://codeforces.com/contest/1264/submission/66344993 (ksun)
*/
ll modinv(ll a, ll m) {
  assert(m > 0);
  if (m == 1) return 0;
  a %= m;
  if (a < 0) a += m;
  assert(a != 0);
  if (a == 1) return 1;
  return m - modinv(m, a) * m / a;
}

template <int MOD_> struct modnum {
private:
  int v;
public:
  static const int MODM = MOD_;
 
  modnum() : v(0) {}
  modnum(ll v_) : v(int32_t(v_ % MODM)) { if (v < 0) v += MODM; }
  explicit operator int () const { return v; }
  friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
  friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }
 
  modnum operator ~ () const {
    modnum res;
    res.v = modinv(v, MODM);
    return res;
  }
 
  modnum& operator += (const modnum& o) {
    v += o.v;
    if (v >= MODM) v -= MODM;
    return *this;
  }
  modnum& operator -= (const modnum& o) {
    v -= o.v;
    if (v < 0) v += MODM;
    return *this;
  }
  modnum& operator *= (const modnum& o) {
    v = int32_t(ll(v) * ll(o.v) % MODM);
    return *this;
  }
  modnum& operator /= (const modnum& o) {
    return *this *= (~o);
  }
 
  friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
  friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
  friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
  friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
 
};
using mint = modnum<MOD>;
mint powr(mint a, ll p) {
    mint ans = 1; assert(p >= 0);
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans;
  }
mint inv(const mint& a) { return powr(a,MOD-2); }
 
vector<mint> fact;
vector<mint> ifact;
 
void init(){
  int N = 1100000; // update acc
  fact = {1};
  for(int i = 1; i < N; i++) fact.push_back(i * fact[i-1]);
  ifact.resize(N);
  ifact.back() = 1 / fact.back();
  for(int i = N - 1; i > 0; i--) ifact[i-1] = i * ifact[i];
}
 
mint ncr(int n, int k){
  if(k < 0 || k > n) return 0;
  return fact[n] * ifact[k] * ifact[n-k];
}
