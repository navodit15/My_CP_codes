#include <bits/stdc++.h>
using namespace std;

#define fr(i,a,b) for(int i = a ; i <= b ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define fst first
#define snd second
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
typedef long long ll;typedef pair<int, int> pii;typedef vector<int> vi;typedef long double ld;
template<class T> ostream& operator<<(ostream &os, vector<T> V) {os << "[ "; for(auto v : V) os << v << " "; return os << "]";}
template<class T> ostream& operator<<(ostream &os, set<T> S){os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {os << "{ "; for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") "; return os<<"}";}
namespace fio{
	template <typename T> void scan(T &x) { cin >> x ;}
	template<class T> void scan(vector<T>& a);
	template<class T> void scan(vector<T>& a) { rep(i,0,sz(a)) scan(a[i]); }
	template<class T, class... Ts> void scan(T& t, Ts&... ts) { scan(t); scan(ts...);}
	template <typename T> void print(T x) { cout << x << endl;}
	template<class T, class... Ts> void print(const T& t, const Ts&... ts) { print(t); print(ts...); }
} 
using namespace fio; 
   
#ifdef np
#define trace(...) cout<<"Line:"<<__LINE__<<" "; __f(#__VA_ARGS__, __VA_ARGS__)
template<typename Arg1>void __f(const char *name, Arg1 &&arg1) { cout<<name<<" : "<<arg1<<endl;}
template<typename Arg1, typename ... Args>void __f(const char *names, Arg1 &&arg1, Args &&... args) {
    const char *comma=strchr(names+1,','); cout.write(names,comma-names)<<" : "<<arg1<<" | ";
    __f(comma+1,args...);
}
#else
#define trace(...)
#define endl '\n'
#endif

//const int N = 1e8;
//bool comp[N];
//vector<int>primes;

//void segmented_sieve() {
	//int n = N;
    //const int S = 10000;
	//primes.clear();
    //vector<int> Ps;
    //int nsqrt = sqrt(n);
    //vector<char> is_prime(nsqrt + 1, true);
    //for (int i = 2; i <= nsqrt; i++) {
        //if (is_prime[i]) {
            //Ps.push_back(i);
            //for (int j = i * i; j <= nsqrt; j += i)
                //is_prime[j] = false;
        //}
    //}
    //vector<char> block(S);
    //for (int k = 0; k * S <= n; k++) {
        //fill(block.begin(), block.end(), true);
        //int start = k * S;
        //for (int p : Ps) {
            //int start_idx = (start + p - 1) / p;
            //int j = max(start_idx, p) * p - start;
            //for (; j < S; j += p)
                //block[j] = false;
        //}
        //if (k == 0)
            //block[0] = block[1] = false;
        //for (int i = 0; i < S && start + i <= n; i++) {
            //if (block[i])
                //primes.push_back(start+i);
        //}
    //};
//}
const int maxn = 1e7+1;
int factor[maxn],mu[maxn],phi[maxn];
vi divs[maxn];
void Mu(){
	memset(factor,0,sizeof factor);
	for(int i = 2;i*i<maxn;i++)
		if(!factor[i])
			for(int j = i*i;j<maxn;j+=i)
				factor[j] = i;
	mu[1] = 1;
	for(int i = 2;i<maxn;i++)
	{
		int p;
		if(!factor[i])
			p = i;
		else
			p = factor[i];
		int j = i/p;
		if(j%p == 0)
			mu[i] = 0;
		else
			mu[i] = mu[j]*(-1);
	}		
	for(int i = 2;i<maxn;i++)
		if(mu[i]!=0)
			for(int j = i;j<maxn;j+=i)
				divs[j].pb(i);
}
void ETF(){ // 0.4s for nax = 1e7+5
	for(int i = 0; i < maxn; ++i) phi[i] = i;
	for(int i = 2; i < maxn; ++i) if(phi[i] == i)
	for(int j = i; j < maxn; j += i)
		phi[j] = phi[j] / i * (i - 1);
}

#define mp make_pair
// NUMBER THEORY SUIT ref~https://codeforces.com/contest/687/submission/18786970

typedef pair<ll,ll> PLL;
namespace Factor {
	const int N=1010000;
	ll C,fac[10010],n,mut,a[1001000];
	int T,cnt,i,l,prime[N],p[N],psize,_cnt;
	ll _e[100],_pr[100];
	vector<ll> d;
	inline ll mul(ll a,ll b,ll p) {
		if (p<=1000000000) return a*b%p;
		else if (p<=1000000000000ll) return (((a*(b>>20)%p)<<20)+(a*(b&((1<<20)-1))))%p;
		else {
			ll d=(ll)floor(a*(long double)b/p+0.5);
			ll ret=(a*b-d*p)%p;
			if (ret<0) ret+=p;
			return ret;
		}
	}
	void prime_table(){
		int i,j,tot,t1;
		for (i=1;i<=psize;i++) p[i]=i;
		for (i=2,tot=0;i<=psize;i++){
			if (p[i]==i) prime[++tot]=i;
			for (j=1;j<=tot && (t1=prime[j]*i)<=psize;j++){
				p[t1]=prime[j];
				if (i%prime[j]==0) break;
			}
		}
	}
	void init(int ps) {
		psize=ps;
		prime_table();
	}
	ll powl(ll a,ll n,ll p) {
		ll ans=1;
		for (;n;n>>=1) {
			if (n&1) ans=mul(ans,a,p);
			a=mul(a,a,p);
		}
		return ans;
	}
	bool witness(ll a,ll n) {
		int t=0;
		ll u=n-1;
		for (;~u&1;u>>=1) t++;
		ll x=powl(a,u,n),_x=0;
		for (;t;t--) {
			_x=mul(x,x,n);
			if (_x==1 && x!=1 && x!=n-1) return 1;
			x=_x;
		}
		return _x!=1;
	}
	bool miller(ll n) {
		if (n<2) return 0;
		if (n<=psize) return p[n]==n;
		if (~n&1) return 0;
		for (int j=0;j<=7;j++) if (witness(rand()%(n-1)+1,n)) return 0;
		return 1;
	}
	ll gcd(ll a,ll b) {
		ll ret=1;
		while (a!=0) {
			if ((~a&1) && (~b&1)) ret<<=1,a>>=1,b>>=1;
			else if (~a&1) a>>=1; else if (~b&1) b>>=1;
			else {
				if (a<b) swap(a,b);
				a-=b;
			}
		}
		return ret*b;
	}
	ll rho(ll n) {
		for (;;) {
			ll X=rand()%n,Y,Z,T=1,*lY=a,*lX=lY;
			int tmp=20;
			C=rand()%10+3;
			X=mul(X,X,n)+C;*(lY++)=X;lX++;
			Y=mul(X,X,n)+C;*(lY++)=Y;
			for(;X!=Y;) {
				ll t=X-Y+n;
				Z=mul(T,t,n);
				if(Z==0) return gcd(T,n);
				tmp--;
				if (tmp==0) {
					tmp=20;
					Z=gcd(Z,n);
					if (Z!=1 && Z!=n) return Z;
				}
				T=Z;
				Y=*(lY++)=mul(Y,Y,n)+C;
				Y=*(lY++)=mul(Y,Y,n)+C;
				X=*(lX++);
			}
		}
	}
	void _factor(ll n) {
		for (int i=0;i<cnt;i++) {
			if (n%fac[i]==0) n/=fac[i],fac[cnt++]=fac[i];}
		if (n<=psize) {
			for (;n!=1;n/=p[n]) fac[cnt++]=p[n];
			return;
		}
		if (miller(n)) fac[cnt++]=n;
		else {
			ll x=rho(n);
			_factor(x);_factor(n/x);
		}
	}
	void dfs(ll x,int dep) {
		if (dep==_cnt) d.pb(x);
		else {
			dfs(x,dep+1);
			for (int i=1;i<=_e[dep];i++) dfs(x*=_pr[dep],dep+1);
		}
	}
	void norm() {
		sort(fac,fac+cnt);
		_cnt=0;
		rep(i,0,cnt) if (i==0||fac[i]!=fac[i-1]) _pr[_cnt]=fac[i],_e[_cnt++]=1;
			else _e[_cnt-1]++;
	}
	vector<ll> getd() {
		d.clear();
		dfs(1,0);
		return d;
	}
	vector<ll> factor(ll n) {
		cnt=0;
		_factor(n);
		norm();
		return getd();
	}
	vector<PLL> factorG(ll n) {
		cnt=0;
		_factor(n);
		norm();
		vector<PLL> d;
		rep(i,0,_cnt) d.pb(mp(_pr[i],_e[i]));
		return d;
	}
	bool is_primitive(ll a,ll p) {
		assert(miller(p));
		vector<PLL> D=factorG(p-1);
		rep(i,0,sz(D)) if (powl(a,(p-1)/D[i].fst,p)==1) return 0;
		return 1;
	}
}

using namespace Factor;

namespace pi{
	// count number of primes upto N in O(N^2/3)
	vector <ll> w, dp;
	int gdz(ll v){
		if (v<=w.back()/v)
			return v-1;
		return w.size()-w.back()/v;
	}
	ll pi(ll n){
		for (ll i=1; i*i<=n; i++)
		{
			w.push_back(i);
			if ((n/i)!=i)
				w.push_back(n/i);
		}
		sort(w.begin(), w.end());
		for (ll i : w)
			dp.push_back(i-1);
		for (ll i=1; (i+1)*(i+1)<=n; i++){
			if (dp[i]==dp[i-1])
				continue;
			for (int j=(int)w.size()-1; w[j]>=(i+1)*(i+1); j--)
				dp[j]-=dp[gdz(w[j]/(i+1))]-dp[i-1];
		}
		return dp.back();
	}
}
long long totient(long long n) {
    long long result = n;
 
    for (long long p = 2; p * p <= n; p++)
        if (n % p == 0) {
            result = result / p * (p - 1);
 
            do {
                n /= p;
            } while (n % p == 0);
        }
 
    if (n > 1)
        result = result / n * (n - 1);
 
    return result;
}


ll modmult(ll x, ll y, ll MOD) {
	ll a = x, r = 0;
	while(y) {
		if(y & 1)
			if((r += a) >= MOD) r -= MOD;
		if((a += a) >= MOD) a -= MOD;
		y >>= 1;
	}
	return r;
}
ll powmodll(ll a, unsigned long long k, const ll MOD) {
	a %= MOD;
	ll r = MOD == 1 ? 0 : 1;
	while(k) {
		if(k & 1)
			r = modmult(r, a, MOD);
		a = modmult(a, a, MOD);
		k >>= 1;
	}
	return (unsigned)r;
}

bool suspect(ll a, int s, ll d, ll n) {
	ll x = powmodll(a, d, n);
	if(x == 1) return true;
	for(int r = 0; r < s; ++r) {
		if(x == n - 1) return true;
		x = modmult(x, x, n);
	}
	return false;
}
// {2,7,61,-1}                 is for n < 4759123141 (= 2^32)
// {2,3,5,7,11,13,17,19,23,-1} is for n < 10^16 (at least)
bool isPrime(ll n) {
	if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
	int test[] = {2,3,5,7,11,13,17,19,23,-1};
	ll d = n - 1; int s = 0;
	while (d % 2 == 0) ++ s, d /= 2;
	for(int i = 0; test[i] < n && test[i] != -1; ++i)
		if(!suspect(test[i], s, d, n)) return false;
	return true;
}
int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);
	

	




#ifdef np
    cerr <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif  
 return 0; 
 }
