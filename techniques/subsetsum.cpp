vector<int> subset_sums;
 
void compute_subset_sums(const vector<int> &numbers) {
    int n = int(numbers.size());
    subset_sums.resize(1 << n);
    vector<int> change(n + 1, 0);
    int sum = 0;
 
    for (int i = 0; i < n; i++) {
        change[i] = numbers[i] - sum;
        sum += numbers[i];
    }
 
    change[n] = -sum;
    sum = 0;
 
    for (int mask = 0; mask < 1 << n; mask++) {
        subset_sums[mask] = sum;
        sum += change[__builtin_ctz(mask + 1)];
    }
 
    assert(sum == 0);
}
 
void solve(){
	vi v = {1,2,3,4,5};
	compute_subset_sums(v);
	trace(subset_sums);
	
}
