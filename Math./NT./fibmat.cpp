#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
using ordered_set = tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>;
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
typedef long long ll;typedef pair<int, int> pii;typedef vector<int> vi;typedef long double ld;

#ifdef np

#include "C:\Users\navodit\Desktop\mycodes\pr.h"
#else
#define trace(...)
#endif
/* too weak too slow */
#define mod 1000000007  

void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }


const int NN = 101;
class matrix{
public:
    ll mat[NN][NN];
    int r, c;
    matrix(){
        fr(i, 0, NN - 1)
            fr(j, 0, NN - 1)
                mat[i][j] = 0;
    }
    void setsize(int _r, int _c){ r = _r, c = _c; }
    inline matrix operator * (const matrix &a){
        assert(c == a.r);
        matrix temp;
        temp.setsize(r, a.c);
        fr(i, 0, r - 1)
            fr(j, 0, a.c - 1){
                fr(k, 0, a.r - 1){
                temp.mat[i][j] += (mat[i][k] * a.mat[k][j]) % mod;
                if(temp.mat[i][j] >= mod)
                    temp.mat[i][j] -= mod;
                }
            }
        return temp;
    }
    inline matrix operator + (const matrix &a){
        assert(r == a.r && c == a.c);
        matrix temp;
        temp.setsize(r, c);
        fr(i, 0, r - 1)
            fr(j, 0, c - 1){
                temp.mat[i][j] = mat[i][j] + a.mat[i][j] ;
                if(temp.mat[i][j] >= mod)
                    temp.mat[i][j] -= mod;
            }
        return temp;
    }
    inline matrix operator - (const matrix &a){
        assert(r == a.r && c == a.c);
        matrix temp;
        temp.setsize(r, c);
        fr(i, 0, r - 1)
            fr(j, 0, c - 1){
                temp.mat[i][j] = mat[i][j] - a.mat[i][j];
                if(temp.mat[i][j] < 0)
                    temp.mat[i][j] += mod;
            }
        return temp;
    }
    inline void operator = (const matrix &a){
        fr(i, 0, r - 1)
            fr(j, 0, c - 1)
                mat[i][j] = a.mat[i][j];
        r = a.r, c = a.c;
    }
    inline void print(){
        fr(i, 0, r - 1){
            fr(j, 0, c - 1)
                cout << mat[i][j] << " ";
            cout << endl;
        }
    }
};
matrix powr(matrix a,ll k){
    assert(a.r == a.c);
    matrix ans;
    fr(i, 0, a.r - 1)
        ans.mat[i][i] = 1;
    ans.r = a.r;
    ans.c = a.r;
    while(k){
        if(k & 1)
            ans = (ans * a);
        a = (a * a);
        k >>= 1;
    }
    return ans;
}

void solve(){
	int n ;
	cin >> n ;
	matrix f;
	f.setsize(2,2);
	f.mat[0][0] = 1;
	f.mat[0][1] = 1;
	f.mat[1][0] = 1;	
	f.mat[1][1] = 0;
	matrix fib = powr(f,n);
	cout << fib.mat[0][1];
	
}

signed main() {
	unsyncIO();
	int tt =1 ;
	// cin >> tt;
	rep(i,0,tt) solve();




#ifdef np
	cout <<endl<<endl<< "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}
