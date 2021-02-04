int arr[Nx+1];
#define lc id<<1
#define rc lc|1
#define mid ((l+r)>>1)


template<class node>
struct segtree {
	int n;
	vector<node> T;
	segtree(int n): n(n), T(4 * n + 10) {}
	inline void push(int id, int l, int r) {
		T[id].mi += T[id].lazy;
		//T[id].mx.F += T[id].lazy;
		if (l != r) {
			T[lc].lazy += T[id].lazy ;
			T[rc].lazy += T[id].lazy ;
		}
		T[id].lazy = 0;
	}
	void build(int id, int l, int r) {
		if (l == r) {
			T[id].mi = arr[l];
			return;
		}
		build(lc, l, mid), build(rc, mid + 1, r);
		T[id] = node::merge( T[lc],  T[rc]);
	}
	void update(int id, int l, int r, int pos, int val) {
		push(id, l, r);
		if (l == r) {
			//T[id].sum = val ;
			T[id].lazy = val; 
			return;
		}
		if (pos <= mid) update(lc, l, mid, pos, val);
		else update(rc, mid + 1, r, pos, val);

		T[id] = node :: merge( T[lc] , T[rc]);
	}

	node query(int id, int l, int r, int u, int v) {
		push(id, l, r);
	    if(l>v or r<u) return 1e18;
			if (l >= u and r <= v)return T[id];
			if (v <= mid) {return query(lc, l, mid, u, v);}
			else if (u >= mid + 1) {return query(rc, mid + 1, r, u, v);}
			return node::merge(query(lc, l, mid, u, v) , query(rc, mid + 1, r, u, v));
		}

	void updr(int id, int l, int r, int u, int v, int val) {
		push(id, l, r);
	  	if (l >= u and r <= v) {
			T[id].lazy = val ;
			push(id, l, r); 
			return;
		}
		if (r < u or l > v) return;
		updr(lc, l, mid, u, v, val), updr(rc, mid + 1, r, u, v, val);
		T[id] = node::merge(T[lc],T[rc]);
	}
};

struct node {
	ll mi = 1e18, lazy;
	node() :mi(), lazy(0) {}
	node(ll val) : mi(val), lazy(val) {}
	static node merge(const node&x, const node&y) {
		node ans;
		//ans.sum = x.sum + y.sum;
		ans.mi = min(x.mi, y.mi);
		return ans;
	}
};
 
