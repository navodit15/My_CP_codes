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
typedef long long ll;typedef pair<int, int> pii;typedef vector<int> vi;
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
template<class T> ostream& operator<<(ostream &os, vector<T> V) {os << "[ "; for(auto v : V) os << v << " "; return os << "]";}
template<class T> ostream& operator<<(ostream &os, set<T> S){os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {os << "{ "; for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") "; return os<<"}";}
namespace fio{
	template <typename T> void read(T &x) { x = 0; int f = 1;char c = getchar_unlocked();
		for (; !isdigit(c); c = getchar_unlocked()) if (c == '-') f = -f;
		for (; isdigit(c); c = getchar_unlocked()) x = x * 10 + c - '0';
		x *= f;
	}
	template<class T> void read(vector<T>& a);
	template<class T> void read(vector<T>& a) { rep(i,0,sz(a)) read(a[i]); }
	template<class T, class... Ts> void read(T& t, Ts&... ts) { read(t); read(ts...);}
	template <typename T> void write(T x) { if (x < 0){ x = -x; putchar('-');}if (x > 9) {write(x / 10);}putchar(x % 10 + '0');}
	template <typename T> void writeln(T x) { write(x);puts("");}
	template<class T, class... Ts> void write(const T& t, const Ts&... ts) { write(t); write(ts...); }
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




int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);
	
	

#ifdef np
    cerr <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif  
 return 0; 
 }
