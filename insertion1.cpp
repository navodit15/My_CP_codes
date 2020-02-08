#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("unroll-loops")
 
const long long infl=0x3f3f3f3f3f3f3f3fLL;
const int infi=0x3f3f3f3f;
const int weirdmod=998244353; 
#define start() ios::sync_with_stdio(false); cin.tie(nullptr);
#define MOD 1000000007
#define sd(x) scanf("%d", &(x))
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define ones(x) __builtin_popcount(x)
#define sz(x) int (x.size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define REP(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define f1(i,a,b) for(int i=a; i<=b; i++)
#define rep(i,a,b) for(int i=a; i<b; i++)
#define NFOR(i,a,b) for(int i=(a);i>=(b);--i)
 
 
using ll = long long ;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;
 
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;  
typedef double ld;
typedef vector<ll> vll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the iterator to kth largest element.(0-based)
 
 
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
 
#ifdef np
#define trace(...) cout<<"Line:"<<__LINE__<<" "; __f(#__VA_ARGS__, __VA_ARGS__)
template<typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
	cout<<name<<" : "<<arg1<<endl;
}
template<typename Arg1, typename ... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
	const char *comma=strchr(names+1,',');
	cout.write(names,comma-names)<<" : "<<arg1<<" | ";
	__f(comma+1,args...);
}
#else
#define trace(...)
#define endl '\n'
#endif
 
auto clk=clock();
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) {
	uniform_int_distribution<int> uid(0,lim-1);
	return uid(rang);
}
ll cnt[50];
 
ll bit(ll x){
	return x&(-x);
}

void solve(){
	int n ;sd(n);
	vll v(n);
	f1(i,1,n){
		ll x; cin>>x;
		ll tmp = bit(x);
		cnt[tmp]++;			
	}
	ll ans  = (cnt[0]*(cnt[0]-1))/2 +cnt[0]+cnt[1];
	cout<<ans;
}
 
signed main(){
	//start()
	int T =1 ; 
	//cin>>T;
	while(T--){
		solve();
	}
 
#ifdef np
	cout<<endl<<endl<<endl<<endl<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
