
const int MAXN = 1e5+5;
vector<int> adj[MAXN];

int st[MAXN];
int cpar[MAXN];
bool vis[MAXN];

void dfs(int n, int p=-1) {
    st[n] = 1;
    for (int v : adj[n]) if (v != p && !vis[v]) {
        dfs(v, n);
        st[n] += st[v];
    }
}

int centroid(int n) {
    dfs(n);
    int num = st[n];
    int p = -1;
    do {
        int nxt = -1;
        for (int v : adj[n]) if (v != p && !vis[v]) {
            if (2 * st[v] > num)
                nxt = v;
        }
        p = n, n = nxt;
    } while (~n);
    return p;
}

void centroid_decomp(int n=0, int p=-1) {
    int c = centroid(n);
    vis[c] = true;
    cpar[c] = p;
    for (int v : adj[c]) if (!vis[v]) {
        centroid_decomp(v, c);
    }
}
