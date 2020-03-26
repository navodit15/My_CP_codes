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

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp> 
//using namespace __gnu_pbds;
//using ordered_set = tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>;  
 
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


signed main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);


	
	
	
	

#ifdef np
    cerr <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif  
 return 0; 
 }
