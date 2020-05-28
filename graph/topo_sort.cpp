void dfs(int node){
	vis[node]=1;
	trav(v,g[node]){
		if(!vis[v]){
			dfs(v);
		}
		else if(vis[v]==1){ // cycle chk
			cout << -1 << endl;
			exit(0);
		}
	}
	vis[node] = 2 ;
}

vi ans ;

void topo_sort(int node ){
	vis[node] = 1 ;
	trav(v,g[node]){
		if(!vis[v]) topo_sort(v);
	}
	ans.pb(node);
}

main(){
  fr(i,0,n-1) if(!vis[i]) dfs(i);
	rep(i,0,n) vis[i] = 0 ;;
	fr(i,0,n-1) if(!vis[i]) topo_sort(i);
}
