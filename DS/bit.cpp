int BIT[N];
constexpr int MAXLG =32;
void update(int x ,int k){
    if(x<1) return ;
    while(x<N){
        BIT[x]+=k;
        x+=((x) & -(x));

    }
}
int query(int x){
    int sum = 0 ;
    while(x){
        sum+=BIT[x];
        x-=((x) & -(x));
    }
    return sum;
}
// Returns the sum of the range [a, b).
int query(int a, int b) {
        return query(b) - query(a);
}

// find_last_prefix(k) finds the k-th smallest element (0-indexed). O(log n )   
int bs(int sum){
    if (sum < 0)
        return -1;
    int prefix = 0;
    for (int k = MAXLG; k >= 0; k--){
        if (prefix + (1 << k) <= N && BIT[prefix + (1 << k)] <= sum) {
            prefix += 1 << k;
            sum -= BIT[prefix];
        }
    }
    return prefix;
}
