//ref~ https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/DSU/DSU%20(7.6).h
struct DSU {
	vi e; void init(int n) { e = vi(n,-1); }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); } 
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	bool unite(int x, int y) { // union-by-rank
		x = find(x), y = find(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};
/**template<class T> T kruskal(int n, vector<pair<T,pii>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(n+1); // edges that unite are in MST
	trav(a,ed) if (D.unite(a.s.f,a.s.s)) ans += a.f; 
	return ans;
}*/
