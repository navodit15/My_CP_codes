#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("unroll-loops") 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#define int long long
#define fr(i,a,b) for(int i = a ; i <= b ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define pb push_back
#define fst first
#define snd second
using namespace __gnu_pbds;
using ordered_set =
 tree<int, null_type,less<int>,
 rb_tree_tag,tree_order_statistics_node_update>;
//find_by_order(k):returns iterator to kth element starting from 0
//order_of_key(k):returns count of elements strictly smaller than k

typedef long long ll;typedef pair<int, int> pii;
typedef vector<int> vi;typedef long double ld;
typedef vector<pii> vpii;
template<class T>
using min_heap = priority_queue<T,vector<T>,greater<T>>; 
template<class T> void re(T& x) { cin >> x; }
template<class T> inline bool chmax(T& a,T b){if(a<b){a=b;return 1;}return 0;}
template<class T> inline bool chmin(T& a,T b){if(a>b){a=b;return 1;}return 0;}
#define lb(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define ub(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define reint(...) int __VA_ARGS__; re(__VA_ARGS__)
#define restr(...) string __VA_ARGS__ ; re(__VA_ARGS__)
template<typename T> 
void remdup(vector<T>& v) {												
	sort(all(v)); v.erase(unique(all(v)), v.end());
}
template<typename T> void re(vector<T> &v) {trav(i,v) cin >> i;}
template<class H, class... T> void re(H& h, T&... t) { re(h); re(t...); }
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }

#ifdef np
#include "/home/wjex/pr.h"
#else
#define trace(...)
#endif




constexpr int MOD = 1000000007;
constexpr int Nx = 2e5+5; // check 

int powr(int a , int b){
  int ret =1 ; 
  while(b){
    if(b&1)ret*=a ;
    a*=a;
    b>>=1;
  } 
  return ret ;
}


void solve()
{

}


signed main() {
	unsyncIO();
	cout << fixed << setprecision(18) ;
	int tt =1 ;
  //	cin >> tt;
	rep(i,0,tt) solve();



#ifdef np
	cout <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}

 

