
#define MAXLG 18
int tab[MAXLG][MAXN];
int lvl[MAXN];
 
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

int anc(int v ,int k){ // kth anc of v
    if(k>=lvl[v]) return 0 ; 
    int ret = v ;
    for(int i = MAXLG - 1 ; i>=0 ; i--){
        if((1ll<<i) <= k) {
            k-=(1ll<<i);
            ret = tab[ret][i];
        }
    } 
    return ret ;
}  

int dist(int u, int v) {
	return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];
}
 
