//https://acgan.sh/posts/2016-12-23-prime-counting.html

/*
  Meissel-Lehmer algorithm
*/

const int MX = 4e7; // MX is the maximum value of sqrt(N) + 2
bool isPrime[MX];
int primePi[MX];
vector<ll> P;

void init() {
  for (int i = 2; i < MX; i++)
    isPrime[i] = true;
  for (int i = 2; i < MX; i++) {
    if (isPrime[i]) {
      for (int j = i + i; j < MX; j += i) {
        isPrime[j] = false;
      }
    }
  }
  for (int i = 2; i < MX; i++) {
    primePi[i] = primePi[i - 1] + isPrime[i];
  }
  for (int i = 2; i < MX; i++) {
    if (isPrime[i]) {
      P.push_back(i);
    }
  }
}

/*
  number of integers in 2..N whose smallest prime factor is <= P[K]
*/
ll rec(ll N, int K) {
  if (N <= 1 || K < 0) return 0;
  if (N <= P[K]) return N - 1;
  if (N < MX && ll(P[K]) * P[K] > N) {
    return (N - 1) - (primePi[N] - primePi[P[K]]);
  }

  const int LIM = 250;
  static int memo[LIM * LIM][LIM];
  bool do_mem = N < LIM * LIM;
  if (do_mem && memo[N][K]) return memo[N][K];
  
  ll result = N / P[K] - rec(N / P[K], K - 1) + rec(N, K - 1);
  
  if (do_mem) memo[N][K] = result;
  return result;
}

ll count_primes(ll N) {
  if (N < MX)
    return primePi[N];
  static map<ll, ll> memo;
  if (memo.count(N)) return memo[N];
  int K = primePi[(int)sqrt(N) + 1];
  return memo[N] = (N - 1) - (rec(N, K) - primePi[P[K]]);
}
