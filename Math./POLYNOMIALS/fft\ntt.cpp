// polymul mod
//http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
//fft template : https://codeforces.com/contest/993/submission/39317957
struct base{
    ld x,y;
    base(){x=y=0;}
    base(ld _x, ld _y){x = _x,y = _y;}
    base(ld _x){x = _x, y = 0;}
    void operator = (ld _x){x = _x,y = 0;}
    ld real(){return x;}
    ld imag(){return y;}
    base operator + (const base& b){return base(x+b.x,y+b.y);}
    void operator += (const base& b){x+=b.x,y+=b.y;}
    base operator * (const base& b){return base(x*b.x - y*b.y,x*b.y+y*b.x);}
    void operator *= (const base& b){ld p = x*b.x - y*b.y, q = x*b.y+y*b.x; x = p, y = q;}
    void operator /= (ld k){x/=k,y/=k;}
    base operator - (const base& b){return base(x - b.x,y - b.y);}
    void operator -= (const base& b){x -= b.x, y -= b.y;}
    base conj(){ return base(x, -y);}
    base operator / (ld k) { return base(x / k, y / k);}
    void Print(){ cerr << x <<  " + " << y << "i\n";}
};
double PI = 2.0*acos(0.0);
const int MAXN = 19;
const int maxn = (1<<MAXN);
base W[maxn],invW[maxn], P1[maxn], Q1[maxn];
void precompute_powers(){
    for(int i = 0;i<maxn/2;i++){
        double ang = (2*PI*i)/maxn; 
        ld _cos = cos(ang), _sin = sin(ang);
        W[i] = base(_cos,_sin);
        invW[i] = base(_cos,-_sin);
    }
}
void fft (vector<base> & a, bool invert) {
    int n = (int) a.size();
 
    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }
    for (int len=2; len<=n; len<<=1) {
        for (int i=0; i<n; i+=len) {
            int ind = 0,add = maxn/len;
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j],  v = (a[i+j+len/2] * (invert?invW[ind]:W[ind]));
                a[i+j] = (u + v);
                a[i+j+len/2] = (u - v);
                ind += add;
            }
        }
    }
    if (invert) for (int i=0; i<n; ++i) a[i] /= n;
}

// 4 FFTs in total for a precise convolution
void mul_big_mod(vll &a, vll & b, ll mod){
    int n1 = a.size(),n2 = b.size();
    int final_size = a.size() + b.size() - 1;
    int n = 1;
    while(n < final_size) n <<= 1;
    vector<base> P(n), Q(n);
    int SQRTMOD = (int)sqrt(mod) + 10;
    for(int i = 0;i < n1;i++) P[i] = base(a[i] % SQRTMOD, a[i] / SQRTMOD);
    for(int i = 0;i < n2;i++) Q[i] = base(b[i] % SQRTMOD, b[i] / SQRTMOD);
    fft(P, 0);
    fft(Q, 0);
    base A1, A2, B1, B2, X, Y;
    for(int i = 0; i < n; i++){
        X = P[i];
        Y = P[(n - i) % n].conj();
        A1 = (X + Y) * base(0.5, 0);
        A2 = (X - Y) * base(0, -0.5);
        X = Q[i];
        Y = Q[(n - i) % n].conj();
        B1 = (X + Y) * base(0.5, 0);
        B2 = (X - Y) * base(0, -0.5);
        P1[i] = A1 * B1 + A2 * B2 * base(0, 1);
        Q1[i] = A1 * B2 + A2 * B1;
    }
    for(int i = 0; i < n; i++) P[i] = P1[i], Q[i] = Q1[i];
    fft(P, 1);
    fft(Q, 1);
    a.resize(final_size);
    for(int i = 0; i < final_size; i++){
        ll x = (ll)(P[i].real() + 0.5);
        ll y = (ll)(P[i].imag() + 0.5) % mod;
        ll z = (ll)(Q[i].real() + 0.5);
        a[i] = (x + ((y * SQRTMOD + z) % mod) * SQRTMOD) % mod;
    }
}

