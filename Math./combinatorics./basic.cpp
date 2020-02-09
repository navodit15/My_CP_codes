#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;typedef pair<int, int> pii;typedef vector<int> vi;
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
template<class T> ostream& operator<<(ostream &os, vector<T> V) {os << "[ "; for(auto v : V) os << v << " "; return os << "]";}
template<class T> ostream& operator<<(ostream &os, set<T> S){os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {os << "{ "; for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") "; return os<<"}";}

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


int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);

	ll t = f.Choose(5,2);
    cout << t << endl;
    

#ifdef np
    cerr <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif  
 return 0; 
 }
