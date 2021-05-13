#define MAXN 100005
#define MAXLG 18
int tab[MAXLG][MAXN];
int lvl[MAXN];
vi adj[MAXN];
void dfs0(int n, int p) {
	lvl[n] = lvl[p] + 1;
	tab[0][n] = p;
	for (int i = 0; i < MAXLG - 1; i++)
		tab[i + 1][n] = tab[i][tab[i][n]];
	for (int v : adj[n]) if (v != p) {
		dfs0(v, n);
	}
}
 
int lca(int u, int v) {
	if (lvl[u] < lvl[v]) u^=v^=u^=v; 
	for (int i = MAXLG - 1; i >= 0; i--) {
		if (lvl[u] - (1<<i) >= lvl[v])
			u = tab[i][u];
	}
	for (int i = MAXLG - 1; i >= 0; i--) {
		if (tab[i][u] != tab[i][v])
			u = tab[i][u], v = tab[i][v];
	}
	return u == v ? u : tab[0][u];
}

int anc(int x, int k){ // k-th anc of x
	int dis = lvl[x] - k;
	for (int i = MAXLG; i >= 0; i--){
		if(dis >= (1<<i)){
			dis -= (1<<i);
			x = tab[x][i];
		}
	}
	return x;
}

int dist(int u, int v) {
	return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];
}
 