void mul(vll a, vll b, int mod) {
    mul_big_mod(a, b, mod);
    return a;
}
// WITHOUT MOD
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef long double Num;
typedef complex<Num> Complex;
void fft(Complex P[], int n, int oper) {
  for (int i = 1, j = 0; i < n - 1; i++) {
    for (int s = n; j ^= s >>= 1, ~j & s;);
    if (i < j) swap(P[i], P[j]);
  }
  for (int d = 0; (1 << d) < n; d++) {
    int m = 1 << d, m2 = m * 2;
    Complex unit_p0(cos(-2*M_PI/m2*oper), sin(-2*M_PI/m2*oper));
    for (int i = 0; i < n; i += m2) {
      Complex unit(1);
      for (int j = 0; j < m; j++) {
        Complex &P1 = P[i + j + m], &P2 = P[i + j];
        Complex t = unit * P1;
        P1 = P2 - t; P2 = P2 + t;
        unit = unit * unit_p0;
      }
    }
  }
}
vector<int> mul(const vector<int> &a, const vector<int> &b) {
  vector<int> ret(max(0, (int) a.size() + (int) b.size() - 1), 0);
  int len = 1; while (len < (int)ret.size()) len <<= 1;
  static Complex A[1000000], B[1000000], C[1000000]; // adjust accordingly
  for (int i = 0; i < len; i++) A[i] = i < (int)a.size() ? a[i] : 0;
  for (int i = 0; i < len; i++) B[i] = i < (int)b.size() ? b[i] : 0;
  fft(A, len, 1); fft(B, len, 1);
  for (int i = 0; i < len; i++) C[i] = A[i] * B[i];
  fft(C, len, -1); for (int i = 0; i < (int)ret.size(); i++) ret[i] = (long long)((C[i]/Complex(len,0)).real() + 0.5);
  return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// NTT

namespace FFT {
	//  `替代方案: $23068673( = 11 * 2 ^ {21} + 1)$, 原根为 $3$`
	const int MOD = 998244353;
	const int PRIMITIVE_ROOT = 3; // `$3 * 2 ^ {18} + 1$`
	const int MAXB = 1 << 20;
	// int getMod(int downLimit) { // `或者现场自己找一个MOD`
	//   for (int c = 3; ; ++c) { int t = (c << 21) | 1;
	//     if (t >= downLimit && isPrime(t)) return t;
	// }}
	inline ll powr(ll a , ll b){
		ll t =1 ;
		while(b){
			if(b&1) t=mul(t,a);	
			a=mul(a,a);
			b>>=1;
		}
		return t%MOD;
	}
	inline ll inv(ll a){ return powr(a,MOD-2); }

	void NTT(int P[], int n, int oper) {
	  for (int i = 1, j = 0; i < n - 1; i++) {
		for (int s = n; j ^= s >>= 1, ~j & s;);
		if (i < j) swap(P[i], P[j]);
	  }
	  for (int d = 0; (1 << d) < n; d++) {
		int m = 1 << d, m2 = m * 2;
		long long unit_p0 = powr(PRIMITIVE_ROOT, (MOD - 1) / m2);
		if (oper < 0) unit_p0 = inv(unit_p0);
		for (int i = 0; i < n; i += m2) {
		  long long unit = 1;
		  for (int j = 0; j < m; j++) {
			int &P1 = P[i + j + m], &P2 = P[i + j];
			int t = unit * P1 % MOD;
			P1 = (P2 - t + MOD) % MOD; P2 = (P2 + t) % MOD;
			unit = unit * unit_p0 % MOD;
		  }
		}
	  }
	}
	vector<ll> mul(const vector<ll> &a, const vector<ll> &b) {
	  vector<ll> ret(max(0, (int) a.size() + (int) b.size() - 1), 0);
	  static int A[MAXB], B[MAXB], C[MAXB];
	  int len = 1; while (len < (int)ret.size()) len <<= 1;
	  for (int i = 0; i < len; i++) A[i] = i < (int)a.size() ? a[i] : 0;
	  for (int i = 0; i < len; i++) B[i] = i < (int)b.size() ? b[i] : 0;
	  NTT(A, len, 1); NTT(B, len, 1);
	  for (int i = 0; i < len; i++) C[i] = (long long) A[i] * B[i] % MOD;
	  NTT(C, len, -1); for (int i = 0, invv = inv(len); i < (int)ret.size(); i++) ret[i] = (long long) C[i] * invv % MOD;
	  return ret;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
