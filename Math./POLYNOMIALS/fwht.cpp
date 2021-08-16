/* AND & Fast Walsh-Hadamard Transform
 * ref:https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
 *    :https://codeforces.com/blog/entry/71899 
 *    :https://codeforces.com/contest/914/submission/34908922
 * */


int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

namespace ANDFFT{
vi andconv(vi p , bool iv = 0){
    for(int len = 1 ; len*2 <= sz(p) ; len<<=1){
        for(int i = 0; i<sz(p) ; i+=(2*len)){
            for(int j = 0 ; j < len ;j++){
                int u = p[i+j];
                int v = p[i+len+j];
                if(!iv) {
                    p[i+j] = v ;
                    p[i+len+j] = (v+u) % MOD;
                } 
                else{
                    p[i+j] = (-u+v+MOD)%MOD;
                    p[i+len+j] = u;
                }
            }
        }
    } 
    return p;
} 

vi convolute(vi a , vi b){
    int s = max(sz(a),sz(b));
    int l = get(s);// bits
    int n = 1<<l;
    if(s<=0) return {} ; 
    // compute dft's
    a.resize(n) ; 
    a=andconv(a);
    b.resize(n) ; 
    b=andconv(b);
    for(int i =0 ; i<n ; ++i) a[i] = a[i]*b[i]%MOD; 
    a=andconv(a,1);  // compute inverse 
    return a;
} 
};
using namespace ANDFFT;



namespace FWHT{
    ll modpow(ll b, ll p) { return !p?1:modpow(b*b%MOD,p/2)*(p&1?b:1)%MOD; }
    ll inv (ll b) { return modpow(b,MOD-2); }
    vi fwht(vi P) {
        for (int len = 1; 2 * len <= sz(P); len <<= 1) {
            for (int i = 0; i < sz(P); i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    ll u = P[i + j];
                    ll v = P[i + len + j];
                    P[i + j] = (u+v)%MOD;
                    P[i + len + j] = (u-v+MOD)%MOD;
                }
            }
        }
        return P;
    }

    vi fwht_rev(vi& a) {
        vi res = fwht(a);
        ll x = inv(sz(a));
        rep(i,0,sz(res)) res[i] = res[i]*x % MOD;
        return res;
    }
    
    vi conv(vi a, vi b) {
        int s = max(sz(a),sz(b)), L = get(s), n = 1<<L;
        if (s <= 0) return {};
        
        a.resize(n); a = fwht(a);
        b.resize(n); b = fwht(b);
        
        rep(i,0,n) a[i] = a[i]*b[i] % MOD;
        a = fwht_rev(a);
        return a;
    }
}; 
using namespace FWHT;

