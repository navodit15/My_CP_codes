/* LCA
 * Description: Calculates least common ancestor in tree 
 	* with root $R$ using binary jumping. 
 * Time: O(N\log N) build, O(\log N) query
 * Source: USACO Camp
 * Verification: Debug the Bugs
 */

template<int SZ> struct LCA {
	static const int BITS = 32-__builtin_clz(SZ);
	int N, R = 1, par[BITS][SZ], depth[SZ]; vi adj[SZ]; 
	/// INITIALIZE
	void add_edge(int u, int v) { adj[u].pb(v), adj[v].pb(u); }
	void dfs(int u, int prv){
		depth[u] = depth[par[0][u] = prv]+1;
		trav(v,adj[u]) if (v != prv) dfs(v,u); }
	void init(int _N) {
		N = _N; dfs(R,0);
		rep(k,1,BITS) rep(i,1,N+1) 
			par[k][i] = par[k-1][par[k-1][i]];
	}
	/// QUERY
	int getPar(int a, int b) {
		for(int k = BITS-1 ; k>=0 ; --k)if (b&(1<<k)) a = par[k][a];
		return a; }
	int lca(int u, int v){
		if (depth[u] < depth[v]) swap(u,v);
		u = getPar(u,depth[u]-depth[v]);
		for(int k = BITS-1 ; k>=0 ; --k) if (par[k][u] != par[k][v]) 
			u = par[k][u], v = par[k][v];
		return u == v ? u : par[0][u];
	}
	int dist(int u, int v) { // # edges on path
		return depth[u]+depth[v]-2*depth[lca(u,v)]; }
};
