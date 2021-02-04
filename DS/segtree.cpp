// usage :: https://codeforces.com/contest/380/submission/106478351

int arr[Nx+1];
#define lc id<<1
#define rc lc|1
#define mid ((l+r)>>1)

template<class node>
struct segtree {
  int n;
  vector<node> T;
  segtree(int n): n(n), T(4 * n + 10) {}

  void build(int id, int l, int r) {
    if (l == r) {
      T[id] = arr[l];
       return;
     }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    T[id] = node::merge(T[lc],T[rc]);
  }
  void update(int id, int l, int r, int pos, int val) {
    if (l == r) {
      T[id] = node(val);
       return;
    }
    if (pos <= mid) update(lc, l, mid, pos, val);
    else update(rc, mid + 1, r, pos, val);

    T[id]=node::merge(T[lc],T[rc]);
  }

  node def;
  node query(int id, int l, int r, int u, int v) {
    if(r<u or l >v) return def;
    if (l >= u and r <= v)return T[id];
    if (v <= mid) return query(lc, l, mid, u, v);
    else if (u >= mid + 1) return query(rc, mid + 1, r, u, v);

    return  node::merge(query(lc, l, mid, u, v) , query(rc, mid + 1, r, u, v));
  }
};

struct node {
  int sum  = 0  ;
  node() {}
  node(int v){
    sum = v;
  }
  static node merge(const node&lhs , const node&rhs) {
    node ret ;
    ret.sum = lhs.sum + rhs.sum;
    return ret ;
  }
};

