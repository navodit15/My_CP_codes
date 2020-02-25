#include<bits/stdc++.h>
using namespace std;
const int N = 1e8;
bool comp[N];
vector<int>primes;
void oldsieve()
{
    memset(comp,0,sizeof comp);
    primes.clear();
    
    bool done = false;
    for(int i=2;i<N;i++)
        if(!comp[i])
        {
            primes.push_back(i);
            
            if (i * i > N) {
            	done = true;
            }
            
            if (!done) for(int j=i*i;j<N;j+=i)
                comp[j]=1;
        }
}
// linear seive ref : https://codeforces.com/blog/entry/54090
void newsieve()
{
    memset(comp,0,sizeof comp);
    primes.clear();
    for(int i=2;i<N;i++)
    {
        if(!comp[i])
            primes.push_back(i);
            for(int j=0,si=primes.size();j<si&&i*primes[j]<N;j++)
            {
                comp[primes[j]*i]=1;
                if(i%primes[j]==0)break;
            }
    }
}
void segmented_sieve() {
	int n = N;
    const int S = 10000;

	primes.clear();
    vector<int> Ps;
    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 1, true);
    for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            Ps.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }

    int result = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : Ps) {
            int start_idx = (start + p - 1) / p;
            int j = max(start_idx, p) * p - start;
            for (; j < S; j += p)
                block[j] = false;
        }
        if (k == 0)
            block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
            if (block[i])
                primes.push_back(start+i);
        }
    };
}

int main()
{
	auto t0 = clock();
    oldsieve();
    auto t1 = clock();
    auto primes_old = primes;
    primes.clear();
    cout << "old: " << (1.0 * (t1 - t0)) / CLOCKS_PER_SEC << endl;
    
    t0 = clock();
    newsieve();
    t1 = clock();
    auto primes_new = primes;
    primes.clear();
    cout << "new: " << (1.0 * (t1 - t0)) / CLOCKS_PER_SEC << endl;
    assert(primes_new == primes_old);
        
    t0 = clock();
    segmented_sieve();
    t1 = clock();
    auto primes_seg = primes;
    primes.clear();
    cout << "segmented_sieve: " << (1.0 * (t1 - t0)) / CLOCKS_PER_SEC << endl;
    assert(primes_seg == primes_old);
}
