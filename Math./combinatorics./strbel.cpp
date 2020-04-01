#include <bits/stdc++.h>
using namespace std;

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
	template<class T, class... Ts> void println(const T& t, const Ts&... ts) { println(t); println(ts...); }
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

#define MOD 1000000007
 
inline int add(int x, int y){ x += y; if(x >= MOD) x -= MOD; return x;}
inline int sub(int x, int y){ x -= y; if(x < 0) x += MOD; return x;}
inline int mul(int x, int y){ return (((ll) x) * y) % MOD;}
 
inline ll powr(ll a , ll b){
	ll t =1 ;
	while(b){
		if(b&1){
			t=mul(t,a);
		}	
		a=mul(a,a);
		b>>=1;
	}
	return t%MOD;
}
 
inline ll inv(ll a){ return powr(a,MOD-2); }
 
template<int SZ> struct Comb{
    ll fac[SZ+1], ifac[SZ+1];
    
    Comb() {
        fac[0] = ifac[0] = 1;
    	rep(i,1,SZ+1) {
    	    fac[i] = i*fac[i-1] % MOD;
    	    ifac[i] = inv(fac[i]);
    	}
    }
    inline ll powr(ll a , ll b){
		ll t =1 ;
		while(b){
			if(b&1){
				t=mul(t,a);
			}	
			a=mul(a,a);
			b>>=1;
		}
		return t%MOD;
	}
 
	inline ll inv(ll a){ return powr(a,MOD-2); }
    ll Choose(ll a, ll b) {
        if (a < b) return 0;
        ll tmp = fac[a]*ifac[b] % MOD;
        tmp = tmp*ifac[a-b] % MOD;
        return tmp;
    }
};
 
Comb<200005> f;
 
//partition n distict people in k non empty groups
 
int Stirling (int n , int k){
	int tot = 0; 
	int iv = f.ifac[k];
	for(int i = 0 ; i < k ; ++i){
		if(i%2==0) tot = add(tot,mul(powr(k-i,n),f.Choose(k,i)));
		else tot=sub(tot,mul(powr(k-i,n),f.Choose(k,i)));
	}
	return mul(iv,tot);
}

/*
 * Consider how placing n distinct primes into identical boxes gives us a way of writing N as
 *  the product of positive integers. First, find the prime factorization of each term of the product,
 *  and place the factors of each term into a box. 
 * Then, since N is the product of distinct prime factors, each prime factor appears in a unique box.
 * Since the product of all of these terms is N, each prime factor must be in a box.
 * Conversely, given any arrangement of these nn distinct primes into r identical boxes,
 *  multiply the primes in a box to create a term, and the product of these terms gives the value of N.
 *  This establishes the bijection. Thus, the number of ways is Bell(n)
 */
 
 
int Bell(int n){
	ll sum = 0;
	for(int k = 1 ; k<n+1 ; ++k){
		sum = add(sum,Stirling(n,k));
	}
	return sum%MOD;
} 

// precompute distinct divisors of N till 2e5; with cnt[i];
const int MAZ = 2e5+6;
ll cnt[MAZ+1]; 
bool mark[MAZ+1];
void pre() { 
    for (int i = 0; i < MAZ; i++) { 
        cnt[i] = 0; 
        mark[i] = true;  
    } 
    for (int i = 2; i <= MAZ; i++) { 
        if (mark[i]) {  
			cnt[i] = 1;   
            for (int j = i * 2; j <= MAZ; j += i) {  
                cnt[j]++;  
                mark[j] = false;  
            } 
        } 
    }     
} 
// take care of ll vs int 
// omega(n)∼lnln(n) bound for cnt[i]  
// works for sqf numbers only proof OEIS

int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);
	
	pre();
	int tt ; for(cin >> tt ; tt-- ;){
		int N ; scan(N);
		int calc = cnt[N];
		trace(calc);
		print(Bell(calc));
	}
#ifdef np
    cerr <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif  
 return 0; 
 }
